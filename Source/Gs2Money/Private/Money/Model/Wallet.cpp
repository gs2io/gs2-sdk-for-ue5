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

#include "Money/Model/Wallet.h"

namespace Gs2::Money::Model
{
    FWallet::FWallet():
        WalletIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        SlotValue(TOptional<int32>()),
        PaidValue(TOptional<int32>()),
        FreeValue(TOptional<int32>()),
        DetailValue(nullptr),
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
        PaidValue(From.PaidValue),
        FreeValue(From.FreeValue),
        DetailValue(From.DetailValue),
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

    TSharedPtr<FWallet> FWallet::WithPaid(
        const TOptional<int32> Paid
    )
    {
        this->PaidValue = Paid;
        return SharedThis(this);
    }

    TSharedPtr<FWallet> FWallet::WithFree(
        const TOptional<int32> Free
    )
    {
        this->FreeValue = Free;
        return SharedThis(this);
    }

    TSharedPtr<FWallet> FWallet::WithDetail(
        const TSharedPtr<TArray<TSharedPtr<Model::FWalletDetail>>> Detail
    )
    {
        this->DetailValue = Detail;
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
    TOptional<int32> FWallet::GetPaid() const
    {
        return PaidValue;
    }

    FString FWallet::GetPaidString() const
    {
        if (!PaidValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), PaidValue.GetValue());
    }
    TOptional<int32> FWallet::GetFree() const
    {
        return FreeValue;
    }

    FString FWallet::GetFreeString() const
    {
        if (!FreeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), FreeValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FWalletDetail>>> FWallet::GetDetail() const
    {
        return DetailValue;
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
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money:(?<namespaceName>.+):user:(?<userId>.+):wallet:(?<slot>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FWallet::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money:(?<namespaceName>.+):user:(?<userId>.+):wallet:(?<slot>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FWallet::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money:(?<namespaceName>.+):user:(?<userId>.+):wallet:(?<slot>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FWallet::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money:(?<namespaceName>.+):user:(?<userId>.+):wallet:(?<slot>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FWallet::GetSlotFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money:(?<namespaceName>.+):user:(?<userId>.+):wallet:(?<slot>.+)"));
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
            ->WithWalletId(Data->HasField("walletId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("walletId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSlot(Data->HasField("slot") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("slot", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithPaid(Data->HasField("paid") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("paid", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithFree(Data->HasField("free") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("free", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithDetail(Data->HasField("detail") ? [Data]() -> TSharedPtr<TArray<Model::FWalletDetailPtr>>
                {
                    auto v = MakeShared<TArray<Model::FWalletDetailPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("detail") && Data->HasTypedField<EJson::Array>("detail"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("detail"))
                        {
                            v->Add(Model::FWalletDetail::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FWalletDetailPtr>>())
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
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField("revision") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("revision", v))
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
        if (PaidValue.IsSet())
        {
            JsonRootObject->SetNumberField("paid", PaidValue.GetValue());
        }
        if (FreeValue.IsSet())
        {
            JsonRootObject->SetNumberField("free", FreeValue.GetValue());
        }
        if (DetailValue != nullptr && DetailValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *DetailValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("detail", v);
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