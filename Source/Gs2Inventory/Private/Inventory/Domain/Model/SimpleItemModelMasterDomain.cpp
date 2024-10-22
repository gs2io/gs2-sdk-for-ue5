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
#include "Inventory/Domain/Model/ItemSetEntry.h"

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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
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
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->InventoryName,
                    "SimpleItemModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FSimpleItemModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FSimpleItemModelMaster::TypeName,
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
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
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->InventoryName,
                    "SimpleItemModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FSimpleItemModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FSimpleItemModelMaster::TypeName,
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName);
        const auto Future = Self->Client->DeleteSimpleItemModelMaster(
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
                const auto ParentKey = Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->InventoryName,
                    "SimpleItemModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FSimpleItemModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Inventory::Model::FSimpleItemModelMaster::TypeName, ParentKey, Key);
            }
        }
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
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Inventory::Model::FSimpleItemModelMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FSimpleItemModelMaster>(
            Self->ParentKey,
            Gs2::Inventory::Domain::Model::FSimpleItemModelMasterDomain::CreateCacheKey(
                Self->ItemName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Inventory::Request::FGetSimpleItemModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Inventory::Domain::Model::FSimpleItemModelMasterDomain::CreateCacheKey(
                    Self->ItemName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FSimpleItemModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "simpleItemModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FSimpleItemModelMaster>(
                Self->ParentKey,
                Gs2::Inventory::Domain::Model::FSimpleItemModelMasterDomain::CreateCacheKey(
                    Self->ItemName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSimpleItemModelMasterDomain::FModelTask>> FSimpleItemModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSimpleItemModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FSimpleItemModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Inventory::Model::FSimpleItemModelMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Inventory::Model::FSimpleItemModelMaster::TypeName,
            ParentKey,
            Gs2::Inventory::Domain::Model::FSimpleItemModelMasterDomain::CreateCacheKey(
                ItemName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Inventory::Model::FSimpleItemModelMaster>(obj));
            }
        );
    }

    void FSimpleItemModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Inventory::Model::FSimpleItemModelMaster::TypeName,
            ParentKey,
            Gs2::Inventory::Domain::Model::FSimpleItemModelMasterDomain::CreateCacheKey(
                ItemName
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

