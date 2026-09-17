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

#include "Inventory/Domain/Model/BigInventory.h"
#include "Inventory/Domain/Model/Namespace.h"
#include "Inventory/Domain/Model/InventoryModelMaster.h"
#include "Inventory/Domain/Model/InventoryModel.h"
#include "Inventory/Domain/Model/ItemModelMaster.h"
#include "Inventory/Domain/Model/ItemModel.h"
#include "Inventory/Domain/Model/SimpleInventoryModelMaster.h"
#include "Inventory/Domain/Model/SimpleInventoryModel.h"
#include "Inventory/Domain/Model/SimpleItemModelMaster.h"
#include "Inventory/Domain/Model/SimpleItemModel.h"
#include "Inventory/Domain/Model/BigInventoryModelMaster.h"
#include "Inventory/Domain/Model/BigInventoryModel.h"
#include "Inventory/Domain/Model/BigItemModelMaster.h"
#include "Inventory/Domain/Model/BigItemModel.h"
#include "Inventory/Domain/Model/CurrentItemModelMaster.h"
#include "Inventory/Domain/Model/Inventory.h"
#include "Inventory/Domain/Model/InventoryAccessToken.h"
#include "Inventory/Domain/Model/ItemSet.h"
#include "Inventory/Domain/Model/ItemSetAccessToken.h"
#include "Inventory/Domain/Model/ReferenceOf.h"
#include "Inventory/Domain/Model/ReferenceOfAccessToken.h"
#include "Inventory/Domain/Model/SimpleInventory.h"
#include "Inventory/Domain/Model/SimpleInventoryAccessToken.h"
#include "Inventory/Domain/Model/SimpleItem.h"
#include "Inventory/Domain/Model/SimpleItemAccessToken.h"
#include "Inventory/Domain/Model/BigInventory.h"
#include "Inventory/Domain/Model/BigInventoryAccessToken.h"
#include "Inventory/Domain/Model/BigItem.h"
#include "Inventory/Domain/Model/BigItemAccessToken.h"
#include "Inventory/Domain/Model/User.h"
#include "Inventory/Domain/Model/UserAccessToken.h"
#include "Inventory/Model/Cache/BigInventory.h"
#include "Inventory/Model/Cache/BigItem.h"
#include "Inventory/Model/Cache/BigItemModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Inventory::Domain::Model
{

    FBigInventoryDomain::FBigInventoryDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> InventoryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Inventory::FGs2InventoryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        InventoryName(InventoryName),
        ParentKey(Gs2::Inventory::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "BigInventory"
        ))
    {
    }

    FBigInventoryDomain::FBigInventoryDomain(
        const FBigInventoryDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        InventoryName(From.InventoryName),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Inventory::Domain::Iterator::FDescribeBigItemsByUserIdIteratorPtr FBigInventoryDomain::BigItems(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Iterator::FDescribeBigItemsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            InventoryName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FBigInventoryDomain::SubscribeBigItems(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Inventory::Model::FBigItem::TypeName,
            Gs2::Inventory::Model::Cache::FBigItemCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                InventoryName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FBigInventoryDomain::UnsubscribeBigItems(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Inventory::Model::FBigItem::TypeName,
            Gs2::Inventory::Model::Cache::FBigItemCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                InventoryName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FBigInventoryDomain::FCollectBigItemsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Inventory::Model::FBigItemPtr>>, public TSharedFromThis<FCollectBigItemsTask>
    {
        const TSharedPtr<FBigInventoryDomain> Self;
        const TFunction<void(TArray<Gs2::Inventory::Model::FBigItemPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectBigItemsTask(const TSharedPtr<FBigInventoryDomain>& Self, TFunction<void(TArray<Gs2::Inventory::Model::FBigItemPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectBigItemsTask(const FCollectBigItemsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Inventory::Model::FBigItemPtr>>> Result) override
        {
            TArray<Gs2::Inventory::Model::FBigItemPtr> Items;
            auto Iterator = Self->BigItems(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Inventory::Model::FBigItemPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FBigInventoryDomain::SubscribeBigItems(
        TFunction<void(TArray<Gs2::Inventory::Model::FBigItemPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Inventory::Domain::FGs2InventoryDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryInventoryName = InventoryName;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Inventory::Model::Cache::FBigItemCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        InventoryName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Inventory::Model::FBigItem::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Inventory::Model::FBigItemPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Inventory::Model::FBigItem>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryInventoryName, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FBigInventoryDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId, QueryInventoryName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectBigItemsTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FBigInventoryDomain::InvalidateBigItems(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Inventory::Model::FBigItem::TypeName,
            Gs2::Inventory::Model::Cache::FBigItemCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        InventoryName,
        TOptional<int32>()
    )
        );
    }

    FBigInventoryDomain::FSubscribeBigItemsWithInitialCallTask::FSubscribeBigItemsWithInitialCallTask(const TSharedPtr<FBigInventoryDomain>& Self, TFunction<void(TArray<Gs2::Inventory::Model::FBigItemPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FBigInventoryDomain::FSubscribeBigItemsWithInitialCallTask::FSubscribeBigItemsWithInitialCallTask(const FSubscribeBigItemsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FBigInventoryDomain::FSubscribeBigItemsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectBigItemsTask>>(Self, TFunction<void(TArray<Gs2::Inventory::Model::FBigItemPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeBigItems(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FBigInventoryDomain::FSubscribeBigItemsWithInitialCallTask>> FBigInventoryDomain::SubscribeBigItemsWithInitialCall(TFunction<void(TArray<Gs2::Inventory::Model::FBigItemPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeBigItemsWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Inventory::Domain::Model::FBigItemDomain> FBigInventoryDomain::BigItem(
        const FString ItemName
    )
    {
        return MakeShared<Gs2::Inventory::Domain::Model::FBigItemDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            InventoryName,
            ItemName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ItemName)
        );
    }

    FString FBigInventoryDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> InventoryName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (InventoryName.IsSet() ? *InventoryName : "null") + ":" +
            ChildType;
    }

    FString FBigInventoryDomain::CreateCacheKey(
        TOptional<FString> InventoryName
    )
    {
        return FString("") +
            (InventoryName.IsSet() ? *InventoryName : "null");
    }

    FBigInventoryDomain::FModelTask::FModelTask(
        const TSharedPtr<FBigInventoryDomain> Self
    ): Self(Self)
    {

    }

    FBigInventoryDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FBigInventoryDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FBigInventory>> Result
    )
    {
        const auto CacheParentKey = Gs2::Inventory::Model::Cache::FBigInventoryCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Inventory::Model::Cache::FBigInventoryCache::CreateCacheKey(

            Self->InventoryName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Inventory::Model::FBigInventory::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Inventory::Model::FBigInventoryPtr Value;
                const auto CacheHit = Gs2::Inventory::Model::Cache::FBigInventoryCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->InventoryName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FBigInventoryDomain::FModelTask>> FBigInventoryDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FBigInventoryDomain::FModelTask>>(this->AsShared());
    }

    void FBigInventoryDomain::Invalidate()
    {
        Gs2::Inventory::Model::Cache::FBigInventoryCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            InventoryName,
            TOptional<int32>()
        );
    }

    FBigInventoryDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FBigInventoryDomain>& Self,
        TFunction<void(Gs2::Inventory::Model::FBigInventoryPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FBigInventoryDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBigInventoryDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Task = Self->Model();
        Task->StartSynchronousTask();
        Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Item = Task->GetTask().Result();
        const auto CallbackId = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBigInventoryDomain::FSubscribeWithInitialCallTask>> FBigInventoryDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Inventory::Model::FBigInventoryPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FBigInventoryDomain::Subscribe(
        TFunction<void(Gs2::Inventory::Model::FBigInventoryPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Inventory::Model::Cache::FBigInventoryCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Inventory::Model::Cache::FBigInventoryCache::CreateCacheKey(

            InventoryName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Inventory::Domain::FGs2InventoryDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryInventoryName = InventoryName;
        return Gs2->Cache->Subscribe(
            Gs2::Inventory::Model::FBigInventory::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Inventory::Model::FBigInventory>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryInventoryName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FBigInventoryDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryInventoryName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FBigInventoryDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Inventory::Model::Cache::FBigInventoryCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Inventory::Model::Cache::FBigInventoryCache::CreateCacheKey(

            InventoryName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Inventory::Model::FBigInventory::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
