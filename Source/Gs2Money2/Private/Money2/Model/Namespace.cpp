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

#include "Money2/Model/Namespace.h"

namespace Gs2::Money2::Model
{
    FNamespace::FNamespace():
        NamespaceIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        TransactionSettingValue(nullptr),
        CurrencyUsagePriorityValue(TOptional<FString>()),
        SharedFreeCurrencyValue(TOptional<bool>()),
        PlatformSettingValue(nullptr),
        DepositBalanceScriptValue(nullptr),
        WithdrawBalanceScriptValue(nullptr),
        VerifyReceiptScriptValue(nullptr),
        SubscribeScriptValue(TOptional<FString>()),
        RenewScriptValue(TOptional<FString>()),
        UnsubscribeScriptValue(TOptional<FString>()),
        TakeOverScriptValue(nullptr),
        ChangeSubscriptionStatusNotificationValue(nullptr),
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
        TransactionSettingValue(From.TransactionSettingValue),
        CurrencyUsagePriorityValue(From.CurrencyUsagePriorityValue),
        SharedFreeCurrencyValue(From.SharedFreeCurrencyValue),
        PlatformSettingValue(From.PlatformSettingValue),
        DepositBalanceScriptValue(From.DepositBalanceScriptValue),
        WithdrawBalanceScriptValue(From.WithdrawBalanceScriptValue),
        VerifyReceiptScriptValue(From.VerifyReceiptScriptValue),
        SubscribeScriptValue(From.SubscribeScriptValue),
        RenewScriptValue(From.RenewScriptValue),
        UnsubscribeScriptValue(From.UnsubscribeScriptValue),
        TakeOverScriptValue(From.TakeOverScriptValue),
        ChangeSubscriptionStatusNotificationValue(From.ChangeSubscriptionStatusNotificationValue),
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

