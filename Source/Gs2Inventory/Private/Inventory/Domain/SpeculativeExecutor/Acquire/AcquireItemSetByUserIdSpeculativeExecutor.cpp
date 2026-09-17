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
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Inventory/Domain/SpeculativeExecutor/SimpleItemMutationSpeculativeCommit.h"
#include "Inventory/Domain/Model/ItemSetEntry.h"
#include "Inventory/Model/Cache/ItemModel.h"
#include "Inventory/Model/Cache/ItemSet.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{
namespace
{
    using FItemSetPtr = Gs2::Inventory::Model::FItemSetPtr;
    using FItemSetEntryPtr = Gs2::Inventory::Model::FItemSetEntryPtr;
    using FItemModelPtr = Gs2::Inventory::Model::FItemModelPtr;
    using FPreparedCommit = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit;

    FString AcquireItemSetJsonString(const TSharedPtr<FJsonObject>& Json)
    {
        if (!Json.IsValid()) return FString();
        FString Result;
        const auto Writer = TJsonWriterFactory<>::Create(&Result);
        FJsonSerializer::Serialize(Json.ToSharedRef(), Writer);
        return Result;
    }

    FString AcquireItemSetItemJson(const FItemSetPtr& Item)
    {
        return Item.IsValid() ? AcquireItemSetJsonString(Item->ToJson()) : FString();
    }

    FString AcquireItemSetParent(
        const TOptional<FString>& NamespaceName,
        const FString& UserId,
        const FString& InventoryName,
        const TOptional<int32>& TimeOffset
    )
    {
        return Gs2::Inventory::Model::Cache::FItemSetCache::CreateCacheParentKey(
            NamespaceName, UserId, InventoryName, TimeOffset
        );
    }

    FString AcquireItemSetAggregateKey(const FString& ItemName)
    {
        return ItemName + TEXT(":any");
    }

    bool TryGetAcquireItemSetAggregate(
        const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
        const TOptional<FString>& NamespaceName,
        const FString& UserId,
        const FString& InventoryName,
        const FString& ItemName,
        const TOptional<int32>& TimeOffset,
        FItemSetEntryPtr* OutEntry
    )
    {
        if (!Cache.IsValid())
        {
            if (OutEntry) *OutEntry = nullptr;
            return false;
        }
        return Cache->TryGet<Gs2::Inventory::Model::FItemSetEntry>(
            AcquireItemSetParent(NamespaceName, UserId, InventoryName, TimeOffset),
            AcquireItemSetAggregateKey(ItemName), OutEntry
        );
    }

