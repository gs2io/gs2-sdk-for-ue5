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

#include "Inventory/Domain/Model/InventoryModel.h"
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

    FInventoryModelDomain::FInventoryModelDomain(
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
            "InventoryModel"
        ))
    {
    }

    FInventoryModelDomain::FInventoryModelDomain(
        const FInventoryModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        InventoryName(From.InventoryName),
        ParentKey(From.ParentKey)
    {

    }

    FInventoryModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FInventoryModelDomain>& Self,
        const Request::FGetInventoryModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FInventoryModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FInventoryModel>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->GetInventoryModel(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FInventoryModelDomain::FGetTask>> FInventoryModelDomain::Get(
        Request::FGetInventoryModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIteratorPtr FInventoryModelDomain::ItemModels(
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIterator>(
            Gs2,
            Client,
            NamespaceName,
            InventoryName
        );
    }

    Gs2::Core::Domain::CallbackID FInventoryModelDomain::SubscribeItemModels(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Inventory::Model::FItemModel::TypeName,
            Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheParentKey(
                NamespaceName,
                InventoryName,
                "ItemModel"
            ),
            Callback
        );
    }

    void FInventoryModelDomain::UnsubscribeItemModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Inventory::Model::FItemModel::TypeName,
            Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheParentKey(
                NamespaceName,
                InventoryName,
                "ItemModel"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Inventory::Domain::Model::FItemModelDomain> FInventoryModelDomain::ItemModel(
        const FString ItemName
    )
    {
        return MakeShared<Gs2::Inventory::Domain::Model::FItemModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            InventoryName,
            ItemName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ItemName)
        );
    }

    FString FInventoryModelDomain::CreateCacheParentKey(
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

    FString FInventoryModelDomain::CreateCacheKey(
        TOptional<FString> InventoryName
    )
    {
        return FString("") +
            (InventoryName.IsSet() ? *InventoryName : "null");
    }

    FInventoryModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FInventoryModelDomain> Self
    ): Self(Self)
    {

    }

    FInventoryModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FInventoryModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Inventory::Model::FInventoryModel> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FInventoryModel>(
            Self->ParentKey,
            Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheKey(
                Self->InventoryName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Inventory::Request::FGetInventoryModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheKey(
                    Self->InventoryName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FInventoryModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "inventoryModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FInventoryModel>(
                Self->ParentKey,
                Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheKey(
                    Self->InventoryName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FInventoryModelDomain::FModelTask>> FInventoryModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FInventoryModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FInventoryModelDomain::Subscribe(
        TFunction<void(Gs2::Inventory::Model::FInventoryModelPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Inventory::Model::FInventoryModel::TypeName,
            ParentKey,
            Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheKey(
                InventoryName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Inventory::Model::FInventoryModel>(obj));
            }
        );
    }

    void FInventoryModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Inventory::Model::FInventoryModel::TypeName,
            ParentKey,
            Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheKey(
                InventoryName
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

