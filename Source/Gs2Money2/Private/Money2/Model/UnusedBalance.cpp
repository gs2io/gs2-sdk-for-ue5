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

#include "Money2/Model/UnusedBalance.h"

namespace Gs2::Money2::Model
{
    FUnusedBalance::FUnusedBalance():
        UnusedBalanceIdValue(TOptional<FString>()),
        CurrencyValue(TOptional<FString>()),
        BalanceValue(TOptional<double>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FUnusedBalance::FUnusedBalance(
        const FUnusedBalance& From
    ):
        UnusedBalanceIdValue(From.UnusedBalanceIdValue),
        CurrencyValue(From.CurrencyValue),
        BalanceValue(From.BalanceValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FUnusedBalance> FUnusedBalance::WithUnusedBalanceId(
        const TOptional<FString> UnusedBalanceId
    )
    {
        this->UnusedBalanceIdValue = UnusedBalanceId;
        return SharedThis(this);
    }

    TSharedPtr<FUnusedBalance> FUnusedBalance::WithCurrency(
        const TOptional<FString> Currency
    )
    {
        this->CurrencyValue = Currency;
        return SharedThis(this);
    }

    TSharedPtr<FUnusedBalance> FUnusedBalance::WithBalance(
        const TOptional<double> Balance
    )
    {
        this->BalanceValue = Balance;
        return SharedThis(this);
    }

    TSharedPtr<FUnusedBalance> FUnusedBalance::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FUnusedBalance> FUnusedBalance::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FUnusedBalance::GetUnusedBalanceId() const
    {
        return UnusedBalanceIdValue;
    }
    TOptional<FString> FUnusedBalance::GetCurrency() const
    {
        return CurrencyValue;
    }
    TOptional<double> FUnusedBalance::GetBalance() const
    {
        return BalanceValue;
    }

    FString FUnusedBalance::GetBalanceString() const
    {
        if (!BalanceValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), BalanceValue.GetValue());
    }
    TOptional<int64> FUnusedBalance::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FUnusedBalance::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FUnusedBalance::GetRevision() const
    {
        return RevisionValue;
    }

    FString FUnusedBalance::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FUnusedBalance::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):unused:(?<currency>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FUnusedBalance::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):unused:(?<currency>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FUnusedBalance::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):unused:(?<currency>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FUnusedBalance::GetCurrencyFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):unused:(?<currency>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FUnusedBalance> FUnusedBalance::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUnusedBalance>()
            ->WithUnusedBalanceId(Data->HasField(ANSI_TO_TCHAR("unusedBalanceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("unusedBalanceId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCurrency(Data->HasField(ANSI_TO_TCHAR("currency")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("currency"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithBalance(Data->HasField(ANSI_TO_TCHAR("balance")) ? [Data]() -> TOptional<double>
                {
                    double v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("balance"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<double>();
                }() : TOptional<double>())
            ->WithUpdatedAt(Data->HasField(ANSI_TO_TCHAR("updatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("updatedAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FUnusedBalance::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UnusedBalanceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("unusedBalanceId", UnusedBalanceIdValue.GetValue());
        }
        if (CurrencyValue.IsSet())
        {
            JsonRootObject->SetStringField("currency", CurrencyValue.GetValue());
        }
        if (BalanceValue.IsSet())
        {
            JsonRootObject->SetNumberField("balance", BalanceValue.GetValue());
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FUnusedBalance::TypeName = "UnusedBalance";
}