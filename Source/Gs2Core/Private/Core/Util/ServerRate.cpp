/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "Core/Util/ServerRate.h"

#include <cmath>

namespace Gs2::Core::Util
{
namespace
{
    using FRateMagnitude = TBigInt<256, false>;

    constexpr int64 MaxPositiveInt64Magnitude = MAX_int64 - 1;
    constexpr int64 MaxNegativeInt64Magnitude = MAX_int64;

    FRateMagnitude CountMagnitude(const int64 Count)
    {
        if (Count >= 0)
        {
            return FRateMagnitude(Count);
        }

        FRateMagnitude Magnitude;
        if (Count == MIN_int64)
        {
            Magnitude.SetBit(63, 1);
        }
        else
        {
            Magnitude = FRateMagnitude(-Count);
        }
        return Magnitude;
    }

    FRateMagnitude MaxConvertibleMagnitude(
        const bool Negative,
        const bool Int32Output
    )
    {
        if (Int32Output)
        {
            return FRateMagnitude(static_cast<int64>(MAX_int32));
        }
        return FRateMagnitude(Negative ? MaxNegativeInt64Magnitude : MaxPositiveInt64Magnitude);
    }

    bool TryConvertMagnitude(
        FRateMagnitude Magnitude,
        const bool Negative,
        const bool Int32Output,
        int64& Value
    )
    {
        if (Magnitude > MaxConvertibleMagnitude(Negative, Int32Output))
        {
            return false;
        }

        const int64 Converted = Magnitude.ToInt();
        Value = Negative && Converted != 0 ? -Converted : Converted;
        return true;
    }

    bool TryConvertMagnitude(
        FRateMagnitude Magnitude,
        const bool Negative,
        const bool Int32Output,
        int32& Value
    )
    {
        if (Magnitude > MaxConvertibleMagnitude(Negative, Int32Output))
        {
            return false;
        }

        const int32 Converted = static_cast<int32>(Magnitude.ToInt());
        Value = Negative && Converted != 0 ? -Converted : Converted;
        return true;
    }

    bool TryScaleDouble(
        const int64 Count,
        const double Rate,
        const FRateMagnitude& PositiveLimit,
        const FRateMagnitude& NegativeLimit,
        FRateMagnitude& Magnitude,
        bool& Negative
    )
    {
        if (!std::isfinite(Rate))
        {
            return false;
        }

        uint64 Bits = 0;
        FMemory::Memcpy(&Bits, &Rate, sizeof(Bits));
        const int32 ExponentBits = static_cast<int32>((Bits >> 52) & 0x7ffULL);
        const uint64 Fraction = Bits & 0x000fffffffffffffULL;
        const bool RateNegative = (Bits & 0x8000000000000000ULL) != 0;
        const uint64 SignificandValue = ExponentBits == 0
            ? Fraction
            : Fraction | 0x0010000000000000ULL;
        const int32 Exponent = ExponentBits == 0 ? -1074 : ExponentBits - 1075;
        Negative = Count < 0 != RateNegative;

        FRateMagnitude Product = CountMagnitude(Count);
        Product.Multiply(FRateMagnitude(static_cast<int64>(SignificandValue)));
        if (Product.IsZero())
        {
            Magnitude = Product;
            Negative = false;
            return true;
        }

        const int32 BitLength = Product.IsZero() ? 0 : Product.GetHighestNonZeroBit() + 1;
        int32 EffectiveExponent = Exponent;
        if (BitLength > 100)
        {
            const int32 Shift = BitLength - 100;
            const FRateMagnitude Quotient = Product >> Shift;
            const FRateMagnitude Remainder = Product - (Quotient << Shift);
            const FRateMagnitude Halfway = FRateMagnitude(1) << (Shift - 1);
            Product = Quotient;
            if (Remainder > Halfway || (Remainder == Halfway && Product.IsFirstBitSet()))
            {
                ++Product;
            }
            EffectiveExponent += Shift;
        }

        const FRateMagnitude& Limit = Negative ? NegativeLimit : PositiveLimit;
        if (EffectiveExponent >= 0)
        {
            if (!Product.IsZero() && EffectiveExponent >= 256)
            {
                return false;
            }
            const FRateMagnitude Allowed = EffectiveExponent >= 256
                ? FRateMagnitude()
                : Limit >> EffectiveExponent;
            if (Product > Allowed)
            {
                return false;
            }
            Product <<= EffectiveExponent;
        }
        else
        {
            Product >>= -EffectiveExponent;
        }

        if (Product > Limit)
        {
            return false;
        }
        Magnitude = Product;
        return true;
    }
}

bool TryApplyServerRate(
    const int64 Count,
    const double Rate,
    int64& Value
)
{
    Value = Count;
    bool Negative = false;
    FRateMagnitude Product;
    if (!TryScaleDouble(
        Count,
        Rate,
        MaxConvertibleMagnitude(false, false),
        MaxConvertibleMagnitude(true, false),
        Product,
        Negative
    ))
    {
        return false;
    }
    return TryConvertMagnitude(Product, Negative, false, Value);
}

bool TryApplyServerRate(
    const int64 Count,
    const TBigInt<1024, false>& Rate,
    int64& Value
)
{
    Value = Count;
    if (Count == 0 || Rate.IsZero())
    {
        Value = 0;
        return true;
    }

    // The exposed C++ Rate type is unsigned. Any rate with bit 63 set is
    // already outside the strict Int64 conversion range for a nonzero count.
    if (Rate.GetHighestNonZeroBit() >= 63)
    {
        return false;
    }

    FRateMagnitude Product = CountMagnitude(Count);
    Product.Multiply(FRateMagnitude(Rate.ToInt()));
    return TryConvertMagnitude(Product, Count < 0, false, Value);
}

bool TryApplyServerRate(
    const int32 Count,
    const double Rate,
    int32& Value
)
{
    Value = Count;
    bool Negative = false;
    FRateMagnitude Product;
    const FRateMagnitude Int32Limit = MaxConvertibleMagnitude(false, true);
    if (!TryScaleDouble(Count, Rate, Int32Limit, Int32Limit, Product, Negative))
    {
        return false;
    }
    return TryConvertMagnitude(Product, Negative, true, Value);
}

bool TryApplyServerRate(
    const int32 Count,
    const TBigInt<1024, false>& Rate,
    int32& Value
)
{
    Value = Count;
    if (Count == 0 || Rate.IsZero())
    {
        Value = 0;
        return true;
    }

    if (Rate.GetHighestNonZeroBit() >= 31)
    {
        return false;
    }

    FRateMagnitude Product = CountMagnitude(Count);
    Product.Multiply(FRateMagnitude(Rate.ToInt()));
    return TryConvertMagnitude(Product, Count < 0, true, Value);
}
}
