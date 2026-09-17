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
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Inventory/Domain/SpeculativeExecutor/SimpleItemMutationSpeculativeCommit.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{
using Private::FSimpleItemBatchSpeculativeCommit;
using Private::FSimpleItemMutationSpeculativeCommit;
using Private::FSimpleItemRate;

FString FConsumeSimpleItemsByUserIdSpeculativeExecutor::Action()
{
    return FString("Gs2Inventory:ConsumeSimpleItemsByUserId");
}

Gs2::Core::Model::FGs2ErrorPtr FConsumeSimpleItemsByUserIdSpeculativeExecutor::Transform(
    const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
    const Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequestPtr&,
    TSharedPtr<TArray<Inventory::Model::FSimpleItemPtr>>
)
{
    return nullptr;
}

FConsumeSimpleItemsByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequestPtr& Request
): Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request) {}

FConsumeSimpleItemsByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
    Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request) {}

Gs2::Core::Model::FGs2ErrorPtr FConsumeSimpleItemsByUserIdSpeculativeExecutor::FCommitTask::Action(
    TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
)
{
    *Result = nullptr;
    Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
    if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
    Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequestPtr Prepared = nullptr;
    if (Request.IsValid()) Prepared = MakeShared<Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequest>(*Request);
    if (Prepared.IsValid() && Prepared->GetConsumeCounts().IsValid())
    {
        auto Snapshot = MakeShared<TArray<TSharedPtr<Gs2::Inventory::Model::FConsumeCount>>>();
        for (const auto& Entry : *Prepared->GetConsumeCounts())
        {
            TSharedPtr<Gs2::Inventory::Model::FConsumeCount> Copy = nullptr;
            if (Entry.IsValid()) Copy = MakeShared<Gs2::Inventory::Model::FConsumeCount>(*Entry);
            Snapshot->Add(Copy);
        }
        Prepared->WithConsumeCounts(Snapshot);
    }
    if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Domain->Cache.IsValid() ||
        !Token.IsValid() || !Prepared.IsValid() || !Token->GetUserId().IsSet() ||
        Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
    if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
        Prepared->WithUserId(Token->GetUserId());
    if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) ||
        !Prepared->GetNamespaceName().IsSet() || !Prepared->GetInventoryName().IsSet() ||
        !Prepared->GetConsumeCounts().IsValid()) return nullptr;

    const auto NamespaceName = Prepared->GetNamespaceName();
    if (Prepared->GetConsumeCounts()->Num() == 0)
    {
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(
            MakeShared<TFunction<void()>>([]() {})
        );
        return nullptr;
    }
    const auto InventoryName = Prepared->GetInventoryName();
    const auto UserId = Token->GetUserId();
    const auto TimeOffset = Token->GetTimeOffset();
    TArray<TSharedPtr<FSimpleItemMutationSpeculativeCommit>> Commits;
    for (const auto& Entry : *Prepared->GetConsumeCounts())
    {
        if (!Entry.IsValid() || !Entry->GetItemName().IsSet() || !Entry->GetCount().IsSet()) continue;
        const FString ItemName = Entry->GetItemName().Get(FString());
        const FString ExpectedId = Private::SimpleItemExpectedId(
            Domain->RestSession->RegionName(), Domain->RestSession->OwnerId(), NamespaceName.Get(FString()),
            UserId.Get(FString()), InventoryName.Get(FString()), ItemName
        );
        Gs2::Inventory::Model::FSimpleItemPtr Cached;
        const bool Found = Gs2::Inventory::Model::Cache::FSimpleItemCache::TryGet(
            Domain->Cache, NamespaceName, UserId, InventoryName, ItemName, TimeOffset, &Cached
        );
        if (!Found || !Cached.IsValid() || !Cached->GetItemId().IsSet() || Cached->GetItemId().Get(FString()) != ExpectedId ||
            !Cached->GetUserId().IsSet() || Cached->GetUserId().Get(FString()) != UserId.Get(FString()) ||
            !Cached->GetItemName().IsSet() || Cached->GetItemName().Get(FString()) != ItemName ||
            !Cached->GetCount().IsSet()) continue;
        const int64 Delta = Entry->GetCount().Get(0);
        Commits.Add(MakeShared<FSimpleItemMutationSpeculativeCommit>(
            Domain->Cache, NamespaceName, UserId.Get(FString()), InventoryName.Get(FString()), ItemName,
            TimeOffset, ExpectedId, Cached->GetRevision(), false,
            [Delta](const Gs2::Inventory::Model::FSimpleItemPtr& Current)
            {
                if (!Current.IsValid() || !Current->GetCount().IsSet()) return Gs2::Inventory::Model::FSimpleItemPtr(nullptr);
                const int64 Base = Current->GetCount().Get(0);
                if ((Delta > 0 && Base < MIN_int64 + Delta) || (Delta < 0 && Base > MAX_int64 + Delta))
                    return Gs2::Inventory::Model::FSimpleItemPtr(nullptr);
                const int64 Value = Base - Delta;
                if (Value < 0) return Gs2::Inventory::Model::FSimpleItemPtr(nullptr);
                return MakeShared<Gs2::Inventory::Model::FSimpleItem>(*Current)->WithCount(Value)->WithRevision(0);
            }
        ));
    }
    if (Prepared->GetConsumeCounts()->Num() > 0 && Commits.Num() == 0) return nullptr;
    const FString BatchKey = Gs2::Inventory::Model::Cache::FSimpleItemCache::CreateCacheParentKey(
        NamespaceName, UserId, InventoryName, TimeOffset
    );
    const TMap<FString, int64> NoAbsoluteSets;
    const auto Batch = MakeShared<FSimpleItemBatchSpeculativeCommit>(BatchKey, Commits, NoAbsoluteSets, false, false);
    *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
        Batch->CompositionKey(),
        [Batch](const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next)
        { return Batch->TryCompose(Current, HasCurrent, Next); },
        [Batch](const TSharedPtr<void>& State) { Batch->Commit(State); }
    );
    return nullptr;
}

