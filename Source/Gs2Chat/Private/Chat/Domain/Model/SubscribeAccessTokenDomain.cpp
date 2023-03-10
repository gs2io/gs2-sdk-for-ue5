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

#include "Chat/Domain/Model/SubscribeAccessToken.h"
#include "Chat/Domain/Model/Subscribe.h"
#include "Chat/Domain/Model/Namespace.h"
#include "Chat/Domain/Model/Room.h"
#include "Chat/Domain/Model/RoomAccessToken.h"
#include "Chat/Domain/Model/Message.h"
#include "Chat/Domain/Model/MessageAccessToken.h"
#include "Chat/Domain/Model/Subscribe.h"
#include "Chat/Domain/Model/SubscribeAccessToken.h"
#include "Chat/Domain/Model/User.h"
#include "Chat/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Chat::Domain::Model
{

    FSubscribeAccessTokenDomain::FSubscribeAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> RoomName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Chat::FGs2ChatRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        RoomName(RoomName),
        ParentKey(Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Subscribe"
        ))
    {
    }

    FSubscribeAccessTokenDomain::FSubscribeAccessTokenDomain(
        const FSubscribeAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FSubscribeAccessTokenDomain::FSubscribeTask::FSubscribeTask(
        const TSharedPtr<FSubscribeAccessTokenDomain> Self,
        const Request::FSubscribeRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSubscribeAccessTokenDomain::FSubscribeTask::FSubscribeTask(
        const FSubscribeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeAccessTokenDomain::FSubscribeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FSubscribeAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithRoomName(Self->RoomName);
        const auto Future = Self->Client->Subscribe(
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
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Subscribe"
                );
                const auto Key = Gs2::Chat::Domain::Model::FSubscribeDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRoomName()
                );
                Self->Cache->Put<Gs2::Chat::Model::FSubscribe>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSubscribeAccessTokenDomain::FSubscribeTask>> FSubscribeAccessTokenDomain::Subscribe(
        Request::FSubscribeRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeTask>>(this->AsShared(), Request);
    }

    FSubscribeAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FSubscribeAccessTokenDomain> Self,
        const Request::FGetSubscribeRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSubscribeAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FSubscribe>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithRoomName(Self->RoomName);
        const auto Future = Self->Client->GetSubscribe(
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
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Subscribe"
                );
                const auto Key = Gs2::Chat::Domain::Model::FSubscribeDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRoomName()
                );
                Self->Cache->Put<Gs2::Chat::Model::FSubscribe>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSubscribeAccessTokenDomain::FGetTask>> FSubscribeAccessTokenDomain::Get(
        Request::FGetSubscribeRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FSubscribeAccessTokenDomain::FUpdateNotificationTypeTask::FUpdateNotificationTypeTask(
        const TSharedPtr<FSubscribeAccessTokenDomain> Self,
        const Request::FUpdateNotificationTypeRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSubscribeAccessTokenDomain::FUpdateNotificationTypeTask::FUpdateNotificationTypeTask(
        const FUpdateNotificationTypeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeAccessTokenDomain::FUpdateNotificationTypeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FSubscribeAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithRoomName(Self->RoomName);
        const auto Future = Self->Client->UpdateNotificationType(
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
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Subscribe"
                );
                const auto Key = Gs2::Chat::Domain::Model::FSubscribeDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRoomName()
                );
                Self->Cache->Put<Gs2::Chat::Model::FSubscribe>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSubscribeAccessTokenDomain::FUpdateNotificationTypeTask>> FSubscribeAccessTokenDomain::UpdateNotificationType(
        Request::FUpdateNotificationTypeRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateNotificationTypeTask>>(this->AsShared(), Request);
    }

    FSubscribeAccessTokenDomain::FUnsubscribeTask::FUnsubscribeTask(
        const TSharedPtr<FSubscribeAccessTokenDomain> Self,
        const Request::FUnsubscribeRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSubscribeAccessTokenDomain::FUnsubscribeTask::FUnsubscribeTask(
        const FUnsubscribeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeAccessTokenDomain::FUnsubscribeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FSubscribeAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithRoomName(Self->RoomName);
        const auto Future = Self->Client->Unsubscribe(
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
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Subscribe"
                );
                const auto Key = Gs2::Chat::Domain::Model::FSubscribeDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRoomName()
                );
                Self->Cache->Delete<Gs2::Chat::Model::FSubscribe>(ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSubscribeAccessTokenDomain::FUnsubscribeTask>> FSubscribeAccessTokenDomain::Unsubscribe(
        Request::FUnsubscribeRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUnsubscribeTask>>(this->AsShared(), Request);
    }

    FString FSubscribeAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> RoomName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (RoomName.IsSet() ? *RoomName : "null") + ":" +
            ChildType;
    }

    FString FSubscribeAccessTokenDomain::CreateCacheKey(
        TOptional<FString> RoomName
    )
    {
        return FString() +
            (RoomName.IsSet() ? *RoomName : "null");
    }

    FSubscribeAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FSubscribeAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FSubscribeAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FSubscribe>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Chat::Model::FSubscribe>(
            Self->ParentKey,
            Gs2::Chat::Domain::Model::FSubscribeDomain::CreateCacheKey(
                Self->RoomName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Chat::Request::FGetSubscribeRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "subscribe")
                    {
                        Self->Cache->Delete<Gs2::Chat::Model::FSubscribe>(
                            Self->ParentKey,
                            Gs2::Chat::Domain::Model::FSubscribeDomain::CreateCacheKey(
                                Self->RoomName
                            )
                        );
                    }
                    else
                    {
                        return Future->GetTask().Error();
                    }
                }
                else
                {
                    return Future->GetTask().Error();
                }
            }
            Value = Self->Cache->Get<Gs2::Chat::Model::FSubscribe>(
                Self->ParentKey,
                Gs2::Chat::Domain::Model::FSubscribeDomain::CreateCacheKey(
                    Self->RoomName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSubscribeAccessTokenDomain::FModelTask>> FSubscribeAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

