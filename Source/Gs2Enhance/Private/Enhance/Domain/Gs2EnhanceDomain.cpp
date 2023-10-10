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

#include "Enhance/Domain/Gs2Enhance.h"
#include "Enhance/Domain/Model/Namespace.h"
#include "Enhance/Domain/Model/RateModel.h"
#include "Enhance/Domain/Model/RateModelMaster.h"
#include "Enhance/Domain/Model/Enhance.h"
#include "Enhance/Domain/Model/Progress.h"
#include "Enhance/Domain/Model/CurrentRateMaster.h"
#include "Enhance/Domain/Model/User.h"
#include "Enhance/Domain/Model/UserAccessToken.h"

namespace Gs2::Enhance::Domain
{

    FGs2EnhanceDomain::FGs2EnhanceDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Enhance::FGs2EnhanceRestClient>(Session)),
        ParentKey("enhance")
    {
    }

    FGs2EnhanceDomain::FGs2EnhanceDomain(
        const FGs2EnhanceDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2EnhanceDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2EnhanceDomain> Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2EnhanceDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2EnhanceDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("enhance:Namespace");
                const auto Key = Gs2::Enhance::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Enhance::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Enhance::Domain::Model::FNamespaceDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2EnhanceDomain::FCreateNamespaceTask>> FGs2EnhanceDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    FGs2EnhanceDomain::FDumpUserDataTask::FDumpUserDataTask(
        TSharedPtr<FGs2EnhanceDomain> Self,
        const Request::FDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2EnhanceDomain::FDumpUserDataTask::FDumpUserDataTask(
        const FDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2EnhanceDomain::FDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2EnhanceDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2EnhanceDomain::FDumpUserDataTask>> FGs2EnhanceDomain::DumpUserData(
        Request::FDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2EnhanceDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        TSharedPtr<FGs2EnhanceDomain> Self,
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2EnhanceDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const FCheckDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2EnhanceDomain::FCheckDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2EnhanceDomain>> Result
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
        Domain->Url = Domain->Url = ResultModel->GetUrl();
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2EnhanceDomain::FCheckDumpUserDataTask>> FGs2EnhanceDomain::CheckDumpUserData(
        Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2EnhanceDomain::FCleanUserDataTask::FCleanUserDataTask(
        TSharedPtr<FGs2EnhanceDomain> Self,
        const Request::FCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2EnhanceDomain::FCleanUserDataTask::FCleanUserDataTask(
        const FCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2EnhanceDomain::FCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2EnhanceDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2EnhanceDomain::FCleanUserDataTask>> FGs2EnhanceDomain::CleanUserData(
        Request::FCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2EnhanceDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        TSharedPtr<FGs2EnhanceDomain> Self,
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2EnhanceDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const FCheckCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2EnhanceDomain::FCheckCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2EnhanceDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2EnhanceDomain::FCheckCleanUserDataTask>> FGs2EnhanceDomain::CheckCleanUserData(
        Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckCleanUserDataTask>>(this->AsShared(), Request);
    }

    Gs2::Enhance::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2EnhanceDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Enhance::Domain::Iterator::FDescribeNamespacesIterator>(
            Cache,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2EnhanceDomain::SubscribeNamespaces(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::Enhance::Model::FNamespace::TypeName,
            "enhance:Namespace",
            Callback
        );
    }

    void FGs2EnhanceDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::Enhance::Model::FNamespace::TypeName,
            "enhance:Namespace",
            CallbackID
        );
    }

    TSharedPtr<Gs2::Enhance::Domain::Model::FNamespaceDomain> FGs2EnhanceDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::Enhance::Domain::Model::FNamespaceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2EnhanceDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "DirectEnhanceByUserId") {
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
            const auto RequestModel = Gs2::Enhance::Request::FDirectEnhanceByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Enhance::Result::FDirectEnhanceByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Enhance::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "RateModel"
                );
                const auto Key = Gs2::Enhance::Domain::Model::FRateModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Put(
                    Gs2::Enhance::Model::FRateModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "CreateProgressByUserId") {
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
            const auto RequestModel = Gs2::Enhance::Request::FCreateProgressByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Enhance::Result::FCreateProgressByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Enhance::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Progress"
                );
                const auto Key = Gs2::Enhance::Domain::Model::FProgressDomain::CreateCacheKey(
                );
                Cache->Put(
                    Gs2::Enhance::Model::FProgress::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2EnhanceDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "DeleteProgressByUserId") {
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
            const auto RequestModel = Gs2::Enhance::Request::FDeleteProgressByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Enhance::Result::FDeleteProgressByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Enhance::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Progress"
                );
                const auto Key = Gs2::Enhance::Domain::Model::FProgressDomain::CreateCacheKey(
                );
                Cache->Delete(Gs2::Enhance::Model::FProgress::TypeName, ParentKey, Key);
            }
        }
    }

    void FGs2EnhanceDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
        if (Method == "direct_enhance_by_user_id") {
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
            const auto RequestModel = Gs2::Enhance::Request::FDirectEnhanceByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Enhance::Result::FDirectEnhanceByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Enhance::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "RateModel"
                );
                const auto Key = Gs2::Enhance::Domain::Model::FRateModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Put(
                    Gs2::Enhance::Model::FRateModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "create_progress_by_user_id") {
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
            const auto RequestModel = Gs2::Enhance::Request::FCreateProgressByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Enhance::Result::FCreateProgressByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Enhance::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Progress"
                );
                const auto Key = Gs2::Enhance::Domain::Model::FProgressDomain::CreateCacheKey(
                );
                Cache->Put(
                    Gs2::Enhance::Model::FProgress::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2EnhanceDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

