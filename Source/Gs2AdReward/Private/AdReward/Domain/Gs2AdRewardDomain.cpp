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

#include "AdReward/Domain/Gs2AdReward.h"
#include "AdReward/Domain/Model/Namespace.h"
#include "AdReward/Domain/Model/User.h"
#include "AdReward/Domain/Model/UserAccessToken.h"
#include "AdReward/Domain/Model/Point.h"

namespace Gs2::AdReward::Domain
{

    FGs2AdRewardDomain::FGs2AdRewardDomain(
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
        Client(MakeShared<Gs2::AdReward::FGs2AdRewardRestClient>(Session)),
        ParentKey("adReward")
    {
    }

    FGs2AdRewardDomain::FGs2AdRewardDomain(
        const FGs2AdRewardDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2AdRewardDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2AdRewardDomain> Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2AdRewardDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2AdRewardDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::AdReward::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("adReward:Namespace");
                const auto Key = Gs2::AdReward::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::AdReward::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::AdReward::Domain::Model::FNamespaceDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2AdRewardDomain::FCreateNamespaceTask>> FGs2AdRewardDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    Gs2::AdReward::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2AdRewardDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::AdReward::Domain::Iterator::FDescribeNamespacesIterator>(
            Cache,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2AdRewardDomain::SubscribeNamespaces(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::AdReward::Model::FNamespace::TypeName,
            "adReward:Namespace",
            Callback
        );
    }

    void FGs2AdRewardDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::AdReward::Model::FNamespace::TypeName,
            "adReward:Namespace",
            CallbackID
        );
    }

    TSharedPtr<Gs2::AdReward::Domain::Model::FNamespaceDomain> FGs2AdRewardDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::AdReward::Domain::Model::FNamespaceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2AdRewardDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "AcquirePointByUserId") {
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
            const auto RequestModel = Gs2::AdReward::Request::FAcquirePointByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::AdReward::Result::FAcquirePointByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::AdReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Point"
                );
                const auto Key = Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
                );
                Cache->Put(
                    Gs2::AdReward::Model::FPoint::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2AdRewardDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "ConsumePointByUserId") {
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
            const auto RequestModel = Gs2::AdReward::Request::FConsumePointByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::AdReward::Result::FConsumePointByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::AdReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Point"
                );
                const auto Key = Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
                );
                Cache->Put(
                    Gs2::AdReward::Model::FPoint::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2AdRewardDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
        if (Method == "acquire_point_by_user_id") {
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
            const auto RequestModel = Gs2::AdReward::Request::FAcquirePointByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::AdReward::Result::FAcquirePointByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::AdReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Point"
                );
                const auto Key = Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
                );
                Cache->Put(
                    Gs2::AdReward::Model::FPoint::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2AdRewardDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
        if (Action == "ChangePoint") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            const auto ParentKey = Gs2::AdReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                PayloadJson->GetStringField("namespaceName"),
                PayloadJson->GetStringField("userId"),
                "Point"
            );
            const auto Key = Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
            );
            Cache->Delete(Gs2::AdReward::Model::FPoint::TypeName, ParentKey, Key);
            ChangePointNotificationEvent.Broadcast(Gs2::AdReward::Model::FChangePointNotification::FromJson(PayloadJson));
        }
    }

    FChangePointNotificationEvent& FGs2AdRewardDomain::OnChangePointNotification()
    {
        return ChangePointNotificationEvent;
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

