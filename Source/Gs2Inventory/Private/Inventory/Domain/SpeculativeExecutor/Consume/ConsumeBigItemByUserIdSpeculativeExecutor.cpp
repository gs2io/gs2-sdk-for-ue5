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

#include "Inventory/Domain/SpeculativeExecutor/Consume/ConsumeBigItemByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{

    FString FConsumeBigItemByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Inventory:ConsumeBigItemByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FConsumeBigItemByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FConsumeBigItemByUserIdRequestPtr& Request,
        Gs2::Inventory::Model::FBigItemPtr Item
    )
    {
        TBigInt<1024, false> V1;
        TBigInt<1024, false> V2;
        V1.Parse(*Item->GetCount());
        V2.Parse(*Request->GetConsumeCount());
        V1.Subtract(V2);
        Item->WithCount(V1.ToString());
        return nullptr;
    }

    FConsumeBigItemByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FConsumeBigItemByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FConsumeBigItemByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FConsumeBigItemByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Inventory->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->BigInventory(
                Request->GetInventoryName().IsSet() ? *Request->GetInventoryName() : FString("")
            )->BigItem(
                Request->GetItemName().IsSet() ? *Request->GetItemName() : FString("")
            )->Model();
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        auto Item = Future->GetTask().Result();

        if (!Item.IsValid())
        {
            *Result = MakeShared<TFunction<void()>>([&]()
            {
                return nullptr;
            });
            return nullptr;
        }
        auto Err = Transform(Domain, AccessToken, Request, Item);
        if (Err != nullptr)
        {
            return Err;
        }

        const auto ParentKey = Model::FBigInventoryDomain::CreateCacheParentKey(
            Request->GetNamespaceName(),
            AccessToken->GetUserId(),
            Request->GetInventoryName(),
            FString("BigItem")
        );
        const auto Key = Model::FBigItemDomain::CreateCacheKey(
            Request->GetItemName()
        );

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                Inventory::Model::FBigItem::TypeName,
                ParentKey,
                Key,
                Item,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FConsumeBigItemByUserIdSpeculativeExecutor::FCommitTask>> FConsumeBigItemByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FConsumeBigItemByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Inventory::Request::FConsumeBigItemByUserIdRequestPtr FConsumeBigItemByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FConsumeBigItemByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetConsumeCount().IsSet())
        {
            TBigInt<1024, false> V1;
            V1.Parse(*Request->GetConsumeCount());
            V1.Multiply(Rate);
            Request->WithConsumeCount(V1.ToString());
        }
        return Request;
    }

    Gs2::Inventory::Request::FConsumeBigItemByUserIdRequestPtr FConsumeBigItemByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FConsumeBigItemByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetConsumeCount().IsSet())
        {
            TBigInt<1024, false> V1;
            V1.Parse(*Request->GetConsumeCount());
            V1.Multiply(Rate);
            Request->WithConsumeCount(V1.ToString());
        }
        return Request;
    }
}
