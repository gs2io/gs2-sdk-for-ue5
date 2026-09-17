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

#include "Inventory/Domain/Model/InventoryModelMaster.h"
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
#include "Inventory/Model/Cache/InventoryModelMaster.h"
#include "Inventory/Model/Cache/ItemModelMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Inventory::Domain::Model
{

    FInventoryModelMasterDomain::FInventoryModelMasterDomain(
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
            "InventoryModelMaster"
        ))
    {
    }

    FInventoryModelMasterDomain::FInventoryModelMasterDomain(
        const FInventoryModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        InventoryName(From.InventoryName),
        ParentKey(From.ParentKey)
    {

    }

    FInventoryModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FInventoryModelMasterDomain>& Self,
        const Request::FGetInventoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FInventoryModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FInventoryModelMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->GetInventoryModelMaster(
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


        Gs2::Inventory::Model::Cache::FInventoryModelMasterCache::Put(
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

    TSharedPtr<FAsyncTask<FInventoryModelMasterDomain::FGetTask>> FInventoryModelMasterDomain::Get(
        Request::FGetInventoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FInventoryModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FInventoryModelMasterDomain>& Self,
        const Request::FUpdateInventoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FInventoryModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->UpdateInventoryModelMaster(
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


        Gs2::Inventory::Model::Cache::FInventoryModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetInventoryName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FInventoryModelMasterDomain::FUpdateTask>> FInventoryModelMasterDomain::Update(
        Request::FUpdateInventoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FInventoryModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FInventoryModelMasterDomain>& Self,
        const Request::FDeleteInventoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FInventoryModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->DeleteInventoryModelMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            const auto Error = Future->GetTask().Error();
            if (Error.IsValid() && Error->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
            {
                *Result = Self;
                return nullptr;
            }
            return Error;
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();


              Gs2::Inventory::Model::Cache::FInventoryModelMasterCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetInventoryName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FInventoryModelMasterDomain::FDeleteTask>> FInventoryModelMasterDomain::Delete(
        Request::FDeleteInventoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FInventoryModelMasterDomain::FCreateItemModelMasterTask::FCreateItemModelMasterTask(
        const TSharedPtr<FInventoryModelMasterDomain>& Self,
        const Request::FCreateItemModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FInventoryModelMasterDomain::FCreateItemModelMasterTask::FCreateItemModelMasterTask(
        const FCreateItemModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryModelMasterDomain::FCreateItemModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->CreateItemModelMaster(
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
        Gs2::Inventory::Model::Cache::FItemModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetInventoryName(),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Inventory::Domain::Model::FItemModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetInventoryName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FInventoryModelMasterDomain::FCreateItemModelMasterTask>> FInventoryModelMasterDomain::CreateItemModelMaster(
        Request::FCreateItemModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateItemModelMasterTask>>(this->AsShared(), Request);
    }

    Gs2::Inventory::Domain::Iterator::FDescribeItemModelMastersIteratorPtr FInventoryModelMasterDomain::ItemModelMasters(
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Iterator::FDescribeItemModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName,
            InventoryName
        );
    }

    Gs2::Core::Domain::CallbackID FInventoryModelMasterDomain::SubscribeItemModelMasters(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Inventory::Model::FItemModelMaster::TypeName,
            Gs2::Inventory::Model::Cache::FItemModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                InventoryName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FInventoryModelMasterDomain::UnsubscribeItemModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Inventory::Model::FItemModelMaster::TypeName,
            Gs2::Inventory::Model::Cache::FItemModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                InventoryName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FInventoryModelMasterDomain::FCollectItemModelMastersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Inventory::Model::FItemModelMasterPtr>>, public TSharedFromThis<FCollectItemModelMastersTask>
    {
        const TSharedPtr<FInventoryModelMasterDomain> Self;
        const TFunction<void(TArray<Gs2::Inventory::Model::FItemModelMasterPtr>)> OnCollected;

    public:
        explicit FCollectItemModelMastersTask(const TSharedPtr<FInventoryModelMasterDomain>& Self, TFunction<void(TArray<Gs2::Inventory::Model::FItemModelMasterPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectItemModelMastersTask(const FCollectItemModelMastersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Inventory::Model::FItemModelMasterPtr>>> Result) override
        {
            TArray<Gs2::Inventory::Model::FItemModelMasterPtr> Items;
            auto Iterator = Self->ItemModelMasters()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Inventory::Model::FItemModelMasterPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FInventoryModelMasterDomain::SubscribeItemModelMasters(
        TFunction<void(TArray<Gs2::Inventory::Model::FItemModelMasterPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Inventory::Domain::FGs2InventoryDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryInventoryName = InventoryName;
        const auto Parent = Gs2::Inventory::Model::Cache::FItemModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        InventoryName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Inventory::Model::FItemModelMaster::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Inventory::Model::FItemModelMasterPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Inventory::Model::FItemModelMaster>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryInventoryName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FInventoryModelMasterDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryInventoryName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectItemModelMastersTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FInventoryModelMasterDomain::InvalidateItemModelMasters()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Inventory::Model::FItemModelMaster::TypeName,
            Gs2::Inventory::Model::Cache::FItemModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        InventoryName,
        TOptional<int32>()
    )
        );
    }

    FInventoryModelMasterDomain::FSubscribeItemModelMastersWithInitialCallTask::FSubscribeItemModelMastersWithInitialCallTask(const TSharedPtr<FInventoryModelMasterDomain>& Self, TFunction<void(TArray<Gs2::Inventory::Model::FItemModelMasterPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FInventoryModelMasterDomain::FSubscribeItemModelMastersWithInitialCallTask::FSubscribeItemModelMastersWithInitialCallTask(const FSubscribeItemModelMastersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FInventoryModelMasterDomain::FSubscribeItemModelMastersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectItemModelMastersTask>>(Self, TFunction<void(TArray<Gs2::Inventory::Model::FItemModelMasterPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeItemModelMasters(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FInventoryModelMasterDomain::FSubscribeItemModelMastersWithInitialCallTask>> FInventoryModelMasterDomain::SubscribeItemModelMastersWithInitialCall(TFunction<void(TArray<Gs2::Inventory::Model::FItemModelMasterPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeItemModelMastersWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Inventory::Domain::Model::FItemModelMasterDomain> FInventoryModelMasterDomain::ItemModelMaster(
        const FString ItemName
    )
    {
        return MakeShared<Gs2::Inventory::Domain::Model::FItemModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            InventoryName,
            ItemName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ItemName)
        );
    }

    FString FInventoryModelMasterDomain::CreateCacheParentKey(
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

    FString FInventoryModelMasterDomain::CreateCacheKey(
        TOptional<FString> InventoryName
    )
    {
        return FString("") +
            (InventoryName.IsSet() ? *InventoryName : "null");
    }

    FInventoryModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FInventoryModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FInventoryModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FInventoryModelMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::Inventory::Model::Cache::FInventoryModelMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Inventory::Model::Cache::FInventoryModelMasterCache::CreateCacheKey(

            Self->InventoryName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Inventory::Model::FInventoryModelMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Inventory::Model::FInventoryModelMasterPtr Value;
                const auto CacheHit = Gs2::Inventory::Model::Cache::FInventoryModelMasterCache::TryGet(
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
                const auto Error = Gs2::Inventory::Model::Cache::FInventoryModelMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->InventoryName,
                    TOptional<int32>(),
                    [Self](Gs2::Inventory::Model::FInventoryModelMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Inventory::Request::FGetInventoryModelMasterRequest>()
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

    TSharedPtr<FAsyncTask<FInventoryModelMasterDomain::FModelTask>> FInventoryModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FInventoryModelMasterDomain::FModelTask>>(this->AsShared());
    }

    void FInventoryModelMasterDomain::Invalidate()
    {
        Gs2::Inventory::Model::Cache::FInventoryModelMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            InventoryName,
            TOptional<int32>()
        );
    }

    FInventoryModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FInventoryModelMasterDomain>& Self,
        TFunction<void(Gs2::Inventory::Model::FInventoryModelMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FInventoryModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryModelMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FInventoryModelMasterDomain::FSubscribeWithInitialCallTask>> FInventoryModelMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Inventory::Model::FInventoryModelMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FInventoryModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Inventory::Model::FInventoryModelMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Inventory::Model::Cache::FInventoryModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Inventory::Model::Cache::FInventoryModelMasterCache::CreateCacheKey(

            InventoryName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Inventory::Domain::FGs2InventoryDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryInventoryName = InventoryName;
        return Gs2->Cache->Subscribe(
            Gs2::Inventory::Model::FInventoryModelMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Inventory::Model::FInventoryModelMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryInventoryName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FInventoryModelMasterDomain>(
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

    void FInventoryModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Inventory::Model::Cache::FInventoryModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Inventory::Model::Cache::FInventoryModelMasterCache::CreateCacheKey(

            InventoryName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Inventory::Model::FInventoryModelMaster::TypeName,
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
