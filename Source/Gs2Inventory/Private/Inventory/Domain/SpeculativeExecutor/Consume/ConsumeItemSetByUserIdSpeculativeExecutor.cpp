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
#pragma warning (disable: 4458)
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
#endif

#include "Inventory/Domain/SpeculativeExecutor/Consume/ConsumeItemSetByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Inventory/Domain/Gs2Inventory.h"
#include "Inventory/Domain/Model/ItemSetEntry.h"
#include "Inventory/Model/Cache/Inventory.h"
#include "Inventory/Model/Cache/InventoryModel.h"
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
    using FRequestPtr = Gs2::Inventory::Request::FConsumeItemSetByUserIdRequestPtr;
    using FPreparedCommit = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit;

    FString JsonString(const TSharedPtr<FJsonObject>& Json)
    {
        if (!Json.IsValid()) return FString();
        FString Result;
        const auto Writer = TJsonWriterFactory<>::Create(&Result);
        FJsonSerializer::Serialize(Json.ToSharedRef(), Writer);
        return Result;
    }

    FString ItemJson(const FItemSetPtr& Item)
    {
        return Item.IsValid() ? JsonString(Item->ToJson()) : FString();
    }

    FString ItemSetParent(
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

    FString AggregateKey(const FString& ItemName)
    {
        return ItemName + TEXT(":any");
    }

    bool TryGetAggregate(
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
            ItemSetParent(NamespaceName, UserId, InventoryName, TimeOffset),
            AggregateKey(ItemName), OutEntry
        );
    }

    void PutAggregate(
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
            if (!Item.IsValid() || !Item->GetCount().IsSet() ||
                Item->GetCount().Get(0) <= 0) continue;
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
            while (Position > 0 &&
                   Remaining[Position - 1]->GetCount().Get(0) < Value->GetCount().Get(0))
            {
                Remaining[Position] = Remaining[Position - 1];
                --Position;
            }
            Remaining[Position] = Value;
        }
        FItemSetEntryPtr Entry = MakeShared<Gs2::Inventory::Model::FItemSetEntry>(Remaining);
        const FDateTime Ttl = HasExpiry
            ? FDateTime::FromUnixTimestamp(0) + FTimespan::FromMilliseconds(MinimumExpiry)
            : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes);
        Cache->Put(
            Gs2::Inventory::Model::FItemSetEntry::TypeName,
            ItemSetParent(NamespaceName, UserId, InventoryName, TimeOffset),
            AggregateKey(ItemName), Entry, Ttl
        );
    }

    bool IsExpectedItem(
        const FItemSetPtr& Item,
        const FString& ExpectedId,
        const FString& ItemSetName,
        const FString& UserId,
        const FString& InventoryName,
        const FString& ItemName
    )
    {
        return Item.IsValid() && Item->GetItemSetId().IsSet() &&
            Item->GetItemSetId().Get(FString()) == ExpectedId &&
            Item->GetName().IsSet() && Item->GetName().Get(FString()) == ItemSetName &&
            Item->GetUserId().IsSet() && Item->GetUserId().Get(FString()) == UserId &&
            Item->GetInventoryName().IsSet() && Item->GetInventoryName().Get(FString()) == InventoryName &&
            Item->GetItemName().IsSet() && Item->GetItemName().Get(FString()) == ItemName &&
            Item->GetCount().IsSet();
    }

    bool IsExpectedItemModel(
        const Gs2::Inventory::Model::FItemModelPtr& Model,
        const FString& ExpectedId,
        const FString& ItemName,
        const TOptional<int32>& SortValue
    )
    {
        return Model.IsValid() && SortValue.IsSet() &&
            Model->GetItemModelId().IsSet() && Model->GetItemModelId().Get(FString()) == ExpectedId &&
            Model->GetName().IsSet() && Model->GetName().Get(FString()) == ItemName &&
            Model->GetSortValue().IsSet() && Model->GetSortValue().Get(0) == SortValue.Get(0);
    }

    bool IsExpectedInventoryModel(
        const Gs2::Inventory::Model::FInventoryModelPtr& Model,
        const FString& ExpectedId,
        const FString& InventoryName,
        const TOptional<bool>& ProtectReferencedItem
    )
    {
        return Model.IsValid() && ProtectReferencedItem.IsSet() &&
            Model->GetInventoryModelId().IsSet() && Model->GetInventoryModelId().Get(FString()) == ExpectedId &&
            Model->GetName().IsSet() && Model->GetName().Get(FString()) == InventoryName &&
            Model->GetProtectReferencedItem().IsSet() &&
            Model->GetProtectReferencedItem().Get(false) == ProtectReferencedItem.Get(false);
    }

    bool CheckedSubtract(const int64 Base, const int64 Delta, int64& Result)
    {
        if ((Delta > 0 && Base < TNumericLimits<int64>::Min() + Delta) ||
            (Delta < 0 && Base > TNumericLimits<int64>::Max() + Delta)) return false;
        Result = Base - Delta;
        return true;
    }

    bool AddCountChecked(const int64 Base, const int64 Delta, int64& Result)
    {
        if (Delta > 0 && Base > TNumericLimits<int64>::Max() - Delta) return false;
        Result = Base + Delta;
        return true;
    }

    struct FRateUInt128 final
    {
        uint32 Words[4] = {0, 0, 0, 0};

        static FRateUInt128 Multiply(const uint64 Left, const uint64 Right)
        {
            const uint32 LeftWords[2] = {
                static_cast<uint32>(Left), static_cast<uint32>(Left >> 32)
            };
            const uint32 RightWords[2] = {
                static_cast<uint32>(Right), static_cast<uint32>(Right >> 32)
            };
            FRateUInt128 Result;
            for (int32 i = 0; i < 2; ++i)
            {
                uint64 Carry = 0;
                for (int32 j = 0; j < 2; ++j)
                {
                    const int32 Index = i + j;
                    const uint64 Product = static_cast<uint64>(LeftWords[i]) * RightWords[j] +
                        Result.Words[Index] + Carry;
                    Result.Words[Index] = static_cast<uint32>(Product);
                    Carry = Product >> 32;
                }
                int32 Index = i + 2;
                while (Carry != 0 && Index < 4)
                {
                    const uint64 Sum = static_cast<uint64>(Result.Words[Index]) + Carry;
                    Result.Words[Index] = static_cast<uint32>(Sum);
                    Carry = Sum >> 32;
                    ++Index;
                }
            }
            return Result;
        }

        bool IsZero() const
        {
            return Words[0] == 0 && Words[1] == 0 && Words[2] == 0 && Words[3] == 0;
        }

        int32 BitLength() const
        {
            for (int32 i = 3; i >= 0; --i)
            {
                if (Words[i] == 0) continue;
                uint32 Value = Words[i];
                int32 Bits = 0;
                while (Value != 0)
                {
                    Value >>= 1;
                    ++Bits;
                }
                return i * 32 + Bits;
            }
            return 0;
        }

        FRateUInt128 ShiftRight(const int32 Shift) const
        {
            if (Shift <= 0) return *this;
            if (Shift >= 128) return FRateUInt128();
            FRateUInt128 Result;
            const int32 WordShift = Shift / 32;
            const int32 BitShift = Shift % 32;
            for (int32 i = WordShift; i < 4; ++i)
            {
                const int32 Target = i - WordShift;
                Result.Words[Target] |= Words[i] >> BitShift;
                if (BitShift != 0 && i + 1 < 4)
                {
                    Result.Words[Target] |= Words[i + 1] << (32 - BitShift);
                }
            }
            return Result;
        }

        FRateUInt128 ShiftLeft(const int32 Shift) const
        {
            if (Shift <= 0) return *this;
            if (Shift >= 128) return FRateUInt128();
            FRateUInt128 Result;
            const int32 WordShift = Shift / 32;
            const int32 BitShift = Shift % 32;
            for (int32 i = 0; i < 4 - WordShift; ++i)
            {
                const int32 Target = i + WordShift;
                Result.Words[Target] |= Words[i] << BitShift;
                if (BitShift != 0 && Target + 1 < 4)
                {
                    Result.Words[Target + 1] |= Words[i] >> (32 - BitShift);
                }
            }
            return Result;
        }

        FRateUInt128 LowBits(const int32 Count) const
        {
            if (Count <= 0) return FRateUInt128();
            if (Count >= 128) return *this;
            FRateUInt128 Result = *this;
            const int32 WordCount = Count / 32;
            const int32 BitCount = Count % 32;
            for (int32 i = WordCount + (BitCount == 0 ? 0 : 1); i < 4; ++i) Result.Words[i] = 0;
            if (BitCount != 0) Result.Words[WordCount] &= (1U << BitCount) - 1U;
            return Result;
        }

        int32 Compare(const FRateUInt128& Other) const
        {
            for (int32 i = 3; i >= 0; --i)
            {
                if (Words[i] != Other.Words[i]) return Words[i] < Other.Words[i] ? -1 : 1;
            }
            return 0;
        }

        void AddOne()
        {
            for (int32 i = 0; i < 4; ++i)
            {
                ++Words[i];
                if (Words[i] != 0) break;
            }
        }

        bool IsPowerOfTwo() const
        {
            bool Found = false;
            for (const uint32 Word : Words)
            {
                if (Word == 0) continue;
                if (Found || (Word & (Word - 1)) != 0) return false;
                Found = true;
            }
            return Found;
        }

        uint64 ToUint64() const
        {
            return static_cast<uint64>(Words[0]) | (static_cast<uint64>(Words[1]) << 32);
        }
    };

    bool TryApplyRateExact(const int64 Count, const double Rate, int64& Result)
    {
        uint64 RateBits = 0;
        FMemory::Memcpy(&RateBits, &Rate, sizeof(RateBits));
        const uint64 ExponentBits = (RateBits >> 52) & 0x7ffULL;
        if (ExponentBits == 0x7ffULL)
        {
            return false;
        }
        uint64 Mantissa = RateBits & 0x000fffffffffffffULL;
        int32 Exponent = -1074;
        if (ExponentBits != 0)
        {
            Mantissa += 1ULL << 52;
            Exponent = static_cast<int32>(ExponentBits) - 1075;
        }
        const bool CountNegative = Count < 0;
        const uint64 CountMagnitude = CountNegative
            ? static_cast<uint64>(-(Count + 1)) + 1
            : static_cast<uint64>(Count);
        FRateUInt128 Product = FRateUInt128::Multiply(CountMagnitude, Mantissa);
        const bool Negative = CountNegative != ((RateBits >> 63) != 0);
        if (!Product.IsZero())
        {
            const int32 BitLength = Product.BitLength();
            if (BitLength > 100)
            {
                int32 Shift = BitLength - 100;
                const FRateUInt128 Rounded = Product.ShiftRight(Shift);
                const FRateUInt128 Remainder = Product.LowBits(Shift);
                const FRateUInt128 Half = FRateUInt128().ShiftLeft(Shift - 1);
                Product = Rounded;
                if (Remainder.Compare(Half) > 0 ||
                    (Remainder.Compare(Half) == 0 && (Product.Words[0] & 1) != 0)) Product.AddOne();
                if (Product.BitLength() > 100)
                {
                    Product = Product.ShiftRight(1);
                    ++Shift;
                }
                Exponent += Shift;
            }
        }
        if (!Product.IsZero() && Exponent >= 0)
        {
            const int32 FinalBitLength = Product.BitLength() + Exponent;
            if ((!Negative && FinalBitLength > 63) || (Negative && FinalBitLength > 64)) return false;
        }
        const FRateUInt128 FinalMagnitude = Exponent >= 0
            ? Product.ShiftLeft(Exponent)
            : Product.ShiftRight(-Exponent);
        const int32 FinalBits = FinalMagnitude.BitLength();
        if ((!Negative && FinalBits > 63) || (Negative && FinalBits > 64) ||
            (Negative && FinalBits == 64 && !FinalMagnitude.IsPowerOfTwo())) return false;
        const uint64 Magnitude = FinalMagnitude.ToUint64();
        if (Negative)
        {
            Result = Magnitude == (1ULL << 63) ? TNumericLimits<int64>::Min() : -static_cast<int64>(Magnitude);
        }
        else
        {
            Result = static_cast<int64>(Magnitude);
        }
        return true;
    }

    bool IsReferenceOf(const FItemSetPtr& Item)
    {
        const auto References = Item.IsValid() ? Item->GetReferenceOf() : nullptr;
        return References.IsValid() && References->Num() > 0;
    }

    class FItemSetCountSpeculativeCommit final
    {
    public:
        using FStatusPtr = Gs2::Inventory::Model::FItemSetPtr;

    private:
        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const TOptional<FString> NamespaceName;
        const FString UserId;
        const FString InventoryName;
        const FString ItemName;
        const FString ItemSetName;
        const TOptional<int32> TimeOffset;
        const FString ExpectedId;
        const FString ExpectedItemModelId;
        const FString ExpectedInventoryModelId;
        const FString PreparedItemJson;
        TOptional<FString> PreparedAggregateJson;
        const int64 ConsumeCount;
        const TOptional<bool> ProtectReferencedItem;
        const TOptional<int32> SortValue;
        const int64 UpdatedAt;
        const FString ExpectedInventoryId;
        const TOptional<FString> PreparedInventoryJson;
        const bool StartedPositive;

        bool TryExpectedAggregate(TArray<FItemSetPtr>& Aggregate, int32& Index) const
        {
            FItemSetEntryPtr Entry;
            if (!TryGetAggregate(Cache, NamespaceName, UserId, InventoryName,
                ItemName, TimeOffset, &Entry) || !Entry.IsValid()) return false;
            Aggregate = Entry->Value;
            Index = -1;
            const FString Snapshot = PreparedAggregateJson.IsSet()
                ? PreparedAggregateJson.Get(FString()) : PreparedItemJson;
            TSet<FString> Names;
            for (int32 i = 0; i < Aggregate.Num(); ++i)
            {
                const auto& Candidate = Aggregate[i];
                if (!Candidate.IsValid() || !Candidate->GetName().IsSet() ||
                    Candidate->GetName().Get(FString()).IsEmpty() ||
                    !Candidate->GetCount().IsSet() ||
                    Names.Contains(Candidate->GetName().Get(FString()))) return false;
                Names.Add(Candidate->GetName().Get(FString()));
                if (Candidate->GetName().Get(FString()) == ItemSetName)
                {
                    if (!IsExpectedItem(Candidate, ExpectedId, ItemSetName, UserId,
                        InventoryName, ItemName) || ItemJson(Candidate) != Snapshot) return false;
                    Index = i;
                }
            }
            return Index >= 0;
        }

        void TryDecrementInventoryCapacity() const
        {
            if (!PreparedInventoryJson.IsSet()) return;
            try
            {
                Gs2::Inventory::Model::FInventoryPtr Inventory;
                if (!Gs2::Inventory::Model::Cache::FInventoryCache::TryGet(
                    Cache, NamespaceName, UserId, InventoryName, TimeOffset, &Inventory) ||
                    !Inventory.IsValid() || !Inventory->GetInventoryId().IsSet() ||
                    Inventory->GetInventoryId().Get(FString()) != ExpectedInventoryId ||
                    !Inventory->GetUserId().IsSet() || Inventory->GetUserId().Get(FString()) != UserId ||
                    !Inventory->GetInventoryName().IsSet() || Inventory->GetInventoryName().Get(FString()) != InventoryName ||
                    !Inventory->GetCurrentInventoryCapacityUsage().IsSet() ||
                    !Inventory->GetRevision().IsSet() || Inventory->GetRevision().Get(0) < 0) return;
                if (Inventory->GetRevision().Get(0) > 0 &&
                    JsonString(Inventory->ToJson()) != PreparedInventoryJson.Get(FString())) return;
                Gs2::Inventory::Model::FInventoryPtr Changed =
                    MakeShared<Gs2::Inventory::Model::FInventory>(*Inventory);
                if (!Changed.IsValid()) return;
                const int64 Usage = Changed->GetCurrentInventoryCapacityUsage().Get(0);
                Changed->WithCurrentInventoryCapacityUsage(static_cast<int32>(FMath::Max<int64>(Usage - 1, 0)))
                    ->WithUpdatedAt(UpdatedAt)->WithRevision(0);
                Cache->Put(
                    Gs2::Inventory::Model::FInventory::TypeName,
                    Gs2::Inventory::Model::Cache::FInventoryCache::CreateCacheParentKey(
                        NamespaceName, UserId, TimeOffset),
                    Gs2::Inventory::Model::Cache::FInventoryCache::CreateCacheKey(InventoryName),
                    Changed,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            catch (...) { }
        }

    public:
        FItemSetCountSpeculativeCommit(
            const Gs2::Core::Domain::FCacheDatabasePtr& InCache,
            const TOptional<FString>& InNamespaceName,
            const FString& InUserId,
            const FString& InInventoryName,
            const FString& InItemName,
            const FString& InItemSetName,
            const TOptional<int32>& InTimeOffset,
            const FString& InExpectedId,
            const FString& InExpectedItemModelId,
            const FString& InExpectedInventoryModelId,
            const FString& InPreparedItemJson,
            const int64 InConsumeCount,
            const TOptional<bool>& InProtectReferencedItem,
            const TOptional<int32>& InSortValue,
            const int64 InUpdatedAt,
            const FString& InExpectedInventoryId,
            const TOptional<FString>& InPreparedInventoryJson,
            const bool InStartedPositive
        ):
            Cache(InCache), NamespaceName(InNamespaceName), UserId(InUserId),
            InventoryName(InInventoryName), ItemName(InItemName), ItemSetName(InItemSetName),
            TimeOffset(InTimeOffset), ExpectedId(InExpectedId),
            ExpectedItemModelId(InExpectedItemModelId), ExpectedInventoryModelId(InExpectedInventoryModelId),
            PreparedItemJson(InPreparedItemJson), ConsumeCount(InConsumeCount),
            ProtectReferencedItem(InProtectReferencedItem), SortValue(InSortValue),
            UpdatedAt(InUpdatedAt), ExpectedInventoryId(InExpectedInventoryId),
            PreparedInventoryJson(InPreparedInventoryJson), StartedPositive(InStartedPositive)
        {
        }

        void RequireAggregate(const FString& PreparedAggregate)
        {
            PreparedAggregateJson = PreparedAggregate;
        }

        FString CompositionKey() const
        {
            return Gs2::Inventory::Model::Cache::FItemSetCache::CreateCacheParentKey(
                NamespaceName, UserId, InventoryName, TimeOffset
            ) + TEXT(":") + Gs2::Inventory::Model::Cache::FItemSetCache::CreateCacheKey(
                ItemName, ItemSetName
            );
        }

        bool TryCompose(
            const TSharedPtr<void>& Current,
            const bool HasCurrent,
            TSharedPtr<void>& Next
        ) const
        {
            try
            {
                if (PreparedAggregateJson.IsSet())
                {
                    TArray<FItemSetPtr> Aggregate;
                    int32 Index;
                    if (!TryExpectedAggregate(Aggregate, Index) || Aggregate.Num() != 1 || Index != 0)
                    {
                        Next = nullptr;
                        return false;
                    }
                }
                FItemSetPtr Item;
                if (HasCurrent)
                {
                    if (!Current.IsValid()) { Next = nullptr; return false; }
                    Item = StaticCastSharedPtr<Gs2::Inventory::Model::FItemSet>(Current);
                }
                else
                {
                    if (!Gs2::Inventory::Model::Cache::FItemSetCache::TryGet(
                        Cache, NamespaceName, UserId, InventoryName, ItemName,
                        ItemSetName, TimeOffset, &Item) || !Item.IsValid() ||
                        (PreparedAggregateJson.IsSet() && ItemJson(Item) != PreparedItemJson))
                    {
                        Next = nullptr;
                        return false;
                    }
                }
                if (!IsExpectedItem(Item, ExpectedId, ItemSetName, UserId, InventoryName, ItemName))
                {
                    Next = nullptr;
                    return false;
                }
                if (ConsumeCount <= 0)
                {
                    Next = Item;
                    return true;
                }
                if (IsReferenceOf(Item))
                {
                    if (!ProtectReferencedItem.IsSet() || ProtectReferencedItem.Get(false))
                    {
                        Next = nullptr;
                        return false;
                    }
                    Gs2::Inventory::Model::FInventoryModelPtr Model;
                    if (!Gs2::Inventory::Model::Cache::FInventoryModelCache::TryGet(
                        Cache, NamespaceName, InventoryName, TOptional<int32>(), &Model) ||
                        !IsExpectedInventoryModel(Model, ExpectedInventoryModelId,
                            InventoryName, ProtectReferencedItem))
                    {
                        Next = nullptr;
                        return false;
                    }
                }
                if (Item->GetCount().Get(0) < ConsumeCount)
                {
                    Next = nullptr;
                    return false;
                }
                int64 ChangedCount;
                if (!CheckedSubtract(Item->GetCount().Get(0), ConsumeCount, ChangedCount) || ChangedCount < 0)
                {
                    Next = nullptr;
                    return false;
                }
                FItemSetPtr Changed = MakeShared<Gs2::Inventory::Model::FItemSet>(*Item);
                if (!Changed.IsValid()) { Next = nullptr; return false; }
                Changed->WithCount(ChangedCount);
                if (SortValue.IsSet())
                {
                    Gs2::Inventory::Model::FItemModelPtr ItemModel;
                    if (Gs2::Inventory::Model::Cache::FItemModelCache::TryGet(
                        Cache, NamespaceName, InventoryName, ItemName, TOptional<int32>(), &ItemModel) &&
                        IsExpectedItemModel(ItemModel, ExpectedItemModelId, ItemName, SortValue))
                    {
                        Changed->WithSortValue(SortValue);
                    }
                }
                Changed->WithUpdatedAt(UpdatedAt);
                if (!IsExpectedItem(Changed, ExpectedId, ItemSetName, UserId, InventoryName, ItemName))
                {
                    Next = nullptr;
                    return false;
                }
                Next = Changed;
                return true;
            }
            catch (...)
            {
                Next = nullptr;
                return false;
            }
        }

        void Commit(const TSharedPtr<void>& State, const bool UpdateAggregate = true) const
        {
            if (!State.IsValid()) return;
            const auto Item = StaticCastSharedPtr<Gs2::Inventory::Model::FItemSet>(State);
            if (!IsExpectedItem(Item, ExpectedId, ItemSetName, UserId, InventoryName, ItemName)) return;
            TArray<FItemSetPtr> Aggregate;
            int32 AggregateIndex;
            const bool HasAggregate = TryExpectedAggregate(Aggregate, AggregateIndex);
            if (UpdateAggregate && PreparedAggregateJson.IsSet() &&
                (!HasAggregate || Aggregate.Num() != 1 || AggregateIndex != 0)) return;
            Gs2::Inventory::Model::Cache::FItemSetCache::Put(
                Cache, NamespaceName, UserId, InventoryName, ItemName, ItemSetName,
                TimeOffset, Item
            );
            if (UpdateAggregate && HasAggregate)
            {
                Aggregate[AggregateIndex] = Item;
                PutAggregate(Cache, NamespaceName, UserId, InventoryName, ItemName, TimeOffset, Aggregate);
            }
            if (StartedPositive && Item->GetCount().IsSet() && Item->GetCount().Get(0) == 0)
            {
                TryDecrementInventoryCapacity();
            }
        }

        const FString& PreparedItem() const { return PreparedItemJson; }
        const FString& ItemNameValue() const { return ItemName; }
        const FString& InventoryNameValue() const { return InventoryName; }
        const TOptional<FString>& NamespaceNameValue() const { return NamespaceName; }
        const FString& UserIdValue() const { return UserId; }
        const TOptional<int32>& TimeOffsetValue() const { return TimeOffset; }

        static TSharedPtr<FItemSetCountSpeculativeCommit> Prepare(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const Gs2::Auth::Model::FAccessTokenPtr& Token,
            const FRequestPtr& Request
        )
        {
            if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Domain->Cache.IsValid() ||
                !Token.IsValid() || !Request.IsValid() || !Request->GetNamespaceName().IsSet() ||
                !Request->GetInventoryName().IsSet() || !Request->GetItemName().IsSet() ||
                !Request->GetItemSetName().IsSet() || !Request->GetConsumeCount().IsSet()) return nullptr;
            const FString Namespace = Request->GetNamespaceName().Get(FString());
            const FString Inventory = Request->GetInventoryName().Get(FString());
            const FString Item = Request->GetItemName().Get(FString());
            const FString ItemSet = Request->GetItemSetName().Get(FString());
            const FString User = Token->GetUserId().Get(FString());
            const TOptional<int32> Offset = Token->GetTimeOffset();
            const FString Expected = FString::Printf(
                TEXT("grn:gs2:%s:%s:inventory:%s:user:%s:inventory:%s:item:%s:itemSet:%s"),
                *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *Namespace,
                *User, *Inventory, *Item, *ItemSet
            );
            const FString ExpectedItemModel = FString::Printf(
                TEXT("grn:gs2:%s:%s:inventory:%s:model:%s:item:%s"),
                *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *Namespace,
                *Inventory, *Item
            );
            const FString ExpectedInventoryModel = FString::Printf(
                TEXT("grn:gs2:%s:%s:inventory:%s:model:%s"),
                *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *Namespace, *Inventory
            );
            const FString ExpectedInventory = FString::Printf(
                TEXT("grn:gs2:%s:%s:inventory:%s:user:%s:inventory:%s"),
                *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *Namespace, *User, *Inventory
            );

            Gs2::Inventory::Model::FItemSetPtr CachedItem;
            if (!Gs2::Inventory::Model::Cache::FItemSetCache::TryGet(
                Domain->Cache, Namespace, User, Inventory, Item, ItemSet, Offset, &CachedItem) ||
                !IsExpectedItem(CachedItem, Expected, ItemSet, User, Inventory, Item)) return nullptr;

            TOptional<int32> Sort;
            Gs2::Inventory::Model::FItemModelPtr ItemModel;
            if (Gs2::Inventory::Model::Cache::FItemModelCache::TryGet(
                Domain->Cache, Namespace, Inventory, Item, TOptional<int32>(), &ItemModel) &&
                ItemModel.IsValid() && ItemModel->GetItemModelId().IsSet() &&
                ItemModel->GetItemModelId().Get(FString()) == ExpectedItemModel &&
                ItemModel->GetName().IsSet() && ItemModel->GetName().Get(FString()) == Item &&
                ItemModel->GetSortValue().IsSet()) Sort = ItemModel->GetSortValue();

            TOptional<bool> Protect;
            Gs2::Inventory::Model::FInventoryModelPtr InventoryModel;
            if (Gs2::Inventory::Model::Cache::FInventoryModelCache::TryGet(
                Domain->Cache, Namespace, Inventory, TOptional<int32>(), &InventoryModel) &&
                InventoryModel.IsValid() && InventoryModel->GetInventoryModelId().IsSet() &&
                InventoryModel->GetInventoryModelId().Get(FString()) == ExpectedInventoryModel &&
                InventoryModel->GetName().IsSet() && InventoryModel->GetName().Get(FString()) == Inventory &&
                InventoryModel->GetProtectReferencedItem().IsSet()) Protect = InventoryModel->GetProtectReferencedItem();
            if (IsReferenceOf(CachedItem) && !Protect.IsSet()) return nullptr;

            TOptional<FString> PreparedInventory;
            Gs2::Inventory::Model::FInventoryPtr InventoryObject;
            if (Gs2::Inventory::Model::Cache::FInventoryCache::TryGet(
                Domain->Cache, Namespace, User, Inventory, Offset, &InventoryObject) &&
                InventoryObject.IsValid() && InventoryObject->GetInventoryId().IsSet() &&
                InventoryObject->GetInventoryId().Get(FString()) == ExpectedInventory &&
                InventoryObject->GetUserId().IsSet() && InventoryObject->GetUserId().Get(FString()) == User &&
                InventoryObject->GetInventoryName().IsSet() && InventoryObject->GetInventoryName().Get(FString()) == Inventory &&
                InventoryObject->GetCurrentInventoryCapacityUsage().IsSet() &&
                InventoryObject->GetRevision().IsSet() && InventoryObject->GetRevision().Get(0) >= 0)
                PreparedInventory = JsonString(InventoryObject->ToJson());
            const int64 Updated = static_cast<int64>(FDateTime::Now().ToUnixTimestampDecimal() * 1000.0) +
                static_cast<int64>(Offset.Get(0)) * 1000;
            return MakeShared<FItemSetCountSpeculativeCommit>(
                Domain->Cache, Namespace, User, Inventory, Item, ItemSet, Offset,
                Expected, ExpectedItemModel, ExpectedInventoryModel, ItemJson(CachedItem),
                Request->GetConsumeCount().Get(0), Protect, Sort, Updated,
                ExpectedInventory, PreparedInventory,
                CachedItem->GetCount().Get(0) > 0
            );
        }
    };

    class FItemSetAggregateConsumeSpeculativeCommit final
    {
        struct FState final
        {
            TArray<TSharedPtr<void>> Values;
        };

        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const TOptional<FString> NamespaceName;
        const FString UserId;
        const FString InventoryName;
        const FString ItemName;
        const TOptional<int32> TimeOffset;
        const TArray<FString> PreparedItems;
        const TOptional<FString> PreparedInventoryModel;
        const TArray<TSharedPtr<FItemSetCountSpeculativeCommit>> Commits;

        bool IsExpectedState() const
        {
            if (PreparedInventoryModel.IsSet())
            {
                Gs2::Inventory::Model::FInventoryModelPtr Model;
                if (!Gs2::Inventory::Model::Cache::FInventoryModelCache::TryGet(
                    Cache, NamespaceName, InventoryName, TOptional<int32>(), &Model) ||
                    !Model.IsValid() || JsonString(Model->ToJson()) != PreparedInventoryModel.Get(FString())) return false;
            }
            FItemSetEntryPtr Entry;
            if (!TryGetAggregate(Cache, NamespaceName, UserId, InventoryName, ItemName, TimeOffset, &Entry) ||
                !Entry.IsValid() || Entry->Value.Num() != PreparedItems.Num()) return false;
            for (int32 i = 0; i < Entry->Value.Num(); ++i)
            {
                if (!Entry->Value[i].IsValid() || ItemJson(Entry->Value[i]) != PreparedItems[i]) return false;
                Gs2::Inventory::Model::FItemSetPtr Direct;
                if (!Gs2::Inventory::Model::Cache::FItemSetCache::TryGet(
                    Cache, NamespaceName, UserId, InventoryName, ItemName,
                    Entry->Value[i]->GetName(), TimeOffset, &Direct) ||
                    !Direct.IsValid() || ItemJson(Direct) != PreparedItems[i]) return false;
            }
            return true;
        }

    public:
        FItemSetAggregateConsumeSpeculativeCommit(
            const Gs2::Core::Domain::FCacheDatabasePtr& InCache,
            const TOptional<FString>& InNamespaceName,
            const FString& InUserId,
            const FString& InInventoryName,
            const FString& InItemName,
            const TOptional<int32>& InTimeOffset,
            const TArray<FString>& InPreparedItems,
            const TOptional<FString>& InPreparedInventoryModel,
            const TArray<TSharedPtr<FItemSetCountSpeculativeCommit>>& InCommits
        ):
            Cache(InCache), NamespaceName(InNamespaceName), UserId(InUserId),
            InventoryName(InInventoryName), ItemName(InItemName), TimeOffset(InTimeOffset),
            PreparedItems(InPreparedItems), PreparedInventoryModel(InPreparedInventoryModel), Commits(InCommits)
        {
        }

        FString CompositionKey() const
        {
            return ItemSetParent(NamespaceName, UserId, InventoryName, TimeOffset) + TEXT(":") + AggregateKey(ItemName);
        }

        bool TryCompose(
            const TSharedPtr<void>& Current,
            const bool HasCurrent,
            TSharedPtr<void>& Next
        ) const
        {
            try
            {
                if (HasCurrent || Current.IsValid() || !IsExpectedState())
                {
                    Next = nullptr;
                    return false;
                }
                const auto State = MakeShared<FState>();
                State->Values.SetNum(Commits.Num());
                for (int32 i = 0; i < Commits.Num(); ++i)
                {
                    if (!Commits[i].IsValid() || !Commits[i]->TryCompose(nullptr, false, State->Values[i]))
                    {
                        Next = nullptr;
                        return false;
                    }
                }
                if (!IsExpectedState())
                {
                    Next = nullptr;
                    return false;
                }
                Next = State;
                return true;
            }
            catch (...)
            {
                Next = nullptr;
                return false;
            }
        }

        void Commit(const TSharedPtr<void>& State) const
        {
            try
            {
                const auto Prepared = StaticCastSharedPtr<FState>(State);
                if (!Prepared.IsValid() || Prepared->Values.Num() != Commits.Num()) return;
                for (int32 i = 0; i < Commits.Num(); ++i)
                {
                    if (!Commits[i].IsValid()) return;
                    Commits[i]->Commit(Prepared->Values[i]);
                }
                TArray<FItemSetPtr> Remaining;
                for (const auto& Value : Prepared->Values)
                {
                    const auto Item = StaticCastSharedPtr<Gs2::Inventory::Model::FItemSet>(Value);
                    if (Item.IsValid() && Item->GetCount().IsSet() && Item->GetCount().Get(0) > 0)
                    {
                        Remaining.Add(Item);
                    }
                }
                PutAggregate(Cache, NamespaceName, UserId, InventoryName, ItemName, TimeOffset, Remaining);
            }
            catch (...) { }
        }
    };
}

