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

#include "Inventory/Domain/Model/SimpleInventoryAccessToken.h"
#include "Inventory/Domain/Model/SimpleInventory.h"
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

    FSimpleInventoryAccessTokenDomain::FSimpleInventoryAccessTokenDomain(
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
            "SimpleInventory"
        ))
    {
    }

    FSimpleInventoryAccessTokenDomain::FSimpleInventoryAccessTokenDomain(
        const FSimpleInventoryAccessTokenDomain& From
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

    FSimpleInventoryAccessTokenDomain::FConsumeSimpleItemsTask::FConsumeSimpleItemsTask(
        const TSharedPtr<FSimpleInventoryAccessTokenDomain>& Self,
        const Request::FConsumeSimpleItemsRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSimpleInventoryAccessTokenDomain::FConsumeSimpleItemsTask::FConsumeSimpleItemsTask(
        const FConsumeSimpleItemsTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSimpleInventoryAccessTokenDomain::FConsumeSimpleItemsTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemAccessTokenDomain>>>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->ConsumeSimpleItems(
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
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId(),
                        Self->InventoryName,
                        "SimpleItem"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FSimpleItemDomain::CreateCacheKey(
                        Item->GetItemName()
                    );
                    Self->Gs2->Cache->Put(
                        Gs2::Inventory::Model::FSimpleItem::TypeName,
                        ParentKey,
                        Key,
                        Item,
                        FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            }
        }
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemAccessTokenDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Inventory::Domain::Model::FSimpleItemAccessTokenDomain>(
                    Self->Gs2,
                    Self->Service,
                    Request->GetNamespaceName(),
                    Self->AccessToken,
                    Request->GetInventoryName(),
                    (*ResultModel->GetItems())[i]->GetItemName()
                )
            );
            const auto ParentKey = Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId(),
                Self->InventoryName,
                "SimpleItem"
            );
            const auto Key = Gs2::Inventory::Domain::Model::FSimpleItemDomain::CreateCacheKey(
                (*ResultModel->GetItems())[i]->GetItemName()
            );
            Self->Gs2->Cache->Put(
                Gs2::Inventory::Model::FSimpleItem::TypeName,
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSimpleInventoryAccessTokenDomain::FConsumeSimpleItemsTask>> FSimpleInventoryAccessTokenDomain::ConsumeSimpleItems(
        Request::FConsumeSimpleItemsRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FConsumeSimpleItemsTask>>(this->AsShared(), Request);
    }

    Gs2::Inventory::Domain::Iterator::FDescribeSimpleItemsIteratorPtr FSimpleInventoryAccessTokenDomain::SimpleItems(
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Iterator::FDescribeSimpleItemsIterator>(
            Gs2,
            Client,
            NamespaceName,
            InventoryName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FSimpleInventoryAccessTokenDomain::SubscribeSimpleItems(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Inventory::Model::FSimpleItem::TypeName,
            Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                InventoryName,
                "SimpleItem"
            ),
            Callback
        );
    }

    void FSimpleInventoryAccessTokenDomain::UnsubscribeSimpleItems(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Inventory::Model::FSimpleItem::TypeName,
            Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                InventoryName,
                "SimpleItem"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemAccessTokenDomain> FSimpleInventoryAccessTokenDomain::SimpleItem(
        const FString ItemName
    )
    {
        return MakeShared<Gs2::Inventory::Domain::Model::FSimpleItemAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            InventoryName,
            ItemName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ItemName)
        );
    }

    FString FSimpleInventoryAccessTokenDomain::CreateCacheParentKey(
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

    FString FSimpleInventoryAccessTokenDomain::CreateCacheKey(
        TOptional<FString> InventoryName
    )
    {
        return FString("") +
            (InventoryName.IsSet() ? *InventoryName : "null");
    }

    FSimpleInventoryAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FSimpleInventoryAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FSimpleInventoryAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSimpleInventoryAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FSimpleInventory>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Inventory::Model::FSimpleInventory> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FSimpleInventory>(
            Self->ParentKey,
            Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheKey(
                Self->InventoryName
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSimpleInventoryAccessTokenDomain::FModelTask>> FSimpleInventoryAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSimpleInventoryAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FSimpleInventoryAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Inventory::Model::FSimpleInventoryPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Inventory::Model::FSimpleInventory::TypeName,
            ParentKey,
            Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheKey(
                InventoryName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Inventory::Model::FSimpleInventory>(obj));
            }
        );
    }

    void FSimpleInventoryAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Inventory::Model::FSimpleInventory::TypeName,
            ParentKey,
            Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheKey(
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

