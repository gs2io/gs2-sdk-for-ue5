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

#include "Inventory/Domain/SpeculativeExecutor/Acquire/DeleteReferenceOfByUserIdSpeculativeExecutor.h"
#include "Inventory/Domain/Gs2Inventory.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Auth/Model/AccessToken.h"
#include "Inventory/Domain/Model/ReferenceOf.h"
#include "Inventory/Model/Cache/ItemSet.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{

    FString FDeleteReferenceOfByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Inventory:DeleteReferenceOfByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteReferenceOfByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FDeleteReferenceOfByUserIdRequestPtr& Request,
        Gs2::Inventory::Model::FReferenceOfPtr Item
    )
    {
        return nullptr;
    }

    FDeleteReferenceOfByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FDeleteReferenceOfByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDeleteReferenceOfByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteReferenceOfByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Inventory::Request::FDeleteReferenceOfByUserIdRequestPtr Prepared = nullptr;
        if (Request.IsValid()) Prepared = MakeShared<Gs2::Inventory::Request::FDeleteReferenceOfByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() || !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty() || !Prepared.IsValid()) return nullptr;
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}")) Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) || !Prepared->GetReferenceOf().IsSet()) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName();
        const auto InventoryName = Prepared->GetInventoryName();
        const auto ItemName = Prepared->GetItemName();
        const auto ItemSetName = Prepared->GetItemSetName();
        const auto ReferenceOf = Prepared->GetReferenceOf().Get(FString());
        const auto UserId = Token->GetUserId().Get(FString());
        const auto TimeOffset = Token->GetTimeOffset();
        const auto ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:inventory:%s:user:%s:inventory:%s:item:%s:itemSet:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()), *UserId, *InventoryName.Get(FString()), *ItemName.Get(FString()), *ItemSetName.Get(FString()));
        Gs2::Inventory::Model::FItemSetPtr Item;
        if (!Gs2::Inventory::Model::Cache::FItemSetCache::TryGet(Domain->Cache, NamespaceName, UserId, InventoryName, ItemName, ItemSetName, TimeOffset, &Item) || !Item.IsValid() || Item->GetItemSetId().Get(FString()) != ExpectedId || !Item->GetReferenceOf().IsValid()) return nullptr;
        const auto ParentKey = Gs2::Inventory::Model::Cache::FItemSetCache::CreateCacheParentKey(NamespaceName, UserId, InventoryName, TimeOffset);
        const auto Key = Gs2::Inventory::Model::Cache::FItemSetCache::CreateCacheKey(ItemName, ItemSetName);
        const auto CompositionKey = ParentKey + TEXT(":") + Key;
        const int64 UpdatedAt = static_cast<int64>(FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0) + static_cast<int64>(TimeOffset.Get(0)) * 1000;
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
            CompositionKey,
            [DomainCopy = Domain, NamespaceName, InventoryName, ItemName, ItemSetName, UserId, TimeOffset, ExpectedId, ReferenceOf, UpdatedAt](const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next)
            {
                Gs2::Inventory::Model::FItemSetPtr CurrentItem;
                if (HasCurrent) CurrentItem = StaticCastSharedPtr<Gs2::Inventory::Model::FItemSet>(Current);
                else if (!Gs2::Inventory::Model::Cache::FItemSetCache::TryGet(DomainCopy->Cache, NamespaceName, UserId, InventoryName, ItemName, ItemSetName, TimeOffset, &CurrentItem)) { Next = nullptr; return false; }
                if (!CurrentItem.IsValid() || CurrentItem->GetItemSetId().Get(FString()) != ExpectedId || CurrentItem->GetName().Get(FString()) != ItemSetName.Get(FString()) || CurrentItem->GetUserId().Get(FString()) != UserId || CurrentItem->GetInventoryName().Get(FString()) != InventoryName.Get(FString()) || CurrentItem->GetItemName().Get(FString()) != ItemName.Get(FString()) || !CurrentItem->GetReferenceOf().IsValid()) { Next = nullptr; return false; }
                auto ChangedReferences = MakeShared<TArray<FString>>();
                bool Removed = false;
                for (const auto& Value : *CurrentItem->GetReferenceOf()) { if (Value == ReferenceOf) Removed = true; else ChangedReferences->Add(Value); }
                if (!Removed) { Next = nullptr; return false; }
                auto Changed = MakeShared<Gs2::Inventory::Model::FItemSet>(*CurrentItem);
                Changed->WithReferenceOf(ChangedReferences)->WithUpdatedAt(UpdatedAt);
                Next = Changed;
                return Changed->GetItemSetId().Get(FString()) == ExpectedId && Changed->GetName().Get(FString()) == ItemSetName.Get(FString()) && Changed->GetUserId().Get(FString()) == UserId && Changed->GetInventoryName().Get(FString()) == InventoryName.Get(FString()) && Changed->GetItemName().Get(FString()) == ItemName.Get(FString()) && Changed->GetReferenceOf().IsValid();
            },
            [DomainCopy = Domain, NamespaceName, InventoryName, ItemName, ItemSetName, UserId, TimeOffset, ExpectedId](const TSharedPtr<void>& State)
            {
                const auto ItemToCommit = StaticCastSharedPtr<Gs2::Inventory::Model::FItemSet>(State);
                if (ItemToCommit.IsValid() && ItemToCommit->GetItemSetId().Get(FString()) == ExpectedId) Gs2::Inventory::Model::Cache::FItemSetCache::Put(DomainCopy->Cache, NamespaceName, UserId, InventoryName, ItemName, ItemSetName, TimeOffset, ItemToCommit);
            }
        );
        /* The generated ReferenceOf target is a component of ItemSet; no standalone tombstone is written. */
        (void)ReferenceOf;
        (void)ParentKey;
        (void)Key;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDeleteReferenceOfByUserIdSpeculativeExecutor::FCommitTask>> FDeleteReferenceOfByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FDeleteReferenceOfByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Inventory::Request::FDeleteReferenceOfByUserIdRequestPtr FDeleteReferenceOfByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FDeleteReferenceOfByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Inventory::Request::FDeleteReferenceOfByUserIdRequestPtr FDeleteReferenceOfByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FDeleteReferenceOfByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
