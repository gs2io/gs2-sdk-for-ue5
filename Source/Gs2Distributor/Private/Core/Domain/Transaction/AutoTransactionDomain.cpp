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
#include "Distributor/Model/Cache/TransactionResult.h"
#include "Misc/ScopeLock.h"

namespace Gs2::Core::Domain
{
    namespace
    {
        Gs2::Core::Model::FGs2ErrorPtr ValidateStatus(
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

        Gs2::Core::Model::FTransactionResultPtr ParseTransactionResult(
            const TSharedPtr<FJsonObject>& Json
        )
        {
            if (!Json.IsValid())
            {
                return nullptr;
            }
            const auto Value = Json->TryGetField(TEXT("transactionResult"));
            const TSharedPtr<FJsonObject>* Object = nullptr;
            if (Value.IsValid() && !Value->IsNull() &&
                Value->TryGetObject(Object) && Object != nullptr && Object->IsValid())
            {
                return Gs2::Core::Model::FTransactionResult::FromJson(*Object);
            }
            return nullptr;
        }

        FString OptionalString(const TOptional<FString>& Value)
        {
            return Value.IsSet() ? *Value : FString();
        }

        bool TryGetJsonString(
            const TSharedPtr<FJsonObject>& Json,
            const TCHAR* FieldName,
            FString& Value
        )
        {
            return Json.IsValid() && Json->TryGetStringField(FieldName, Value);
        }

        bool TryGetJsonBool(
            const TSharedPtr<FJsonObject>& Json,
            const TCHAR* FieldName,
            bool& Value
        )
        {
            return Json.IsValid() && Json->TryGetBoolField(FieldName, Value);
        }

        Gs2::Core::Model::FGs2ErrorPtr MissingResult(
            const TOptional<FString>& Body = TOptional<FString>()
        )
        {
            return Gs2::Core::Model::FGs2Error::FromResponse(
                999,
                Body.IsSet() ? *Body : FString()
            );
        }

        Gs2::Core::Model::FGs2ErrorPtr ValidateStampEntries(
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
                const TOptional<FString> Body = TOptional<FString>((*Bodies)[Index]);
                const auto Error = ValidateStatus(Status, Body);
                if (Error.IsValid())
                {
                    return Error;
                }
            }
            return nullptr;
        }

        Gs2::Core::Model::FGs2ErrorPtr TransactionFailed()
        {
            auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(
                TEXT("unknown"), TEXT("Ran transaction failed."), TEXT("")));
            return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
        }

