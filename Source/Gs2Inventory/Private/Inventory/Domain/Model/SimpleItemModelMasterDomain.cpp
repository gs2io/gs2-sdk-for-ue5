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

#include "Inventory/Domain/Model/SimpleItemModelMaster.h"
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
#include "Inventory/Model/Cache/SimpleItemModelMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Inventory::Domain::Model
{

    FSimpleItemModelMasterDomain::FSimpleItemModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> InventoryName,
        const TOptional<FString> ItemName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Inventory::FGs2InventoryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        InventoryName(InventoryName),
        ItemName(ItemName),
        ParentKey(Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain::CreateCacheParentKey(
            NamespaceName,
            InventoryName,
            "SimpleItemModelMaster"
        ))
    {
    }

    FSimpleItemModelMasterDomain::FSimpleItemModelMasterDomain(
        const FSimpleItemModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        InventoryName(From.InventoryName),
        ItemName(From.ItemName),
        ParentKey(From.ParentKey)
    {

    }

    FSimpleItemModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FSimpleItemModelMasterDomain>& Self,
        const Request::FGetSimpleItemModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSimpleItemModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSimpleItemModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FSimpleItemModelMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName);
        const auto Future = Self->Client->GetSimpleItemModelMaster(
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


        Gs2::Inventory::Model::Cache::FSimpleItemModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetInventoryName(),
            Request->GetItemName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSimpleItemModelMasterDomain::FGetTask>> FSimpleItemModelMasterDomain::Get(
        Request::FGetSimpleItemModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FSimpleItemModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FSimpleItemModelMasterDomain>& Self,
        const Request::FUpdateSimpleItemModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSimpleItemModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSimpleItemModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName);
        const auto Future = Self->Client->UpdateSimpleItemModelMaster(
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


        Gs2::Inventory::Model::Cache::FSimpleItemModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetInventoryName(),
            Request->GetItemName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSimpleItemModelMasterDomain::FUpdateTask>> FSimpleItemModelMasterDomain::Update(
        Request::FUpdateSimpleItemModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FSimpleItemModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FSimpleItemModelMasterDomain>& Self,
        const Request::FDeleteSimpleItemModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSimpleItemModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSimpleItemModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName);
        const auto Future = Self->Client->DeleteSimpleItemModelMaster(
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


              Gs2::Inventory::Model::Cache::FSimpleItemModelMasterCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetInventoryName(),
            Request->GetItemName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSimpleItemModelMasterDomain::FDeleteTask>> FSimpleItemModelMasterDomain::Delete(
        Request::FDeleteSimpleItemModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FSimpleItemModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> InventoryName,
        TOptional<FString> ItemName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (InventoryName.IsSet() ? *InventoryName : "null") + ":" +
            (ItemName.IsSet() ? *ItemName : "null") + ":" +
            ChildType;
    }

    FString FSimpleItemModelMasterDomain::CreateCacheKey(
        TOptional<FString> ItemName
    )
    {
        return FString("") +
            (ItemName.IsSet() ? *ItemName : "null");
    }

    FSimpleItemModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FSimpleItemModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FSimpleItemModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSimpleItemModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FSimpleItemModelMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::Inventory::Model::Cache::FSimpleItemModelMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->InventoryName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Inventory::Model::Cache::FSimpleItemModelMasterCache::CreateCacheKey(

            Self->ItemName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Inventory::Model::FSimpleItemModelMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Inventory::Model::FSimpleItemModelMasterPtr Value;
                const auto CacheHit = Gs2::Inventory::Model::Cache::FSimpleItemModelMasterCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->InventoryName,
                    Self->ItemName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Inventory::Model::Cache::FSimpleItemModelMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->InventoryName,
                    Self->ItemName,
                    TOptional<int32>(),
                    [Self](Gs2::Inventory::Model::FSimpleItemModelMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Inventory::Request::FGetSimpleItemModelMasterRequest>()
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

    TSharedPtr<FAsyncTask<FSimpleItemModelMasterDomain::FModelTask>> FSimpleItemModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSimpleItemModelMasterDomain::FModelTask>>(this->AsShared());
    }

    void FSimpleItemModelMasterDomain::Invalidate()
    {
        Gs2::Inventory::Model::Cache::FSimpleItemModelMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            InventoryName,
            ItemName,
            TOptional<int32>()
        );
    }

    FSimpleItemModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FSimpleItemModelMasterDomain>& Self,
        TFunction<void(Gs2::Inventory::Model::FSimpleItemModelMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FSimpleItemModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSimpleItemModelMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FSimpleItemModelMasterDomain::FSubscribeWithInitialCallTask>> FSimpleItemModelMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Inventory::Model::FSimpleItemModelMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FSimpleItemModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Inventory::Model::FSimpleItemModelMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Inventory::Model::Cache::FSimpleItemModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            InventoryName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Inventory::Model::Cache::FSimpleItemModelMasterCache::CreateCacheKey(

            ItemName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Inventory::Domain::FGs2InventoryDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryInventoryName = InventoryName;
        const TOptional<FString> QueryItemName = ItemName;
        return Gs2->Cache->Subscribe(
            Gs2::Inventory::Model::FSimpleItemModelMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Inventory::Model::FSimpleItemModelMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryInventoryName, QueryItemName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FSimpleItemModelMasterDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryInventoryName,
                    QueryItemName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FSimpleItemModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Inventory::Model::Cache::FSimpleItemModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            InventoryName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Inventory::Model::Cache::FSimpleItemModelMasterCache::CreateCacheKey(

            ItemName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Inventory::Model::FSimpleItemModelMaster::TypeName,
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
