/*
* Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
* Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License").
* You may not use this file except in compliance with the License.
* A copy of the License is located at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
* or in the "license" file accompanying this file. This file is distributed
* on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied. See the License for the specific language governing
* permissions and limitations under the License.
*/

#include "../Public/Core/Domain/Transaction/AutoTransactionAccessTokenDomain.h"

#include "Core/Domain/Gs2.h"
#include "Distributor/Domain/Gs2Distributor.h"
#include "Distributor/Model/Cache/TransactionResult.h"
#include "Misc/ScopeLock.h"

namespace Gs2::Core::Domain
{
	namespace
	{
		Gs2::Core::Model::FGs2ErrorPtr ValidateAccessTokenStatus(
			const TOptional<int32>& StatusCode,
			const TOptional<FString>& Body
		)
		{
			if (!StatusCode.IsSet() || *StatusCode < 200 || *StatusCode >= 300)
			{
				return Gs2::Core::Model::FGs2Error::FromResponse(
					StatusCode.IsSet() ? *StatusCode : 999,
					Body.IsSet() ? *Body : FString()
				);
			}
			return nullptr;
		}

		Gs2::Core::Model::FGs2ErrorPtr MissingAccessTokenResult()
		{
			return ValidateAccessTokenStatus(TOptional<int32>(), TOptional<FString>());
		}

		Gs2::Core::Model::FGs2ErrorPtr ValidateAccessTokenStampEntries(
			const int32 RequestCount,
			const int32 BodyCount,
			const TSharedPtr<TArray<int32>>& Codes,
			const TSharedPtr<TArray<FString>>& Bodies
		)
		{
			const int32 CodeCount = Codes.IsValid() ? Codes->Num() : 0;
			const int32 Count = FMath::Min(RequestCount, BodyCount);
			for (int32 Index = 0; Index < Count; ++Index)
			{
				const TOptional<int32> Status = Codes.IsValid() && Index < CodeCount
					? TOptional<int32>((*Codes)[Index])
					: TOptional<int32>();
				const auto Error = ValidateAccessTokenStatus(Status, TOptional<FString>((*Bodies)[Index]));
				if (Error.IsValid())
				{
					return Error;
				}
			}
			return nullptr;
		}

		Gs2::Core::Model::FGs2ErrorPtr AccessTokenTransactionFailed()
		{
			auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
			Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(
				TEXT("unknown"), TEXT("Ran transaction failed."), TEXT("")));
			return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
		}

