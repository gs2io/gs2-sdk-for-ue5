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
 */

#include "Lottery/Model/PrizeLimit.h"

namespace Gs2::Lottery::Model
{
    FPrizeLimit::FPrizeLimit():
        PrizeLimitIdValue(TOptional<FString>()),
        PrizeIdValue(TOptional<FString>()),
        DrawnCountValue(TOptional<int32>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FPrizeLimit::FPrizeLimit(
        const FPrizeLimit& From
    ):
        PrizeLimitIdValue(From.PrizeLimitIdValue),
        PrizeIdValue(From.PrizeIdValue),
        DrawnCountValue(From.DrawnCountValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FPrizeLimit> FPrizeLimit::WithPrizeLimitId(
        const TOptional<FString> PrizeLimitId
    )
    {
        this->PrizeLimitIdValue = PrizeLimitId;
        return SharedThis(this);
    }

    TSharedPtr<FPrizeLimit> FPrizeLimit::WithPrizeId(
        const TOptional<FString> PrizeId
    )
    {
        this->PrizeIdValue = PrizeId;
        return SharedThis(this);
    }

    TSharedPtr<FPrizeLimit> FPrizeLimit::WithDrawnCount(
        const TOptional<int32> DrawnCount
    )
    {
        this->DrawnCountValue = DrawnCount;
        return SharedThis(this);
    }

    TSharedPtr<FPrizeLimit> FPrizeLimit::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FPrizeLimit> FPrizeLimit::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FPrizeLimit::GetPrizeLimitId() const
    {
        return PrizeLimitIdValue;
    }
    TOptional<FString> FPrizeLimit::GetPrizeId() const
    {
        return PrizeIdValue;
    }
    TOptional<int32> FPrizeLimit::GetDrawnCount() const
    {
        return DrawnCountValue;
    }

    FString FPrizeLimit::GetDrawnCountString() const
    {
        if (!DrawnCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DrawnCountValue.GetValue());
    }
    TOptional<int64> FPrizeLimit::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FPrizeLimit::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FPrizeLimit::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FPrizeLimit::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FPrizeLimit::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):table:(?<prizeTableName>.+):prize:(?<prizeId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FPrizeLimit::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):table:(?<prizeTableName>.+):prize:(?<prizeId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FPrizeLimit::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):table:(?<prizeTableName>.+):prize:(?<prizeId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FPrizeLimit::GetPrizeTableNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):table:(?<prizeTableName>.+):prize:(?<prizeId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FPrizeLimit::GetPrizeIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):lottery:(?<namespaceName>.+):table:(?<prizeTableName>.+):prize:(?<prizeId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FPrizeLimit> FPrizeLimit::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPrizeLimit>()
            ->WithPrizeLimitId(Data->HasField("prizeLimitId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("prizeLimitId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPrizeId(Data->HasField("prizeId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("prizeId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDrawnCount(Data->HasField("drawnCount") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("drawnCount", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField("updatedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("updatedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FPrizeLimit::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (PrizeLimitIdValue.IsSet())
        {
            JsonRootObject->SetStringField("prizeLimitId", PrizeLimitIdValue.GetValue());
        }
        if (PrizeIdValue.IsSet())
        {
            JsonRootObject->SetStringField("prizeId", PrizeIdValue.GetValue());
        }
        if (DrawnCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("drawnCount", DrawnCountValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FPrizeLimit::TypeName = "PrizeLimit";
}