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

#include "Inventory/Domain/Model/InventoryAccessToken.h"
#include "Inventory/Domain/Model/Inventory.h"
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
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Inventory::Domain::Model
{

    FInventoryAccessTokenDomain::FInventoryAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> InventoryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Inventory::FGs2InventoryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        InventoryName(InventoryName),
        ParentKey(Gs2::Inventory::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Inventory"
        ))
    {
    }

    FInventoryAccessTokenDomain::FInventoryAccessTokenDomain(
        const FInventoryAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        InventoryName(From.InventoryName),
        ParentKey(From.ParentKey)
    {

    }

    FInventoryAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FInventoryAccessTokenDomain>& Self,
        const Request::FGetInventoryRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FInventoryAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FInventory>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->GetInventory(
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
                const auto ParentKey = Gs2::Inventory::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetInventoryName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FInventory::TypeName,
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

    TSharedPtr<FAsyncTask<FInventoryAccessTokenDomain::FGetTask>> FInventoryAccessTokenDomain::Get(
        Request::FGetInventoryRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FInventoryAccessTokenDomain::FVerifyCurrentMaxCapacityTask::FVerifyCurrentMaxCapacityTask(
        const TSharedPtr<FInventoryAccessTokenDomain>& Self,
        const Request::FVerifyInventoryCurrentMaxCapacityRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FInventoryAccessTokenDomain::FVerifyCurrentMaxCapacityTask::FVerifyCurrentMaxCapacityTask(
        const FVerifyCurrentMaxCapacityTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryAccessTokenDomain::FVerifyCurrentMaxCapacityTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FInventoryAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->VerifyInventoryCurrentMaxCapacity(
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
            
        }
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FInventoryAccessTokenDomain::FVerifyCurrentMaxCapacityTask>> FInventoryAccessTokenDomain::VerifyCurrentMaxCapacity(
        Request::FVerifyInventoryCurrentMaxCapacityRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyCurrentMaxCapacityTask>>(this->AsShared(), Request);
    }

    Gs2::Inventory::Domain::Iterator::FDescribeItemSetsIteratorPtr FInventoryAccessTokenDomain::ItemSets(
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Iterator::FDescribeItemSetsIterator>(
            Gs2,
            Client,
            NamespaceName,
            InventoryName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FInventoryAccessTokenDomain::SubscribeItemSets(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Inventory::Model::FItemSet::TypeName,
            Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                InventoryName,
                "ItemSet"
            ),
            Callback
        );
    }

    void FInventoryAccessTokenDomain::UnsubscribeItemSets(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Inventory::Model::FItemSet::TypeName,
            Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                InventoryName,
                "ItemSet"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetAccessTokenDomain> FInventoryAccessTokenDomain::ItemSet(
        const FString ItemName,
        const TOptional<FString> ItemSetName
    )
    {
        return MakeShared<Gs2::Inventory::Domain::Model::FItemSetAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            InventoryName,
            ItemName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ItemName),
            ItemSetName
        );
    }

    FString FInventoryAccessTokenDomain::CreateCacheParentKey(
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

    FString FInventoryAccessTokenDomain::CreateCacheKey(
        TOptional<FString> InventoryName
    )
    {
        return FString("") +
            (InventoryName.IsSet() ? *InventoryName : "null");
    }

    FInventoryAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FInventoryAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FInventoryAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FInventory>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Inventory::Model::FInventory> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FInventory>(
            Self->ParentKey,
            Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                Self->InventoryName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Inventory::Request::FGetInventoryRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    Self->InventoryName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FInventory::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "inventory")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FInventory>(
                Self->ParentKey,
                Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    Self->InventoryName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FInventoryAccessTokenDomain::FModelTask>> FInventoryAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FInventoryAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FInventoryAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Inventory::Model::FInventoryPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Inventory::Model::FInventory::TypeName,
            ParentKey,
            Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                InventoryName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Inventory::Model::FInventory>(obj));
            }
        );
    }

    void FInventoryAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Inventory::Model::FInventory::TypeName,
            ParentKey,
            Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
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