    void PutAcquireItemSetAggregate(
        const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
        const TOptional<FString>& NamespaceName,
        const FString& UserId,
        const FString& InventoryName,
        const FString& ItemName,
        const TOptional<int32>& TimeOffset,
        const TArray<FItemSetPtr>& Items
    )
    {
        if (!Cache.IsValid()) return;
        TArray<FItemSetPtr> Remaining;
        bool HasExpiry = false;
        int64 MinimumExpiry = 0;
        for (const auto& Item : Items)
        {
            if (!Item.IsValid() || !Item->GetCount().IsSet() || Item->GetCount().Get(0) <= 0) continue;
            Remaining.Add(Item);
            if (Item->GetExpiresAt().IsSet() && Item->GetExpiresAt().Get(0) != 0)
            {
                if (!HasExpiry || Item->GetExpiresAt().Get(0) < MinimumExpiry)
                {
                    HasExpiry = true;
                    MinimumExpiry = Item->GetExpiresAt().Get(0);
                }
            }
        }
        for (int32 i = 1; i < Remaining.Num(); ++i)
        {
            const FItemSetPtr Value = Remaining[i];
            int32 Position = i;
            while (Position > 0 && Remaining[Position - 1]->GetCount().Get(0) < Value->GetCount().Get(0))
            {
                Remaining[Position] = Remaining[Position - 1];
                --Position;
            }
            Remaining[Position] = Value;
        }
        const auto Entry = MakeShared<Gs2::Inventory::Model::FItemSetEntry>(Remaining);
        const FDateTime Ttl = HasExpiry
            ? FDateTime::FromUnixTimestamp(0) + FTimespan::FromMilliseconds(MinimumExpiry)
            : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes);
        Cache->Put(
            Gs2::Inventory::Model::FItemSetEntry::TypeName,
            AcquireItemSetParent(NamespaceName, UserId, InventoryName, TimeOffset),
            AcquireItemSetAggregateKey(ItemName), Entry, Ttl
        );
    }

    FString ExpectedItemSetId(
        const FString& Region,
        const FString& OwnerId,
        const FString& NamespaceName,
        const FString& UserId,
        const FString& InventoryName,
        const FString& ItemName,
        const FString& ItemSetName
    )
    {
        return FString::Printf(
            TEXT("grn:gs2:%s:%s:inventory:%s:user:%s:inventory:%s:item:%s:itemSet:%s"),
            *Region, *OwnerId, *NamespaceName, *UserId, *InventoryName, *ItemName, *ItemSetName
        );
    }

    FString ExpectedItemModelId(
        const FString& Region,
        const FString& OwnerId,
        const FString& NamespaceName,
        const FString& InventoryName,
        const FString& ItemName
    )
    {
        return FString::Printf(
            TEXT("grn:gs2:%s:%s:inventory:%s:model:%s:item:%s"),
            *Region, *OwnerId, *NamespaceName, *InventoryName, *ItemName
        );
    }

    bool IsExpectedAcquireItemSet(
        const FItemSetPtr& Item,
        const FString& ExpectedId,
        const FString& ItemSetName,
        const FString& UserId,
        const FString& InventoryName,
        const FString& ItemName
    )
    {
        return Item.IsValid() && Item->GetItemSetId().IsSet() && Item->GetItemSetId().Get(FString()) == ExpectedId &&
            Item->GetName().IsSet() && Item->GetName().Get(FString()) == ItemSetName &&
            Item->GetUserId().IsSet() && Item->GetUserId().Get(FString()) == UserId &&
            Item->GetInventoryName().IsSet() && Item->GetInventoryName().Get(FString()) == InventoryName &&
            Item->GetItemName().IsSet() && Item->GetItemName().Get(FString()) == ItemName &&
            Item->GetCount().IsSet();
    }

    bool IsExpectedModel(
        const FItemModelPtr& Model,
        const FString& ExpectedId,
        const FString& ItemName,
        const int64 StackingLimit,
        const int32 SortValue
    )
    {
        return Model.IsValid() && Model->GetItemModelId().IsSet() && Model->GetItemModelId().Get(FString()) == ExpectedId &&
            Model->GetName().IsSet() && Model->GetName().Get(FString()) == ItemName &&
            Model->GetStackingLimit().IsSet() && Model->GetStackingLimit().Get(0) == StackingLimit &&
            Model->GetSortValue().IsSet() && Model->GetSortValue().Get(0) == SortValue;
    }

    bool CheckedAdd(const int64 Left, const int64 Right, int64& Result)
    {
        if ((Right > 0 && Left > MAX_int64 - Right) || (Right < 0 && Left < MIN_int64 - Right)) return false;
        Result = Left + Right;
        return true;
    }

    class FItemSetAcquireSpeculativeCommit final
    {
        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const TOptional<FString> NamespaceName;
        const FString UserId;
        const FString InventoryName;
        const FString ItemName;
        const FString ItemSetName;
        const TOptional<int32> TimeOffset;
        const FString ExpectedItemSetIdValue;
        const FString ExpectedItemModelIdValue;
        const FString PreparedItemJson;
        const TArray<FString> PreparedAggregateJson;
        const bool HasPreparedAggregate;
        const int64 AcquireCount;
        const int64 StackingLimit;
        const int32 SortValue;
        const TOptional<int64> ExpiresAt;
        const int64 UpdatedAt;

        bool TryGetExpectedAggregate(TArray<FItemSetPtr>& Aggregate, int32& Index) const
        {
            FItemSetEntryPtr Entry;
            if (!TryGetAcquireItemSetAggregate(Cache, NamespaceName, UserId, InventoryName, ItemName, TimeOffset, &Entry) || !Entry.IsValid()) return false;
            Aggregate = Entry->Value;
            Index = -1;
            if (HasPreparedAggregate && Aggregate.Num() != PreparedAggregateJson.Num()) return false;
            TSet<FString> Names;
            for (int32 i = 0; i < Aggregate.Num(); ++i)
            {
                const auto& Candidate = Aggregate[i];
                if (!Candidate.IsValid() || !Candidate->GetName().IsSet() || Candidate->GetName().Get(FString()).IsEmpty() ||
                    !Candidate->GetCount().IsSet() || Names.Contains(Candidate->GetName().Get(FString()))) return false;
                Names.Add(Candidate->GetName().Get(FString()));
                const FString Serialized = AcquireItemSetItemJson(Candidate);
                if (HasPreparedAggregate && Serialized != PreparedAggregateJson[i]) return false;
                FItemSetPtr Direct;
                if (!Gs2::Inventory::Model::Cache::FItemSetCache::TryGet(
                    Cache, NamespaceName, UserId, InventoryName, ItemName,
                    Candidate->GetName(), TimeOffset, &Direct
                ) || !Direct.IsValid() || AcquireItemSetItemJson(Direct) != Serialized) return false;
                if (Candidate->GetName().Get(FString()) == ItemSetName)
                {
                    if (!IsExpectedAcquireItemSet(Candidate, ExpectedItemSetIdValue, ItemSetName, UserId, InventoryName, ItemName) ||
                        Serialized != PreparedItemJson) return false;
                    Index = i;
                }
            }
            return Index >= 0;
        }

        bool IsExpectedModelNow() const
        {
            FItemModelPtr Model;
            return Gs2::Inventory::Model::Cache::FItemModelCache::TryGet(
                Cache, NamespaceName, InventoryName, ItemName, TOptional<int32>(), &Model
            ) && IsExpectedModel(Model, ExpectedItemModelIdValue, ItemName, StackingLimit, SortValue);
        }

    public:
        FItemSetAcquireSpeculativeCommit(
            const Gs2::Core::Domain::FCacheDatabasePtr& InCache,
            const TOptional<FString>& InNamespaceName,
            const FString& InUserId,
            const FString& InInventoryName,
            const FString& InItemName,
            const FString& InItemSetName,
            const TOptional<int32>& InTimeOffset,
            const FString& InExpectedItemSetId,
            const FString& InExpectedItemModelId,
            const FString& InPreparedItemJson,
            const TArray<FString>& InPreparedAggregateJson,
            bool InHasPreparedAggregate,
            int64 InAcquireCount,
            int64 InStackingLimit,
            int32 InSortValue,
            const TOptional<int64>& InExpiresAt,
            int64 InUpdatedAt
        ):
            Cache(InCache), NamespaceName(InNamespaceName), UserId(InUserId), InventoryName(InInventoryName),
            ItemName(InItemName), ItemSetName(InItemSetName), TimeOffset(InTimeOffset),
            ExpectedItemSetIdValue(InExpectedItemSetId), ExpectedItemModelIdValue(InExpectedItemModelId),
            PreparedItemJson(InPreparedItemJson), PreparedAggregateJson(InPreparedAggregateJson),
            HasPreparedAggregate(InHasPreparedAggregate), AcquireCount(InAcquireCount), StackingLimit(InStackingLimit),
            SortValue(InSortValue), ExpiresAt(InExpiresAt), UpdatedAt(InUpdatedAt)
        {
        }

        FString CompositionKey() const
        {
            return Gs2::Inventory::Model::Cache::FItemSetCache::CreateCacheParentKey(
                NamespaceName, UserId, InventoryName, TimeOffset
            ) + TEXT(":") + Gs2::Inventory::Model::Cache::FItemSetCache::CreateCacheKey(ItemName, ItemSetName);
        }

        bool TryCompose(const TSharedPtr<void>& Current, bool HasCurrent, TSharedPtr<void>& Next) const
        {
            try
            {
                if (HasPreparedAggregate)
                {
                    TArray<FItemSetPtr> Aggregate;
                    int32 Index = -1;
                    if (!TryGetExpectedAggregate(Aggregate, Index)) { Next = nullptr; return false; }
                }
                FItemSetPtr Item;
                if (HasCurrent)
                {
                    Item = StaticCastSharedPtr<Gs2::Inventory::Model::FItemSet>(Current);
                }
                else
                {
                    if (!Gs2::Inventory::Model::Cache::FItemSetCache::TryGet(
                        Cache, NamespaceName, UserId, InventoryName, ItemName, ItemSetName, TimeOffset, &Item
                    ) || !IsExpectedAcquireItemSet(Item, ExpectedItemSetIdValue, ItemSetName, UserId, InventoryName, ItemName) ||
                        AcquireItemSetItemJson(Item) != PreparedItemJson) { Next = nullptr; return false; }
                }
                if (!IsExpectedAcquireItemSet(Item, ExpectedItemSetIdValue, ItemSetName, UserId, InventoryName, ItemName) ||
                    !IsExpectedModelNow() || (ExpiresAt.IsSet() &&
                    (!Item->GetExpiresAt().IsSet() || Item->GetExpiresAt().Get(0) != ExpiresAt.Get(0))))
                { Next = nullptr; return false; }
                int64 Count = 0;
                if (!CheckedAdd(Item->GetCount().Get(0), AcquireCount, Count)) { Next = nullptr; return false; }
                const int64 Capped = Count < StackingLimit ? Count : StackingLimit;
                Gs2::Inventory::Model::FItemSetPtr Changed = MakeShared<Gs2::Inventory::Model::FItemSet>(*Item);
                if (!Changed.IsValid()) { Next = nullptr; return false; }
                Changed->WithCount(Capped)->WithSortValue(SortValue)->WithUpdatedAt(UpdatedAt);
                if (!IsExpectedAcquireItemSet(Changed, ExpectedItemSetIdValue, ItemSetName, UserId, InventoryName, ItemName))
                { Next = nullptr; return false; }
                Next = Changed;
                return true;
            }
            catch (...) { Next = nullptr; return false; }
        }

        void Commit(const TSharedPtr<void>& State) const
        {
            try
            {
                const auto Item = StaticCastSharedPtr<Gs2::Inventory::Model::FItemSet>(State);
                if (!IsExpectedAcquireItemSet(Item, ExpectedItemSetIdValue, ItemSetName, UserId, InventoryName, ItemName)) return;
                TArray<FItemSetPtr> Aggregate;
                int32 AggregateIndex = -1;
                const bool HasAggregate = TryGetExpectedAggregate(Aggregate, AggregateIndex);
                if (HasPreparedAggregate && !HasAggregate) return;
                Gs2::Inventory::Model::Cache::FItemSetCache::Put(
                    Cache, NamespaceName, UserId, InventoryName, ItemName, ItemSetName, TimeOffset, Item
                );
                if (HasAggregate)
                {
                    Aggregate[AggregateIndex] = Item;
                    PutAcquireItemSetAggregate(Cache, NamespaceName, UserId, InventoryName, ItemName, TimeOffset, Aggregate);
                }
            }
            catch (...) { }
        }
    };
}