FString FConsumeItemSetByUserIdSpeculativeExecutor::Action()
{
    return FString("Gs2Inventory:ConsumeItemSetByUserId");
}

Gs2::Core::Model::FGs2ErrorPtr FConsumeItemSetByUserIdSpeculativeExecutor::Transform(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Inventory::Request::FConsumeItemSetByUserIdRequestPtr& Request,
    TSharedPtr<TArray<Gs2::Inventory::Model::FItemSetPtr>> Items
)
{
    return nullptr;
}

FConsumeItemSetByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Inventory::Request::FConsumeItemSetByUserIdRequestPtr& Request
):
    Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request)
{
}

FConsumeItemSetByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
    const FCommitTask& From
):
    Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request)
{
}

Gs2::Core::Model::FGs2ErrorPtr FConsumeItemSetByUserIdSpeculativeExecutor::FCommitTask::Action(
    TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
)
{
    *Result = nullptr;
    Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
    if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
    FRequestPtr PreparedRequest = nullptr;
    if (Request.IsValid()) PreparedRequest = MakeShared<Gs2::Inventory::Request::FConsumeItemSetByUserIdRequest>(*Request);
    if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Domain->Cache.IsValid() ||
        !PreparedToken.IsValid() || !PreparedRequest.IsValid() ||
        !PreparedToken->GetUserId().IsSet() || PreparedToken->GetUserId().Get(FString()).IsEmpty()) return nullptr;
    if (PreparedRequest->GetUserId().IsSet() && PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}"))
        PreparedRequest->WithUserId(PreparedToken->GetUserId());
    if (!PreparedRequest->GetUserId().IsSet() ||
        PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString()) ||
        !PreparedRequest->GetNamespaceName().IsSet() || !PreparedRequest->GetInventoryName().IsSet() ||
        !PreparedRequest->GetItemName().IsSet() || !PreparedRequest->GetConsumeCount().IsSet()) return nullptr;

    const auto ItemSetName = PreparedRequest->GetItemSetName();
    if (!ItemSetName.IsSet() || ItemSetName.Get(FString()).IsEmpty())
    {
        FItemSetEntryPtr Entry;
        const FString Namespace = PreparedRequest->GetNamespaceName().Get(FString());
        const FString User = PreparedToken->GetUserId().Get(FString());
        const FString Inventory = PreparedRequest->GetInventoryName().Get(FString());
        const FString Item = PreparedRequest->GetItemName().Get(FString());
        const auto Offset = PreparedToken->GetTimeOffset();
        if (!TryGetAggregate(Domain->Cache, Namespace, User, Inventory, Item, Offset, &Entry) ||
            !Entry.IsValid() || Entry->Value.Num() == 0) return nullptr;
        const bool Multiple = Entry->Value.Num() > 1;
        const int64 AggregateUpdatedAt = static_cast<int64>(FDateTime::Now().ToUnixTimestampDecimal() * 1000.0) +
            static_cast<int64>(Offset.Get(0)) * 1000;
        TSet<FString> Names;
        TArray<FString> PreparedItems;
        TArray<bool> Eligible;
        TArray<int64> ConsumeCounts;
        bool HasReferences = false;
        bool TotalOverflow = false;
        int64 Total = 0;
        for (const auto& AggregateItem : Entry->Value)
        {
            const FString Name = AggregateItem.IsValid() && AggregateItem->GetName().IsSet()
                ? AggregateItem->GetName().Get(FString()) : FString();
            const FString Expected = FString::Printf(
                TEXT("grn:gs2:%s:%s:inventory:%s:user:%s:inventory:%s:item:%s:itemSet:%s"),
                *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *Namespace,
                *User, *Inventory, *Item, *Name
            );
            if (!AggregateItem.IsValid() || Name.IsEmpty() || Names.Contains(Name) ||
                !AggregateItem->GetItemSetId().IsSet() || AggregateItem->GetItemSetId().Get(FString()) != Expected ||
                !AggregateItem->GetUserId().IsSet() || AggregateItem->GetUserId().Get(FString()) != User ||
                !AggregateItem->GetInventoryName().IsSet() || AggregateItem->GetInventoryName().Get(FString()) != Inventory ||
                !AggregateItem->GetItemName().IsSet() || AggregateItem->GetItemName().Get(FString()) != Item ||
                !AggregateItem->GetCount().IsSet() || AggregateItem->GetCount().Get(0) <= 0 ||
                (AggregateItem->GetExpiresAt().IsSet() && AggregateItem->GetExpiresAt().Get(0) != 0 &&
                 AggregateItem->GetExpiresAt().Get(0) <= AggregateUpdatedAt)) return nullptr;
            Names.Add(Name);
            FItemSetPtr Direct;
            if (!Gs2::Inventory::Model::Cache::FItemSetCache::TryGet(
                Domain->Cache, Namespace, User, Inventory, Item, Name, Offset, &Direct) ||
                !Direct.IsValid() || ItemJson(Direct) != ItemJson(AggregateItem)) return nullptr;
            PreparedItems.Add(ItemJson(AggregateItem));
            const bool References = IsReferenceOf(AggregateItem);
            HasReferences |= References;
        }
        TOptional<FString> PreparedInventoryModel;
        TOptional<bool> Protect;
        if (HasReferences)
        {
            const FString ExpectedModel = FString::Printf(
                TEXT("grn:gs2:%s:%s:inventory:%s:model:%s"),
                *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *Namespace, *Inventory
            );
            Gs2::Inventory::Model::FInventoryModelPtr Model;
            if (!Gs2::Inventory::Model::Cache::FInventoryModelCache::TryGet(
                Domain->Cache, Namespace, Inventory, TOptional<int32>(), &Model) ||
                !Model.IsValid() || !Model->GetInventoryModelId().IsSet() ||
                Model->GetInventoryModelId().Get(FString()) != ExpectedModel ||
                !Model->GetName().IsSet() || Model->GetName().Get(FString()) != Inventory ||
                !Model->GetProtectReferencedItem().IsSet()) return nullptr;
            Protect = Model->GetProtectReferencedItem();
            PreparedInventoryModel = JsonString(Model->ToJson());
        }
        for (const auto& AggregateItem : Entry->Value)
            Eligible.Add(!Protect.Get(false) || !IsReferenceOf(AggregateItem));
        for (int32 i = 0; i < Entry->Value.Num(); ++i)
        {
            if (!Eligible[i] || TotalOverflow) continue;
            if (!AddCountChecked(Total, Entry->Value[i]->GetCount().Get(0), Total)) TotalOverflow = true;
        }
        ConsumeCounts.SetNum(Entry->Value.Num());
        if (Multiple)
        {
            const int64 Requested = PreparedRequest->GetConsumeCount().Get(0);
            if (Requested <= 0 || (!TotalOverflow && Total < Requested)) return nullptr;
            if (!TotalOverflow && Total == Requested)
            {
                for (int32 i = 0; i < Entry->Value.Num(); ++i)
                    if (Eligible[i]) ConsumeCounts[i] = Entry->Value[i]->GetCount().Get(0);
            }
            else
            {
                TArray<int32> Order;
                for (int32 i = 0; i < Entry->Value.Num(); ++i)
                {
                    if (!Eligible[i]) continue;
                    if (!Entry->Value[i]->GetSortValue().IsSet() || !Entry->Value[i]->GetExpiresAt().IsSet() ||
                        Entry->Value[i]->GetExpiresAt().Get(0) <= 0) return nullptr;
                    Order.Add(i);
                }
                auto Compare = [&Entry](const int32 Left, const int32 Right)
                {
                    const auto& L = Entry->Value[Left]; const auto& R = Entry->Value[Right];
                    if (L->GetSortValue().Get(0) != R->GetSortValue().Get(0)) return L->GetSortValue().Get(0) > R->GetSortValue().Get(0);
                    if (L->GetExpiresAt().Get(0) != R->GetExpiresAt().Get(0)) return L->GetExpiresAt().Get(0) < R->GetExpiresAt().Get(0);
                    return L->GetCount().Get(0) < R->GetCount().Get(0);
                };
                Order.Sort(Compare);
                for (int32 i = 1; i < Order.Num(); ++i)
                {
                    const int32 A = Order[i - 1], B = Order[i];
                    if (Entry->Value[A]->GetSortValue().Get(0) == Entry->Value[B]->GetSortValue().Get(0) &&
                        Entry->Value[A]->GetExpiresAt().Get(0) == Entry->Value[B]->GetExpiresAt().Get(0) &&
                        Entry->Value[A]->GetCount().Get(0) == Entry->Value[B]->GetCount().Get(0)) return nullptr;
                }
                int64 Remaining = Requested;
                for (const int32 Index : Order)
                {
                    ConsumeCounts[Index] = FMath::Min(Remaining, Entry->Value[Index]->GetCount().Get(0));
                    Remaining -= ConsumeCounts[Index];
                    if (Remaining == 0) break;
                }
            }
        }
        TArray<TSharedPtr<FItemSetCountSpeculativeCommit>> Commits;
        for (int32 i = 0; i < Entry->Value.Num(); ++i)
        {
            FRequestPtr Named = MakeShared<Gs2::Inventory::Request::FConsumeItemSetByUserIdRequest>(*PreparedRequest);
            Named->WithItemSetName(Entry->Value[i]->GetName());
            if (Multiple) Named->WithConsumeCount(ConsumeCounts[i]);
            auto Commit = FItemSetCountSpeculativeCommit::Prepare(Domain, PreparedToken, Named);
            if (!Commit.IsValid()) return nullptr;
            Commits.Add(Commit);
        }
        if (!Multiple)
        {
            Commits[0]->RequireAggregate(PreparedItems[0]);
            *Result = FPreparedCommit::CreateComposable(
                Commits[0]->CompositionKey(),
                [Commit = Commits[0]](const TSharedPtr<void>& Current, bool HasCurrent, TSharedPtr<void>& Next)
                { return Commit->TryCompose(Current, HasCurrent, Next); },
                [Commit = Commits[0]](const TSharedPtr<void>& State) { Commit->Commit(State); }
            );
            return nullptr;
        }
        const auto Wrapper = MakeShared<FItemSetAggregateConsumeSpeculativeCommit>(
            Domain->Cache, Namespace, User, Inventory, Item, Offset,
            PreparedItems, PreparedInventoryModel, Commits);
        *Result = FPreparedCommit::CreateComposable(
            Wrapper->CompositionKey(),
            [Wrapper](const TSharedPtr<void>& Current, bool HasCurrent, TSharedPtr<void>& Next)
            { return Wrapper->TryCompose(Current, HasCurrent, Next); },
            [Wrapper](const TSharedPtr<void>& State)
            { Wrapper->Commit(State); }
        );
        return nullptr;
    }

    auto Commit = FItemSetCountSpeculativeCommit::Prepare(Domain, PreparedToken, PreparedRequest);
    if (!Commit.IsValid()) return nullptr;
    *Result = FPreparedCommit::CreateComposable(
        Commit->CompositionKey(),
        [Commit](const TSharedPtr<void>& Current, bool HasCurrent, TSharedPtr<void>& Next)
        { return Commit->TryCompose(Current, HasCurrent, Next); },
        [Commit](const TSharedPtr<void>& State) { Commit->Commit(State); }
    );
    return nullptr;
}

