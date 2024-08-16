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

#include "Inventory/Domain/SpeculativeExecutor/Acquire/AddCapacityByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Inventory/Domain/Gs2Inventory.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{

    FString FAddCapacityByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Inventory:AddCapacityByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FAddCapacityByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FAddCapacityByUserIdRequestPtr& Request,
        Gs2::Inventory::Model::FInventoryPtr Item
    )
    {
        Item->WithCurrentInventoryMaxCapacity(*Item->GetCurrentInventoryMaxCapacity() + *Request->GetAddCapacityValue());
        return nullptr;
    }

    FAddCapacityByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FAddCapacityByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FAddCapacityByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAddCapacityByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Inventory->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Inventory(
                Request->GetInventoryName().IsSet() ? *Request->GetInventoryName() : FString("")
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

        const auto ParentKey = Model::FUserDomain::CreateCacheParentKey(
            Request->GetNamespaceName(),
            AccessToken->GetUserId(),
            FString("Inventory")
        );
        const auto Key = Model::FInventoryDomain::CreateCacheKey(
            Request->GetInventoryName()
        );

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                Inventory::Model::FInventory::TypeName,
                ParentKey,
                Key,
                Item,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAddCapacityByUserIdSpeculativeExecutor::FCommitTask>> FAddCapacityByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FAddCapacityByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Inventory::Request::FAddCapacityByUserIdRequestPtr FAddCapacityByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FAddCapacityByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetAddCapacityValue().IsSet())
        {
            Request->WithAddCapacityValue(*Request->GetAddCapacityValue() * Rate);
        }
        return Request;
    }

    Gs2::Inventory::Request::FAddCapacityByUserIdRequestPtr FAddCapacityByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FAddCapacityByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetAddCapacityValue().IsSet())
        {
            Rate.Multiply(*Request->GetAddCapacityValue());
            Request->WithAddCapacityValue(Rate.ToInt());
        }
        return Request;
    }
}
