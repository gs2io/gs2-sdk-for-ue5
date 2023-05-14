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

    FSubscribeDomain::FSubscribeDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> RoomName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Chat::FGs2ChatRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        RoomName(RoomName),
        ParentKey(Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Subscribe"
        ))
    {
    }

    FSubscribeDomain::FSubscribeDomain(
        const FSubscribeDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FSubscribeDomain::FSubscribeTask::FSubscribeTask(
        const TSharedPtr<FSubscribeDomain> Self,
        const Request::FSubscribeByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSubscribeDomain::FSubscribeTask::FSubscribeTask(
        const FSubscribeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeDomain::FSubscribeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FSubscribeDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithRoomName(Self->RoomName);
        const auto Future = Self->Client->SubscribeByUserId(
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
                    Self->UserId,
                    "Subscribe"
                );
                const auto Key = Gs2::Chat::Domain::Model::FSubscribeDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRoomName()
                );
                Self->Cache->Put(
                    Gs2::Chat::Model::FSubscribe::TypeName,
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

    TSharedPtr<FAsyncTask<FSubscribeDomain::FSubscribeTask>> FSubscribeDomain::Subscribe(
        Request::FSubscribeByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeTask>>(this->AsShared(), Request);
    }

    FSubscribeDomain::FGetTask::FGetTask(
        const TSharedPtr<FSubscribeDomain> Self,
        const Request::FGetSubscribeByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSubscribeDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FSubscribe>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithRoomName(Self->RoomName);
        const auto Future = Self->Client->GetSubscribeByUserId(
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
                    Self->UserId,
                    "Subscribe"
                );
                const auto Key = Gs2::Chat::Domain::Model::FSubscribeDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRoomName()
                );
                Self->Cache->Put(
                    Gs2::Chat::Model::FSubscribe::TypeName,
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

    TSharedPtr<FAsyncTask<FSubscribeDomain::FGetTask>> FSubscribeDomain::Get(
        Request::FGetSubscribeByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FSubscribeDomain::FUpdateNotificationTypeTask::FUpdateNotificationTypeTask(
        const TSharedPtr<FSubscribeDomain> Self,
        const Request::FUpdateNotificationTypeByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSubscribeDomain::FUpdateNotificationTypeTask::FUpdateNotificationTypeTask(
        const FUpdateNotificationTypeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeDomain::FUpdateNotificationTypeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FSubscribeDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithRoomName(Self->RoomName);
        const auto Future = Self->Client->UpdateNotificationTypeByUserId(
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
                    Self->UserId,
                    "Subscribe"
                );
                const auto Key = Gs2::Chat::Domain::Model::FSubscribeDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRoomName()
                );
                Self->Cache->Put(
                    Gs2::Chat::Model::FSubscribe::TypeName,
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

    TSharedPtr<FAsyncTask<FSubscribeDomain::FUpdateNotificationTypeTask>> FSubscribeDomain::UpdateNotificationType(
        Request::FUpdateNotificationTypeByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateNotificationTypeTask>>(this->AsShared(), Request);
    }

    FSubscribeDomain::FUnsubscribeTask::FUnsubscribeTask(
        const TSharedPtr<FSubscribeDomain> Self,
        const Request::FUnsubscribeByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSubscribeDomain::FUnsubscribeTask::FUnsubscribeTask(
        const FUnsubscribeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeDomain::FUnsubscribeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FSubscribeDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithRoomName(Self->RoomName);
        const auto Future = Self->Client->UnsubscribeByUserId(
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
                    Self->UserId,
                    "Subscribe"
                );
                const auto Key = Gs2::Chat::Domain::Model::FSubscribeDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetRoomName()
                );
                Self->Cache->Delete(Gs2::Chat::Model::FSubscribe::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSubscribeDomain::FUnsubscribeTask>> FSubscribeDomain::Unsubscribe(
        Request::FUnsubscribeByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUnsubscribeTask>>(this->AsShared(), Request);
    }

    FString FSubscribeDomain::CreateCacheParentKey(
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

    FString FSubscribeDomain::CreateCacheKey(
        TOptional<FString> RoomName
    )
    {
        return FString() +
            (RoomName.IsSet() ? *RoomName : "null");
    }

    FSubscribeDomain::FModelTask::FModelTask(
        const TSharedPtr<FSubscribeDomain> Self
    ): Self(Self)
    {

    }

    FSubscribeDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeDomain::FModelTask::Action(
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
                MakeShared<Gs2::Chat::Request::FGetSubscribeByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "subscribe")
                    {
                        Self->Cache->Delete(
                            Gs2::Chat::Model::FSubscribe::TypeName,
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

    TSharedPtr<FAsyncTask<FSubscribeDomain::FModelTask>> FSubscribeDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