TSharedPtr<FAsyncTask<FConsumeItemSetByUserIdSpeculativeExecutor::FCommitTask>> FConsumeItemSetByUserIdSpeculativeExecutor::Execute(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Inventory::Request::FConsumeItemSetByUserIdRequestPtr& Request
)
{
    return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
}

Gs2::Inventory::Request::FConsumeItemSetByUserIdRequestPtr FConsumeItemSetByUserIdSpeculativeExecutor::Rate(
    const Gs2::Inventory::Request::FConsumeItemSetByUserIdRequestPtr& Request,
    const double Rate
)
{
    if (!Request.IsValid() || !Request->GetConsumeCount().IsSet()) return nullptr;
    int64 Value;
    if (!TryApplyRateExact(Request->GetConsumeCount().Get(0), Rate, Value)) return nullptr;
    Request->WithConsumeCount(Value);
    return Request;
}

Gs2::Inventory::Request::FConsumeItemSetByUserIdRequestPtr FConsumeItemSetByUserIdSpeculativeExecutor::Rate(
    const Gs2::Inventory::Request::FConsumeItemSetByUserIdRequestPtr& Request,
    TBigInt<1024, false> Rate
)
{
    if (!Request.IsValid() || !Request->GetConsumeCount().IsSet()) return nullptr;
    Rate.Multiply(*Request->GetConsumeCount());
    const FString Product = Rate.ToString();
    const bool Negative = Product.StartsWith(TEXT("-"));
    const FString Digits = Negative ? Product.RightChop(1) : Product;
    const FString Limit = Negative ? TEXT("9223372036854775808") : TEXT("9223372036854775807");
    if (Digits.IsEmpty() || Digits.Len() > Limit.Len() ||
        (Digits.Len() == Limit.Len() && Digits.Compare(Limit, ESearchCase::CaseSensitive) > 0)) return nullptr;
    Request->WithConsumeCount(Rate.ToInt());
    return Request;
}
}
