#pragma once

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Inventory/Model/BigItem.h"
#include "Inventory/Model/Cache/BigItem.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor::Private
{
    class FBigInteger final
    {
        static constexpr uint32 Base = 1000000000U;
        TArray<uint32> Digits;
        int32 Sign = 0;

        void Normalize()
        {
            while (Digits.Num() > 0 && Digits.Last() == 0) Digits.Pop();
            if (Digits.Num() == 0) Sign = 0;
        }

        static int32 CompareMagnitude(const FBigInteger& Left, const FBigInteger& Right)
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

        static FBigInteger AddMagnitude(const FBigInteger& Left, const FBigInteger& Right)
        {
            FBigInteger Result;
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

        static FBigInteger SubtractMagnitude(const FBigInteger& Left, const FBigInteger& Right)
        {
            FBigInteger Result;
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
            FBigInteger Value = Absolute(*this);
            int32 Bits = 0;
            while (Value.Sign != 0)
            {
                Value.ShiftRightOne();
                ++Bits;
            }
            return Bits;
        }

        static FBigInteger Absolute(const FBigInteger& Value)
        {
            FBigInteger Result = Value;
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
        FBigInteger() = default;

        static bool TryParse(const FString& Text, FBigInteger& Out)
        {
            Out = FBigInteger();
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

        static FBigInteger FromUInt64(const uint64 Value)
        {
            FBigInteger Result;
            uint64 Remaining = Value;
            while (Remaining != 0)
            {
                Result.Digits.Add(static_cast<uint32>(Remaining % Base));
                Remaining /= Base;
            }
            Result.Sign = Result.Digits.Num() == 0 ? 0 : 1;
            return Result;
        }

        static FBigInteger One()
        {
            FBigInteger Result;
            Result.Digits.Add(1);
            Result.Sign = 1;
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

        static FBigInteger Add(const FBigInteger& Left, const FBigInteger& Right)
        {
            if (Left.Sign == 0) return Right;
            if (Right.Sign == 0) return Left;
            if (Left.Sign == Right.Sign)
            {
                FBigInteger Result = AddMagnitude(Left, Right);
                Result.Sign = Left.Sign;
                return Result;
            }
            const int32 Comparison = CompareMagnitude(Left, Right);
            if (Comparison == 0) return FBigInteger();
            FBigInteger Result = Comparison > 0 ? SubtractMagnitude(Left, Right) : SubtractMagnitude(Right, Left);
            Result.Sign = Comparison > 0 ? Left.Sign : Right.Sign;
            return Result;
        }

        static FBigInteger Subtract(const FBigInteger& Left, const FBigInteger& Right)
        {
            FBigInteger NegativeRight = Right;
            NegativeRight.Sign = -NegativeRight.Sign;
            return Add(Left, NegativeRight);
        }

        static FBigInteger Multiply(const FBigInteger& Left, const FBigInteger& Right)
        {
            if (Left.Sign == 0 || Right.Sign == 0) return FBigInteger();
            FBigInteger Result;
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

        static FBigInteger ParseCountOrOne(const TOptional<FString>& Count)
        {
            FBigInteger Result;
            if (!Count.IsSet() || Count.Get(FString()).IsEmpty() ||
                !TryParse(Count.Get(FString()), Result)) return One();
            return Result;
        }

        static bool TryApplyRate(const FBigInteger& Count, const double Rate, FBigInteger& Out)
        {
            uint64 Bits = 0;
            FMemory::Memcpy(&Bits, &Rate, sizeof(Bits));
            const uint64 ExponentBits = (Bits >> 52) & 0x7ffULL;
            if (ExponentBits == 0x7ffULL) return false;
            FBigInteger RoundedCount = Count;
            int32 CountExponent = 0;
            RoundedCount.RoundTo100Bits(CountExponent);
            FBigInteger Mantissa = FromUInt64(Bits & 0x000fffffffffffffULL);
            int32 Exponent = -1074;
            if (ExponentBits != 0)
            {
                Mantissa = FromUInt64((Bits & 0x000fffffffffffffULL) + (1ULL << 52));
                Exponent = static_cast<int32>(ExponentBits) - 1075;
            }
            FBigInteger Product = Multiply(RoundedCount, Mantissa);
            if ((Bits >> 63) != 0) Product.Sign = -Product.Sign;
            Exponent += CountExponent;
            Product.RoundTo100Bits(Exponent);
            if (Exponent >= 0) Product.ShiftLeft(Exponent);
            else Product.ShiftRight(-Exponent);
            Out = Product;
            return true;
        }

        static bool TryApplyRate(const FBigInteger& Count, const FString& Rate, FBigInteger& Out)
        {
            FBigInteger ParsedRate;
            if (!TryParse(Rate, ParsedRate)) return false;
            Out = Multiply(Count, ParsedRate);
            return true;
        }
    };

    inline FString BigItemExpectedId(
        const FString& Region,
        const FString& OwnerId,
        const FString& NamespaceName,
        const FString& UserId,
        const FString& InventoryName,
        const FString& ItemName
    )
    {
        return FString::Printf(
            TEXT("grn:gs2:%s:%s:inventory:%s:user:%s:big:inventory:%s:item:%s"),
            *Region, *OwnerId, *NamespaceName, *UserId, *InventoryName, *ItemName
        );
    }

    class FBigItemMutationSpeculativeCommit final
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
        const TFunction<Gs2::Inventory::Model::FBigItemPtr(const Gs2::Inventory::Model::FBigItemPtr&)> Transform;

        bool IsExpected(const Gs2::Inventory::Model::FBigItemPtr& Item) const
        {
            return Item.IsValid() && Item->GetItemId().IsSet() && Item->GetItemId().Get(FString()) == ExpectedId &&
                Item->GetUserId().IsSet() && Item->GetUserId().Get(FString()) == UserId &&
                Item->GetItemName().IsSet() && Item->GetItemName().Get(FString()) == ItemName;
        }

    public:
        FBigItemMutationSpeculativeCommit(
            const Gs2::Core::Domain::FCacheDatabasePtr& InCache,
            const TOptional<FString>& InNamespaceName,
            const FString& InUserId,
            const FString& InInventoryName,
            const FString& InItemName,
            const TOptional<int32>& InTimeOffset,
            const FString& InExpectedId,
            const TOptional<int64>& InPreparedRevision,
            const bool InPreparedWasTombstone,
            const TFunction<Gs2::Inventory::Model::FBigItemPtr(const Gs2::Inventory::Model::FBigItemPtr&)>& InTransform
        ):
            Cache(InCache), NamespaceName(InNamespaceName), UserId(InUserId), InventoryName(InInventoryName),
            ItemName(InItemName), TimeOffset(InTimeOffset), ExpectedId(InExpectedId),
            PreparedRevision(InPreparedRevision), PreparedWasTombstone(InPreparedWasTombstone), Transform(InTransform)
        {
        }

        static Gs2::Inventory::Model::FBigItemPtr KnownZero(
            const FString& ExpectedId, const FString& UserId, const FString& ItemName
        )
        {
            return MakeShared<Gs2::Inventory::Model::FBigItem>()
                ->WithItemId(ExpectedId)->WithUserId(UserId)->WithItemName(ItemName)->WithCount(FString(TEXT("0")))->WithRevision(0);
        }

        FString CompositionKey() const
        {
            return Gs2::Inventory::Model::Cache::FBigItemCache::CreateCacheParentKey(
                NamespaceName, UserId, InventoryName, TimeOffset
            ) + TEXT(":") + Gs2::Inventory::Model::Cache::FBigItemCache::CreateCacheKey(ItemName);
        }

        bool TryCompose(const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next) const
        {
            try
            {
                Gs2::Inventory::Model::FBigItemPtr Item;
                if (HasCurrent)
                {
                    Item = StaticCastSharedPtr<Gs2::Inventory::Model::FBigItem>(Current);
                }
                else
                {
                    Gs2::Inventory::Model::FBigItemPtr Cached;
                    if (!Gs2::Inventory::Model::Cache::FBigItemCache::TryGet(
                        Cache, NamespaceName, UserId, InventoryName, ItemName, TimeOffset, &Cached
                    ) || (!Cached.IsValid() && !PreparedWasTombstone))
                    {
                        Next = nullptr;
                        return false;
                    }
                    Item = Cached.IsValid() ? Cached : KnownZero(ExpectedId, UserId, ItemName);
                    if (!IsExpected(Item) || (Item->GetRevision().IsSet() && Item->GetRevision().Get(0) > 0 &&
                        (!PreparedRevision.IsSet() || Item->GetRevision().Get(0) != PreparedRevision.Get(0))))
                    {
                        Next = nullptr;
                        return false;
                    }
                }
                if (!IsExpected(Item))
                {
                    Next = nullptr;
                    return false;
                }
                Next = Transform(Item);
                const auto Changed = StaticCastSharedPtr<Gs2::Inventory::Model::FBigItem>(Next);
                if (!IsExpected(Changed) || !Changed->GetCount().IsSet())
                {
                    Next = nullptr;
                    return false;
                }
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
                const auto Item = StaticCastSharedPtr<Gs2::Inventory::Model::FBigItem>(State);
                if (!IsExpected(Item) || !Item->GetCount().IsSet()) return;
                const auto Changed = MakeShared<Gs2::Inventory::Model::FBigItem>(*Item)->WithRevision(0);
                Cache->Put(
                    Gs2::Inventory::Model::FBigItem::TypeName,
                    Gs2::Inventory::Model::Cache::FBigItemCache::CreateCacheParentKey(
                        NamespaceName, UserId, InventoryName, TimeOffset
                    ),
                    Gs2::Inventory::Model::Cache::FBigItemCache::CreateCacheKey(ItemName),
                    Changed,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            catch (...) { }
        }
    };
}
