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

#include "Inventory/Domain/Model/BigInventoryModel.h"
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
#include "Inventory/Model/Cache/BigInventoryModel.h"
#include "Inventory/Model/Cache/BigItemModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Inventory::Domain::Model
{

    FBigInventoryModelDomain::FBigInventoryModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> InventoryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Inventory::FGs2InventoryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        InventoryName(InventoryName),
        ParentKey(Gs2::Inventory::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "BigInventoryModel"
        ))
    {
    }

    FBigInventoryModelDomain::FBigInventoryModelDomain(
        const FBigInventoryModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        InventoryName(From.InventoryName),
        ParentKey(From.ParentKey)
    {

    }

    FBigInventoryModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FBigInventoryModelDomain>& Self,
        const Request::FGetBigInventoryModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBigInventoryModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBigInventoryModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FBigInventoryModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->GetBigInventoryModel(
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


        Gs2::Inventory::Model::Cache::FBigInventoryModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetInventoryName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBigInventoryModelDomain::FGetTask>> FBigInventoryModelDomain::Get(
        Request::FGetBigInventoryModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    Gs2::Inventory::Domain::Iterator::FDescribeBigItemModelsIteratorPtr FBigInventoryModelDomain::BigItemModels(
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Iterator::FDescribeBigItemModelsIterator>(
            Gs2,
            Client,
            NamespaceName,
            InventoryName
        );
    }

    Gs2::Core::Domain::CallbackID FBigInventoryModelDomain::SubscribeBigItemModels(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Inventory::Model::FBigItemModel::TypeName,
            Gs2::Inventory::Model::Cache::FBigItemModelCache::CreateCacheParentKey(
                NamespaceName,
                InventoryName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FBigInventoryModelDomain::UnsubscribeBigItemModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Inventory::Model::FBigItemModel::TypeName,
            Gs2::Inventory::Model::Cache::FBigItemModelCache::CreateCacheParentKey(
                NamespaceName,
                InventoryName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FBigInventoryModelDomain::FCollectBigItemModelsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Inventory::Model::FBigItemModelPtr>>, public TSharedFromThis<FCollectBigItemModelsTask>
    {
        const TSharedPtr<FBigInventoryModelDomain> Self;
        const TFunction<void(TArray<Gs2::Inventory::Model::FBigItemModelPtr>)> OnCollected;

    public:
        explicit FCollectBigItemModelsTask(const TSharedPtr<FBigInventoryModelDomain>& Self, TFunction<void(TArray<Gs2::Inventory::Model::FBigItemModelPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectBigItemModelsTask(const FCollectBigItemModelsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Inventory::Model::FBigItemModelPtr>>> Result) override
        {
            TArray<Gs2::Inventory::Model::FBigItemModelPtr> Items;
            auto Iterator = Self->BigItemModels()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Inventory::Model::FBigItemModelPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FBigInventoryModelDomain::SubscribeBigItemModels(
        TFunction<void(TArray<Gs2::Inventory::Model::FBigItemModelPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Inventory::Domain::FGs2InventoryDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryInventoryName = InventoryName;
        const auto Parent = Gs2::Inventory::Model::Cache::FBigItemModelCache::CreateCacheParentKey(
        NamespaceName,
        InventoryName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Inventory::Model::FBigItemModel::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Inventory::Model::FBigItemModelPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Inventory::Model::FBigItemModel>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryInventoryName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FBigInventoryModelDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryInventoryName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectBigItemModelsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FBigInventoryModelDomain::InvalidateBigItemModels()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Inventory::Model::FBigItemModel::TypeName,
            Gs2::Inventory::Model::Cache::FBigItemModelCache::CreateCacheParentKey(
        NamespaceName,
        InventoryName,
        TOptional<int32>()
    )
        );
    }

    FBigInventoryModelDomain::FSubscribeBigItemModelsWithInitialCallTask::FSubscribeBigItemModelsWithInitialCallTask(const TSharedPtr<FBigInventoryModelDomain>& Self, TFunction<void(TArray<Gs2::Inventory::Model::FBigItemModelPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FBigInventoryModelDomain::FSubscribeBigItemModelsWithInitialCallTask::FSubscribeBigItemModelsWithInitialCallTask(const FSubscribeBigItemModelsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FBigInventoryModelDomain::FSubscribeBigItemModelsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectBigItemModelsTask>>(Self, TFunction<void(TArray<Gs2::Inventory::Model::FBigItemModelPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeBigItemModels(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FBigInventoryModelDomain::FSubscribeBigItemModelsWithInitialCallTask>> FBigInventoryModelDomain::SubscribeBigItemModelsWithInitialCall(TFunction<void(TArray<Gs2::Inventory::Model::FBigItemModelPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeBigItemModelsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Inventory::Domain::Model::FBigItemModelDomain> FBigInventoryModelDomain::BigItemModel(
        const FString ItemName
    )
    {
        return MakeShared<Gs2::Inventory::Domain::Model::FBigItemModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            InventoryName,
            ItemName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ItemName)
        );
    }

    FString FBigInventoryModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> InventoryName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (InventoryName.IsSet() ? *InventoryName : "null") + ":" +
            ChildType;
    }

    FString FBigInventoryModelDomain::CreateCacheKey(
        TOptional<FString> InventoryName
    )
    {
        return FString("") +
            (InventoryName.IsSet() ? *InventoryName : "null");
    }

    FBigInventoryModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FBigInventoryModelDomain> Self
    ): Self(Self)
    {

    }

    FBigInventoryModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FBigInventoryModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FBigInventoryModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Inventory::Model::Cache::FBigInventoryModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Inventory::Model::Cache::FBigInventoryModelCache::CreateCacheKey(

            Self->InventoryName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Inventory::Model::FBigInventoryModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Inventory::Model::FBigInventoryModelPtr Value;
                const auto CacheHit = Gs2::Inventory::Model::Cache::FBigInventoryModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->InventoryName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Inventory::Model::Cache::FBigInventoryModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->InventoryName,
                    TOptional<int32>(),
                    [Self](Gs2::Inventory::Model::FBigInventoryModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Inventory::Request::FGetBigInventoryModelRequest>()
                        );
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError()) return Future->GetTask().Error();
                        *OutItem = Future->GetTask().Result();
                        Future->EnsureCompletion();
                        return nullptr;
                    },
                    &Value
                );
                if (Error.IsValid()) return Error;
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FBigInventoryModelDomain::FModelTask>> FBigInventoryModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FBigInventoryModelDomain::FModelTask>>(this->AsShared());
    }

    void FBigInventoryModelDomain::Invalidate()
    {
        Gs2::Inventory::Model::Cache::FBigInventoryModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            InventoryName,
            TOptional<int32>()
        );
    }

    FBigInventoryModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FBigInventoryModelDomain>& Self,
        TFunction<void(Gs2::Inventory::Model::FBigInventoryModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FBigInventoryModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBigInventoryModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FBigInventoryModelDomain::FSubscribeWithInitialCallTask>> FBigInventoryModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Inventory::Model::FBigInventoryModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FBigInventoryModelDomain::Subscribe(
        TFunction<void(Gs2::Inventory::Model::FBigInventoryModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Inventory::Model::Cache::FBigInventoryModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Inventory::Model::Cache::FBigInventoryModelCache::CreateCacheKey(

            InventoryName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Inventory::Domain::FGs2InventoryDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryInventoryName = InventoryName;
        return Gs2->Cache->Subscribe(
            Gs2::Inventory::Model::FBigInventoryModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Inventory::Model::FBigInventoryModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryInventoryName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FBigInventoryModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryInventoryName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FBigInventoryModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Inventory::Model::Cache::FBigInventoryModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Inventory::Model::Cache::FBigInventoryModelCache::CreateCacheKey(

            InventoryName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Inventory::Model::FBigInventoryModel::TypeName,
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
