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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "Mission/Domain/Gs2Mission.h"
#include "Mission/Domain/Model/Complete.h"
#include "Mission/Domain/Model/CounterModelMaster.h"
#include "Mission/Domain/Model/MissionGroupModelMaster.h"
#include "Mission/Domain/Model/Namespace.h"
#include "Mission/Domain/Model/Counter.h"
#include "Mission/Domain/Model/CurrentMissionMaster.h"
#include "Mission/Domain/Model/CounterModel.h"
#include "Mission/Domain/Model/MissionGroupModel.h"
#include "Mission/Domain/Model/MissionTaskModel.h"
#include "Mission/Domain/Model/MissionTaskModelMaster.h"
#include "Mission/Domain/Model/User.h"
#include "Mission/Domain/Model/UserAccessToken.h"
#include "Core/Domain/Gs2.h"

namespace Gs2::Mission::Domain
{

    FGs2MissionDomain::FGs2MissionDomain(
        const Core::Domain::FGs2Ptr& Gs2
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Mission::FGs2MissionRestClient>(Gs2->RestSession)),
        ParentKey("mission")
    {
    }

    FGs2MissionDomain::FGs2MissionDomain(
        const FGs2MissionDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2MissionDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const TSharedPtr<FGs2MissionDomain>& Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2MissionDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2MissionDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FNamespaceDomain>> Result
    )
    {
        const auto Future = Self->Client->CreateNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            {
                const auto ParentKey = FString("mission:Namespace");
                const auto Key = Gs2::Mission::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Mission::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Mission::Domain::Model::FNamespaceDomain>(
            Self->Gs2,
            Self,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2MissionDomain::FCreateNamespaceTask>> FGs2MissionDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    FGs2MissionDomain::FDumpUserDataTask::FDumpUserDataTask(
        const TSharedPtr<FGs2MissionDomain>& Self,
        const Request::FDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2MissionDomain::FDumpUserDataTask::FDumpUserDataTask(
        const FDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2MissionDomain::FDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2MissionDomain>> Result
    )
    {
        const auto Future = Self->Client->DumpUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2MissionDomain::FDumpUserDataTask>> FGs2MissionDomain::DumpUserData(
        Request::FDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2MissionDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const TSharedPtr<FGs2MissionDomain>& Self,
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2MissionDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const FCheckDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2MissionDomain::FCheckDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2MissionDomain>> Result
    )
    {
        const auto Future = Self->Client->CheckDumpUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetUrl().IsSet())
            {
                Self->Url = Domain->Url = ResultModel->GetUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2MissionDomain::FCheckDumpUserDataTask>> FGs2MissionDomain::CheckDumpUserData(
        Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2MissionDomain::FCleanUserDataTask::FCleanUserDataTask(
        const TSharedPtr<FGs2MissionDomain>& Self,
        const Request::FCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2MissionDomain::FCleanUserDataTask::FCleanUserDataTask(
        const FCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2MissionDomain::FCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2MissionDomain>> Result
    )
    {
        const auto Future = Self->Client->CleanUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2MissionDomain::FCleanUserDataTask>> FGs2MissionDomain::CleanUserData(
        Request::FCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2MissionDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const TSharedPtr<FGs2MissionDomain>& Self,
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2MissionDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const FCheckCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2MissionDomain::FCheckCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2MissionDomain>> Result
    )
    {
        const auto Future = Self->Client->CheckCleanUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2MissionDomain::FCheckCleanUserDataTask>> FGs2MissionDomain::CheckCleanUserData(
        Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2MissionDomain::FPrepareImportUserDataTask::FPrepareImportUserDataTask(
        const TSharedPtr<FGs2MissionDomain>& Self,
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2MissionDomain::FPrepareImportUserDataTask::FPrepareImportUserDataTask(
        const FPrepareImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2MissionDomain::FPrepareImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2MissionDomain>> Result
    )
    {
        const auto Future = Self->Client->PrepareImportUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetUploadToken().IsSet())
            {
                Self->UploadToken = Domain->UploadToken = ResultModel->GetUploadToken();
            }
            if (ResultModel->GetUploadUrl().IsSet())
            {
                Self->UploadUrl = Domain->UploadUrl = ResultModel->GetUploadUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2MissionDomain::FPrepareImportUserDataTask>> FGs2MissionDomain::PrepareImportUserData(
        Request::FPrepareImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareImportUserDataTask>>(this->AsShared(), Request);
    }

    FGs2MissionDomain::FImportUserDataTask::FImportUserDataTask(
        const TSharedPtr<FGs2MissionDomain>& Self,
        const Request::FImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2MissionDomain::FImportUserDataTask::FImportUserDataTask(
        const FImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2MissionDomain::FImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2MissionDomain>> Result
    )
    {
        const auto Future = Self->Client->ImportUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2MissionDomain::FImportUserDataTask>> FGs2MissionDomain::ImportUserData(
        Request::FImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FImportUserDataTask>>(this->AsShared(), Request);
    }

    FGs2MissionDomain::FCheckImportUserDataTask::FCheckImportUserDataTask(
        const TSharedPtr<FGs2MissionDomain>& Self,
        const Request::FCheckImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2MissionDomain::FCheckImportUserDataTask::FCheckImportUserDataTask(
        const FCheckImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2MissionDomain::FCheckImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2MissionDomain>> Result
    )
    {
        const auto Future = Self->Client->CheckImportUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetUrl().IsSet())
            {
                Self->Url = Domain->Url = ResultModel->GetUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2MissionDomain::FCheckImportUserDataTask>> FGs2MissionDomain::CheckImportUserData(
        Request::FCheckImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckImportUserDataTask>>(this->AsShared(), Request);
    }

    Gs2::Mission::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2MissionDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Mission::Domain::Iterator::FDescribeNamespacesIterator>(
            Gs2,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2MissionDomain::SubscribeNamespaces(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Mission::Model::FNamespace::TypeName,
            "mission:Namespace",
            Callback
        );
    }

    void FGs2MissionDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Mission::Model::FNamespace::TypeName,
            "mission:Namespace",
            CallbackID
        );
    }

    TSharedPtr<Gs2::Mission::Domain::Model::FNamespaceDomain> FGs2MissionDomain::Namespace(
        const FString NamespaceName
    )
    {
        return MakeShared<Gs2::Mission::Domain::Model::FNamespaceDomain>(
            Gs2,
            AsShared(),
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2MissionDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "RevertReceiveByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Mission::Request::FRevertReceiveByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Mission::Result::FRevertReceiveByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Complete"
                );
                const auto Key = Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetMissionGroupName()
                );
                Gs2->Cache->Put(
                    Gs2::Mission::Model::FComplete::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    ResultModel->GetItem()->GetNextResetAt().IsSet() && *ResultModel->GetItem()->GetNextResetAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItem()->GetNextResetAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "IncreaseCounterByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Mission::Request::FIncreaseCounterByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Mission::Result::FIncreaseCounterByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Counter"
                );
                const auto Key = Gs2::Mission::Domain::Model::FCounterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Gs2->Cache->Put(
                    Gs2::Mission::Model::FCounter::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
                Gs2->Cache->ClearListCache(
                    Gs2::Mission::Model::FComplete::TypeName,
                    ParentKey.Replace(TEXT("Counter"), TEXT("Complete"))
                );
            }{
                for (auto Item : *ResultModel->GetChangedCompletes())
                {
                    const auto ParentKey = Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        "Complete"
                    );
                    const auto Key = Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                        Item->GetMissionGroupName()
                    );
                }
            }
        }
        if (Method == "SetCounterByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Mission::Request::FSetCounterByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Mission::Result::FSetCounterByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Counter"
                );
                const auto Key = Gs2::Mission::Domain::Model::FCounterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Gs2->Cache->Put(
                    Gs2::Mission::Model::FCounter::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }{
                for (auto Item : *ResultModel->GetChangedCompletes())
                {
                    const auto ParentKey = Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        "Complete"
                    );
                    const auto Key = Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                        Item->GetMissionGroupName()
                    );
                }
            }
        }
    }

    void FGs2MissionDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "ReceiveByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Mission::Request::FReceiveByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Mission::Result::FReceiveByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Complete"
                );
                const auto Key = Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetMissionGroupName()
                );
                Gs2->Cache->Put(
                    Gs2::Mission::Model::FComplete::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    ResultModel->GetItem()->GetNextResetAt().IsSet() && *ResultModel->GetItem()->GetNextResetAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItem()->GetNextResetAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "DecreaseCounterByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Mission::Request::FDecreaseCounterByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Mission::Result::FDecreaseCounterByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Counter"
                );
                const auto Key = Gs2::Mission::Domain::Model::FCounterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Gs2->Cache->Put(
                    Gs2::Mission::Model::FCounter::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }{
                for (auto Item : *ResultModel->GetChangedCompletes())
                {
                    const auto ParentKey = Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        "Complete"
                    );
                    const auto Key = Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                        Item->GetMissionGroupName()
                    );
                }
            }
        }
    }

    void FGs2MissionDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
        if (Method == "revert_receive_by_user_id") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Mission::Request::FRevertReceiveByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Mission::Result::FRevertReceiveByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Complete"
                );
                const auto Key = Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetMissionGroupName()
                );
                Gs2->Cache->Put(
                    Gs2::Mission::Model::FComplete::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    ResultModel->GetItem()->GetNextResetAt().IsSet() && *ResultModel->GetItem()->GetNextResetAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItem()->GetNextResetAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "increase_counter_by_user_id") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Mission::Request::FIncreaseCounterByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Mission::Result::FIncreaseCounterByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Counter"
                );
                const auto Key = Gs2::Mission::Domain::Model::FCounterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Gs2->Cache->Put(
                    Gs2::Mission::Model::FCounter::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
                Gs2->Cache->ClearListCache(
                    Gs2::Mission::Model::FComplete::TypeName,
                    ParentKey.Replace(TEXT("Counter"), TEXT("Complete"))
                );
            }{
                for (auto Item : *ResultModel->GetChangedCompletes())
                {
                    const auto ParentKey = Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        "Complete"
                    );
                    const auto Key = Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                        Item->GetMissionGroupName()
                    );
                }
            }
        }
        if (Method == "set_counter_by_user_id") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Mission::Request::FSetCounterByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Mission::Result::FSetCounterByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Counter"
                );
                const auto Key = Gs2::Mission::Domain::Model::FCounterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Gs2->Cache->Put(
                    Gs2::Mission::Model::FCounter::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }{
                for (auto Item : *ResultModel->GetChangedCompletes())
                {
                    const auto ParentKey = Gs2::Mission::Domain::Model::FUserDomain::CreateCacheParentKey(
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        "Complete"
                    );
                    const auto Key = Gs2::Mission::Domain::Model::FCompleteDomain::CreateCacheKey(
                        Item->GetMissionGroupName()
                    );
                }
            }
        }
    }

    void FGs2MissionDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
        if (Action == "Complete") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            CompleteNotificationEvent.Broadcast(Gs2::Mission::Model::FCompleteNotification::FromJson(PayloadJson));
        }
    }

    FCompleteNotificationEvent& FGs2MissionDomain::OnCompleteNotification()
    {
        return CompleteNotificationEvent;
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

