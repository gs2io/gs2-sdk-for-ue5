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
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Inventory/Domain/SpeculativeExecutor/SimpleItemMutationSpeculativeCommit.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{
using Private::FSimpleItemBatchSpeculativeCommit;
using Private::FSimpleItemMutationSpeculativeCommit;

FString FSetSimpleItemsByUserIdSpeculativeExecutor::Action()
{
    return FString("Gs2Inventory:SetSimpleItemsByUserId");
}

Gs2::Core::Model::FGs2ErrorPtr FSetSimpleItemsByUserIdSpeculativeExecutor::Transform(
    const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
    const Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequestPtr&,
    TSharedPtr<TArray<Gs2::Inventory::Model::FSimpleItemPtr>>
)
{
    return nullptr;
}

FSetSimpleItemsByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequestPtr& Request
): Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request) {}

FSetSimpleItemsByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
    Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request) {}

Gs2::Core::Model::FGs2ErrorPtr FSetSimpleItemsByUserIdSpeculativeExecutor::FCommitTask::Action(
    TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
)
{
    *Result = nullptr;
    Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
    if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
    Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequestPtr Prepared = nullptr;
    if (Request.IsValid()) Prepared = MakeShared<Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequest>(*Request);
    if (Prepared.IsValid() && Prepared->GetCounts().IsValid())
    {
        auto Snapshot = MakeShared<TArray<TSharedPtr<Gs2::Inventory::Model::FHeldCount>>>();
        for (const auto& Entry : *Prepared->GetCounts())
        {
            TSharedPtr<Gs2::Inventory::Model::FHeldCount> Copy = nullptr;
            if (Entry.IsValid()) Copy = MakeShared<Gs2::Inventory::Model::FHeldCount>(*Entry);
            Snapshot->Add(Copy);
        }
        Prepared->WithCounts(Snapshot);
    }
    if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Domain->Cache.IsValid() ||
        !Token.IsValid() || !Prepared.IsValid() || !Token->GetUserId().IsSet() ||
        Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
    if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
        Prepared->WithUserId(Token->GetUserId());
    if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) ||
        !Prepared->GetNamespaceName().IsSet() || !Prepared->GetInventoryName().IsSet() ||
        !Prepared->GetCounts().IsValid()) return nullptr;

    const auto NamespaceName = Prepared->GetNamespaceName();
    if (Prepared->GetCounts()->Num() == 0)
    {
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(
            MakeShared<TFunction<void()>>([]() {})
        );
        return nullptr;
    }
    const auto InventoryName = Prepared->GetInventoryName();
    const auto UserId = Token->GetUserId();
    const auto TimeOffset = Token->GetTimeOffset();
    TMap<FString, int64> AbsoluteSets;
    bool HasConflict = false;
    for (const auto& Entry : *Prepared->GetCounts())
    {
        if (!Entry.IsValid() || !Entry->GetItemName().IsSet() || !Entry->GetCount().IsSet()) continue;
        const FString ItemName = Entry->GetItemName().Get(FString());
        const int64 Count = Entry->GetCount().Get(0);
        int64* Existing = AbsoluteSets.Find(ItemName);
        if (Existing != nullptr && *Existing != Count) HasConflict = true;
        AbsoluteSets.Add(ItemName, Count);
    }
    if (Prepared->GetCounts()->Num() > 0 && AbsoluteSets.Num() == 0) return nullptr;

    TArray<TSharedPtr<FSimpleItemMutationSpeculativeCommit>> Commits;
    for (int32 Index = 0; Index < Prepared->GetCounts()->Num(); ++Index)
    {
        const auto& Entry = (*Prepared->GetCounts())[Index];
        if (!Entry.IsValid() || !Entry->GetItemName().IsSet() || !Entry->GetCount().IsSet()) continue;
        const FString ItemName = Entry->GetItemName().Get(FString());
        bool Superseded = false;
        for (int32 Later = Index + 1; Later < Prepared->GetCounts()->Num(); ++Later)
        {
            const auto& LaterEntry = (*Prepared->GetCounts())[Later];
            if (LaterEntry.IsValid() && LaterEntry->GetItemName().IsSet() &&
                LaterEntry->GetItemName().Get(FString()) == ItemName) { Superseded = true; break; }
        }
        if (Superseded) continue;
        const int64 Count = Entry->GetCount().Get(0);
        const FString ExpectedId = Private::SimpleItemExpectedId(
            Domain->RestSession->RegionName(), Domain->RestSession->OwnerId(), NamespaceName.Get(FString()),
            UserId.Get(FString()), InventoryName.Get(FString()), ItemName
        );
        Gs2::Inventory::Model::FSimpleItemPtr Cached;
        const bool Found = Gs2::Inventory::Model::Cache::FSimpleItemCache::TryGet(
            Domain->Cache, NamespaceName, UserId, InventoryName, ItemName, TimeOffset, &Cached
        );
        if (!Found) continue;
        const bool Tombstone = !Cached.IsValid();
        Gs2::Inventory::Model::FSimpleItemPtr Item = Cached;
        if (!Item.IsValid()) Item = FSimpleItemMutationSpeculativeCommit::KnownZero(ExpectedId, UserId.Get(FString()), ItemName);
        if (!Item->GetItemId().IsSet() || Item->GetItemId().Get(FString()) != ExpectedId ||
            !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId.Get(FString()) ||
            !Item->GetItemName().IsSet() || Item->GetItemName().Get(FString()) != ItemName) continue;
        Commits.Add(MakeShared<FSimpleItemMutationSpeculativeCommit>(
            Domain->Cache, NamespaceName, UserId.Get(FString()), InventoryName.Get(FString()), ItemName,
            TimeOffset, ExpectedId, Item->GetRevision(), Tombstone,
            [Count](const Gs2::Inventory::Model::FSimpleItemPtr& Current)
            {
                if (!Current.IsValid()) return Gs2::Inventory::Model::FSimpleItemPtr(nullptr);
                return MakeShared<Gs2::Inventory::Model::FSimpleItem>(*Current)->WithCount(Count)->WithRevision(0);
            }, Count
        ));
    }
    const FString BatchKey = Gs2::Inventory::Model::Cache::FSimpleItemCache::CreateCacheParentKey(
        NamespaceName, UserId, InventoryName, TimeOffset
    );
    const auto Batch = MakeShared<FSimpleItemBatchSpeculativeCommit>(BatchKey, Commits, AbsoluteSets, true, HasConflict);
    *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
        Batch->CompositionKey(),
        [Batch](const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next)
        { return Batch->TryCompose(Current, HasCurrent, Next); },
        [Batch](const TSharedPtr<void>& State) { Batch->Commit(State); }
    );
    return nullptr;
}

Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequestPtr FSetSimpleItemsByUserIdSpeculativeExecutor::Rate(
    const Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequestPtr& Request, const double)
{
    return Request;
}

Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequestPtr FSetSimpleItemsByUserIdSpeculativeExecutor::Rate(
    const Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequestPtr& Request, TBigInt<1024, false>)
{
    return Request;
}

TSharedPtr<FAsyncTask<FSetSimpleItemsByUserIdSpeculativeExecutor::FCommitTask>> FSetSimpleItemsByUserIdSpeculativeExecutor::Execute(
    const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Inventory::Request::FSetSimpleItemsByUserIdRequestPtr& Request)
{
    return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
}
}
