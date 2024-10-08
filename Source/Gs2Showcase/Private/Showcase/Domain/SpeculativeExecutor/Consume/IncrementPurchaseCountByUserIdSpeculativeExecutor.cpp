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

#include "Showcase/Domain/SpeculativeExecutor/Consume/IncrementPurchaseCountByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Showcase/Domain/Gs2Showcase.h"

namespace Gs2::Showcase::Domain::SpeculativeExecutor
{

    FString FIncrementPurchaseCountByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Showcase:IncrementPurchaseCountByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FIncrementPurchaseCountByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Showcase::Request::FIncrementPurchaseCountByUserIdRequestPtr& Request,
        Gs2::Showcase::Model::FRandomDisplayItemPtr& Item
    )
    {
        Item->WithCurrentPurchaseCount(*Item->GetCurrentPurchaseCount() + *Request->GetCount());
        if (*Item->GetCurrentPurchaseCount() > *Item->GetMaximumPurchaseCount()) {
            return MakeShared<Gs2::Core::Model::FBadRequestError>([]
            {
                auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
                return Arr;
            }());
        }
        return nullptr;
    }

    FIncrementPurchaseCountByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Showcase::Request::FIncrementPurchaseCountByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FIncrementPurchaseCountByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FIncrementPurchaseCountByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Showcase->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->RandomShowcase(
                Request->GetShowcaseName().IsSet() ? *Request->GetShowcaseName() : FString("")
            )->RandomDisplayItem(
                Request->GetDisplayItemName().IsSet() ? *Request->GetDisplayItemName() : FString("")
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

        const auto ParentKey = Gs2::Showcase::Domain::Model::FRandomShowcaseDomain::CreateCacheParentKey(
            Request->GetNamespaceName(),
            AccessToken->GetUserId(),
            Request->GetShowcaseName(),
            "RandomDisplayItem"
        );
        const auto Key = Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain::CreateCacheKey(
            Request->GetDisplayItemName()
        );
        
        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                Showcase::Model::FRandomDisplayItem::TypeName,
                ParentKey,
                Key,
                Item,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIncrementPurchaseCountByUserIdSpeculativeExecutor::FCommitTask>> FIncrementPurchaseCountByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Showcase::Request::FIncrementPurchaseCountByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Showcase::Request::FIncrementPurchaseCountByUserIdRequestPtr FIncrementPurchaseCountByUserIdSpeculativeExecutor::Rate(
        const Gs2::Showcase::Request::FIncrementPurchaseCountByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Showcase::Request::FIncrementPurchaseCountByUserIdRequestPtr FIncrementPurchaseCountByUserIdSpeculativeExecutor::Rate(
        const Gs2::Showcase::Request::FIncrementPurchaseCountByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
