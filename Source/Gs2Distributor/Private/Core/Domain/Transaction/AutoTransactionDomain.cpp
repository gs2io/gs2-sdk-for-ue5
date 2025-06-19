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

#include "../Public/Core/Domain/Transaction/AutoTransactionDomain.h"

#include "Core/Domain/Gs2.h"
#include "Distributor/Domain/Gs2Distributor.h"

namespace Gs2::Core::Domain
{
	TMap<FString, FDateTime> FAutoTransactionDomain::Handled;
	
	FTransactionDomainPtr FAutoTransactionDomain::HandleResult(
		Gs2::Distributor::Model::FStampSheetResultPtr Result)
	{
		auto bSkipCallback = false;
		if (Handled.Contains(TransactionId)) {
			// TODO: expire handled
			bSkipCallback = true;
		}
		else {
			Handled.Add(this->TransactionId, FDateTime::Now() + FTimespan::FromMinutes(3));
		}
            
		if (Result->GetTaskRequests().IsValid()) {
			for (auto i = 0; i < Result->GetTaskRequests()->Num(); i++) {
				const auto StampTask = (*Result->GetTaskRequests())[i];
				if (i < Result->GetTaskResults()->Num()) {
					if (!bSkipCallback) {
						Gs2->TransactionConfiguration->StampTaskEventHandler(
							*StampTask->GetAction(),
							*StampTask->GetRequest(),
							(*Result->GetTaskResults())[i]
						);
					}
				}
			}
		}

		if (!Result->GetSheetResult()->IsEmpty()) {
			if (!bSkipCallback) {
				Gs2->TransactionConfiguration->StampSheetEventHandler(
					*Result->GetSheetRequest()->GetAction(),
					*Result->GetSheetRequest()->GetRequest(),
					*Result->GetSheetResult()
				);
			}

			TSharedPtr<FJsonObject> ResultModelJson;
			if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetSheetResult());
				!FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
			{
				return nullptr;
			}
			auto NextTransactions = MakeShared<TArray<FTransactionDomainPtr>>();
			if (*Result->GetSheetRequest()->GetAction() == "Gs2JobQueue:PushByUserId")
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
				return MakeShared<FTransactionDomain>(
					Gs2,
					NewJobQueueDomain,
					NewTransactionDomain,
					UserId,
					NextTransactions
				);
			}
		}
		return nullptr;
	}

	FAutoTransactionDomain::FAutoTransactionDomain(
		const FGs2Ptr& Gs2,
		const TFunction<TSharedPtr<FTransactionDomain>(
			const Gs2::JobQueue::Result::FPushByUserIdResultPtr& Result
		)>& NewJobQueueDomain,
		const TFunction<TSharedPtr<FTransactionDomain>(
			bool bAutoRun,
			FString TransactionId,
			FString StampSheet,
			FString StampSheetEncryptionKeyId,
			bool bAtomicCommit,
			Gs2::Core::Model::FTransactionResultPtr TransactionResult
		)>& NewTransactionDomain,
		const FString UserId,
		const FString TransactionId
	):
		FTransactionDomain(
			Gs2,
			NewJobQueueDomain,
			NewTransactionDomain,
			UserId,
			nullptr
		),
		TransactionId(TransactionId)
	{
	        
	}

	FAutoTransactionDomain::FAutoTransactionDomain(
		const FAutoTransactionDomain& From
	):
		FTransactionDomain(
			From.Gs2,
			From.NewJobQueueDomain,
			From.NewTransactionDomain,
			From.UserId,
			nullptr
		),
		TransactionId(From.TransactionId)
	{
	}

	Gs2::Core::Model::FGs2ErrorPtr FAutoTransactionDomain::WaitImpl(
		const bool All,
		TSharedPtr<TSharedPtr<FTransactionDomain>> Result
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
		const auto Future = MakeShared<Gs2::Distributor::Domain::FGs2DistributorDomain>(
			Gs2
		)->Namespace(
			Gs2->TransactionConfiguration->NamespaceName.IsSet() ? *Gs2->TransactionConfiguration->NamespaceName : "default"
		)->User(
			UserId
		)->StampSheetResult(
			TransactionId
		)->Model();
		Future->StartSynchronousTask();
		if (Future->GetTask().IsError())
		{
			return Future->GetTask().Error();
		}
		auto FutureResult = Future->GetTask().Result();
		if (!FutureResult.IsValid()) {
			FPlatformProcess::Sleep(0.01f);

			const auto Future2 = Gs2->Distributor->DispatchByUserId(UserId);
			Future2->StartSynchronousTask();
			if (Future2->GetTask().IsError())
			{
				return Future2->GetTask().Error();
			}
			goto RETRY;
		}

		const auto Transaction = HandleResult(FutureResult);
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

	TSharedPtr<FAsyncTask<FTransactionDomain::FWaitTask>> FAutoTransactionDomain::Wait(
		bool All
	)
	{
		return Gs2::Core::Util::New<FAsyncTask<FWaitTask>>(this->AsShared(), [this, All](
			TSharedPtr<TSharedPtr<FTransactionDomain>> Result
		) {
			return WaitImpl(All, Result);
		});
	}
}
