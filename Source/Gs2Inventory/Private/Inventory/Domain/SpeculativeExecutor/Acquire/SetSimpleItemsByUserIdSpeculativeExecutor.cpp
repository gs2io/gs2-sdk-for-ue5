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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Inventory/Domain/SpeculativeExecutor/Acquire/SetSimpleItemsByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Inventory/Domain/Gs2Inventory.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{

    FString FSetSimpleItemsByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Inventory:SetSimpleItemsByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FSetSimpleItemsByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequestPtr& Request,
        TSharedPtr<TArray<Gs2::Inventory::Model::FSimpleItemPtr>> Items
    )
    {
        for (auto Count : *Request->GetCounts())
        {
            auto Item = Items->FilterByPredicate([Count](Inventory::Model::FSimpleItemPtr V)
            {
                return V->GetItemName() == Count->GetItemName();
            });
            if (Item.Num() == 0) {
                Item.Add(
                    MakeShared<Gs2::Inventory::Model::FSimpleItem>()
                        ->WithItemName(Count->GetItemName())
                        ->WithCount(0)
                        ->WithRevision(0)
                );
            }
            auto First = Item[0];
            First->WithCount(*Count->GetCount());
            *Items = Items->FilterByPredicate([Count](Inventory::Model::FSimpleItemPtr V)
            {
                return V->GetItemName() != Count->GetItemName();
            });
            Items->Add(First);
        }
        Items->Sort([](const Inventory::Model::FSimpleItemPtr& V1, const Inventory::Model::FSimpleItemPtr& V2)
        {
            return V1->GetItemName()->Compare(*V2->GetItemName()) < 0;
        });
        return nullptr;
    }

    FSetSimpleItemsByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FSetSimpleItemsByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSetSimpleItemsByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto It = Domain->Inventory->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->SimpleInventory(
                Request->GetInventoryName().IsSet() ? *Request->GetInventoryName() : FString("")
            )->SimpleItems();
        auto Items = MakeShared<TArray<Gs2::Inventory::Model::FSimpleItemPtr>>();
        for (auto Item : *It)
        {
            if (Item->IsError())
            {
                return Item->Error();
            }
            Items->Add(Item->Current());
        }

        auto Err = Transform(Domain, AccessToken, Request, Items);
        if (Err != nullptr)
        {
            return Err;
        }

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            for (auto Item : *Items)
            {
                const auto ParentKey = Model::FSimpleInventoryDomain::CreateCacheParentKey(
                    Request->GetNamespaceName(),
                    AccessToken->GetUserId(),
                    Request->GetInventoryName(),
                    FString("SimpleItem")
                );
                const auto Key = Model::FSimpleItemDomain::CreateCacheKey(
                    Item->GetItemName()
                );

                Domain->Cache->Put(
                    Inventory::Model::FSimpleItem::TypeName,
                    ParentKey,
                    Key,
                    Item,
                    FDateTime::Now() + FTimespan::FromSeconds(10)
                );
            }
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSetSimpleItemsByUserIdSpeculativeExecutor::FCommitTask>> FSetSimpleItemsByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequestPtr FSetSimpleItemsByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequestPtr FSetSimpleItemsByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
