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

#include "Chat/Domain/Model/UserAccessToken.h"
#include "Chat/Domain/Model/User.h"
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
#include "Chat/Model/Cache/Room.h"
#include "Chat/Model/Cache/Message.h"
#include "Chat/Model/Cache/Subscribe.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Chat::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Chat::Domain::FGs2ChatDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Chat::FGs2ChatRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Chat::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const FUserAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FUserAccessTokenDomain::FCreateRoomTask::FCreateRoomTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FCreateRoomRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FCreateRoomTask::FCreateRoomTask(
        const FCreateRoomTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FCreateRoomTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->CreateRoom(
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


        Gs2::Chat::Model::Cache::FRoomCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Chat::Domain::Model::FRoomAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetName(),
            ResultModel->GetItem()->GetPassword()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FCreateRoomTask>> FUserAccessTokenDomain::CreateRoom(
        Request::FCreateRoomRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateRoomTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Chat::Domain::Model::FRoomAccessTokenDomain> FUserAccessTokenDomain::Room(
        const FString RoomName,
        const TOptional<FString> Password
    )
    {
        return MakeShared<Gs2::Chat::Domain::Model::FRoomAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            RoomName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RoomName),
            Password
        );
    }

    Gs2::Chat::Domain::Iterator::FDescribeSubscribesIteratorPtr FUserAccessTokenDomain::Subscribes(
        const TOptional<FString> RoomNamePrefix
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Iterator::FDescribeSubscribesIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            RoomNamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeSubscribes(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Chat::Model::FSubscribe::TypeName,
            Gs2::Chat::Model::Cache::FSubscribeCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserAccessTokenDomain::UnsubscribeSubscribes(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Chat::Model::FSubscribe::TypeName,
            Gs2::Chat::Model::Cache::FSubscribeCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserAccessTokenDomain::FCollectSubscribesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Chat::Model::FSubscribePtr>>, public TSharedFromThis<FCollectSubscribesTask>
    {
        const TSharedPtr<FUserAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> OnCollected;
    const TOptional<FString> QueryRoomNamePrefix;
    public:
        explicit FCollectSubscribesTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> OnCollected,const TOptional<FString> RoomNamePrefix) : Self(Self), OnCollected(OnCollected), QueryRoomNamePrefix(RoomNamePrefix) {}
        FCollectSubscribesTask(const FCollectSubscribesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryRoomNamePrefix(From.QueryRoomNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Chat::Model::FSubscribePtr>>> Result) override
        {
            TArray<Gs2::Chat::Model::FSubscribePtr> Items;
            auto Iterator = Self->Subscribes(QueryRoomNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Chat::Model::FSubscribePtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeSubscribes(
        TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> Callback,const TOptional<FString> RoomNamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Chat::Domain::FGs2ChatDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryRoomNamePrefix = RoomNamePrefix;
        const auto Parent = Gs2::Chat::Model::Cache::FSubscribeCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Chat::Model::FSubscribe::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Chat::Model::FSubscribePtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Chat::Model::FSubscribe>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryRoomNamePrefix, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FUserAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSubscribesTask>>(Domain, Callback, QueryRoomNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserAccessTokenDomain::InvalidateSubscribes(const TOptional<FString> RoomNamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Chat::Model::FSubscribe::TypeName,
            Gs2::Chat::Model::Cache::FSubscribeCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FUserAccessTokenDomain::FSubscribeSubscribesWithInitialCallTask::FSubscribeSubscribesWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> Callback,const TOptional<FString> RoomNamePrefix) : Self(Self), Callback(Callback), QueryRoomNamePrefix(RoomNamePrefix) {}
    FUserAccessTokenDomain::FSubscribeSubscribesWithInitialCallTask::FSubscribeSubscribesWithInitialCallTask(const FSubscribeSubscribesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryRoomNamePrefix(From.QueryRoomNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeSubscribesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSubscribesTask>>(Self, TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)>(), QueryRoomNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeSubscribes(Callback, QueryRoomNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeSubscribesWithInitialCallTask>> FUserAccessTokenDomain::SubscribeSubscribesWithInitialCall(TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> Callback,const TOptional<FString> RoomNamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeSubscribesWithInitialCallTask>>(this->AsShared(), Callback, RoomNamePrefix);
    }

    TSharedPtr<Gs2::Chat::Domain::Model::FSubscribeAccessTokenDomain> FUserAccessTokenDomain::Subscribe(
        const FString RoomName
    )
    {
        return MakeShared<Gs2::Chat::Domain::Model::FSubscribeAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            RoomName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RoomName)
        );
    }

    FString FUserAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserAccessTokenDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
