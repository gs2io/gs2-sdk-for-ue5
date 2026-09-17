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

#include "Showcase/Domain/SpeculativeExecutor/Acquire/DecrementPurchaseCountByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Showcase/Domain/Gs2Showcase.h"
#include "Showcase/Model/Cache/RandomDisplayItem.h"

namespace Gs2::Showcase::Domain::SpeculativeExecutor
{

    FString FDecrementPurchaseCountByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Showcase:DecrementPurchaseCountByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDecrementPurchaseCountByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Showcase::Request::FDecrementPurchaseCountByUserIdRequestPtr& Request,
        Gs2::Showcase::Model::FRandomDisplayItemPtr Item
    )
    {
        Item->WithCurrentPurchaseCount(*Item->GetCurrentPurchaseCount() - *Request->GetCount());
        if (*Item->GetCurrentPurchaseCount() < 0) {
            return MakeShared<Gs2::Core::Model::FBadRequestError>([]
            {
                auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
                return Arr;
            }());
        }
        return nullptr;
    }

    FDecrementPurchaseCountByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Showcase::Request::FDecrementPurchaseCountByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDecrementPurchaseCountByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDecrementPurchaseCountByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        const auto Prepared = Request.IsValid() ? Gs2::Showcase::Request::FDecrementPurchaseCountByUserIdRequest::FromJson(Request->ToJson()) : nullptr;
        if (Prepared.IsValid() && Prepared->GetUserId().IsSet() && *Prepared->GetUserId() == TEXT("#{userId}")) Prepared->WithUserId(AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>());
        Gs2::Auth::Model::FAccessTokenPtr PreparedAccessToken;
        if (AccessToken.IsValid()) PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Prepared.IsValid() || !PreparedAccessToken.IsValid() || !PreparedAccessToken->GetUserId().IsSet() || Prepared->GetUserId() != PreparedAccessToken->GetUserId()) return nullptr;
        const auto UserId = *PreparedAccessToken->GetUserId();
        const auto TimeOffset = PreparedAccessToken->GetTimeOffset();
        Gs2::Showcase::Model::FRandomDisplayItemPtr PreparedItem;
        if (!Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::TryGet(Domain->Cache, Prepared->GetNamespaceName(), UserId, Prepared->GetShowcaseName(), Prepared->GetDisplayItemName(), TimeOffset, &PreparedItem) || !PreparedItem.IsValid() || PreparedItem->GetShowcaseName() != Prepared->GetShowcaseName() || PreparedItem->GetName() != Prepared->GetDisplayItemName()) return nullptr;
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(MakeShared<TFunction<void()>>([DomainCopy = Domain, Prepared, UserId, TimeOffset, PreparedItem]()
        {
            Gs2::Showcase::Model::FRandomDisplayItemPtr Live;
            if (!Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::TryGet(DomainCopy->Cache, Prepared->GetNamespaceName(), UserId, Prepared->GetShowcaseName(), Prepared->GetDisplayItemName(), TimeOffset, &Live) || !Live.IsValid() || Live != PreparedItem || Live->GetShowcaseName() != Prepared->GetShowcaseName() || Live->GetName() != Prepared->GetDisplayItemName()) return;
            const int64 Count = Prepared->GetCount().Get(1);
            if (!Live->GetCurrentPurchaseCount().IsSet()) return;
            const int64 ChangedCount = static_cast<int64>(*Live->GetCurrentPurchaseCount()) - Count;
            if (ChangedCount < 0 || ChangedCount > INT32_MAX || ChangedCount < INT32_MIN) return;
            auto Changed = Gs2::Showcase::Model::FRandomDisplayItem::FromJson(Live->ToJson());
            if (!Changed.IsValid()) return;
            Changed->WithCurrentPurchaseCount(static_cast<int32>(ChangedCount));
            Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::Put(DomainCopy->Cache, Prepared->GetNamespaceName(), UserId, Prepared->GetShowcaseName(), Prepared->GetDisplayItemName(), TimeOffset, Changed);
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDecrementPurchaseCountByUserIdSpeculativeExecutor::FCommitTask>> FDecrementPurchaseCountByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Showcase::Request::FDecrementPurchaseCountByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Showcase::Request::FDecrementPurchaseCountByUserIdRequestPtr FDecrementPurchaseCountByUserIdSpeculativeExecutor::Rate(
        const Gs2::Showcase::Request::FDecrementPurchaseCountByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Showcase::Request::FDecrementPurchaseCountByUserIdRequestPtr FDecrementPurchaseCountByUserIdSpeculativeExecutor::Rate(
        const Gs2::Showcase::Request::FDecrementPurchaseCountByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
