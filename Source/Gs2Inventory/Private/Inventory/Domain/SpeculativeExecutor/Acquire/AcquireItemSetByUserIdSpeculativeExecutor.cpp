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

#include "Inventory/Domain/SpeculativeExecutor/Acquire/AcquireItemSetByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{

    FString FAcquireItemSetByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Inventory:AcquireItemSetByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FAcquireItemSetByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FAcquireItemSetByUserIdRequestPtr& Request,
        TSharedPtr<TArray<Gs2::Inventory::Model::FItemSetPtr>>& Items
    )
    {
        if (Items->Num() > 0) {
            auto Item = (*Items)[Items->Num()-1];
            Item->WithCount(*Item->GetCount() + *Request->GetAcquireCount());
        }
        return nullptr;
    }

    FAcquireItemSetByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FAcquireItemSetByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FAcquireItemSetByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAcquireItemSetByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Inventory->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Inventory(
                Request->GetInventoryName().IsSet() ? *Request->GetInventoryName() : FString("")
            )->ItemSet(
                Request->GetItemName().IsSet() ? *Request->GetItemName() : FString(""),
                Request->GetItemSetName()
            )->Model();
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        auto Items = Future->GetTask().Result();

        if (!Items.IsValid())
        {
            *Result = MakeShared<TFunction<void()>>([&]()
            {
                return nullptr;
            });
            return nullptr;
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
                const auto ParentKey = Model::FInventoryDomain::CreateCacheParentKey(
                    Request->GetNamespaceName(),
                    AccessToken->GetUserId(),
                    Request->GetInventoryName(),
                    FString("ItemSet")
                );
                const auto Key = Model::FItemSetDomain::CreateCacheKey(
                    Request->GetItemName(),
                    Item->GetName()
                );

                Domain->Cache->Put(
                    Inventory::Model::FItemSet::TypeName,
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

    TSharedPtr<FAsyncTask<FAcquireItemSetByUserIdSpeculativeExecutor::FCommitTask>> FAcquireItemSetByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FAcquireItemSetByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Inventory::Request::FAcquireItemSetByUserIdRequestPtr FAcquireItemSetByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FAcquireItemSetByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetAcquireCount().IsSet())
        {
            Request->WithAcquireCount(*Request->GetAcquireCount() * Rate);
        }
        return Request;
    }

    Gs2::Inventory::Request::FAcquireItemSetByUserIdRequestPtr FAcquireItemSetByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FAcquireItemSetByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetAcquireCount().IsSet())
        {
            Rate.Multiply(*Request->GetAcquireCount());
            Request->WithAcquireCount(Rate.ToInt());
        }
        return Request;
    }
}
