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

#include "Inbox/Domain/Gs2Inbox.h"
#include "Inbox/Domain/Model/Namespace.h"
#include "Inbox/Domain/Model/User.h"
#include "Inbox/Domain/Model/UserAccessToken.h"
#include "Inbox/Domain/Model/Message.h"
#include "Inbox/Domain/Model/CurrentMessageMaster.h"
#include "Inbox/Domain/Model/GlobalMessageMaster.h"
#include "Inbox/Domain/Model/GlobalMessage.h"
#include "Inbox/Domain/Model/Received.h"

namespace Gs2::Inbox::Domain
{

    FGs2InboxDomain::FGs2InboxDomain(
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
        Client(MakeShared<Gs2::Inbox::FGs2InboxRestClient>(Session)),
        ParentKey("inbox")
    {
    }

    FGs2InboxDomain::FGs2InboxDomain(
        const FGs2InboxDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2InboxDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2InboxDomain> Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2InboxDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2InboxDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("inbox:Namespace");
                const auto Key = Gs2::Inbox::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Inbox::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Inbox::Domain::Model::FNamespaceDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2InboxDomain::FCreateNamespaceTask>> FGs2InboxDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    Gs2::Inbox::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2InboxDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Inbox::Domain::Iterator::FDescribeNamespacesIterator>(
            Cache,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2InboxDomain::SubscribeNamespaces(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::Inbox::Model::FNamespace::TypeName,
            "inbox:Namespace",
            Callback
        );
    }

    void FGs2InboxDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::Inbox::Model::FNamespace::TypeName,
            "inbox:Namespace",
            CallbackID
        );
    }

    TSharedPtr<Gs2::Inbox::Domain::Model::FNamespaceDomain> FGs2InboxDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::Inbox::Domain::Model::FNamespaceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2InboxDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "SendMessageByUserId") {
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
            const auto RequestModel = Gs2::Inbox::Request::FSendMessageByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inbox::Result::FSendMessageByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Message"
                );
                const auto Key = Gs2::Inbox::Domain::Model::FMessageDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Put(
                    Gs2::Inbox::Model::FMessage::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    ResultModel->GetItem()->GetExpiresAt().IsSet() && *ResultModel->GetItem()->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItem()->GetExpiresAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2InboxDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "OpenMessageByUserId") {
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
            const auto RequestModel = Gs2::Inbox::Request::FOpenMessageByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inbox::Result::FOpenMessageByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Message"
                );
                const auto Key = Gs2::Inbox::Domain::Model::FMessageDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Delete(Gs2::Inbox::Model::FMessage::TypeName, ParentKey, Key);
                Cache->ClearListCache(
                    Gs2::Inbox::Model::FMessage::TypeName,
                    ParentKey
                );
            }
        }
        if (Method == "DeleteMessageByUserId") {
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
            const auto RequestModel = Gs2::Inbox::Request::FDeleteMessageByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inbox::Result::FDeleteMessageByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Message"
                );
                const auto Key = Gs2::Inbox::Domain::Model::FMessageDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Delete(Gs2::Inbox::Model::FMessage::TypeName, ParentKey, Key);
            }
        }
    }

    void FGs2InboxDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
        if (Method == "send_message_by_user_id") {
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
            const auto RequestModel = Gs2::Inbox::Request::FSendMessageByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inbox::Result::FSendMessageByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Message"
                );
                const auto Key = Gs2::Inbox::Domain::Model::FMessageDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Put(
                    Gs2::Inbox::Model::FMessage::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    ResultModel->GetItem()->GetExpiresAt().IsSet() && *ResultModel->GetItem()->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItem()->GetExpiresAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2InboxDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
        if (Action == "ReceiveNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            const auto ListParentKey = Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                PayloadJson->GetStringField("namespaceName"),
                PayloadJson->GetStringField("userId"),
                "Message"
            );
            Cache->ClearListCache(Gs2::Inbox::Model::FMessage::TypeName, ListParentKey);
            ReceiveNotificationEvent.Broadcast(Gs2::Inbox::Model::FReceiveNotification::FromJson(PayloadJson));
        }
    }

    FReceiveNotificationEvent& FGs2InboxDomain::OnReceiveNotification()
    {
        return ReceiveNotificationEvent;
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

