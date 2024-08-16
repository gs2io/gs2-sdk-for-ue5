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

#include "Inventory/Domain/SpeculativeExecutor/Consume/ConsumeSimpleItemsByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Inventory/Domain/Gs2Inventory.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{

    FString FConsumeSimpleItemsByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Inventory:ConsumeSimpleItemsByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FConsumeSimpleItemsByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequestPtr& Request,
        TSharedPtr<TArray<Inventory::Model::FSimpleItemPtr>> Items
    )
    {
        for (auto ConsumeCount : *Request->GetConsumeCounts())
        {
            auto Item = Items->FilterByPredicate([ConsumeCount](Inventory::Model::FSimpleItemPtr V)
            {
                return V->GetItemName() == ConsumeCount->GetItemName();
            });
            if (Item.Num() == 0) {
                return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                {
                    auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                    Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
                    return Arr;
                }());
            }
            auto First = Item[0];
            First->WithCount(*First->GetCount() - *ConsumeCount->GetCount());
            if (*First->GetCount() < 0) {
                return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                {
                    auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                    Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
                    return Arr;
                }());
            }
            *Items = Items->FilterByPredicate([ConsumeCount](Inventory::Model::FSimpleItemPtr V)
            {
                return V->GetItemName() != ConsumeCount->GetItemName();
            });
            Items->Add(First);
        }
        Items->Sort([](const Inventory::Model::FSimpleItemPtr& V1, const Inventory::Model::FSimpleItemPtr& V2)
        {
            return V1->GetItemName()->Compare(*V2->GetItemName()) < 0;
        });
        return nullptr;
    }

    FConsumeSimpleItemsByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FConsumeSimpleItemsByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FConsumeSimpleItemsByUserIdSpeculativeExecutor::FCommitTask::Action(
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
        auto Items = MakeShared<TArray<Inventory::Model::FSimpleItemPtr>>();
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

    TSharedPtr<FAsyncTask<FConsumeSimpleItemsByUserIdSpeculativeExecutor::FCommitTask>> FConsumeSimpleItemsByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequestPtr FConsumeSimpleItemsByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequestPtr FConsumeSimpleItemsByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