    TSharedPtr<FNamespace> FNamespace::WithTransactionSetting(
        const TSharedPtr<FTransactionSetting> TransactionSetting
    )
    {
        this->TransactionSettingValue = TransactionSetting;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCurrencyUsagePriority(
        const TOptional<FString> CurrencyUsagePriority
    )
    {
        this->CurrencyUsagePriorityValue = CurrencyUsagePriority;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithSharedFreeCurrency(
        const TOptional<bool> SharedFreeCurrency
    )
    {
        this->SharedFreeCurrencyValue = SharedFreeCurrency;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithPlatformSetting(
        const TSharedPtr<FPlatformSetting> PlatformSetting
    )
    {
        this->PlatformSettingValue = PlatformSetting;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithDepositBalanceScript(
        const TSharedPtr<FScriptSetting> DepositBalanceScript
    )
    {
        this->DepositBalanceScriptValue = DepositBalanceScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithWithdrawBalanceScript(
        const TSharedPtr<FScriptSetting> WithdrawBalanceScript
    )
    {
        this->WithdrawBalanceScriptValue = WithdrawBalanceScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithVerifyReceiptScript(
        const TSharedPtr<FScriptSetting> VerifyReceiptScript
    )
    {
        this->VerifyReceiptScriptValue = VerifyReceiptScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithSubscribeScript(
        const TOptional<FString> SubscribeScript
    )
    {
        this->SubscribeScriptValue = SubscribeScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithRenewScript(
        const TOptional<FString> RenewScript
    )
    {
        this->RenewScriptValue = RenewScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithUnsubscribeScript(
        const TOptional<FString> UnsubscribeScript
    )
    {
        this->UnsubscribeScriptValue = UnsubscribeScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithTakeOverScript(
        const TSharedPtr<FScriptSetting> TakeOverScript
    )
    {
        this->TakeOverScriptValue = TakeOverScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithChangeSubscriptionStatusNotification(
        const TSharedPtr<FNotificationSetting> ChangeSubscriptionStatusNotification
    )
    {
        this->ChangeSubscriptionStatusNotificationValue = ChangeSubscriptionStatusNotification;
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
    TSharedPtr<FTransactionSetting> FNamespace::GetTransactionSetting() const
    {
        return TransactionSettingValue;
    }
    TOptional<FString> FNamespace::GetCurrencyUsagePriority() const
    {
        return CurrencyUsagePriorityValue;
    }
    TOptional<bool> FNamespace::GetSharedFreeCurrency() const
    {
        return SharedFreeCurrencyValue;
    }

    FString FNamespace::GetSharedFreeCurrencyString() const
    {
        if (!SharedFreeCurrencyValue.IsSet())
        {
            return FString("null");
        }
        return FString(SharedFreeCurrencyValue.GetValue() ? "true" : "false");
    }
    TSharedPtr<FPlatformSetting> FNamespace::GetPlatformSetting() const
    {
        return PlatformSettingValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetDepositBalanceScript() const
    {
        return DepositBalanceScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetWithdrawBalanceScript() const
    {
        return WithdrawBalanceScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetVerifyReceiptScript() const
    {
        return VerifyReceiptScriptValue;
    }
    TOptional<FString> FNamespace::GetSubscribeScript() const
    {
        return SubscribeScriptValue;
    }
    TOptional<FString> FNamespace::GetRenewScript() const
    {
        return RenewScriptValue;
    }
    TOptional<FString> FNamespace::GetUnsubscribeScript() const
    {
        return UnsubscribeScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetTakeOverScript() const
    {
        return TakeOverScriptValue;
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetChangeSubscriptionStatusNotification() const
    {
        return ChangeSubscriptionStatusNotificationValue;
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
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+)"));
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
            ->WithNamespaceId(Data->HasField(ANSI_TO_TCHAR("namespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTransactionSetting(Data->HasField(ANSI_TO_TCHAR("transactionSetting")) ? [Data]() -> Model::FTransactionSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("transactionSetting")))
                    {
                        return nullptr;
                    }
                    return Model::FTransactionSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("transactionSetting")));
                 }() : nullptr)
            ->WithCurrencyUsagePriority(Data->HasField(ANSI_TO_TCHAR("currencyUsagePriority")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("currencyUsagePriority"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSharedFreeCurrency(Data->HasField(ANSI_TO_TCHAR("sharedFreeCurrency")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("sharedFreeCurrency"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithPlatformSetting(Data->HasField(ANSI_TO_TCHAR("platformSetting")) ? [Data]() -> Model::FPlatformSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("platformSetting")))
                    {
                        return nullptr;
                    }
                    return Model::FPlatformSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("platformSetting")));
                 }() : nullptr)
            ->WithDepositBalanceScript(Data->HasField(ANSI_TO_TCHAR("depositBalanceScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("depositBalanceScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("depositBalanceScript")));
                 }() : nullptr)
            ->WithWithdrawBalanceScript(Data->HasField(ANSI_TO_TCHAR("withdrawBalanceScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("withdrawBalanceScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("withdrawBalanceScript")));
                 }() : nullptr)
            ->WithVerifyReceiptScript(Data->HasField(ANSI_TO_TCHAR("verifyReceiptScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("verifyReceiptScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("verifyReceiptScript")));
                 }() : nullptr)
            ->WithSubscribeScript(Data->HasField(ANSI_TO_TCHAR("subscribeScript")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("subscribeScript"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRenewScript(Data->HasField(ANSI_TO_TCHAR("renewScript")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("renewScript"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUnsubscribeScript(Data->HasField(ANSI_TO_TCHAR("unsubscribeScript")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("unsubscribeScript"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTakeOverScript(Data->HasField(ANSI_TO_TCHAR("takeOverScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("takeOverScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("takeOverScript")));
                 }() : nullptr)
            ->WithChangeSubscriptionStatusNotification(Data->HasField(ANSI_TO_TCHAR("changeSubscriptionStatusNotification")) ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("changeSubscriptionStatusNotification")))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("changeSubscriptionStatusNotification")));
                 }() : nullptr)
            ->WithLogSetting(Data->HasField(ANSI_TO_TCHAR("logSetting")) ? [Data]() -> Model::FLogSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("logSetting")))
                    {
                        return nullptr;
                    }
                    return Model::FLogSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("logSetting")));
                 }() : nullptr)
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
        if (TransactionSettingValue != nullptr && TransactionSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("transactionSetting", TransactionSettingValue->ToJson());
        }
        if (CurrencyUsagePriorityValue.IsSet())
        {
            JsonRootObject->SetStringField("currencyUsagePriority", CurrencyUsagePriorityValue.GetValue());
        }
        if (SharedFreeCurrencyValue.IsSet())
        {
            JsonRootObject->SetBoolField("sharedFreeCurrency", SharedFreeCurrencyValue.GetValue());
        }
        if (PlatformSettingValue != nullptr && PlatformSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("platformSetting", PlatformSettingValue->ToJson());
        }
        if (DepositBalanceScriptValue != nullptr && DepositBalanceScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("depositBalanceScript", DepositBalanceScriptValue->ToJson());
        }
        if (WithdrawBalanceScriptValue != nullptr && WithdrawBalanceScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("withdrawBalanceScript", WithdrawBalanceScriptValue->ToJson());
        }
        if (VerifyReceiptScriptValue != nullptr && VerifyReceiptScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("verifyReceiptScript", VerifyReceiptScriptValue->ToJson());
        }
        if (SubscribeScriptValue.IsSet())
        {
            JsonRootObject->SetStringField("subscribeScript", SubscribeScriptValue.GetValue());
        }
        if (RenewScriptValue.IsSet())
        {
            JsonRootObject->SetStringField("renewScript", RenewScriptValue.GetValue());
        }
        if (UnsubscribeScriptValue.IsSet())
        {
            JsonRootObject->SetStringField("unsubscribeScript", UnsubscribeScriptValue.GetValue());
        }
        if (TakeOverScriptValue != nullptr && TakeOverScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("takeOverScript", TakeOverScriptValue->ToJson());
        }
        if (ChangeSubscriptionStatusNotificationValue != nullptr && ChangeSubscriptionStatusNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("changeSubscriptionStatusNotification", ChangeSubscriptionStatusNotificationValue->ToJson());
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