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

#include "AdReward/Domain/SpeculativeExecutor/Consume/ConsumePointByUserIdSpeculativeExecutor.h"

#include "AdReward/Domain/Gs2AdReward.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Auth/Model/AccessToken.h"
#include "AdReward/Model/Cache/Point.h"

namespace Gs2::AdReward::Domain::SpeculativeExecutor
{

    FString FConsumePointByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2AdReward:ConsumePointByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FConsumePointByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::AdReward::Request::FConsumePointByUserIdRequestPtr& Request,
        Gs2::AdReward::Model::FPointPtr Item
    )
    {
        (void)Domain;
        (void)AccessToken;
        (void)Request;
        (void)Item;
        return nullptr;
    }

    FConsumePointByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::AdReward::Domain::FGs2AdRewardDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::AdReward::Request::FConsumePointByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FConsumePointByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FConsumePointByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::AdReward::Request::FConsumePointByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid()) PreparedRequest = MakeShared<Gs2::AdReward::Request::FConsumePointByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Domain->Cache.IsValid() || !PreparedToken.IsValid() || !PreparedRequest.IsValid() || !PreparedToken->GetUserId().IsSet() || PreparedToken->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() && PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}")) PreparedRequest->WithUserId(PreparedToken->GetUserId());
        if (!PreparedRequest->GetUserId().IsSet() || PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString()) || !PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName().Get(FString()).IsEmpty() || !PreparedRequest->GetPoint().IsSet()) return nullptr;
        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const auto UserId = PreparedToken->GetUserId();
        const auto TimeOffset = PreparedToken->GetTimeOffset();
        const FString ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:adReward:%s:user:%s:point"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()), *UserId.Get(FString()));
        Gs2::AdReward::Model::FPointPtr Item;
        if (!Gs2::AdReward::Model::Cache::FPointCache::TryGet(Domain->Cache, NamespaceName, UserId, TimeOffset, &Item) || !Item.IsValid() || !Item->GetPointId().IsSet() || Item->GetPointId().Get(FString()) != ExpectedId || !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId.Get(FString())) return nullptr;
        const auto PreparedRevision = Item->GetRevision();
        const int64 CurrentTimeMillis = static_cast<int64>(FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0) + static_cast<int64>(TimeOffset.Get(0)) * 1000;
        const int64 PointValue = PreparedRequest->GetPoint().Get(0);
        const FString CompositionKey = FString::Printf(TEXT("adReward:%s:%s:%d:Point:Singleton"), *NamespaceName.Get(FString()), *UserId.Get(FString()), TimeOffset.Get(0));
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
            CompositionKey,
            [DomainCopy = Domain, NamespaceName, UserId = UserId.Get(FString()), TimeOffset, ExpectedId, PreparedRevision, PointValue, CurrentTimeMillis](const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next)
            {
                Gs2::AdReward::Model::FPointPtr CurrentItem;
                if (HasCurrent)
                {
                    if (!Current.IsValid()) { Next = nullptr; return false; }
                    CurrentItem = StaticCastSharedPtr<Gs2::AdReward::Model::FPoint>(Current);
                }
                else
                {
                    if (!Gs2::AdReward::Model::Cache::FPointCache::TryGet(DomainCopy->Cache, NamespaceName, UserId, TimeOffset, &CurrentItem)) { Next = nullptr; return false; }
                    const auto CachedRevision = CurrentItem.IsValid() ? CurrentItem->GetRevision() : TOptional<int64>();
                    if (CachedRevision.IsSet() && CachedRevision.Get(0) > 0 && (!PreparedRevision.IsSet() || CachedRevision.Get(0) != PreparedRevision.Get(0))) { Next = nullptr; return false; }
                }
                if (!CurrentItem.IsValid() || !CurrentItem->GetPointId().IsSet() || CurrentItem->GetPointId().Get(FString()) != ExpectedId || !CurrentItem->GetUserId().IsSet() || CurrentItem->GetUserId().Get(FString()) != UserId || !CurrentItem->GetPoint().IsSet()) { Next = nullptr; return false; }
                const int64 Base = CurrentItem->GetPoint().Get(0);
                if (PointValue > 0 && Base < PointValue) { Next = nullptr; return false; }
                if ((PointValue > 0 && Base < TNumericLimits<int64>::Min() + PointValue) || (PointValue < 0 && Base > TNumericLimits<int64>::Max() + PointValue)) { Next = nullptr; return false; }
                auto Changed = MakeShared<Gs2::AdReward::Model::FPoint>(*CurrentItem);
                Changed->WithPoint(Base - PointValue)->WithUpdatedAt(CurrentTimeMillis)->WithRevision(0);
                Next = Changed;
                return Changed->GetPointId().IsSet() && Changed->GetPointId().Get(FString()) == ExpectedId && Changed->GetUserId().IsSet() && Changed->GetUserId().Get(FString()) == UserId && Changed->GetRevision().IsSet() && Changed->GetRevision().Get(0) == 0;
            },
            [DomainCopy = Domain, NamespaceName, UserId = UserId.Get(FString()), TimeOffset, ExpectedId](const TSharedPtr<void>& State)
            {
                if (!State.IsValid()) return;
                const auto ItemToCommit = StaticCastSharedPtr<Gs2::AdReward::Model::FPoint>(State);
                if (ItemToCommit.IsValid() && ItemToCommit->GetPointId().IsSet() && ItemToCommit->GetPointId().Get(FString()) == ExpectedId && ItemToCommit->GetUserId().IsSet() && ItemToCommit->GetUserId().Get(FString()) == UserId && ItemToCommit->GetRevision().IsSet() && ItemToCommit->GetRevision().Get(0) == 0) Gs2::AdReward::Model::Cache::FPointCache::Put(DomainCopy->Cache, NamespaceName, UserId, TimeOffset, ItemToCommit);
            }
        );
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FConsumePointByUserIdSpeculativeExecutor::FCommitTask>> FConsumePointByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::AdReward::Domain::FGs2AdRewardDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::AdReward::Request::FConsumePointByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::AdReward::Request::FConsumePointByUserIdRequestPtr FConsumePointByUserIdSpeculativeExecutor::Rate(
        const Gs2::AdReward::Request::FConsumePointByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::AdReward::Request::FConsumePointByUserIdRequestPtr FConsumePointByUserIdSpeculativeExecutor::Rate(
        const Gs2::AdReward::Request::FConsumePointByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