FString FAcquireItemSetByUserIdSpeculativeExecutor::Action()
{
    return FString("Gs2Inventory:AcquireItemSetByUserId");
}

Gs2::Core::Model::FGs2ErrorPtr FAcquireItemSetByUserIdSpeculativeExecutor::Transform(
    const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
    const Gs2::Inventory::Request::FAcquireItemSetByUserIdRequestPtr&,
    TSharedPtr<TArray<Gs2::Inventory::Model::FItemSetPtr>>&
)
{
    return nullptr;
}

FAcquireItemSetByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Inventory::Request::FAcquireItemSetByUserIdRequestPtr& Request
): Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request) {}

FAcquireItemSetByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
    Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request) {}

Gs2::Core::Model::FGs2ErrorPtr FAcquireItemSetByUserIdSpeculativeExecutor::FCommitTask::Action(
    TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
)
{
    *Result = nullptr;
    Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
    if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
    Gs2::Inventory::Request::FAcquireItemSetByUserIdRequestPtr Prepared = nullptr;
    if (Request.IsValid()) Prepared = MakeShared<Gs2::Inventory::Request::FAcquireItemSetByUserIdRequest>(*Request);
    if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() || !Prepared.IsValid() ||
        !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
    if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
        Prepared->WithUserId(Token->GetUserId());
    if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) ||
        !Prepared->GetAcquireCount().IsSet() ||
        (Prepared->GetCreateNewItemSet().IsSet() && Prepared->GetCreateNewItemSet().Get(false))) return nullptr;

    const auto NamespaceName = Prepared->GetNamespaceName();
    const auto InventoryName = Prepared->GetInventoryName();
    const auto ItemName = Prepared->GetItemName();
    const auto UserId = Token->GetUserId();
    const auto TimeOffset = Token->GetTimeOffset();
    const int64 UpdatedAt = static_cast<int64>(FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0) +
        static_cast<int64>(TimeOffset.Get(0)) * 1000;
    const FString Region = Domain->RestSession->RegionName();
    const FString OwnerId = Domain->RestSession->OwnerId();
    const bool Unnamed = !Prepared->GetItemSetName().IsSet() || Prepared->GetItemSetName().Get(FString()).IsEmpty();
    TArray<FString> PreparedAggregate;
    bool HasPreparedAggregate = false;
    FString SelectedItemJson;

    if (Unnamed)
    {
        if (!Prepared->GetAcquireCount().IsSet() || Prepared->GetAcquireCount().Get(0) <= 0) return nullptr;
        FItemSetEntryPtr Entry;
        if (!TryGetAcquireItemSetAggregate(Domain->Cache, NamespaceName, UserId.Get(FString()), InventoryName.Get(FString()),
            ItemName.Get(FString()), TimeOffset, &Entry) || !Entry.IsValid() || Entry->Value.Num() == 0) return nullptr;
        FItemModelPtr Model;
        const FString ExpectedModel = ExpectedItemModelId(Region, OwnerId, NamespaceName.Get(FString()), InventoryName.Get(FString()), ItemName.Get(FString()));
        if (!Gs2::Inventory::Model::Cache::FItemModelCache::TryGet(
            Domain->Cache, NamespaceName, InventoryName, ItemName, TOptional<int32>(), &Model) || !Model.IsValid() ||
            !Model->GetItemModelId().IsSet() || Model->GetItemModelId().Get(FString()) != ExpectedModel ||
            !Model->GetName().IsSet() || Model->GetName().Get(FString()) != ItemName.Get(FString()) ||
            !Model->GetStackingLimit().IsSet() || !Model->GetSortValue().IsSet()) return nullptr;
        TSet<FString> Names;
        const int64 EffectiveExpiresAt = Prepared->GetExpiresAt().Get(0);
        FItemSetPtr Selected = nullptr;
        for (const auto& Candidate : Entry->Value)
        {
            const FString CandidateName = Candidate.IsValid() && Candidate->GetName().IsSet()
                ? Candidate->GetName().Get(FString()) : FString();
            const FString Expected = ExpectedItemSetId(Region, OwnerId, NamespaceName.Get(FString()), UserId.Get(FString()),
                InventoryName.Get(FString()), ItemName.Get(FString()), CandidateName);
            if (!Candidate.IsValid() || CandidateName.IsEmpty() || Names.Contains(CandidateName) ||
                !Candidate->GetItemSetId().IsSet() || Candidate->GetItemSetId().Get(FString()) != Expected ||
                !Candidate->GetUserId().IsSet() || Candidate->GetUserId().Get(FString()) != UserId.Get(FString()) ||
                !Candidate->GetInventoryName().IsSet() || Candidate->GetInventoryName().Get(FString()) != InventoryName.Get(FString()) ||
                !Candidate->GetItemName().IsSet() || Candidate->GetItemName().Get(FString()) != ItemName.Get(FString()) ||
                !Candidate->GetCount().IsSet() || Candidate->GetCount().Get(0) <= 0 ||
                Candidate->GetCount().Get(0) > Model->GetStackingLimit().Get(0) || !Candidate->GetExpiresAt().IsSet() ||
                (Candidate->GetExpiresAt().Get(0) != 0 && Candidate->GetExpiresAt().Get(0) <= UpdatedAt)) return nullptr;
            Names.Add(CandidateName);
            const FString Serialized = AcquireItemSetItemJson(Candidate);
            PreparedAggregate.Add(Serialized);
            FItemSetPtr Direct;
            if (!Gs2::Inventory::Model::Cache::FItemSetCache::TryGet(
                Domain->Cache, NamespaceName, UserId, InventoryName, ItemName, CandidateName, TimeOffset, &Direct) ||
                !Direct.IsValid() || AcquireItemSetItemJson(Direct) != Serialized) return nullptr;
            if (Candidate->GetExpiresAt().Get(0) != EffectiveExpiresAt) continue;
            const int64 Room = Model->GetStackingLimit().Get(0) - Candidate->GetCount().Get(0);
            if (Room <= 0) continue;
            if (Prepared->GetAcquireCount().Get(0) > Room) return nullptr;
            if (Selected.IsValid()) return nullptr;
            Selected = Candidate;
        }
        if (!Selected.IsValid()) return nullptr;
        Prepared->WithItemSetName(Selected->GetName());
        SelectedItemJson = AcquireItemSetItemJson(Selected);
        HasPreparedAggregate = true;
    }

    const FString ItemSetName = Prepared->GetItemSetName().Get(FString());
    const FString ExpectedId = ExpectedItemSetId(Region, OwnerId, NamespaceName.Get(FString()), UserId.Get(FString()),
        InventoryName.Get(FString()), ItemName.Get(FString()), ItemSetName);
    const FString ExpectedModel = ExpectedItemModelId(Region, OwnerId, NamespaceName.Get(FString()), InventoryName.Get(FString()), ItemName.Get(FString()));
    FItemSetPtr Item;
    FItemModelPtr Model;
    if (!Gs2::Inventory::Model::Cache::FItemSetCache::TryGet(
        Domain->Cache, NamespaceName, UserId, InventoryName, ItemName, ItemSetName, TimeOffset, &Item) ||
        !IsExpectedAcquireItemSet(Item, ExpectedId, ItemSetName, UserId.Get(FString()), InventoryName.Get(FString()), ItemName.Get(FString())) ||
        !Gs2::Inventory::Model::Cache::FItemModelCache::TryGet(
        Domain->Cache, NamespaceName, InventoryName, ItemName, TOptional<int32>(), &Model) ||
        !Model.IsValid() || !Model->GetStackingLimit().IsSet() || !Model->GetSortValue().IsSet() ||
        !IsExpectedModel(Model, ExpectedModel, ItemName.Get(FString()), Model->GetStackingLimit().Get(0), Model->GetSortValue().Get(0)) ||
        (Prepared->GetExpiresAt().IsSet() && (!Item->GetExpiresAt().IsSet() || Item->GetExpiresAt().Get(0) != Prepared->GetExpiresAt().Get(0)))) return nullptr;
    if (HasPreparedAggregate)
    {
        int64 CheckedCount = 0;
        if (AcquireItemSetItemJson(Item) != SelectedItemJson ||
            !CheckedAdd(Item->GetCount().Get(0), Prepared->GetAcquireCount().Get(0), CheckedCount) ||
            CheckedCount > Model->GetStackingLimit().Get(0)) return nullptr;
    }
    const TArray<FString> AggregateSnapshot = PreparedAggregate;
    const FString ItemSnapshot = AcquireItemSetItemJson(Item);
    const auto Commit = MakeShared<FItemSetAcquireSpeculativeCommit>(
        Domain->Cache, NamespaceName, UserId.Get(FString()), InventoryName.Get(FString()), ItemName.Get(FString()), ItemSetName,
        TimeOffset, ExpectedId, ExpectedModel, ItemSnapshot, AggregateSnapshot, HasPreparedAggregate,
        Prepared->GetAcquireCount().Get(0), Model->GetStackingLimit().Get(0), Model->GetSortValue().Get(0),
        Prepared->GetExpiresAt(), UpdatedAt
    );
    *Result = FPreparedCommit::CreateComposable(
        Commit->CompositionKey(),
        [Commit](const TSharedPtr<void>& Current, bool HasCurrent, TSharedPtr<void>& Next)
        { return Commit->TryCompose(Current, HasCurrent, Next); },
        [Commit](const TSharedPtr<void>& State) { Commit->Commit(State); }
    );
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
    const Gs2::Inventory::Request::FAcquireItemSetByUserIdRequestPtr& Request, const double Rate)
{
    if (!Request.IsValid() || !Request->GetAcquireCount().IsSet()) return nullptr;
    Private::FSimpleItemRate Count = Private::FSimpleItemRate::FromInt64(Request->GetAcquireCount().Get(0));
    Private::FSimpleItemRate Value;
    if (!Private::FSimpleItemRate::TryApplyRate(Count, Rate, Value)) return nullptr;
    Request->WithAcquireCount(Private::FSimpleItemRate::SaturateToInt64(Value));
    return Request;
}

Gs2::Inventory::Request::FAcquireItemSetByUserIdRequestPtr FAcquireItemSetByUserIdSpeculativeExecutor::Rate(
    const Gs2::Inventory::Request::FAcquireItemSetByUserIdRequestPtr& Request, TBigInt<1024, false> Rate)
{
    if (!Request.IsValid() || !Request->GetAcquireCount().IsSet()) return nullptr;
    Private::FSimpleItemRate Count = Private::FSimpleItemRate::FromInt64(Request->GetAcquireCount().Get(0));
    Private::FSimpleItemRate Value;
    if (!Private::FSimpleItemRate::TryApplyRate(Count, Rate.ToString(), Value)) return nullptr;
    Request->WithAcquireCount(Private::FSimpleItemRate::SaturateToInt64(Value));
    return Request;
}
}
