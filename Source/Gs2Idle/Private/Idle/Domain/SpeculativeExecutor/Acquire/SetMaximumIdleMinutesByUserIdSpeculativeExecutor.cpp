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

#include "Idle/Domain/SpeculativeExecutor/Acquire/SetMaximumIdleMinutesByUserIdSpeculativeExecutor.h"
#include "Idle/Domain/Gs2Idle.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Auth/Model/AccessToken.h"
#include "Idle/Model/Cache/Status.h"

namespace Gs2::Idle::Domain::SpeculativeExecutor
{

    FString FSetMaximumIdleMinutesByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Idle:SetMaximumIdleMinutesByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FSetMaximumIdleMinutesByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Idle::Request::FSetMaximumIdleMinutesByUserIdRequestPtr& Request,
        Gs2::Idle::Model::FStatusPtr Item
    )
    {
        // TODO: Speculative execution not supported
        UE_LOG(Gs2Log, Warning, TEXT("Speculative execution not supported on this action: %s"), ToCStr(Action()))
        return nullptr;
    }

    FSetMaximumIdleMinutesByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Idle::Domain::FGs2IdleDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Idle::Request::FSetMaximumIdleMinutesByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FSetMaximumIdleMinutesByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSetMaximumIdleMinutesByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Idle::Request::FSetMaximumIdleMinutesByUserIdRequestPtr Prepared = nullptr;
        if (Request.IsValid()) Prepared = MakeShared<Gs2::Idle::Request::FSetMaximumIdleMinutesByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() || !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty() || !Prepared.IsValid()) return nullptr;
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}")) Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) || !Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() || !Prepared->GetCategoryName().IsSet() || Prepared->GetCategoryName().Get(FString()).IsEmpty()) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName();
        const auto CategoryName = Prepared->GetCategoryName();
        const auto UserId = Token->GetUserId();
        const auto TimeOffset = Token->GetTimeOffset();
        const auto ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:idle:%s:user:%s:categoryModel:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()), *UserId.Get(FString()), *CategoryName.Get(FString()));
        Gs2::Idle::Model::FStatusPtr Item;
        if (!Gs2::Idle::Model::Cache::FStatusCache::TryGet(Domain->Cache, NamespaceName, UserId, CategoryName, TimeOffset, &Item) || !Item.IsValid() || Item->GetStatusId().Get(FString()) != ExpectedId || Item->GetUserId().Get(FString()) != UserId.Get(FString()) || Item->GetCategoryName().Get(FString()) != CategoryName.Get(FString())) return nullptr;
        const int64 UpdatedAt = static_cast<int64>(FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0) + static_cast<int64>(TimeOffset.Get(0)) * 1000;
        const int32 MaximumIdleMinutes = Prepared->GetMaximumIdleMinutes().Get(0);
        const auto CompositionKey = FString::Printf(TEXT("idle:%s:%s:%d:Status:%s"), *NamespaceName.Get(FString()), *UserId.Get(FString()), TimeOffset.Get(0), *CategoryName.Get(FString()));
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
            CompositionKey,
            [DomainCopy = Domain, NamespaceName, CategoryName, UserId = UserId.Get(FString()), TimeOffset, ExpectedId, MaximumIdleMinutes, UpdatedAt](const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next)
            {
                Gs2::Idle::Model::FStatusPtr CurrentItem;
                if (HasCurrent) CurrentItem = StaticCastSharedPtr<Gs2::Idle::Model::FStatus>(Current);
                else if (!Gs2::Idle::Model::Cache::FStatusCache::TryGet(DomainCopy->Cache, NamespaceName, UserId, CategoryName, TimeOffset, &CurrentItem)) { Next = nullptr; return false; }
                if (!CurrentItem.IsValid() || CurrentItem->GetStatusId().Get(FString()) != ExpectedId || CurrentItem->GetUserId().Get(FString()) != UserId || CurrentItem->GetCategoryName().Get(FString()) != CategoryName) { Next = nullptr; return false; }
                auto Changed = MakeShared<Gs2::Idle::Model::FStatus>(*CurrentItem);
                Changed->WithMaximumIdleMinutes(MaximumIdleMinutes)->WithUpdatedAt(UpdatedAt)->WithRevision(0);
                Next = Changed;
                return Changed->GetStatusId().Get(FString()) == ExpectedId && Changed->GetUserId().Get(FString()) == UserId && Changed->GetCategoryName().Get(FString()) == CategoryName && Changed->GetRevision().Get(-1) == 0;
            },
            [DomainCopy = Domain, NamespaceName, CategoryName, UserId = UserId.Get(FString()), TimeOffset, ExpectedId](const TSharedPtr<void>& State)
            {
                const auto ItemToCommit = StaticCastSharedPtr<Gs2::Idle::Model::FStatus>(State);
                if (ItemToCommit.IsValid() && ItemToCommit->GetStatusId().Get(FString()) == ExpectedId && ItemToCommit->GetUserId().Get(FString()) == UserId && ItemToCommit->GetCategoryName().Get(FString()) == CategoryName && ItemToCommit->GetRevision().Get(-1) == 0) DomainCopy->Cache->Put(
                    Gs2::Idle::Model::FStatus::TypeName,
                    Gs2::Idle::Model::Cache::FStatusCache::CreateCacheParentKey(NamespaceName, UserId, TimeOffset),
                    Gs2::Idle::Model::Cache::FStatusCache::CreateCacheKey(CategoryName),
                    ItemToCommit,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        );
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSetMaximumIdleMinutesByUserIdSpeculativeExecutor::FCommitTask>> FSetMaximumIdleMinutesByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Idle::Domain::FGs2IdleDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Idle::Request::FSetMaximumIdleMinutesByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Idle::Request::FSetMaximumIdleMinutesByUserIdRequestPtr FSetMaximumIdleMinutesByUserIdSpeculativeExecutor::Rate(
        const Gs2::Idle::Request::FSetMaximumIdleMinutesByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Idle::Request::FSetMaximumIdleMinutesByUserIdRequestPtr FSetMaximumIdleMinutesByUserIdSpeculativeExecutor::Rate(
        const Gs2::Idle::Request::FSetMaximumIdleMinutesByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
