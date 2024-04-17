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
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Chat::Domain::Model
{

    FRoomDomain::FRoomDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Chat::Domain::FGs2ChatDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> RoomName,
        const TOptional<FString> Password
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Chat::FGs2ChatRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        RoomName(RoomName),
        Password(Password),
        ParentKey(Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            TOptional<FString>("Singleton"),
            "Room"
        ))
    {
    }

    FRoomDomain::FRoomDomain(
        const FRoomDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        RoomName(From.RoomName),
        Password(From.Password),
        ParentKey(From.ParentKey)
    {

    }

    FRoomDomain::FGetTask::FGetTask(
        const TSharedPtr<FRoomDomain>& Self,
        const Request::FGetRoomRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FRoom>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRoomName(Self->RoomName);
        const auto Future = Self->Client->GetRoom(
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
                    TOptional<FString>("Singleton"),
                    "Room"
                );
                const auto Key = Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Chat::Model::FRoom::TypeName,
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

    TSharedPtr<FAsyncTask<FRoomDomain::FGetTask>> FRoomDomain::Get(
        Request::FGetRoomRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FRoomDomain::FUpdateFromBackendTask::FUpdateFromBackendTask(
        const TSharedPtr<FRoomDomain>& Self,
        const Request::FUpdateRoomFromBackendRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomDomain::FUpdateFromBackendTask::FUpdateFromBackendTask(
        const FUpdateFromBackendTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FUpdateFromBackendTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithRoomName(Self->RoomName)
            ->WithPassword(Self->Password);
        const auto Future = Self->Client->UpdateRoomFromBackend(
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
                    TOptional<FString>("Singleton"),
                    "Room"
                );
                const auto Key = Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Chat::Model::FRoom::TypeName,
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

    TSharedPtr<FAsyncTask<FRoomDomain::FUpdateFromBackendTask>> FRoomDomain::UpdateFromBackend(
        Request::FUpdateRoomFromBackendRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromBackendTask>>(this->AsShared(), Request);
    }

    FRoomDomain::FDeleteFromBackendTask::FDeleteFromBackendTask(
        const TSharedPtr<FRoomDomain>& Self,
        const Request::FDeleteRoomFromBackendRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomDomain::FDeleteFromBackendTask::FDeleteFromBackendTask(
        const FDeleteFromBackendTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FDeleteFromBackendTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithRoomName(Self->RoomName);
        const auto Future = Self->Client->DeleteRoomFromBackend(
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
                    TOptional<FString>("Singleton"),
                    "Room"
                );
                const auto Key = Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Chat::Model::FRoom::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomDomain::FDeleteFromBackendTask>> FRoomDomain::DeleteFromBackend(
        Request::FDeleteRoomFromBackendRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteFromBackendTask>>(this->AsShared(), Request);
    }

    FRoomDomain::FPostTask::FPostTask(
        const TSharedPtr<FRoomDomain>& Self,
        const Request::FPostByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomDomain::FPostTask::FPostTask(
        const FPostTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FPostTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FMessageDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithRoomName(Self->RoomName)
            ->WithPassword(Self->Password);
        const auto Future = Self->Client->PostByUserId(
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
                const auto ParentKey = Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    TOptional<FString>("Singleton"),
                    Self->RoomName,
                    "Message"
                );
                const auto Key = Gs2::Chat::Domain::Model::FMessageDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Chat::Model::FMessage::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Chat::Domain::Model::FMessageDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetRoomName(),
            Request->GetPassword(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomDomain::FPostTask>> FRoomDomain::Post(
        Request::FPostByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPostTask>>(this->AsShared(), Request);
    }

    Gs2::Chat::Domain::Iterator::FDescribeMessagesByUserIdIteratorPtr FRoomDomain::Messages(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Iterator::FDescribeMessagesByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            RoomName,
            Password,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FRoomDomain::SubscribeMessages(
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

    void FRoomDomain::UnsubscribeMessages(
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

    TSharedPtr<Gs2::Chat::Domain::Model::FMessageDomain> FRoomDomain::Message(
        const FString MessageName
    )
    {
        return MakeShared<Gs2::Chat::Domain::Model::FMessageDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            RoomName,
            Password,
            MessageName == TEXT("") ? TOptional<FString>() : TOptional<FString>(MessageName)
        );
    }

    FString FRoomDomain::CreateCacheParentKey(
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

    FString FRoomDomain::CreateCacheKey(
        TOptional<FString> RoomName
    )
    {
        return FString("") +
            (RoomName.IsSet() ? *RoomName : "null");
    }

    FRoomDomain::FModelTask::FModelTask(
        const TSharedPtr<FRoomDomain> Self
    ): Self(Self)
    {

    }

    FRoomDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FModelTask::Action(
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

    TSharedPtr<FAsyncTask<FRoomDomain::FModelTask>> FRoomDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRoomDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FRoomDomain::Subscribe(
        TFunction<void(Gs2::Chat::Model::FRoomPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Chat::Model::FRoom::TypeName,
            ParentKey,
            Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheKey(
                RoomName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Chat::Model::FRoom>(obj));
            }
        );
    }

    void FRoomDomain::Unsubscribe(
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

