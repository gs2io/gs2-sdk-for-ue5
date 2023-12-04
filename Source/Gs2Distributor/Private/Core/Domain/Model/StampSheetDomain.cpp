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


#include "Core/Domain/Model/StampSheetDomain.h"

#include "Distributor/Gs2DistributorRestClient.h"


namespace Gs2::Core::Domain::Model
{
    FStampSheetDomain::FStampSheetDomain(
        const Gs2::Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Net::Rest::FGs2RestSessionPtr Session,
        const FString StampSheet,
        const FString StampSheetEncryptionKeyId,
        const FTransactionConfigurationPtr StampSheetConfiguration
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        Session(Session),
        StampSheet(StampSheet),
        StampSheetEncryptionKeyId(StampSheetEncryptionKeyId),
        StampSheetConfiguration(StampSheetConfiguration)
    {
    }

    FStampSheetDomain::FStampSheetDomain(
        const FStampSheetDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        Session(From.Session),
        StampSheet(From.StampSheet),
        StampSheetEncryptionKeyId(From.StampSheetEncryptionKeyId),
        StampSheetConfiguration(From.StampSheetConfiguration)
    {
    }

    FStampSheetDomain::FRunTask::FRunTask(
            const TSharedPtr<FStampSheetDomain> Self
    ): Self(Self)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStampSheetDomain::FRunTask::Action(
        TSharedPtr<TSharedPtr<void*>> Result
    )
    {
        TArray<TSharedPtr<FJsonValue>> StampTasks;
        TSharedPtr<FJsonObject> StampPayloadJson;
        TSharedPtr<FJsonObject> StampSheetJson;
        if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Self->StampSheet);
            FJsonSerializer::Deserialize(JsonReader, StampSheetJson))
        {
            const auto StampSheetPayload = StampSheetJson->GetStringField("body");
            if (const TSharedRef<TJsonReader<>> JsonReader2 = TJsonReaderFactory<>::Create(StampSheetPayload);
                FJsonSerializer::Deserialize(JsonReader2, StampPayloadJson))
            {
                if (!StampPayloadJson->HasTypedField<EJson::Null>("tasks"))
                {
                    StampTasks = StampPayloadJson->GetArrayField("tasks");
                }
            }
        }

        TOptional<FString> StampSheetResult;
        TSharedPtr<TArray<FString>> StampTaskResults;
        
        const auto Client = MakeShared<Gs2::Distributor::FGs2DistributorRestClient>(Self->Session);
        if (Self->StampSheetConfiguration->NamespaceName.IsSet() && *Self->StampSheetConfiguration->NamespaceName != "")
        {
            const auto Future = Client->RunStampSheetExpress(
                MakeShared<Gs2::Distributor::Request::FRunStampSheetExpressRequest>()
                    ->WithNamespaceName(Self->StampSheetConfiguration->NamespaceName)
                    ->WithStampSheet(Self->StampSheet)
                    ->WithKeyId(Self->StampSheetEncryptionKeyId)
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                Future->EnsureCompletion();
                return Future->GetTask().Error();
            }
            Future->EnsureCompletion();
            const auto RunResult = Future->GetTask().Result();
            StampSheetResult = RunResult->GetSheetResult();
            StampTaskResults = RunResult->GetTaskResults();
        }
        else
        {
            const auto Future = Client->RunStampSheetExpressWithoutNamespace(
                MakeShared<Gs2::Distributor::Request::FRunStampSheetExpressWithoutNamespaceRequest>()
                    ->WithStampSheet(Self->StampSheet)
                    ->WithKeyId(Self->StampSheetEncryptionKeyId)
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                Future->EnsureCompletion();
                return Future->GetTask().Error();
            }
            Future->EnsureCompletion();
            const auto RunResult = Future->GetTask().Result();
            StampSheetResult = RunResult->GetSheetResult();
            StampTaskResults = RunResult->GetTaskResults();
        }

        if (StampTaskResults != nullptr)
        {
            int Index = 0;
            for (auto StampTaskResult : *StampTaskResults)
            {
                const auto StampTask = StampTasks[Index];
                TSharedPtr<FJsonObject> StampTaskJson;
                if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(StampTask->AsString());
                    FJsonSerializer::Deserialize(JsonReader, StampTaskJson))
                {
                    const auto StampTaskPayload = StampTaskJson->GetStringField("body");
                    TSharedPtr<FJsonObject> StampTaskPayloadJson;
                    if (const TSharedRef<TJsonReader<>> JsonReader2 = TJsonReaderFactory<>::Create(StampTaskPayload);
                        FJsonSerializer::Deserialize(JsonReader2, StampTaskPayloadJson))
                    {
                        const auto Action = StampTaskPayloadJson->GetStringField("action");
                        const auto Request = StampTaskPayloadJson->GetStringField("args");
                        Self->StampSheetConfiguration->StampTaskEventHandler(
                            Action,
                            Request,
                            StampTaskResult
                        );
                    }
                }
                Index++;
            }
        }
        if (StampSheetResult.IsSet())
        {
            const auto Action = StampPayloadJson->GetStringField("action");
            const auto Request = StampPayloadJson->GetStringField("args");
            Self->StampSheetConfiguration->StampSheetEventHandler(
                Action,
                Request,
                *StampSheetResult
            );

            TSharedPtr<FJsonObject> StampSheetResultJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*StampSheetResult);
                FJsonSerializer::Deserialize(JsonReader, StampSheetResultJson))
            {
                if(StampSheetResultJson->HasField("autoRunStampSheet") && !StampSheetResultJson->GetBoolField("autoRunStampSheet"))
                {
                    FString NewStampSheet("");
                    FString NewStampSheetEncryptionKeyId("");
                    if(StampSheetResultJson->HasField("stampSheet") && StampSheetResultJson->TryGetStringField("stampSheet", NewStampSheet) &&
                        StampSheetResultJson->HasField("stampSheetEncryptionKeyId") && StampSheetResultJson->TryGetStringField("stampSheetEncryptionKeyId", NewStampSheetEncryptionKeyId))
                    {
                        const auto NewStampSheetDomain = MakeShared<FStampSheetDomain>(
                            Self->Cache,
                            Self->JobQueueDomain,
                            Self->Session,
                            NewStampSheet,
                            NewStampSheetEncryptionKeyId,
                            Self->StampSheetConfiguration
                        );
                        const auto Future = NewStampSheetDomain->Run();
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError())
                        {
                            Future->EnsureCompletion();
                            return Future->GetTask().Error();
                        }
                        Future->EnsureCompletion();
                    }
                }
            }

            if (Action == "Gs2JobQueue:PushByUserId")
            {
                TSharedPtr<FJsonObject> RequestJson;
                if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                    FJsonSerializer::Deserialize(JsonReader, RequestJson))
                {
                    FString NamespaceName("");
                    if(RequestJson->HasField("namespaceName") && RequestJson->TryGetStringField("namespaceName", NamespaceName))
                    {
                        Self->JobQueueDomain->Push(
                        NamespaceName
                        );
                    }
                }
            }
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStampSheetDomain::FRunTask>> FStampSheetDomain::Run()
    {
        return Gs2::Core::Util::New<FAsyncTask<FRunTask>>(this->AsShared());
    }
}
