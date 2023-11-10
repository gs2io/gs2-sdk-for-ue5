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

#include "Money/Model/Namespace.h"

namespace Gs2::Money::Model
{
    FNamespace::FNamespace():
        NamespaceIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        PriorityValue(TOptional<FString>()),
        ShareFreeValue(TOptional<bool>()),
        CurrencyValue(TOptional<FString>()),
        AppleKeyValue(TOptional<FString>()),
        GoogleKeyValue(TOptional<FString>()),
        EnableFakeReceiptValue(TOptional<bool>()),
        CreateWalletScriptValue(nullptr),
        DepositScriptValue(nullptr),
        WithdrawScriptValue(nullptr),
        BalanceValue(TOptional<double>()),
        LogSettingValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FNamespace::FNamespace(
        const FNamespace& From
    ):
        NamespaceIdValue(From.NamespaceIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        PriorityValue(From.PriorityValue),
        ShareFreeValue(From.ShareFreeValue),
        CurrencyValue(From.CurrencyValue),
        AppleKeyValue(From.AppleKeyValue),
        GoogleKeyValue(From.GoogleKeyValue),
        EnableFakeReceiptValue(From.EnableFakeReceiptValue),
        CreateWalletScriptValue(From.CreateWalletScriptValue),
        DepositScriptValue(From.DepositScriptValue),
        WithdrawScriptValue(From.WithdrawScriptValue),
        BalanceValue(From.BalanceValue),
        LogSettingValue(From.LogSettingValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FNamespace> FNamespace::WithNamespaceId(
        const TOptional<FString> NamespaceId
    )
    {
        this->NamespaceIdValue = NamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithPriority(
        const TOptional<FString> Priority
    )
    {
        this->PriorityValue = Priority;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithShareFree(
        const TOptional<bool> ShareFree
    )
    {
        this->ShareFreeValue = ShareFree;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCurrency(
        const TOptional<FString> Currency
    )
    {
        this->CurrencyValue = Currency;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithAppleKey(
        const TOptional<FString> AppleKey
    )
    {
        this->AppleKeyValue = AppleKey;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithGoogleKey(
        const TOptional<FString> GoogleKey
    )
    {
        this->GoogleKeyValue = GoogleKey;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithEnableFakeReceipt(
        const TOptional<bool> EnableFakeReceipt
    )
    {
        this->EnableFakeReceiptValue = EnableFakeReceipt;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCreateWalletScript(
        const TSharedPtr<FScriptSetting> CreateWalletScript
    )
    {
        this->CreateWalletScriptValue = CreateWalletScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithDepositScript(
        const TSharedPtr<FScriptSetting> DepositScript
    )
    {
        this->DepositScriptValue = DepositScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithWithdrawScript(
        const TSharedPtr<FScriptSetting> WithdrawScript
    )
    {
        this->WithdrawScriptValue = WithdrawScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithBalance(
        const TOptional<double> Balance
    )
    {
        this->BalanceValue = Balance;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithLogSetting(
        const TSharedPtr<FLogSetting> LogSetting
    )
    {
        this->LogSettingValue = LogSetting;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FNamespace::GetNamespaceId() const
    {
        return NamespaceIdValue;
    }
    TOptional<FString> FNamespace::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FNamespace::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FNamespace::GetPriority() const
    {
        return PriorityValue;
    }
    TOptional<bool> FNamespace::GetShareFree() const
    {
        return ShareFreeValue;
    }

    FString FNamespace::GetShareFreeString() const
    {
        if (!ShareFreeValue.IsSet())
        {
            return FString("null");
        }
        return FString(ShareFreeValue.GetValue() ? "true" : "false");
    }
    TOptional<FString> FNamespace::GetCurrency() const
    {
        return CurrencyValue;
    }
    TOptional<FString> FNamespace::GetAppleKey() const
    {
        return AppleKeyValue;
    }
    TOptional<FString> FNamespace::GetGoogleKey() const
    {
        return GoogleKeyValue;
    }
    TOptional<bool> FNamespace::GetEnableFakeReceipt() const
    {
        return EnableFakeReceiptValue;
    }

    FString FNamespace::GetEnableFakeReceiptString() const
    {
        if (!EnableFakeReceiptValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableFakeReceiptValue.GetValue() ? "true" : "false");
    }
    TSharedPtr<FScriptSetting> FNamespace::GetCreateWalletScript() const
    {
        return CreateWalletScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetDepositScript() const
    {
        return DepositScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetWithdrawScript() const
    {
        return WithdrawScriptValue;
    }
    TOptional<double> FNamespace::GetBalance() const
    {
        return BalanceValue;
    }

    FString FNamespace::GetBalanceString() const
    {
        if (!BalanceValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), BalanceValue.GetValue());
    }
    TSharedPtr<FLogSetting> FNamespace::GetLogSetting() const
    {
        return LogSettingValue;
    }
    TOptional<int64> FNamespace::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FNamespace::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FNamespace::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FNamespace::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FNamespace::GetRevision() const
    {
        return RevisionValue;
    }

    FString FNamespace::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FNamespace::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FNamespace> FNamespace::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FNamespace>()
            ->WithNamespaceId(Data->HasField("namespaceId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("namespaceId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("description", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPriority(Data->HasField("priority") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("priority", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithShareFree(Data->HasField("shareFree") ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField("shareFree", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithCurrency(Data->HasField("currency") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("currency", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAppleKey(Data->HasField("appleKey") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("appleKey", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGoogleKey(Data->HasField("googleKey") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("googleKey", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithEnableFakeReceipt(Data->HasField("enableFakeReceipt") ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField("enableFakeReceipt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithCreateWalletScript(Data->HasField("createWalletScript") ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("createWalletScript"))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField("createWalletScript"));
                 }() : nullptr)
            ->WithDepositScript(Data->HasField("depositScript") ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("depositScript"))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField("depositScript"));
                 }() : nullptr)
            ->WithWithdrawScript(Data->HasField("withdrawScript") ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("withdrawScript"))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField("withdrawScript"));
                 }() : nullptr)
            ->WithBalance(Data->HasField("balance") ? [Data]() -> TOptional<double>
                {
                    double v;
                    if (Data->TryGetNumberField("balance", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<double>();
                }() : TOptional<double>())
            ->WithLogSetting(Data->HasField("logSetting") ? [Data]() -> Model::FLogSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("logSetting"))
                    {
                        return nullptr;
                    }
                    return Model::FLogSetting::FromJson(Data->GetObjectField("logSetting"));
                 }() : nullptr)
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

    TSharedPtr<FJsonObject> FNamespace::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceId", NamespaceIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (PriorityValue.IsSet())
        {
            JsonRootObject->SetStringField("priority", PriorityValue.GetValue());
        }
        if (ShareFreeValue.IsSet())
        {
            JsonRootObject->SetBoolField("shareFree", ShareFreeValue.GetValue());
        }
        if (CurrencyValue.IsSet())
        {
            JsonRootObject->SetStringField("currency", CurrencyValue.GetValue());
        }
        if (AppleKeyValue.IsSet())
        {
            JsonRootObject->SetStringField("appleKey", AppleKeyValue.GetValue());
        }
        if (GoogleKeyValue.IsSet())
        {
            JsonRootObject->SetStringField("googleKey", GoogleKeyValue.GetValue());
        }
        if (EnableFakeReceiptValue.IsSet())
        {
            JsonRootObject->SetBoolField("enableFakeReceipt", EnableFakeReceiptValue.GetValue());
        }
        if (CreateWalletScriptValue != nullptr && CreateWalletScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("createWalletScript", CreateWalletScriptValue->ToJson());
        }
        if (DepositScriptValue != nullptr && DepositScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("depositScript", DepositScriptValue->ToJson());
        }
        if (WithdrawScriptValue != nullptr && WithdrawScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("withdrawScript", WithdrawScriptValue->ToJson());
        }
        if (BalanceValue.IsSet())
        {
            JsonRootObject->SetNumberField("balance", BalanceValue.GetValue());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
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

    FString FNamespace::TypeName = "Namespace";
}