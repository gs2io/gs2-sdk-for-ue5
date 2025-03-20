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

#include "Chat/Domain/Model/RoomAccessToken.h"
#include "Chat/Domain/Model/Room.h"
#include "Chat/Domain/Model/Namespace.h"
#include "Chat/Domain/Model/Room.h"
#include "Chat/Domain/Model/RoomAccessToken.h"
#include "Chat/Domain/Model/Message.h"
#include "Chat/Domain/Model/MessageAccessToken.h"
#include "Chat/Domain/Model/Subscribe.h"
#include "Chat/Domain/Model/SubscribeAccessToken.h"
#include "Chat/Domain/Model/User.h"
#include "Chat/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Chat::Domain::Model
{

    FRoomAccessTokenDomain::FRoomAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Chat::Domain::FGs2ChatDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> RoomName,
        const TOptional<FString> Password
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Chat::FGs2ChatRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        RoomName(RoomName),
        Password(Password),
        ParentKey(Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            TOptional<FString>("Singleton"),
            "Room"
        ))
    {
    }

    FRoomAccessTokenDomain::FRoomAccessTokenDomain(
        const FRoomAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        RoomName(From.RoomName),
        Password(From.Password),
        ParentKey(From.ParentKey)
    {

    }

    FRoomAccessTokenDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FRoomAccessTokenDomain>& Self,
        const Request::FUpdateRoomRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomAccessTokenDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomAccessTokenDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRoomName(Self->RoomName)
            ->WithPassword(Self->Password)
            ->WithAccessToken(Self->AccessToken->GetToken());
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomAccessTokenDomain::FUpdateTask>> FRoomAccessTokenDomain::Update(
        Request::FUpdateRoomRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FRoomAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FRoomAccessTokenDomain>& Self,
        const Request::FDeleteRoomRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRoomName(Self->RoomName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomAccessTokenDomain::FDeleteTask>> FRoomAccessTokenDomain::Delete(
        Request::FDeleteRoomRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FRoomAccessTokenDomain::FPostTask::FPostTask(
        const TSharedPtr<FRoomAccessTokenDomain>& Self,
        const Request::FPostRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomAccessTokenDomain::FPostTask::FPostTask(
        const FPostTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomAccessTokenDomain::FPostTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FMessageAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRoomName(Self->RoomName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithPassword(Self->Password);
        auto Domain = MakeShared<Gs2::Chat::Domain::Model::FMessageAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetRoomName(),
            Request->GetPassword(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomAccessTokenDomain::FPostTask>> FRoomAccessTokenDomain::Post(
        Request::FPostRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPostTask>>(this->AsShared(), Request);
    }

    FRoomAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FRoomAccessTokenDomain>& Self,
        const Request::FGetRoomRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FRoom>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRoomName(Self->RoomName);
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomAccessTokenDomain::FGetTask>> FRoomAccessTokenDomain::Get(
        Request::FGetRoomRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    Gs2::Chat::Domain::Iterator::FDescribeMessagesIteratorPtr FRoomAccessTokenDomain::Messages(
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Iterator::FDescribeMessagesIterator>(
            Gs2,
            Client,
            NamespaceName,
            RoomName,
            AccessToken,
            Password
        );
    }

    Gs2::Core::Domain::CallbackID FRoomAccessTokenDomain::SubscribeMessages(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Chat::Model::FMessage::TypeName,
            Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>("Singleton"),
                RoomName,
                "Message"
            ),
            Callback
        );
    }

    void FRoomAccessTokenDomain::UnsubscribeMessages(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Chat::Model::FMessage::TypeName,
            Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>("Singleton"),
                RoomName,
                "Message"
            ),
            CallbackID
        );
    }

    Gs2::Chat::Domain::Iterator::FDescribeLatestMessagesIteratorPtr FRoomAccessTokenDomain::LatestMessages(
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Iterator::FDescribeLatestMessagesIterator>(
            Gs2,
            Client,
            NamespaceName,
            RoomName,
            AccessToken,
            Password
        );
    }

    Gs2::Core::Domain::CallbackID FRoomAccessTokenDomain::SubscribeLatestMessages(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Chat::Model::FMessage::TypeName,
            Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>("Singleton"),
                RoomName,
                "Message"
            ),
            Callback
        );
    }

    void FRoomAccessTokenDomain::UnsubscribeLatestMessages(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Chat::Model::FMessage::TypeName,
            Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>("Singleton"),
                RoomName,
                "Message"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Chat::Domain::Model::FMessageAccessTokenDomain> FRoomAccessTokenDomain::Message(
        const FString MessageName
    )
    {
        return MakeShared<Gs2::Chat::Domain::Model::FMessageAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            RoomName,
            Password,
            MessageName == TEXT("") ? TOptional<FString>() : TOptional<FString>(MessageName)
        );
    }

    FString FRoomAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> RoomName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (RoomName.IsSet() ? *RoomName : "null") + ":" +
            ChildType;
    }

    FString FRoomAccessTokenDomain::CreateCacheKey(
        TOptional<FString> RoomName
    )
    {
        return FString("") +
            (RoomName.IsSet() ? *RoomName : "null");
    }

    FRoomAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FRoomAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FRoomAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FRoom>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Chat::Model::FRoom> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Chat::Model::FRoom>(
            Self->ParentKey,
            Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheKey(
                Self->RoomName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Chat::Request::FGetRoomRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheKey(
                    Self->RoomName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Chat::Model::FRoom::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "room")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Chat::Model::FRoom>(
                Self->ParentKey,
                Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheKey(
                    Self->RoomName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomAccessTokenDomain::FModelTask>> FRoomAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRoomAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FRoomAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Chat::Model::FRoomPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Chat::Model::FRoom::TypeName,
            ParentKey,
            Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheKey(
                RoomName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Chat::Model::FRoom>(obj));
            }
        );
    }

    void FRoomAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Chat::Model::FRoom::TypeName,
            ParentKey,
            Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheKey(
                RoomName
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

