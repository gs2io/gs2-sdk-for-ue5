#pragma once

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Inventory/Model/Cache/SimpleItem.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor::Private
{
    class FSimpleItemRate final
    {
        static constexpr uint32 Base = 1000000000U;
        TArray<uint32> Digits;
        int32 Sign = 0;

        void Normalize()
        {
            while (Digits.Num() > 0 && Digits.Last() == 0) Digits.Pop();
            if (Digits.Num() == 0) Sign = 0;
        }

        static int32 CompareMagnitude(const FSimpleItemRate& Left, const FSimpleItemRate& Right)
        {
            if (Left.Digits.Num() != Right.Digits.Num())
                return Left.Digits.Num() < Right.Digits.Num() ? -1 : 1;
            for (int32 i = Left.Digits.Num() - 1; i >= 0; --i)
            {
                if (Left.Digits[i] != Right.Digits[i])
                    return Left.Digits[i] < Right.Digits[i] ? -1 : 1;
            }
            return 0;
        }

        static FSimpleItemRate AddMagnitude(const FSimpleItemRate& Left, const FSimpleItemRate& Right)
        {
            FSimpleItemRate Result;
            const int32 Count = FMath::Max(Left.Digits.Num(), Right.Digits.Num());
            Result.Digits.SetNumZeroed(Count + 1);
            uint64 Carry = 0;
            for (int32 i = 0; i < Count; ++i)
            {
                const uint64 Value = Carry + (i < Left.Digits.Num() ? Left.Digits[i] : 0) +
                    (i < Right.Digits.Num() ? Right.Digits[i] : 0);
                Result.Digits[i] = static_cast<uint32>(Value % Base);
                Carry = Value / Base;
            }
            Result.Digits[Count] = static_cast<uint32>(Carry);
            Result.Sign = 1;
            Result.Normalize();
            return Result;
        }

        static FSimpleItemRate SubtractMagnitude(const FSimpleItemRate& Left, const FSimpleItemRate& Right)
        {
            FSimpleItemRate Result;
            Result.Digits.SetNumZeroed(Left.Digits.Num());
            int64 Borrow = 0;
            for (int32 i = 0; i < Left.Digits.Num(); ++i)
            {
                int64 Value = static_cast<int64>(Left.Digits[i]) - Borrow -
                    (i < Right.Digits.Num() ? Right.Digits[i] : 0);
                if (Value < 0)
                {
                    Value += Base;
                    Borrow = 1;
                }
                else Borrow = 0;
                Result.Digits[i] = static_cast<uint32>(Value);
            }
            Result.Sign = 1;
            Result.Normalize();
            return Result;
        }

        void AddSmall(const uint32 Value)
        {
            uint64 Carry = Value;
            for (int32 i = 0; Carry != 0; ++i)
            {
                if (i == Digits.Num()) Digits.Add(0);
                const uint64 Sum = static_cast<uint64>(Digits[i]) + Carry;
                Digits[i] = static_cast<uint32>(Sum % Base);
                Carry = Sum / Base;
            }
            if (Sign == 0 && Value != 0) Sign = 1;
        }

        void MultiplySmall(const uint32 Value)
        {
            if (Sign == 0 || Value == 0)
            {
                Digits.Reset();
                Sign = 0;
                return;
            }
            uint64 Carry = 0;
            for (uint32& Digit : Digits)
            {
                const uint64 Product = static_cast<uint64>(Digit) * Value + Carry;
                Digit = static_cast<uint32>(Product % Base);
                Carry = Product / Base;
            }
            if (Carry != 0) Digits.Add(static_cast<uint32>(Carry));
        }

        void ShiftRightOne()
        {
            uint64 Carry = 0;
            for (int32 i = Digits.Num() - 1; i >= 0; --i)
            {
                const uint64 Value = Carry * Base + Digits[i];
                Digits[i] = static_cast<uint32>(Value / 2);
                Carry = Value % 2;
            }
            Normalize();
        }

        int32 BitLength() const
        {
            if (Sign == 0) return 0;
            FSimpleItemRate Value = Absolute(*this);
            int32 Bits = 0;
            while (Value.Sign != 0)
            {
                Value.ShiftRightOne();
                ++Bits;
            }
            return Bits;
        }

        static FSimpleItemRate Absolute(const FSimpleItemRate& Value)
        {
            FSimpleItemRate Result = Value;
            if (Result.Sign < 0) Result.Sign = 1;
            return Result;
        }

        bool IsOdd() const
        {
            return Sign != 0 && (Digits[0] & 1U) != 0;
        }

        void RoundTo100Bits(int32& Exponent)
        {
            if (Sign == 0) return;
            const int32 Length = BitLength();
            if (Length <= 100) return;
            const int32 Shift = Length - 100;
            bool HalfBit = false;
            bool LowerBits = false;
            for (int32 i = 0; i < Shift; ++i)
            {
                const bool Bit = IsOdd();
                ShiftRightOne();
                if (i == Shift - 1) HalfBit = Bit;
                else LowerBits |= Bit;
            }
            if (HalfBit && (LowerBits || IsOdd())) AddSmall(1);
            if (BitLength() > 100)
            {
                ShiftRightOne();
                Exponent += 1;
            }
            Exponent += Shift;
        }

    public:
        FSimpleItemRate() = default;

        static bool TryParse(const FString& Text, FSimpleItemRate& Out)
        {
            Out = FSimpleItemRate();
            if (Text.IsEmpty()) return false;
            int32 Index = 0;
            bool Negative = false;
            if (Text[0] == TEXT('+') || Text[0] == TEXT('-'))
            {
                Negative = Text[0] == TEXT('-');
                Index = 1;
                if (Index == Text.Len()) return false;
            }
            for (; Index < Text.Len(); ++Index)
            {
                const TCHAR Character = Text[Index];
                if (Character < TEXT('0') || Character > TEXT('9')) return false;
                Out.MultiplySmall(10);
                Out.AddSmall(static_cast<uint32>(Character - TEXT('0')));
            }
            if (Negative && Out.Sign != 0) Out.Sign = -1;
            return true;
        }

        static FSimpleItemRate FromUInt64(const uint64 Value)
        {
            FSimpleItemRate Result;
            uint64 Remaining = Value;
            while (Remaining != 0)
            {
                Result.Digits.Add(static_cast<uint32>(Remaining % Base));
                Remaining /= Base;
            }
            Result.Sign = Result.Digits.Num() == 0 ? 0 : 1;
            return Result;
        }

        static FSimpleItemRate One()
        {
            FSimpleItemRate Result;
            Result.Digits.Add(1);
            Result.Sign = 1;
            return Result;
        }

        static FSimpleItemRate FromInt64(const int64 Value)
        {
            if (Value >= 0) return FromUInt64(static_cast<uint64>(Value));
            const uint64 Magnitude = static_cast<uint64>(-(Value + 1)) + 1ULL;
            FSimpleItemRate Result = FromUInt64(Magnitude);
            Result.Sign = -Result.Sign;
            return Result;
        }

        bool IsNegative() const
        {
            return Sign < 0;
        }

        FString ToString() const
        {
            if (Sign == 0) return TEXT("0");
            FString Result = Sign < 0 ? TEXT("-") : TEXT("");
            Result += FString::FromInt(Digits.Last());
            for (int32 i = Digits.Num() - 2; i >= 0; --i)
                Result += FString::Printf(TEXT("%09u"), Digits[i]);
            return Result;
        }

        static FSimpleItemRate Add(const FSimpleItemRate& Left, const FSimpleItemRate& Right)
        {
            if (Left.Sign == 0) return Right;
            if (Right.Sign == 0) return Left;
            if (Left.Sign == Right.Sign)
            {
                FSimpleItemRate Result = AddMagnitude(Left, Right);
                Result.Sign = Left.Sign;
                return Result;
            }
            const int32 Comparison = CompareMagnitude(Left, Right);
            if (Comparison == 0) return FSimpleItemRate();
            FSimpleItemRate Result = Comparison > 0 ? SubtractMagnitude(Left, Right) : SubtractMagnitude(Right, Left);
            Result.Sign = Comparison > 0 ? Left.Sign : Right.Sign;
            return Result;
        }

        static FSimpleItemRate Subtract(const FSimpleItemRate& Left, const FSimpleItemRate& Right)
        {
            FSimpleItemRate NegativeRight = Right;
            NegativeRight.Sign = -NegativeRight.Sign;
            return Add(Left, NegativeRight);
        }

        static FSimpleItemRate Multiply(const FSimpleItemRate& Left, const FSimpleItemRate& Right)
        {
            if (Left.Sign == 0 || Right.Sign == 0) return FSimpleItemRate();
            FSimpleItemRate Result;
            Result.Digits.SetNumZeroed(Left.Digits.Num() + Right.Digits.Num());
            for (int32 i = 0; i < Left.Digits.Num(); ++i)
            {
                uint64 Carry = 0;
                for (int32 j = 0; j < Right.Digits.Num(); ++j)
                {
                    const int32 Index = i + j;
                    const uint64 Value = static_cast<uint64>(Result.Digits[Index]) +
                        static_cast<uint64>(Left.Digits[i]) * Right.Digits[j] + Carry;
                    Result.Digits[Index] = static_cast<uint32>(Value % Base);
                    Carry = Value / Base;
                }
                int32 Index = i + Right.Digits.Num();
                while (Carry != 0)
                {
                    if (Index == Result.Digits.Num()) Result.Digits.Add(0);
                    const uint64 Value = static_cast<uint64>(Result.Digits[Index]) + Carry;
                    Result.Digits[Index] = static_cast<uint32>(Value % Base);
                    Carry = Value / Base;
                    ++Index;
                }
            }
            Result.Sign = Left.Sign == Right.Sign ? 1 : -1;
            Result.Normalize();
            return Result;
        }

        void ShiftLeft(const int32 Count)
        {
            for (int32 i = 0; i < Count; ++i) MultiplySmall(2);
        }

        void ShiftRight(const int32 Count)
        {
            for (int32 i = 0; i < Count && Sign != 0; ++i) ShiftRightOne();
        }

        static FSimpleItemRate ParseCountOrOne(const TOptional<FString>& Count)
        {
            FSimpleItemRate Result;
            if (!Count.IsSet() || Count.Get(FString()).IsEmpty() ||
                !TryParse(Count.Get(FString()), Result)) return One();
            return Result;
        }

        static bool TryApplyRate(const FSimpleItemRate& Count, const double Rate, FSimpleItemRate& Out)
        {
            uint64 Bits = 0;
            FMemory::Memcpy(&Bits, &Rate, sizeof(Bits));
            const uint64 ExponentBits = (Bits >> 52) & 0x7ffULL;
            if (ExponentBits == 0x7ffULL) return false;
            FSimpleItemRate Mantissa = FromUInt64(Bits & 0x000fffffffffffffULL);
            int32 Exponent = -1074;
            if (ExponentBits != 0)
            {
                Mantissa = FromUInt64((Bits & 0x000fffffffffffffULL) + (1ULL << 52));
                Exponent = static_cast<int32>(ExponentBits) - 1075;
            }
            FSimpleItemRate Product = Multiply(Count, Mantissa);
            if ((Bits >> 63) != 0) Product.Sign = -Product.Sign;
            Product.RoundTo100Bits(Exponent);
            if (Exponent >= 0) Product.ShiftLeft(Exponent);
            else Product.ShiftRight(-Exponent);
            Out = Product;
            return true;
        }

        static bool TryApplyRate(const FSimpleItemRate& Count, const FString& Rate, FSimpleItemRate& Out)
        {
            FSimpleItemRate ParsedRate;
            if (!TryParse(Rate, ParsedRate)) return false;
            Out = Multiply(Count, ParsedRate);
            return true;
        }

        static int64 SaturateToInt64(const FSimpleItemRate& Value)
        {
            static const FSimpleItemRate MaxValue = [] { FSimpleItemRate V; TryParse(TEXT("9223372036854775807"), V); return V; }();
            static const FSimpleItemRate MinMagnitude = [] { FSimpleItemRate V; TryParse(TEXT("9223372036854775808"), V); return V; }();
            if (Value.Sign > 0 && CompareMagnitude(Value, MaxValue) > 0) return MAX_int64;
            if (Value.Sign < 0 && CompareMagnitude(Value, MinMagnitude) > 0) return MIN_int64;
            uint64 Magnitude = 0;
            for (int32 i = Value.Digits.Num() - 1; i >= 0; --i)
            {
                if (Magnitude > (~static_cast<uint64>(0) - Value.Digits[i]) / Base)
                    return Value.Sign < 0 ? MIN_int64 : MAX_int64;
                Magnitude = Magnitude * Base + Value.Digits[i];
            }
            if (Value.Sign < 0)
            {
                if (Magnitude >= (static_cast<uint64>(MAX_int64) + 1ULL)) return MIN_int64;
                return -static_cast<int64>(Magnitude);
            }
            if (Magnitude > static_cast<uint64>(MAX_int64)) return MAX_int64;
            return static_cast<int64>(Magnitude);
        }
    };


    inline FString SimpleItemExpectedId(
        const FString& Region,
        const FString& OwnerId,
        const FString& NamespaceName,
        const FString& UserId,
        const FString& InventoryName,
        const FString& ItemName
    )
    {
        return FString::Printf(
            TEXT("grn:gs2:%s:%s:inventory:%s:user:%s:simple:inventory:%s:item:%s"),
            *Region, *OwnerId, *NamespaceName, *UserId, *InventoryName, *ItemName
        );
    }

    struct FSimpleItemCompositionState final
    {
        Gs2::Inventory::Model::FSimpleItemPtr Item;
        bool HasAbsoluteSet = false;
        int64 AbsoluteSetCount = 0;
    };

    class FSimpleItemMutationSpeculativeCommit final
    {
        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const TOptional<FString> NamespaceName;
        const FString UserId;
        const FString InventoryName;
        const FString ItemName;
        const TOptional<int32> TimeOffset;
        const FString ExpectedId;
        const TOptional<int64> PreparedRevision;
        const bool PreparedWasTombstone;
        const TFunction<Gs2::Inventory::Model::FSimpleItemPtr(const Gs2::Inventory::Model::FSimpleItemPtr&)> Transform;
        const TOptional<int64> AbsoluteSetCount;

        bool IsExpected(const Gs2::Inventory::Model::FSimpleItemPtr& Item) const
        {
            return Item.IsValid() && Item->GetItemId().IsSet() && Item->GetItemId().Get(FString()) == ExpectedId &&
                Item->GetUserId().IsSet() && Item->GetUserId().Get(FString()) == UserId &&
                Item->GetItemName().IsSet() && Item->GetItemName().Get(FString()) == ItemName;
        }

    public:
        FSimpleItemMutationSpeculativeCommit(
            const Gs2::Core::Domain::FCacheDatabasePtr& InCache,
            const TOptional<FString>& InNamespaceName,
            const FString& InUserId,
            const FString& InInventoryName,
            const FString& InItemName,
            const TOptional<int32>& InTimeOffset,
            const FString& InExpectedId,
            const TOptional<int64>& InPreparedRevision,
            bool InPreparedWasTombstone,
            const TFunction<Gs2::Inventory::Model::FSimpleItemPtr(const Gs2::Inventory::Model::FSimpleItemPtr&)>& InTransform,
            const TOptional<int64>& InAbsoluteSetCount = TOptional<int64>()
        ):
            Cache(InCache), NamespaceName(InNamespaceName), UserId(InUserId), InventoryName(InInventoryName),
            ItemName(InItemName), TimeOffset(InTimeOffset), ExpectedId(InExpectedId),
            PreparedRevision(InPreparedRevision), PreparedWasTombstone(InPreparedWasTombstone),
            Transform(InTransform), AbsoluteSetCount(InAbsoluteSetCount)
        {
        }

        static Gs2::Inventory::Model::FSimpleItemPtr KnownZero(const FString& ExpectedId, const FString& UserId, const FString& ItemName)
        {
            return MakeShared<Gs2::Inventory::Model::FSimpleItem>()
                ->WithItemId(ExpectedId)->WithUserId(UserId)->WithItemName(ItemName)->WithCount(0)->WithRevision(0);
        }

        FString ItemNameValue() const { return ItemName; }
        FString CompositionKey() const
        {
            return Gs2::Inventory::Model::Cache::FSimpleItemCache::CreateCacheParentKey(
                NamespaceName, UserId, InventoryName, TimeOffset
            ) + TEXT(":") + Gs2::Inventory::Model::Cache::FSimpleItemCache::CreateCacheKey(ItemName);
        }

        bool CanCommit(const TSharedPtr<void>& State) const
        {
            const auto Composition = StaticCastSharedPtr<FSimpleItemCompositionState>(State);
            return Composition.IsValid() && IsExpected(Composition->Item) && Composition->Item->GetCount().IsSet();
        }

        bool TryCompose(const TSharedPtr<void>& Current, bool HasCurrent, TSharedPtr<void>& Next) const
        {
            try
            {
                FSimpleItemCompositionState State;
                if (HasCurrent)
                {
                    const auto Existing = StaticCastSharedPtr<FSimpleItemCompositionState>(Current);
                    if (!Existing.IsValid() || !IsExpected(Existing->Item)) { Next = nullptr; return false; }
                    State = *Existing;
                }
                else
                {
                    Gs2::Inventory::Model::FSimpleItemPtr Cached;
                    if (!Gs2::Inventory::Model::Cache::FSimpleItemCache::TryGet(
                        Cache, NamespaceName, UserId, InventoryName, ItemName, TimeOffset, &Cached
                    ) || (!Cached.IsValid() && !PreparedWasTombstone)) { Next = nullptr; return false; }
                    State.Item = Cached.IsValid() ? Cached : KnownZero(ExpectedId, UserId, ItemName);
                    if (!IsExpected(State.Item) || (State.Item->GetRevision().IsSet() && State.Item->GetRevision().Get(0) > 0 &&
                        (!PreparedRevision.IsSet() || State.Item->GetRevision().Get(0) != PreparedRevision.Get(0))))
                    { Next = nullptr; return false; }
                }
                if (AbsoluteSetCount.IsSet() && State.HasAbsoluteSet)
                {
                    if (State.AbsoluteSetCount != AbsoluteSetCount.Get(0)) { Next = nullptr; return false; }
                    Next = MakeShared<FSimpleItemCompositionState>(State);
                    return true;
                }
                const auto Changed = Transform(State.Item);
                if (!IsExpected(Changed) || !Changed->GetCount().IsSet()) { Next = nullptr; return false; }
                State.Item = Changed;
                if (AbsoluteSetCount.IsSet())
                {
                    State.HasAbsoluteSet = true;
                    State.AbsoluteSetCount = AbsoluteSetCount.Get(0);
                }
                Next = MakeShared<FSimpleItemCompositionState>(State);
                return true;
            }
            catch (...) { Next = nullptr; return false; }
        }

        void Commit(const TSharedPtr<void>& State) const
        {
            try
            {
                if (!CanCommit(State)) return;
                const auto Composition = StaticCastSharedPtr<FSimpleItemCompositionState>(State);
                const auto Item = MakeShared<Gs2::Inventory::Model::FSimpleItem>(*Composition->Item)->WithRevision(0);
                Cache->Put(
                    Gs2::Inventory::Model::FSimpleItem::TypeName,
                    Gs2::Inventory::Model::Cache::FSimpleItemCache::CreateCacheParentKey(
                        NamespaceName, UserId, InventoryName, TimeOffset
                    ),
                    Gs2::Inventory::Model::Cache::FSimpleItemCache::CreateCacheKey(ItemName),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            catch (...) { }
        }
    };

    struct FSimpleItemBatchEntry final
    {
        TSharedPtr<void> State;
        TSharedPtr<FSimpleItemMutationSpeculativeCommit> Commit;
    };

    struct FSimpleItemBatchCompositionState final
    {
        TMap<FString, FSimpleItemBatchEntry> Items;
        TMap<FString, int64> AbsoluteSets;
        int32 SetActionCount = 0;
        bool HasInternalSetConflict = false;
    };

    class FSimpleItemBatchSpeculativeCommit final
    {
        const FString BatchKey;
        const TArray<TSharedPtr<FSimpleItemMutationSpeculativeCommit>> Commits;
        const TMap<FString, int64> AbsoluteSets;
        const bool IsSetAction;
        const bool HasInternalSetConflict;

    public:
        FSimpleItemBatchSpeculativeCommit(
            const FString& InBatchKey,
            const TArray<TSharedPtr<FSimpleItemMutationSpeculativeCommit>>& InCommits,
            const TMap<FString, int64>& InAbsoluteSets,
            bool InIsSetAction,
            bool InHasInternalSetConflict
        ):
            BatchKey(InBatchKey), Commits(InCommits), AbsoluteSets(InAbsoluteSets),
            IsSetAction(InIsSetAction), HasInternalSetConflict(InHasInternalSetConflict)
        {
        }

        FString CompositionKey() const { return BatchKey; }

        bool TryCompose(const TSharedPtr<void>& Current, bool HasCurrent, TSharedPtr<void>& Next) const
        {
            TSharedPtr<FSimpleItemBatchCompositionState> Source = nullptr;
            if (HasCurrent) Source = StaticCastSharedPtr<FSimpleItemBatchCompositionState>(Current);
            if (HasCurrent && !Source.IsValid()) { Next = nullptr; return false; }
            if (IsSetAction && Source.IsValid() && Source->SetActionCount > 0 &&
                (Source->HasInternalSetConflict || HasInternalSetConflict)) { Next = nullptr; return false; }
            auto Result = MakeShared<FSimpleItemBatchCompositionState>();
            if (Source.IsValid()) *Result = *Source;
            for (const auto& Intent : AbsoluteSets)
            {
                if (Result->AbsoluteSets.Contains(Intent.Key) && Result->AbsoluteSets[Intent.Key] != Intent.Value)
                { Next = nullptr; return false; }
                Result->AbsoluteSets.Add(Intent.Key, Intent.Value);
            }
            for (const auto& Commit : Commits)
            {
                if (!Commit.IsValid()) { Next = nullptr; return false; }
                FSimpleItemBatchEntry* Existing = Result->Items.Find(Commit->ItemNameValue());
                TSharedPtr<void> Changed;
                if (!Commit->TryCompose(Existing ? Existing->State : nullptr, Existing != nullptr, Changed))
                { Next = nullptr; return false; }
                FSimpleItemBatchEntry Entry;
                Entry.State = Changed;
                Entry.Commit = Commit;
                Result->Items.Add(Commit->ItemNameValue(), Entry);
            }
            Result->SetActionCount += IsSetAction ? 1 : 0;
            Result->HasInternalSetConflict |= HasInternalSetConflict;
            Next = Result;
            return true;
        }

        void Commit(const TSharedPtr<void>& State) const
        {
            const auto Batch = StaticCastSharedPtr<FSimpleItemBatchCompositionState>(State);
            if (!Batch.IsValid()) return;
            for (const auto& Pair : Batch->Items) if (!Pair.Value.Commit.IsValid() || !Pair.Value.Commit->CanCommit(Pair.Value.State)) return;
            for (const auto& Pair : Batch->Items) Pair.Value.Commit->Commit(Pair.Value.State);
        }
    };
}
