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

#pragma once

#include "CoreMinimal.h"
#include "Core/Gs2Object.h"
#include "ScriptSetting.h"
#include "LogSetting.h"

namespace Gs2::Money::Model
{
    class GS2MONEY_API FNamespace final : public Gs2Object, public TSharedFromThis<FNamespace>
    {
        TOptional<FString> NamespaceIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> PriorityValue;
        TOptional<bool> ShareFreeValue;
        TOptional<FString> CurrencyValue;
        TOptional<FString> AppleKeyValue;
        TOptional<FString> GoogleKeyValue;
        TOptional<bool> EnableFakeReceiptValue;
        TSharedPtr<FScriptSetting> CreateWalletScriptValue;
        TSharedPtr<FScriptSetting> DepositScriptValue;
        TSharedPtr<FScriptSetting> WithdrawScriptValue;
        TOptional<double> BalanceValue;
        TSharedPtr<FLogSetting> LogSettingValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FNamespace();
        FNamespace(
            const FNamespace& From
        );
        virtual ~FNamespace() override = default;

        TSharedPtr<FNamespace> WithNamespaceId(const TOptional<FString> NamespaceId);
        TSharedPtr<FNamespace> WithName(const TOptional<FString> Name);
        TSharedPtr<FNamespace> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FNamespace> WithPriority(const TOptional<FString> Priority);
        TSharedPtr<FNamespace> WithShareFree(const TOptional<bool> ShareFree);
        TSharedPtr<FNamespace> WithCurrency(const TOptional<FString> Currency);
        TSharedPtr<FNamespace> WithAppleKey(const TOptional<FString> AppleKey);
        TSharedPtr<FNamespace> WithGoogleKey(const TOptional<FString> GoogleKey);
        TSharedPtr<FNamespace> WithEnableFakeReceipt(const TOptional<bool> EnableFakeReceipt);
        TSharedPtr<FNamespace> WithCreateWalletScript(const TSharedPtr<FScriptSetting> CreateWalletScript);
        TSharedPtr<FNamespace> WithDepositScript(const TSharedPtr<FScriptSetting> DepositScript);
        TSharedPtr<FNamespace> WithWithdrawScript(const TSharedPtr<FScriptSetting> WithdrawScript);
        TSharedPtr<FNamespace> WithBalance(const TOptional<double> Balance);
        TSharedPtr<FNamespace> WithLogSetting(const TSharedPtr<FLogSetting> LogSetting);
        TSharedPtr<FNamespace> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FNamespace> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FNamespace> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetNamespaceId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetPriority() const;
        TOptional<bool> GetShareFree() const;
        FString GetShareFreeString() const;
        TOptional<FString> GetCurrency() const;
        TOptional<FString> GetAppleKey() const;
        TOptional<FString> GetGoogleKey() const;
        TOptional<bool> GetEnableFakeReceipt() const;
        FString GetEnableFakeReceiptString() const;
        TSharedPtr<FScriptSetting> GetCreateWalletScript() const;
        TSharedPtr<FScriptSetting> GetDepositScript() const;
        TSharedPtr<FScriptSetting> GetWithdrawScript() const;
        TOptional<double> GetBalance() const;
        FString GetBalanceString() const;
        TSharedPtr<FLogSetting> GetLogSetting() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);

        static TSharedPtr<FNamespace> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FNamespace, ESPMode::ThreadSafe> FNamespacePtr;
}