		Gs2::Core::Model::FGs2ErrorPtr ValidateAccessTokenNestedTransactionResult(
			const Gs2::Distributor::Model::FTransactionResultPtr& Result
		)
		{
			if (!Result.IsValid()) return nullptr;
			const auto VerifyResults = Result->GetVerifyResults();
			if (VerifyResults.IsValid())
			{
				for (const auto& Item : *VerifyResults)
				{
					if (!Item.IsValid()) return MissingAccessTokenResult();
					const auto Error = ValidateAccessTokenStatus(Item->GetStatusCode(), Item->GetVerifyResult());
					if (Error.IsValid()) return Error;
				}
			}
			const auto ConsumeResults = Result->GetConsumeResults();
			if (ConsumeResults.IsValid())
			{
				for (const auto& Item : *ConsumeResults)
				{
					if (!Item.IsValid()) return MissingAccessTokenResult();
					const auto Error = ValidateAccessTokenStatus(Item->GetStatusCode(), Item->GetConsumeResult());
					if (Error.IsValid()) return Error;
				}
			}
			const auto AcquireResults = Result->GetAcquireResults();
			if (AcquireResults.IsValid())
			{
				for (const auto& Item : *AcquireResults)
				{
					if (!Item.IsValid()) return MissingAccessTokenResult();
					const auto Error = ValidateAccessTokenStatus(Item->GetStatusCode(), Item->GetAcquireResult());
					if (Error.IsValid()) return Error;
				}
			}

			const auto HasError = Result->GetHasError();
			if (!HasError.IsSet() || !HasError.GetValue()) return nullptr;
			if (AcquireResults.IsValid())
			{
				for (const auto& Item : *AcquireResults)
				{
					if (!Item.IsValid() || !Item->GetAcquireResult().IsSet() || Item->GetAcquireResult()->IsEmpty()) continue;
					TSharedPtr<FJsonObject> Json;
					if (const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(*Item->GetAcquireResult());
						FJsonSerializer::Deserialize(Reader, Json))
					{
						const TSharedPtr<FJsonObject>* NestedObject = nullptr;
						const auto NestedValue = Json->TryGetField(TEXT("transactionResult"));
						if (NestedValue.IsValid() && !NestedValue->IsNull() &&
							NestedValue->TryGetObject(NestedObject) && NestedObject != nullptr && NestedObject->IsValid())
						{
							const auto NestedResult = Gs2::Distributor::Model::FTransactionResult::FromJson(*NestedObject);
							const auto Error = ValidateAccessTokenNestedTransactionResult(NestedResult);
							if (Error.IsValid()) return Error;
						}
					}
				}
			}
			return AccessTokenTransactionFailed();
		}
	}

	TMap<FString, FDateTime> FAutoTransactionAccessTokenDomain::Handled;
	FCriticalSection FAutoTransactionAccessTokenDomain::HandledMutex;

	bool FAutoTransactionAccessTokenDomain::MarkHandled()
	{
		FScopeLock Lock(&HandledMutex);
		const auto Now = FDateTime::Now();
		for (auto It = Handled.CreateIterator(); It; ++It)
		{
			if (It.Value() <= Now)
			{
				It.RemoveCurrent();
			}
		}
		if (const auto Existing = Handled.Find(TransactionId))
		{
			return *Existing > Now;
		}
		Handled.Add(TransactionId, Now + FTimespan::FromMinutes(3));
		return false;
	}

	bool FAutoTransactionAccessTokenDomain::MarkTransactionResultHandled()
	{
		FScopeLock Lock(&TransactionResultMutex);
		if (bTransactionResultHandled)
		{
			return true;
		}
		bTransactionResultHandled = true;
		return false;
	}
	
	FTransactionAccessTokenDomainPtr FAutoTransactionAccessTokenDomain::HandleResult(
		Gs2::Distributor::Model::FStampSheetResultPtr Result,
		Gs2::Core::Model::FGs2ErrorPtr& Error
	)
	{
		if (!Result.IsValid())
		{
			return nullptr;
		}

		const auto VerifyCodes = Result->GetVerifyTaskResultCodes();
		const auto VerifyBodies = Result->GetVerifyTaskResults();
		const auto VerifyRequests = Result->GetVerifyTaskRequests();
		if (VerifyRequests.IsValid() && VerifyBodies.IsValid())
		{
			for (int32 Index = 0; Index < FMath::Min(VerifyRequests->Num(), VerifyBodies->Num()); ++Index)
			{
				if (!(*VerifyRequests)[Index].IsValid())
				{
					Error = MissingAccessTokenResult();
					return nullptr;
				}
			}
		}
		Error = ValidateAccessTokenStampEntries(
			VerifyRequests.IsValid() ? VerifyRequests->Num() : 0,
			VerifyBodies.IsValid() ? VerifyBodies->Num() : 0,
			VerifyCodes,
			VerifyBodies
		);
		if (Error.IsValid()) return nullptr;

		const auto TaskCodes = Result->GetTaskResultCodes();
		const auto TaskBodies = Result->GetTaskResults();
		const auto TaskRequests = Result->GetTaskRequests();
		if (TaskRequests.IsValid() && TaskBodies.IsValid())
		{
			for (int32 Index = 0; Index < FMath::Min(TaskRequests->Num(), TaskBodies->Num()); ++Index)
			{
				if (!(*TaskRequests)[Index].IsValid())
				{
					Error = MissingAccessTokenResult();
					return nullptr;
				}
			}
		}
		Error = ValidateAccessTokenStampEntries(
			TaskRequests.IsValid() ? TaskRequests->Num() : 0,
			TaskBodies.IsValid() ? TaskBodies->Num() : 0,
			TaskCodes,
			TaskBodies
		);
		if (Error.IsValid()) return nullptr;

		if (Result->GetSheetResult().IsSet() || Result->GetSheetResultCode().IsSet())
		{
			Error = ValidateAccessTokenStatus(Result->GetSheetResultCode(), Result->GetSheetResult());
			if (Error.IsValid()) return nullptr;
		}
		const bool SkipCallback = MarkHandled();

		if (!SkipCallback && VerifyRequests.IsValid() && VerifyBodies.IsValid()) {
			for (auto i = 0; i < FMath::Min(VerifyRequests->Num(), VerifyBodies->Num()); i++) {
				const auto VerifyTask = (*VerifyRequests)[i];
				if (VerifyTask.IsValid()) {
					Gs2->TransactionConfiguration->VerifyActionEventHandler(
						Gs2->Cache,
						TransactionId + FString::Printf(TEXT("[%d]"), i),
						AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>(),
						VerifyTask->GetAction().IsSet() ? *VerifyTask->GetAction() : FString(),
						VerifyTask->GetRequest().IsSet() ? *VerifyTask->GetRequest() : FString(),
						(*VerifyBodies)[i]
					);
				}
			}
		}
            
		if (!SkipCallback && TaskRequests.IsValid() && TaskBodies.IsValid()) {
			for (auto i = 0; i < FMath::Min(TaskRequests->Num(), TaskBodies->Num()); i++) {
				const auto StampTask = (*TaskRequests)[i];
				if (StampTask.IsValid()) {
					Gs2->TransactionConfiguration->ConsumeActionEventHandler(
						Gs2->Cache,
						TransactionId + FString::Printf(TEXT("[%d]"), i),
						AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>(),
						StampTask->GetAction().IsSet() ? *StampTask->GetAction() : FString(),
						StampTask->GetRequest().IsSet() ? *StampTask->GetRequest() : FString(),
						(*TaskBodies)[i]
					);
				}
			}
		}

		if (Result->GetSheetResult().IsSet() && !Result->GetSheetResult()->IsEmpty() && Result->GetSheetRequest().IsValid()) {
			if (!SkipCallback)
			{
			Gs2->TransactionConfiguration->AcquireActionEventHandler(
				Gs2->Cache,
				TransactionId,
				AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>(),
				Result->GetSheetRequest()->GetAction().IsSet() ? *Result->GetSheetRequest()->GetAction() : FString(),
				Result->GetSheetRequest()->GetRequest().IsSet() ? *Result->GetSheetRequest()->GetRequest() : FString(),
				*Result->GetSheetResult()
			);
			}

			TSharedPtr<FJsonObject> ResultModelJson;
			if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetSheetResult());
				!FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
			{
				return nullptr;
			}
			auto NextTransactions = MakeShared<TArray<FTransactionAccessTokenDomainPtr>>();
			if (Result->GetSheetRequest()->GetAction().IsSet() && *Result->GetSheetRequest()->GetAction() == "Gs2JobQueue:PushByUserId")
			{
				NextTransactions->Add(NewJobQueueDomain(
					Gs2::JobQueue::Result::FPushByUserIdResult::FromJson(ResultModelJson)
				));
			}

			if (ResultModelJson->HasField(ANSI_TO_TCHAR("autoRunStampSheet"))) {
				NextTransactions->Add(NewTransactionDomain(
					ResultModelJson->HasField(ANSI_TO_TCHAR("autoRunStampSheet")) && ResultModelJson->GetBoolField(ANSI_TO_TCHAR("autoRunStampSheet")),
					ResultModelJson->HasField(ANSI_TO_TCHAR("transactionId")) ? ResultModelJson->GetStringField(ANSI_TO_TCHAR("transactionId")) : FString(""),
                    ResultModelJson->HasField(ANSI_TO_TCHAR("stampSheet")) ? ResultModelJson->GetStringField(ANSI_TO_TCHAR("stampSheet")) : FString(""),
                    ResultModelJson->HasField(ANSI_TO_TCHAR("stampSheetEncryptionKeyId")) ? ResultModelJson->GetStringField(ANSI_TO_TCHAR("stampSheetEncryptionKeyId")) : FString(""),
                    ResultModelJson->HasField(ANSI_TO_TCHAR("atomicCommit")) && ResultModelJson->GetBoolField(ANSI_TO_TCHAR("atomicCommit")),
                    ResultModelJson->HasField(ANSI_TO_TCHAR("transactionResult")) ? Gs2::Core::Model::FTransactionResult::FromJson(ResultModelJson->GetObjectField(ANSI_TO_TCHAR("transactionResult"))) : nullptr
				));
			}
			if (NextTransactions->Num() > 0) {
				return MakeShared<FTransactionAccessTokenDomain>(
					Gs2,
					NewJobQueueDomain,
					NewTransactionDomain,
					Dispatch,
					AccessToken,
					NextTransactions
				);
			}
		}
		return nullptr;
	}

	FTransactionAccessTokenDomainPtr FAutoTransactionAccessTokenDomain::HandleTransactionResult(
		Gs2::Distributor::Model::FTransactionResultPtr Result,
		Gs2::Core::Model::FGs2ErrorPtr& Error
	)
	{
		if (!Result.IsValid())
		{
			return nullptr;
		}

		const TOptional<FString> CacheNamespace = TransactionNamespaceName.IsSet()
			? TransactionNamespaceName
			: Gs2->TransactionConfiguration->NamespaceName;
		Gs2::Distributor::Model::Cache::FTransactionResultCache::Put(
			Gs2->Cache,
			CacheNamespace,
			AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
			Result->GetTransactionId(),
			AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>(),
			Result
		);

		if (Result->GetVerifyResults().IsValid())
		{
			for (const auto& Item : *Result->GetVerifyResults())
			{
				if (!Item.IsValid())
				{
					Error = MissingAccessTokenResult();
					return nullptr;
				}
				Error = ValidateAccessTokenStatus(Item->GetStatusCode(), Item->GetVerifyResult());
				if (Error.IsValid())
				{
					return nullptr;
				}
			}
		}
		if (Result->GetConsumeResults().IsValid())
		{
			for (const auto& Item : *Result->GetConsumeResults())
			{
				if (!Item.IsValid())
				{
					Error = MissingAccessTokenResult();
					return nullptr;
				}
				Error = ValidateAccessTokenStatus(Item->GetStatusCode(), Item->GetConsumeResult());
				if (Error.IsValid())
				{
					return nullptr;
				}
			}
		}
		if (Result->GetAcquireResults().IsValid())
		{
			for (const auto& Item : *Result->GetAcquireResults())
			{
				if (!Item.IsValid())
				{
					Error = MissingAccessTokenResult();
					return nullptr;
				}
				Error = ValidateAccessTokenStatus(Item->GetStatusCode(), Item->GetAcquireResult());
				if (Error.IsValid())
				{
					return nullptr;
				}
			}
		}
		Error = ValidateAccessTokenNestedTransactionResult(Result);
		if (Error.IsValid()) return nullptr;

		const bool SkipCallback = MarkTransactionResultHandled();

		if (!SkipCallback && Result->GetVerifyResults().IsValid())
		{
			for (int32 Index = 0; Index < Result->GetVerifyResults()->Num(); ++Index)
			{
				const auto Item = (*Result->GetVerifyResults())[Index];
				if (Item.IsValid())
				{
					Gs2->TransactionConfiguration->VerifyActionEventHandler(
						Gs2->Cache,
						TransactionId + FString::Printf(TEXT("[%d]"), Index),
						AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>(),
						Item->GetAction().IsSet() ? *Item->GetAction() : FString(),
						Item->GetVerifyRequest().IsSet() ? *Item->GetVerifyRequest() : FString(),
						Item->GetVerifyResult().IsSet() ? *Item->GetVerifyResult() : FString()
					);
				}
			}
		}
		if (!SkipCallback && Result->GetConsumeResults().IsValid())
		{
			for (int32 Index = 0; Index < Result->GetConsumeResults()->Num(); ++Index)
			{
				const auto Item = (*Result->GetConsumeResults())[Index];
				if (Item.IsValid())
				{
					Gs2->TransactionConfiguration->ConsumeActionEventHandler(
						Gs2->Cache,
						TransactionId + FString::Printf(TEXT("[%d]"), Index),
						AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>(),
						Item->GetAction().IsSet() ? *Item->GetAction() : FString(),
						Item->GetConsumeRequest().IsSet() ? *Item->GetConsumeRequest() : FString(),
						Item->GetConsumeResult().IsSet() ? *Item->GetConsumeResult() : FString()
					);
				}
			}
		}

		auto NextTransactions = MakeShared<TArray<FTransactionAccessTokenDomainPtr>>();
		if (Result->GetAcquireResults().IsValid())
		{
			for (const auto& Item : *Result->GetAcquireResults())
			{
				if (!Item.IsValid()) continue;
				const FString Action = Item->GetAction().IsSet() ? *Item->GetAction() : FString();
				const FString Body = Item->GetAcquireResult().IsSet() ? *Item->GetAcquireResult() : FString();
				if (!SkipCallback)
				{
					Gs2->TransactionConfiguration->AcquireActionEventHandler(
						Gs2->Cache,
						TransactionId,
						AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>(),
						Action,
						Item->GetAcquireRequest().IsSet() ? *Item->GetAcquireRequest() : FString(),
						Body
					);
				}

				TSharedPtr<FJsonObject> ResultJson;
				if (Body.IsEmpty()) continue;
				if (const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Body);
					!FJsonSerializer::Deserialize(Reader, ResultJson))
				{
					continue;
				}
				if (Action == TEXT("Gs2JobQueue:PushByUserId"))
				{
					NextTransactions->Add(NewJobQueueDomain(
						Gs2::JobQueue::Result::FPushByUserIdResult::FromJson(ResultJson)
					));
				}
				bool AutoRunStampSheet = false;
				if (ResultJson->TryGetBoolField(TEXT("autoRunStampSheet"), AutoRunStampSheet))
				{
					FString NestedTransactionId;
					FString NestedStampSheet;
					FString NestedEncryptionKeyId;
					bool NestedAtomicCommit = false;
					ResultJson->TryGetStringField(TEXT("transactionId"), NestedTransactionId);
					ResultJson->TryGetStringField(TEXT("stampSheet"), NestedStampSheet);
					ResultJson->TryGetStringField(TEXT("stampSheetEncryptionKeyId"), NestedEncryptionKeyId);
					ResultJson->TryGetBoolField(TEXT("atomicCommit"), NestedAtomicCommit);
					Gs2::Core::Model::FTransactionResultPtr NestedResult;
					const TSharedPtr<FJsonObject>* NestedResultObject = nullptr;
					const auto NestedResultValue = ResultJson->TryGetField(TEXT("transactionResult"));
					if (NestedResultValue.IsValid() && !NestedResultValue->IsNull() &&
						NestedResultValue->TryGetObject(NestedResultObject) &&
						NestedResultObject != nullptr && NestedResultObject->IsValid())
					{
						NestedResult = Gs2::Core::Model::FTransactionResult::FromJson(*NestedResultObject);
					}
					NextTransactions->Add(NewTransactionDomain(
						AutoRunStampSheet,
						NestedTransactionId,
						NestedStampSheet,
						NestedEncryptionKeyId,
						NestedAtomicCommit,
						NestedResult
					));
				}
			}
		}
		if (NextTransactions->Num() > 0)
		{
			return MakeShared<FTransactionAccessTokenDomain>(
				Gs2,
				NewJobQueueDomain,
				NewTransactionDomain,
				Dispatch,
				AccessToken,
				NextTransactions
			);
		}
		return nullptr;
	}

	FAutoTransactionAccessTokenDomain::FAutoTransactionAccessTokenDomain(
		const FGs2Ptr& Gs2,
		const TFunction<TSharedPtr<FTransactionAccessTokenDomain>(
			const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
		)>& NewJobQueueDomain,
		const TFunction<TSharedPtr<FTransactionAccessTokenDomain>(
			bool bAutoRun,
			FString TransactionId,
			FString StampSheet,
			FString StampSheetEncryptionKeyId,
			bool bAtomicCommit,
			Gs2::Core::Model::FTransactionResultPtr TransactionResult
		)>& NewTransactionDomain,
		const TFunction<Gs2::Core::Model::FGs2ErrorPtr(
			const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
		)>& Dispatch,
		const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
		const FString TransactionId,
		const bool bAtomicCommit,
		const Gs2::Core::Model::FTransactionResultPtr InitialTransactionResult,
		const TOptional<FString> NamespaceName
	):
		FTransactionAccessTokenDomain(
			Gs2,
			NewJobQueueDomain,
			NewTransactionDomain,
			Dispatch,
			AccessToken,
			nullptr
		),
		TransactionId(TransactionId),
		TransactionNamespaceName(NamespaceName),
		bAtomicCommit(bAtomicCommit),
		InitialTransactionResult(InitialTransactionResult)
	{
		bTransactionResultHandled = false;
	        
	}

	FAutoTransactionAccessTokenDomain::FAutoTransactionAccessTokenDomain(
		const FAutoTransactionAccessTokenDomain& From
	):
		FTransactionAccessTokenDomain(
			From.Gs2,
			From.NewJobQueueDomain,
			From.NewTransactionDomain,
			From.Dispatch,
			From.AccessToken,
			nullptr
		),
		TransactionId(From.TransactionId),
		TransactionNamespaceName(From.TransactionNamespaceName),
		bAtomicCommit(From.bAtomicCommit),
		InitialTransactionResult(From.InitialTransactionResult)
	{
		bTransactionResultHandled = false;
	}

	Gs2::Core::Model::FGs2ErrorPtr FAutoTransactionAccessTokenDomain::WaitImpl(
		const bool All,
		TSharedPtr<TSharedPtr<FTransactionAccessTokenDomain>> Result
	)
	{
		const auto begin = FDateTime::Now();
	RETRY:
		if (FDateTime::Now() - begin > FTimespan::FromSeconds(10)) {
			return MakeShared<Gs2::Core::Model::FUnknownError>(
				[]
				{
					auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
					Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(
						"unknown",
						"Failed to retrieve transaction results, either because there is some failure in GS2, or the GS2-Gateway used to notify the GS2-Distributor used to execute the transaction is not yet configured, or the GS2-Gateway has a user ID to receive notifications The configuration API may not have been invoked.",
						""
					));
					return Arr;
				}()
			);
		}
		Gs2::Core::Model::FGs2ErrorPtr Error;
		FTransactionAccessTokenDomainPtr Transaction;
		const FString NamespaceName = TransactionNamespaceName.IsSet()
			? *TransactionNamespaceName
			: (Gs2->TransactionConfiguration->NamespaceName.IsSet() ? *Gs2->TransactionConfiguration->NamespaceName : TEXT("default"));
		if (bAtomicCommit && InitialTransactionResult.IsValid())
		{
			Transaction = HandleTransactionResult(
				Gs2::Distributor::Model::FTransactionResult::FromJson(InitialTransactionResult->ToJson()),
				Error
			);
		}
		else if (bAtomicCommit)
		{
			const auto Future = MakeShared<Gs2::Distributor::Domain::FGs2DistributorDomain>(Gs2)
				->Namespace(NamespaceName)
				->AccessToken(AccessToken)
				->TransactionResult(TransactionId)
				->ModelNoCache();
			Future->StartSynchronousTask();
			if (Future->GetTask().IsError())
			{
				if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
				{
					FPlatformProcess::Sleep(0.01f);
					const auto Future2 = Gs2->Distributor->Dispatch(AccessToken);
					Future2->StartSynchronousTask();
					if (Future2->GetTask().IsError()) return Future2->GetTask().Error();
					goto RETRY;
				}
				return Future->GetTask().Error();
			}
			const auto FutureResult = Future->GetTask().Result();
			if (!FutureResult.IsValid())
			{
				FPlatformProcess::Sleep(0.01f);
				const auto Future2 = Gs2->Distributor->Dispatch(AccessToken);
				Future2->StartSynchronousTask();
				if (Future2->GetTask().IsError()) return Future2->GetTask().Error();
				goto RETRY;
			}
			Transaction = HandleTransactionResult(FutureResult, Error);
		}
		else
		{
			const auto Future = MakeShared<Gs2::Distributor::Domain::FGs2DistributorDomain>(Gs2)
				->Namespace(NamespaceName)
				->AccessToken(AccessToken)
				->StampSheetResult(TransactionId)
				->Model();
			Future->StartSynchronousTask();
			if (Future->GetTask().IsError())
			{
				if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
				{
					FPlatformProcess::Sleep(0.01f);
					const auto Future2 = Gs2->Distributor->Dispatch(AccessToken);
					Future2->StartSynchronousTask();
					if (Future2->GetTask().IsError()) return Future2->GetTask().Error();
					goto RETRY;
				}
				return Future->GetTask().Error();
			}
			const auto FutureResult = Future->GetTask().Result();
			if (!FutureResult.IsValid())
			{
				FPlatformProcess::Sleep(0.01f);
				const auto Future2 = Gs2->Distributor->Dispatch(AccessToken);
				Future2->StartSynchronousTask();
				if (Future2->GetTask().IsError()) return Future2->GetTask().Error();
				goto RETRY;
			}
			Transaction = HandleResult(FutureResult, Error);
		}
		if (Error.IsValid())
		{
			return Error;
		}
		if (All && Transaction.IsValid()) {
			const auto Future3 = Transaction->Wait(true);
			Future3->StartSynchronousTask();
			if (Future3->GetTask().IsError())
			{
				return Future3->GetTask().Error();
			}
			*Result = nullptr;
			return nullptr;
		}
		*Result = Transaction;
		return nullptr;
	}

	TSharedPtr<FAsyncTask<FTransactionAccessTokenDomain::FWaitTask>> FAutoTransactionAccessTokenDomain::Wait(
		bool All
	)
	{
		return Gs2::Core::Util::New<FAsyncTask<FWaitTask>>(this->AsShared(), [this, All](
			TSharedPtr<TSharedPtr<FTransactionAccessTokenDomain>> Result
		) {
			return WaitImpl(All, Result);
		});
	}

	TOptional<FString> FAutoTransactionAccessTokenDomain::GetTransactionId() const
	{
		return TransactionId;
	}
}
