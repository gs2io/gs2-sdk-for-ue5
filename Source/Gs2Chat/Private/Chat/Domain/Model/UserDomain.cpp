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
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Chat::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Chat::Domain::FGs2ChatDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Chat::FGs2ChatRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Chat::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Chat::Domain::Iterator::FDescribeRoomsIteratorPtr FUserDomain::Rooms(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Iterator::FDescribeRoomsIterator>(
            Gs2,
            Client,
            NamespaceName,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeRooms(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Chat::Model::FRoom::TypeName,
            Gs2::Chat::Model::Cache::FRoomCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeRooms(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Chat::Model::FRoom::TypeName,
            Gs2::Chat::Model::Cache::FRoomCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectRoomsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Chat::Model::FRoomPtr>>, public TSharedFromThis<FCollectRoomsTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Chat::Model::FRoomPtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectRoomsTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FRoomPtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectRoomsTask(const FCollectRoomsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Chat::Model::FRoomPtr>>> Result) override
        {
            TArray<Gs2::Chat::Model::FRoomPtr> Items;
            auto Iterator = Self->Rooms(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Chat::Model::FRoomPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeRooms(
        TFunction<void(TArray<Gs2::Chat::Model::FRoomPtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Chat::Domain::FGs2ChatDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Chat::Model::Cache::FRoomCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Chat::Model::FRoom::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Chat::Model::FRoomPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Chat::Model::FRoom>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRoomsTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateRooms(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Chat::Model::FRoom::TypeName,
            Gs2::Chat::Model::Cache::FRoomCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeRoomsWithInitialCallTask::FSubscribeRoomsWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FRoomPtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FUserDomain::FSubscribeRoomsWithInitialCallTask::FSubscribeRoomsWithInitialCallTask(const FSubscribeRoomsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeRoomsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRoomsTask>>(Self, TFunction<void(TArray<Gs2::Chat::Model::FRoomPtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeRooms(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeRoomsWithInitialCallTask>> FUserDomain::SubscribeRoomsWithInitialCall(TFunction<void(TArray<Gs2::Chat::Model::FRoomPtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeRoomsWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Chat::Domain::Model::FRoomDomain> FUserDomain::Room(
        const FString RoomName,
        const TOptional<FString> Password
    )
    {
        return MakeShared<Gs2::Chat::Domain::Model::FRoomDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            RoomName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RoomName),
            Password
        );
    }

    Gs2::Chat::Domain::Iterator::FDescribeSubscribesByUserIdIteratorPtr FUserDomain::Subscribes(
        const TOptional<FString> RoomNamePrefix,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Iterator::FDescribeSubscribesByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            RoomNamePrefix,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeSubscribes(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Chat::Model::FSubscribe::TypeName,
            Gs2::Chat::Model::Cache::FSubscribeCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeSubscribes(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Chat::Model::FSubscribe::TypeName,
            Gs2::Chat::Model::Cache::FSubscribeCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectSubscribesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Chat::Model::FSubscribePtr>>, public TSharedFromThis<FCollectSubscribesTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> OnCollected;
    const TOptional<FString> QueryRoomNamePrefix;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectSubscribesTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> OnCollected,const TOptional<FString> RoomNamePrefix,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryRoomNamePrefix(RoomNamePrefix), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectSubscribesTask(const FCollectSubscribesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryRoomNamePrefix(From.QueryRoomNamePrefix), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Chat::Model::FSubscribePtr>>> Result) override
        {
            TArray<Gs2::Chat::Model::FSubscribePtr> Items;
            auto Iterator = Self->Subscribes(QueryRoomNamePrefix, QueryTimeOffsetToken)->begin();
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

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeSubscribes(
        TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> Callback,const TOptional<FString> RoomNamePrefix,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Chat::Domain::FGs2ChatDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryRoomNamePrefix = RoomNamePrefix;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Chat::Model::Cache::FSubscribeCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
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
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryRoomNamePrefix, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSubscribesTask>>(Domain, Callback, QueryRoomNamePrefix, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateSubscribes(const TOptional<FString> RoomNamePrefix,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Chat::Model::FSubscribe::TypeName,
            Gs2::Chat::Model::Cache::FSubscribeCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeSubscribesWithInitialCallTask::FSubscribeSubscribesWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> Callback,const TOptional<FString> RoomNamePrefix,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryRoomNamePrefix(RoomNamePrefix), QueryTimeOffsetToken(TimeOffsetToken) {}
    FUserDomain::FSubscribeSubscribesWithInitialCallTask::FSubscribeSubscribesWithInitialCallTask(const FSubscribeSubscribesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryRoomNamePrefix(From.QueryRoomNamePrefix), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeSubscribesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSubscribesTask>>(Self, TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)>(), QueryRoomNamePrefix, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeSubscribes(Callback, QueryRoomNamePrefix, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeSubscribesWithInitialCallTask>> FUserDomain::SubscribeSubscribesWithInitialCall(TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> Callback,const TOptional<FString> RoomNamePrefix,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeSubscribesWithInitialCallTask>>(this->AsShared(), Callback, RoomNamePrefix, TimeOffsetToken);
    }

    Gs2::Chat::Domain::Iterator::FDescribeSubscribesByRoomNameIteratorPtr FUserDomain::SubscribesByRoomName(
        const FString RoomName
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Iterator::FDescribeSubscribesByRoomNameIterator>(
            Gs2,
            Client,
            NamespaceName,
            RoomName
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeSubscribesByRoomName(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Chat::Model::FSubscribe::TypeName,
            Gs2::Chat::Model::Cache::FSubscribeCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeSubscribesByRoomName(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Chat::Model::FSubscribe::TypeName,
            Gs2::Chat::Model::Cache::FSubscribeCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectSubscribesByRoomNameTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Chat::Model::FSubscribePtr>>, public TSharedFromThis<FCollectSubscribesByRoomNameTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> OnCollected;
    const FString QueryRoomName;
    public:
        explicit FCollectSubscribesByRoomNameTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> OnCollected,const FString RoomName) : Self(Self), OnCollected(OnCollected), QueryRoomName(RoomName) {}
        FCollectSubscribesByRoomNameTask(const FCollectSubscribesByRoomNameTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryRoomName(From.QueryRoomName) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Chat::Model::FSubscribePtr>>> Result) override
        {
            TArray<Gs2::Chat::Model::FSubscribePtr> Items;
            auto Iterator = Self->SubscribesByRoomName(QueryRoomName)->begin();
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

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeSubscribesByRoomName(
        TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> Callback,const FString RoomName
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Chat::Domain::FGs2ChatDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryRoomName = RoomName;
        const auto Parent = Gs2::Chat::Model::Cache::FSubscribeCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
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
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryRoomName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSubscribesByRoomNameTask>>(Domain, Callback, QueryRoomName);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateSubscribesByRoomName(const FString RoomName)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Chat::Model::FSubscribe::TypeName,
            Gs2::Chat::Model::Cache::FSubscribeCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeSubscribesByRoomNameWithInitialCallTask::FSubscribeSubscribesByRoomNameWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> Callback,const FString RoomName) : Self(Self), Callback(Callback), QueryRoomName(RoomName) {}
    FUserDomain::FSubscribeSubscribesByRoomNameWithInitialCallTask::FSubscribeSubscribesByRoomNameWithInitialCallTask(const FSubscribeSubscribesByRoomNameWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryRoomName(From.QueryRoomName) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeSubscribesByRoomNameWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSubscribesByRoomNameTask>>(Self, TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)>(), QueryRoomName);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeSubscribesByRoomName(Callback, QueryRoomName);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeSubscribesByRoomNameWithInitialCallTask>> FUserDomain::SubscribeSubscribesByRoomNameWithInitialCall(TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> Callback,const FString RoomName)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeSubscribesByRoomNameWithInitialCallTask>>(this->AsShared(), Callback, RoomName);
    }

    TSharedPtr<Gs2::Chat::Domain::Model::FSubscribeDomain> FUserDomain::Subscribe(
        const FString RoomName
    )
    {
        return MakeShared<Gs2::Chat::Domain::Model::FSubscribeDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            RoomName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RoomName)
        );
    }

    FString FUserDomain::CreateCacheParentKey(
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

    FString FUserDomain::CreateCacheKey(
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
