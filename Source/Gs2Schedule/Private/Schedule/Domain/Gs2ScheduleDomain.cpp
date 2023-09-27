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

#include "Schedule/Domain/Gs2Schedule.h"
#include "Schedule/Domain/Model/Namespace.h"
#include "Schedule/Domain/Model/EventMaster.h"
#include "Schedule/Domain/Model/Trigger.h"
#include "Schedule/Domain/Model/Event.h"
#include "Schedule/Domain/Model/CurrentEventMaster.h"
#include "Schedule/Domain/Model/User.h"
#include "Schedule/Domain/Model/UserAccessToken.h"

namespace Gs2::Schedule::Domain
{

    FGs2ScheduleDomain::FGs2ScheduleDomain(
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
        Client(MakeShared<Gs2::Schedule::FGs2ScheduleRestClient>(Session)),
        ParentKey("schedule")
    {
    }

    FGs2ScheduleDomain::FGs2ScheduleDomain(
        const FGs2ScheduleDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2ScheduleDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2ScheduleDomain> Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2ScheduleDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2ScheduleDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("schedule:Namespace");
                const auto Key = Gs2::Schedule::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Schedule::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Schedule::Domain::Model::FNamespaceDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2ScheduleDomain::FCreateNamespaceTask>> FGs2ScheduleDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    Gs2::Schedule::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2ScheduleDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Schedule::Domain::Iterator::FDescribeNamespacesIterator>(
            Cache,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2ScheduleDomain::SubscribeNamespaces(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::Schedule::Model::FNamespace::TypeName,
            "schedule:Namespace",
            Callback
        );
    }

    void FGs2ScheduleDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::Schedule::Model::FNamespace::TypeName,
            "schedule:Namespace",
            CallbackID
        );
    }

    TSharedPtr<Gs2::Schedule::Domain::Model::FNamespaceDomain> FGs2ScheduleDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::Schedule::Domain::Model::FNamespaceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2ScheduleDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "TriggerByUserId") {
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
            const auto RequestModel = Gs2::Schedule::Request::FTriggerByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Schedule::Result::FTriggerByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Schedule::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Trigger"
                );
                const auto Key = Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Put(
                    Gs2::Schedule::Model::FTrigger::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
                Cache->ClearListCache(
                    Gs2::Schedule::Model::FEvent::TypeName,
                    ParentKey.Replace(TEXT("Trigger"), TEXT("Event"))
                );
            }
        }
    }

    void FGs2ScheduleDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "DeleteTriggerByUserId") {
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
            const auto RequestModel = Gs2::Schedule::Request::FDeleteTriggerByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Schedule::Result::FDeleteTriggerByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Schedule::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Trigger"
                );
                const auto Key = Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Delete(Gs2::Schedule::Model::FTrigger::TypeName, ParentKey, Key);
            }
        }
    }

    void FGs2ScheduleDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
        if (Method == "trigger_by_user_id") {
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
            const auto RequestModel = Gs2::Schedule::Request::FTriggerByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Schedule::Result::FTriggerByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Schedule::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Trigger"
                );
                const auto Key = Gs2::Schedule::Domain::Model::FTriggerDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Put(
                    Gs2::Schedule::Model::FTrigger::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
                Cache->ClearListCache(
                    Gs2::Schedule::Model::FEvent::TypeName,
                    ParentKey.Replace(TEXT("Trigger"), TEXT("Event"))
                );
            }
        }
    }

    void FGs2ScheduleDomain::HandleNotification(
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