        Gs2::Core::Model::FGs2ErrorPtr ValidateNestedTransactionResult(
            const Gs2::Distributor::Model::FTransactionResultPtr& Result
        )
        {
            if (!Result.IsValid()) return nullptr;
            const auto VerifyResults = Result->GetVerifyResults();
            if (VerifyResults.IsValid())
            {
                for (const auto& Item : *VerifyResults)
                {
                    if (!Item.IsValid()) return MissingResult();
                    const auto Error = ValidateStatus(Item->GetStatusCode(), Item->GetVerifyResult());
                    if (Error.IsValid()) return Error;
                }
            }
            const auto ConsumeResults = Result->GetConsumeResults();
            if (ConsumeResults.IsValid())
            {
                for (const auto& Item : *ConsumeResults)
                {
                    if (!Item.IsValid()) return MissingResult();
                    const auto Error = ValidateStatus(Item->GetStatusCode(), Item->GetConsumeResult());
                    if (Error.IsValid()) return Error;
                }
            }
            const auto AcquireResults = Result->GetAcquireResults();
            if (AcquireResults.IsValid())
            {
                for (const auto& Item : *AcquireResults)
                {
                    if (!Item.IsValid()) return MissingResult();
                    const auto Error = ValidateStatus(Item->GetStatusCode(), Item->GetAcquireResult());
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
                            const auto Error = ValidateNestedTransactionResult(NestedResult);
                            if (Error.IsValid()) return Error;
                        }
                    }
                }
            }
            return TransactionFailed();
        }
    }

    TMap<FString, FDateTime> FAutoTransactionDomain::Handled;
    FCriticalSection FAutoTransactionDomain::HandledMutex;

    bool FAutoTransactionDomain::MarkHandled()
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

    bool FAutoTransactionDomain::MarkTransactionResultHandled()
    {
        FScopeLock Lock(&TransactionResultMutex);
        if (bTransactionResultHandled)
        {
            return true;
        }
        bTransactionResultHandled = true;
        return false;
    }

    FTransactionDomainPtr FAutoTransactionDomain::HandleResult(
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
                    Error = MissingResult();
                    return nullptr;
                }
            }
        }
        Error = ValidateStampEntries(
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
                    Error = MissingResult();
                    return nullptr;
                }
            }
        }
        Error = ValidateStampEntries(
            TaskRequests.IsValid() ? TaskRequests->Num() : 0,
            TaskBodies.IsValid() ? TaskBodies->Num() : 0,
            TaskCodes,
            TaskBodies
        );
        if (Error.IsValid()) return nullptr;

        if (Result->GetSheetResult().IsSet() || Result->GetSheetResultCode().IsSet())
        {
            Error = ValidateStatus(Result->GetSheetResultCode(), Result->GetSheetResult());
            if (Error.IsValid())
            {
                return nullptr;
            }
        }

        const bool SkipCallback = MarkHandled();
        if (!SkipCallback && VerifyRequests.IsValid() && VerifyBodies.IsValid())
        {
            for (int32 Index = 0; Index < FMath::Min(VerifyRequests->Num(), VerifyBodies->Num()); ++Index)
            {
                const auto Request = (*VerifyRequests)[Index];
                if (Request.IsValid())
                {
                    Gs2->TransactionConfiguration->VerifyActionEventHandler(
                        Gs2->Cache,
                        TransactionId + FString::Printf(TEXT("[%d]"), Index),
                        TOptional<int32>(),
                        OptionalString(Request->GetAction()),
                        OptionalString(Request->GetRequest()),
                        (*VerifyBodies)[Index]
                    );
                }
            }
        }

        if (!SkipCallback && TaskRequests.IsValid() && TaskBodies.IsValid())
        {
            for (int32 Index = 0; Index < FMath::Min(TaskRequests->Num(), TaskBodies->Num()); ++Index)
            {
                const auto Request = (*TaskRequests)[Index];
                if (Request.IsValid())
                {
                    Gs2->TransactionConfiguration->ConsumeActionEventHandler(
                        Gs2->Cache,
                        TransactionId + FString::Printf(TEXT("[%d]"), Index),
                        TOptional<int32>(),
                        OptionalString(Request->GetAction()),
                        OptionalString(Request->GetRequest()),
                        (*TaskBodies)[Index]
                    );
                }
            }
        }

        const auto SheetRequest = Result->GetSheetRequest();
        const auto SheetBody = Result->GetSheetResult();
        auto NextTransactions = MakeShared<TArray<FTransactionDomainPtr>>();
        if (SheetRequest.IsValid() && SheetBody.IsSet() && !SheetBody->IsEmpty())
        {
            if (!SkipCallback)
            {
                Gs2->TransactionConfiguration->AcquireActionEventHandler(
                    Gs2->Cache,
                    TransactionId,
                    TOptional<int32>(),
                    OptionalString(SheetRequest->GetAction()),
                    OptionalString(SheetRequest->GetRequest()),
                    *SheetBody
                );
            }

            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*SheetBody);
                FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                const auto Action = OptionalString(SheetRequest->GetAction());
                if (Action == TEXT("Gs2JobQueue:PushByUserId"))
                {
                    NextTransactions->Add(NewJobQueueDomain(
                        Gs2::JobQueue::Result::FPushByUserIdResult::FromJson(ResultModelJson)
                    ));
                }
                bool AutoRunStampSheet = false;
                if (TryGetJsonBool(ResultModelJson, TEXT("autoRunStampSheet"), AutoRunStampSheet))
                {
                    FString NestedTransactionId;
                    FString NestedStampSheet;
                    FString NestedEncryptionKeyId;
                    bool NestedAtomicCommit = false;
                    TryGetJsonString(ResultModelJson, TEXT("transactionId"), NestedTransactionId);
                    TryGetJsonString(ResultModelJson, TEXT("stampSheet"), NestedStampSheet);
                    TryGetJsonString(ResultModelJson, TEXT("stampSheetEncryptionKeyId"), NestedEncryptionKeyId);
                    TryGetJsonBool(ResultModelJson, TEXT("atomicCommit"), NestedAtomicCommit);
                    NextTransactions->Add(NewTransactionDomain(
                        AutoRunStampSheet,
                        NestedTransactionId,
                        NestedStampSheet,
                        NestedEncryptionKeyId,
                        NestedAtomicCommit,
                        ParseTransactionResult(ResultModelJson)
                    ));
                }
            }
        }
        if (NextTransactions->Num() > 0)
        {
            return MakeShared<FTransactionDomain>(
                Gs2,
                NewJobQueueDomain,
                NewTransactionDomain,
                UserId,
                NextTransactions
            );
        }
        return nullptr;
    }

    FTransactionDomainPtr FAutoTransactionDomain::HandleTransactionResult(
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
			UserId,
			Result->GetTransactionId(),
			TOptional<int32>(),
			Result
		);

		const auto VerifyResults = Result->GetVerifyResults();
        if (VerifyResults.IsValid())
        {
            for (const auto& Item : *VerifyResults)
            {
                if (!Item.IsValid())
                {
                    Error = MissingResult();
                    return nullptr;
                }
                else
                {
                    Error = ValidateStatus(Item->GetStatusCode(), Item->GetVerifyResult());
                    if (Error.IsValid()) return nullptr;
                }
            }
        }
        const auto ConsumeResults = Result->GetConsumeResults();
        if (ConsumeResults.IsValid())
        {
            for (const auto& Item : *ConsumeResults)
            {
                if (!Item.IsValid())
                {
                    Error = MissingResult();
                    return nullptr;
                }
                else
                {
                    Error = ValidateStatus(Item->GetStatusCode(), Item->GetConsumeResult());
                    if (Error.IsValid()) return nullptr;
                }
            }
        }
        const auto AcquireResults = Result->GetAcquireResults();
        if (AcquireResults.IsValid())
        {
            for (const auto& Item : *AcquireResults)
            {
                if (!Item.IsValid())
                {
                    Error = MissingResult();
                    return nullptr;
                }
                else
                {
                    Error = ValidateStatus(Item->GetStatusCode(), Item->GetAcquireResult());
                    if (Error.IsValid()) return nullptr;
                }
            }
        }

        Error = ValidateNestedTransactionResult(Result);
        if (Error.IsValid()) return nullptr;

        const bool SkipCallback = MarkTransactionResultHandled();
        if (!SkipCallback && VerifyResults.IsValid())
        {
            for (int32 Index = 0; Index < VerifyResults->Num(); ++Index)
            {
                const auto Item = (*VerifyResults)[Index];
                if (Item.IsValid())
                {
                    Gs2->TransactionConfiguration->VerifyActionEventHandler(
                        Gs2->Cache,
                        TransactionId + FString::Printf(TEXT("[%d]"), Index),
                        TOptional<int32>(),
                        OptionalString(Item->GetAction()),
                        OptionalString(Item->GetVerifyRequest()),
                        OptionalString(Item->GetVerifyResult())
                    );
                }
            }
        }
        if (!SkipCallback && ConsumeResults.IsValid())
        {
            for (int32 Index = 0; Index < ConsumeResults->Num(); ++Index)
            {
                const auto Item = (*ConsumeResults)[Index];
                if (Item.IsValid())
                {
                    Gs2->TransactionConfiguration->ConsumeActionEventHandler(
                        Gs2->Cache,
                        TransactionId + FString::Printf(TEXT("[%d]"), Index),
                        TOptional<int32>(),
                        OptionalString(Item->GetAction()),
                        OptionalString(Item->GetConsumeRequest()),
                        OptionalString(Item->GetConsumeResult())
                    );
                }
            }
        }

        auto NextTransactions = MakeShared<TArray<FTransactionDomainPtr>>();
        if (AcquireResults.IsValid())
        {
            for (const auto& Item : *AcquireResults)
            {
                if (!Item.IsValid()) continue;
                const FString Action = OptionalString(Item->GetAction());
                const FString Body = OptionalString(Item->GetAcquireResult());
                if (!SkipCallback)
                {
                    Gs2->TransactionConfiguration->AcquireActionEventHandler(
                        Gs2->Cache,
                        TransactionId,
                        TOptional<int32>(),
                        Action,
                        OptionalString(Item->GetAcquireRequest()),
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
                if (TryGetJsonBool(ResultJson, TEXT("autoRunStampSheet"), AutoRunStampSheet))
                {
                    FString NestedTransactionId;
                    FString NestedStampSheet;
                    FString NestedEncryptionKeyId;
                    bool NestedAtomicCommit = false;
                    TryGetJsonString(ResultJson, TEXT("transactionId"), NestedTransactionId);
                    TryGetJsonString(ResultJson, TEXT("stampSheet"), NestedStampSheet);
                    TryGetJsonString(ResultJson, TEXT("stampSheetEncryptionKeyId"), NestedEncryptionKeyId);
                    TryGetJsonBool(ResultJson, TEXT("atomicCommit"), NestedAtomicCommit);
                    NextTransactions->Add(NewTransactionDomain(
                        AutoRunStampSheet,
                        NestedTransactionId,
                        NestedStampSheet,
                        NestedEncryptionKeyId,
                        NestedAtomicCommit,
                        ParseTransactionResult(ResultJson)
                    ));
                }
            }
        }
        if (NextTransactions->Num() > 0)
        {
            return MakeShared<FTransactionDomain>(
                Gs2,
                NewJobQueueDomain,
                NewTransactionDomain,
                UserId,
                NextTransactions
            );
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
        const FString TransactionId,
        const bool bAtomicCommit,
        const Gs2::Core::Model::FTransactionResultPtr InitialTransactionResult,
        const TOptional<FString> NamespaceName
    ):
        FTransactionDomain(
            Gs2,
            NewJobQueueDomain,
            NewTransactionDomain,
            UserId,
            nullptr
        ),
        TransactionId(TransactionId),
        TransactionNamespaceName(NamespaceName),
        bAtomicCommit(bAtomicCommit),
        InitialTransactionResult(InitialTransactionResult)
    {
        bTransactionResultHandled = false;
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
        TransactionId(From.TransactionId),
        TransactionNamespaceName(From.TransactionNamespaceName),
        bAtomicCommit(From.bAtomicCommit),
        InitialTransactionResult(From.InitialTransactionResult)
    {
        bTransactionResultHandled = false;
    }

    Gs2::Core::Model::FGs2ErrorPtr FAutoTransactionDomain::WaitImpl(
        const bool All,
        TSharedPtr<TSharedPtr<FTransactionDomain>> Result
    )
    {
        const auto Begin = FDateTime::Now();
    RETRY:
        if (FDateTime::Now() - Begin > FTimespan::FromSeconds(10))
        {
            return MakeShared<Gs2::Core::Model::FUnknownError>(
                []
                {
                    auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                    Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(
                        "unknown",
                        "Failed to retrieve transaction results, either because there is some failure in GS2, or the GS2-Gateway used to notify the GS2-Distributor used to execute the transaction is not yet configured, or the GS2-Gateway has a user ID to receive notifications The configuration API may not have been invoked.",
                        ""
                    ));
                    return Details;
                }()
            );
        }

        Gs2::Core::Model::FGs2ErrorPtr Error;
        FTransactionDomainPtr Transaction;
        const FString NamespaceName = TransactionNamespaceName.IsSet()
            ? *TransactionNamespaceName
            : (Gs2->TransactionConfiguration->NamespaceName.IsSet() ? *Gs2->TransactionConfiguration->NamespaceName : TEXT("default"));
        if (bAtomicCommit)
        {
            Gs2::Distributor::Model::FTransactionResultPtr Value;
            if (InitialTransactionResult.IsValid())
            {
                Value = Gs2::Distributor::Model::FTransactionResult::FromJson(InitialTransactionResult->ToJson());
            }
            else
            {
                const auto Future = MakeShared<Gs2::Distributor::Domain::FGs2DistributorDomain>(Gs2)
                    ->Namespace(NamespaceName)
                    ->User(UserId)
                    ->TransactionResult(TransactionId)
                    ->ModelNoCache();
                Future->StartSynchronousTask();
                if (Future->GetTask().IsError())
                {
                    if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                    {
                        FPlatformProcess::Sleep(0.01f);
                        const auto Dispatch = Gs2->Distributor->DispatchByUserId(UserId);
                        Dispatch->StartSynchronousTask();
                        if (Dispatch->GetTask().IsError()) return Dispatch->GetTask().Error();
                        goto RETRY;
                    }
                    return Future->GetTask().Error();
                }
                Value = Future->GetTask().Result();
                if (!Value.IsValid())
                {
                    FPlatformProcess::Sleep(0.01f);
                    const auto Dispatch = Gs2->Distributor->DispatchByUserId(UserId);
                    Dispatch->StartSynchronousTask();
                    if (Dispatch->GetTask().IsError()) return Dispatch->GetTask().Error();
                    goto RETRY;
                }
            }
            Transaction = HandleTransactionResult(Value, Error);
        }
        else
        {
            const auto Future = MakeShared<Gs2::Distributor::Domain::FGs2DistributorDomain>(Gs2)
                ->Namespace(NamespaceName)
                ->User(UserId)
                ->StampSheetResult(TransactionId)
                ->ModelNoCache();
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    FPlatformProcess::Sleep(0.01f);
                    const auto Dispatch = Gs2->Distributor->DispatchByUserId(UserId);
                    Dispatch->StartSynchronousTask();
                    if (Dispatch->GetTask().IsError()) return Dispatch->GetTask().Error();
                    goto RETRY;
                }
                return Future->GetTask().Error();
            }
            const auto Value = Future->GetTask().Result();
            if (!Value.IsValid())
            {
                FPlatformProcess::Sleep(0.01f);
                const auto Dispatch = Gs2->Distributor->DispatchByUserId(UserId);
                Dispatch->StartSynchronousTask();
                if (Dispatch->GetTask().IsError()) return Dispatch->GetTask().Error();
                goto RETRY;
            }
            Transaction = HandleResult(Value, Error);
        }

        if (Error.IsValid())
        {
            return Error;
        }
        if (All && Transaction.IsValid())
        {
            const auto Future = Transaction->Wait(true);
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
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
