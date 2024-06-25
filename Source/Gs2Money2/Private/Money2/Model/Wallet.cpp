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

#include "Money2/Model/Wallet.h"

namespace Gs2::Money2::Model
{
    FWallet::FWallet():
        WalletIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        SlotValue(TOptional<int32>()),
        SummaryValue(nullptr),
        DepositTransactionsValue(nullptr),
        SharedFreeCurrencyValue(TOptional<bool>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FWallet::FWallet(
        const FWallet& From
    ):
        WalletIdValue(From.WalletIdValue),
        UserIdValue(From.UserIdValue),
        SlotValue(From.SlotValue),
        SummaryValue(From.SummaryValue),
        DepositTransactionsValue(From.DepositTransactionsValue),
        SharedFreeCurrencyValue(From.SharedFreeCurrencyValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FWallet> FWallet::WithWalletId(
        const TOptional<FString> WalletId
    )
    {
        this->WalletIdValue = WalletId;
        return SharedThis(this);
    }

    TSharedPtr<FWallet> FWallet::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FWallet> FWallet::WithSlot(
        const TOptional<int32> Slot
    )
    {
        this->SlotValue = Slot;
        return SharedThis(this);
    }

    TSharedPtr<FWallet> FWallet::WithSummary(
        const TSharedPtr<FWalletSummary> Summary
    )
    {
        this->SummaryValue = Summary;
        return SharedThis(this);
    }

    TSharedPtr<FWallet> FWallet::WithDepositTransactions(
        const TSharedPtr<TArray<TSharedPtr<Model::FDepositTransaction>>> DepositTransactions
    )
    {
        this->DepositTransactionsValue = DepositTransactions;
        return SharedThis(this);
    }

    TSharedPtr<FWallet> FWallet::WithSharedFreeCurrency(
        const TOptional<bool> SharedFreeCurrency
    )
    {
        this->SharedFreeCurrencyValue = SharedFreeCurrency;
        return SharedThis(this);
    }

    TSharedPtr<FWallet> FWallet::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FWallet> FWallet::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FWallet> FWallet::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FWallet::GetWalletId() const
    {
        return WalletIdValue;
    }
    TOptional<FString> FWallet::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int32> FWallet::GetSlot() const
    {
        return SlotValue;
    }

    FString FWallet::GetSlotString() const
    {
        if (!SlotValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), SlotValue.GetValue());
    }
    TSharedPtr<FWalletSummary> FWallet::GetSummary() const
    {
        return SummaryValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FDepositTransaction>>> FWallet::GetDepositTransactions() const
    {
        return DepositTransactionsValue;
    }
    TOptional<bool> FWallet::GetSharedFreeCurrency() const
    {
        return SharedFreeCurrencyValue;
    }

    FString FWallet::GetSharedFreeCurrencyString() const
    {
        if (!SharedFreeCurrencyValue.IsSet())
        {
            return FString("null");
        }
        return FString(SharedFreeCurrencyValue.GetValue() ? "true" : "false");
    }
    TOptional<int64> FWallet::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FWallet::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FWallet::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FWallet::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FWallet::GetRevision() const
    {
        return RevisionValue;
    }

    FString FWallet::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FWallet::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):user:(?<userId>.+):wallet:(?<slot>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FWallet::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):user:(?<userId>.+):wallet:(?<slot>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FWallet::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):user:(?<userId>.+):wallet:(?<slot>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FWallet::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):user:(?<userId>.+):wallet:(?<slot>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FWallet::GetSlotFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):user:(?<userId>.+):wallet:(?<slot>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FWallet> FWallet::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FWallet>()
            ->WithWalletId(Data->HasField(ANSI_TO_TCHAR("walletId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("walletId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSlot(Data->HasField(ANSI_TO_TCHAR("slot")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("slot"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithSummary(Data->HasField(ANSI_TO_TCHAR("summary")) ? [Data]() -> Model::FWalletSummaryPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("summary")))
                    {
                        return nullptr;
                    }
                    return Model::FWalletSummary::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("summary")));
                 }() : nullptr)
            ->WithDepositTransactions(Data->HasField(ANSI_TO_TCHAR("depositTransactions")) ? [Data]() -> TSharedPtr<TArray<Model::FDepositTransactionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FDepositTransactionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("depositTransactions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("depositTransactions")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("depositTransactions")))
                        {
                            v->Add(Model::FDepositTransaction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FDepositTransactionPtr>>())
            ->WithSharedFreeCurrency(Data->HasField(ANSI_TO_TCHAR("sharedFreeCurrency")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("sharedFreeCurrency"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
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

    TSharedPtr<FJsonObject> FWallet::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (WalletIdValue.IsSet())
        {
            JsonRootObject->SetStringField("walletId", WalletIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (SlotValue.IsSet())
        {
            JsonRootObject->SetNumberField("slot", SlotValue.GetValue());
        }
        if (SummaryValue != nullptr && SummaryValue.IsValid())
        {
            JsonRootObject->SetObjectField("summary", SummaryValue->ToJson());
        }
        if (DepositTransactionsValue != nullptr && DepositTransactionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *DepositTransactionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("depositTransactions", v);
        }
        if (SharedFreeCurrencyValue.IsSet())
        {
            JsonRootObject->SetBoolField("sharedFreeCurrency", SharedFreeCurrencyValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
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

    FString FWallet::TypeName = "Wallet";
}