TSharedPtr<FAsyncTask<FConsumeSimpleItemsByUserIdSpeculativeExecutor::FCommitTask>> FConsumeSimpleItemsByUserIdSpeculativeExecutor::Execute(
    const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequestPtr& Request)
{
    return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
}

Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequestPtr FConsumeSimpleItemsByUserIdSpeculativeExecutor::Rate(
    const Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequestPtr& Request, const double Rate)
{
    if (!Request.IsValid() || !Request->GetConsumeCounts().IsValid()) return nullptr;
    for (const auto& Entry : *Request->GetConsumeCounts())
    {
        if (!Entry.IsValid() || !Entry->GetCount().IsSet()) continue;
        FSimpleItemRate Count = FSimpleItemRate::FromInt64(Entry->GetCount().Get(0));
        FSimpleItemRate Value;
        if (!FSimpleItemRate::TryApplyRate(Count, Rate, Value)) return nullptr;
        Entry->WithCount(FSimpleItemRate::SaturateToInt64(Value));
    }
    return Request;
}

Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequestPtr FConsumeSimpleItemsByUserIdSpeculativeExecutor::Rate(
    const Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequestPtr& Request, TBigInt<1024, false> Rate)
{
    if (!Request.IsValid() || !Request->GetConsumeCounts().IsValid()) return nullptr;
    for (const auto& Entry : *Request->GetConsumeCounts())
    {
        if (!Entry.IsValid() || !Entry->GetCount().IsSet()) continue;
        FSimpleItemRate Count = FSimpleItemRate::FromInt64(Entry->GetCount().Get(0));
        FSimpleItemRate Value;
        if (!FSimpleItemRate::TryApplyRate(Count, Rate.ToString(), Value)) return nullptr;
        Entry->WithCount(FSimpleItemRate::SaturateToInt64(Value));
    }
    return Request;
}
}
