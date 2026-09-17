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

#include "Chat/Domain/Model/MessageAccessToken.h"
#include "Chat/Domain/Model/Message.h"
#include "Chat/Domain/Model/Namespace.h"
#include "Chat/Domain/Model/Room.h"
#include "Chat/Domain/Model/RoomAccessToken.h"
#include "Chat/Domain/Model/Message.h"
#include "Chat/Domain/Model/MessageAccessToken.h"
#include "Chat/Domain/Model/Subscribe.h"
#include "Chat/Domain/Model/SubscribeAccessToken.h"
#include "Chat/Domain/Model/CategoryModel.h"
#include "Chat/Domain/Model/CategoryModelMaster.h"
#include "Chat/Domain/Model/CurrentModelMaster.h"
#include "Chat/Domain/Model/User.h"
#include "Chat/Domain/Model/UserAccessToken.h"
#include "Chat/Model/Cache/Message.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Chat::Domain::Model
{

    FMessageAccessTokenDomain::FMessageAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Chat::Domain::FGs2ChatDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> RoomName,
        const TOptional<FString> Password,
        const TOptional<FString> MessageName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Chat::FGs2ChatRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        RoomName(RoomName),
        Password(Password),
        MessageName(MessageName),
        ParentKey(Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
            NamespaceName,
            AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
            RoomName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        ))
    {
    }

    FMessageAccessTokenDomain::FMessageAccessTokenDomain(
        const FMessageAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        RoomName(From.RoomName),
        Password(From.Password),
        MessageName(From.MessageName),
        ParentKey(From.ParentKey)
    {

    }

    FMessageAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FMessageAccessTokenDomain>& Self,
        const Request::FGetMessageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMessageAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FMessage>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRoomName(Self->RoomName)
            ->WithMessageName(Self->MessageName)
            ->WithPassword(Self->Password)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->GetMessage(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
        {
            if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
                const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
            }
            Gs2::Chat::Model::Cache::FMessageCache::Put(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                CacheOwnerSnapshotUserId,
                ResultModel->GetItem()->GetRoomName(),
                Request->GetMessageName(),
                CacheOwnerSnapshotTimeOffset,
                ResultModel->GetItem()
            );
        }
        *Result = ResultModel.IsValid() ? ResultModel->GetItem() : nullptr;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMessageAccessTokenDomain::FGetTask>> FMessageAccessTokenDomain::Get(
        Request::FGetMessageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FMessageAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> RoomName,
        TOptional<FString> MessageName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (RoomName.IsSet() ? *RoomName : "null") + ":" +
            (MessageName.IsSet() ? *MessageName : "null") + ":" +
            ChildType;
    }

    FString FMessageAccessTokenDomain::CreateCacheKey(
        TOptional<FString> MessageName
    )
    {
        return FString("") +
            (MessageName.IsSet() ? *MessageName : "null");
    }

    FMessageAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FMessageAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FMessageAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FMessage>> Result
    )
    {
        const auto CacheParentKey = Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->AccessToken->GetUserId() : TOptional<FString>(),
            Self->RoomName,
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto CacheKey = Gs2::Chat::Model::Cache::FMessageCache::CreateCacheKey(Self->MessageName);
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Chat::Model::FMessage::TypeName,
            CacheParentKey,
            CacheKey,
            [this, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Chat::Model::FMessagePtr Value;
                if (Gs2::Chat::Model::Cache::FMessageCache::TryGet(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetUserId() : TOptional<FString>(),
                    Self->RoomName,
                    Self->MessageName,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    &Value
                ))
                {
                    *Result = Value;
                    return nullptr;
                }
                return Gs2::Chat::Model::Cache::FMessageCache::Fetch(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetUserId() : TOptional<FString>(),
                    Self->RoomName,
                    Self->MessageName,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    [this](Gs2::Chat::Model::FMessagePtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(MakeShared<Gs2::Chat::Request::FGetMessageRequest>());
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError())
                        {
                            return Future->GetTask().Error();
                        }
                        *OutItem = Future->GetTask().Result();
                        Future->EnsureCompletion();
                        return nullptr;
                    },
                    Result.Get()
                );
            }
        );
    }

    TSharedPtr<FAsyncTask<FMessageAccessTokenDomain::FModelTask>> FMessageAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMessageAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    FMessageAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FMessageAccessTokenDomain> Self,
        const TFunction<void(Gs2::Chat::Model::FMessagePtr)>& Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FMessageAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Future = Self->Model();
        Future->StartSynchronousTask();
        Future->EnsureCompletion();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto Item = Future->GetTask().Result();
        const auto ID = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(ID);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMessageAccessTokenDomain::FSubscribeWithInitialCallTask>> FMessageAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Chat::Model::FMessagePtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    void FMessageAccessTokenDomain::Invalidate()
    {
        Gs2::Chat::Model::Cache::FMessageCache::Delete(
            Gs2->Cache,
            NamespaceName,
            AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
            RoomName,
            MessageName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    Gs2::Core::Domain::CallbackID FMessageAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Chat::Model::FMessagePtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Chat::Domain::FGs2ChatDomain> WeakService = Service;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryRoomName = RoomName;
        const TOptional<FString> QueryPassword = Password;
        const TOptional<FString> QueryMessageName = MessageName;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const auto OwnerSubscriptionParentKey = Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
            NamespaceName,
            RegisteredUserId,
            RoomName,
            SourceToken.IsValid() ? SourceToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto OwnerSubscriptionKey = Gs2::Chat::Model::Cache::FMessageCache::CreateCacheKey(MessageName);

        return Gs2->Cache->Subscribe(
            Gs2::Chat::Model::FMessage::TypeName,
            OwnerSubscriptionParentKey,
            OwnerSubscriptionKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Chat::Model::FMessage>(obj));
            },
            [WeakGs2, WeakService, QueryNamespaceName, QueryRoomName, QueryPassword, QueryMessageName, SourceToken, RegisteredUserId]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet())
                {
                    return;
                }
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                const auto Domain = MakeShared<FMessageAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot,
                    QueryRoomName,
                    QueryPassword,
                    QueryMessageName
                );
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FMessageAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto OwnerSubscriptionParentKey = Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
            NamespaceName,
            AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
            RoomName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto OwnerSubscriptionKey = Gs2::Chat::Model::Cache::FMessageCache::CreateCacheKey(MessageName);
        Gs2->Cache->Unsubscribe(
            Gs2::Chat::Model::FMessage::TypeName,
            OwnerSubscriptionParentKey,
            OwnerSubscriptionKey,
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
