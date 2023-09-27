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

#include "Matchmaking/Domain/Gs2Matchmaking.h"
#include "Matchmaking/Domain/Model/Namespace.h"
#include "Matchmaking/Domain/Model/Gathering.h"
#include "Matchmaking/Domain/Model/RatingModelMaster.h"
#include "Matchmaking/Domain/Model/RatingModel.h"
#include "Matchmaking/Domain/Model/CurrentRatingModelMaster.h"
#include "Matchmaking/Domain/Model/Rating.h"
#include "Matchmaking/Domain/Model/Ballot.h"
#include "Matchmaking/Domain/Model/Vote.h"
#include "Matchmaking/Domain/Model/User.h"
#include "Matchmaking/Domain/Model/UserAccessToken.h"

namespace Gs2::Matchmaking::Domain
{

    FGs2MatchmakingDomain::FGs2MatchmakingDomain(
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
        Client(MakeShared<Gs2::Matchmaking::FGs2MatchmakingRestClient>(Session)),
        ParentKey("matchmaking")
    {
    }

    FGs2MatchmakingDomain::FGs2MatchmakingDomain(
        const FGs2MatchmakingDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2MatchmakingDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2MatchmakingDomain> Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2MatchmakingDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2MatchmakingDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Matchmaking::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("matchmaking:Namespace");
                const auto Key = Gs2::Matchmaking::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Matchmaking::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Matchmaking::Domain::Model::FNamespaceDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2MatchmakingDomain::FCreateNamespaceTask>> FGs2MatchmakingDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    Gs2::Matchmaking::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2MatchmakingDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Iterator::FDescribeNamespacesIterator>(
            Cache,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2MatchmakingDomain::SubscribeNamespaces(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::Matchmaking::Model::FNamespace::TypeName,
            "matchmaking:Namespace",
            Callback
        );
    }

    void FGs2MatchmakingDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::Matchmaking::Model::FNamespace::TypeName,
            "matchmaking:Namespace",
            CallbackID
        );
    }

    TSharedPtr<Gs2::Matchmaking::Domain::Model::FNamespaceDomain> FGs2MatchmakingDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::Matchmaking::Domain::Model::FNamespaceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2MatchmakingDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2MatchmakingDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2MatchmakingDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
    }

    void FGs2MatchmakingDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
        if (Action == "Join") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            JoinNotificationEvent.Broadcast(Gs2::Matchmaking::Model::FJoinNotification::FromJson(PayloadJson));
        }
        if (Action == "Leave") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            LeaveNotificationEvent.Broadcast(Gs2::Matchmaking::Model::FLeaveNotification::FromJson(PayloadJson));
        }
        if (Action == "Complete") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            CompleteNotificationEvent.Broadcast(Gs2::Matchmaking::Model::FCompleteNotification::FromJson(PayloadJson));
        }
        if (Action == "ChangeRatingNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            const auto ListParentKey = Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
                PayloadJson->GetStringField("namespaceName"),
                PayloadJson->GetStringField("userId"),
                "Rating"
            );
            Cache->ClearListCache(Gs2::Matchmaking::Model::FRating::TypeName, ListParentKey);
            ChangeRatingNotificationEvent.Broadcast(Gs2::Matchmaking::Model::FChangeRatingNotification::FromJson(PayloadJson));
        }
    }

    FJoinNotificationEvent& FGs2MatchmakingDomain::OnJoinNotification()
    {
        return JoinNotificationEvent;
    }

    FLeaveNotificationEvent& FGs2MatchmakingDomain::OnLeaveNotification()
    {
        return LeaveNotificationEvent;
    }

    FCompleteNotificationEvent& FGs2MatchmakingDomain::OnCompleteNotification()
    {
        return CompleteNotificationEvent;
    }

    FChangeRatingNotificationEvent& FGs2MatchmakingDomain::OnChangeRatingNotification()
    {
        return ChangeRatingNotificationEvent;
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

