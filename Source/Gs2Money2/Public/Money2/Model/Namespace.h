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
#include "PlatformSetting.h"
#include "ScriptSetting.h"
#include "NotificationSetting.h"
#include "LogSetting.h"

namespace Gs2::Money2::Model
{
    class GS2MONEY2_API FNamespace final : public FGs2Object, public TSharedFromThis<FNamespace>
    {
        TOptional<FString> NamespaceIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> CurrencyUsagePriorityValue;
        TOptional<bool> SharedFreeCurrencyValue;
        TSharedPtr<FPlatformSetting> PlatformSettingValue;
        TSharedPtr<FScriptSetting> DepositBalanceScriptValue;
        TSharedPtr<FScriptSetting> WithdrawBalanceScriptValue;
        TOptional<FString> SubscribeScriptValue;
        TOptional<FString> RenewScriptValue;
        TOptional<FString> UnsubscribeScriptValue;
        TSharedPtr<FScriptSetting> TakeOverScriptValue;
        TSharedPtr<FNotificationSetting> ChangeSubscriptionStatusNotificationValue;
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
        TSharedPtr<FNamespace> WithCurrencyUsagePriority(const TOptional<FString> CurrencyUsagePriority);
        TSharedPtr<FNamespace> WithSharedFreeCurrency(const TOptional<bool> SharedFreeCurrency);
        TSharedPtr<FNamespace> WithPlatformSetting(const TSharedPtr<FPlatformSetting> PlatformSetting);
        TSharedPtr<FNamespace> WithDepositBalanceScript(const TSharedPtr<FScriptSetting> DepositBalanceScript);
        TSharedPtr<FNamespace> WithWithdrawBalanceScript(const TSharedPtr<FScriptSetting> WithdrawBalanceScript);
        TSharedPtr<FNamespace> WithSubscribeScript(const TOptional<FString> SubscribeScript);
        TSharedPtr<FNamespace> WithRenewScript(const TOptional<FString> RenewScript);
        TSharedPtr<FNamespace> WithUnsubscribeScript(const TOptional<FString> UnsubscribeScript);
        TSharedPtr<FNamespace> WithTakeOverScript(const TSharedPtr<FScriptSetting> TakeOverScript);
        TSharedPtr<FNamespace> WithChangeSubscriptionStatusNotification(const TSharedPtr<FNotificationSetting> ChangeSubscriptionStatusNotification);
        TSharedPtr<FNamespace> WithLogSetting(const TSharedPtr<FLogSetting> LogSetting);
        TSharedPtr<FNamespace> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FNamespace> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FNamespace> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetNamespaceId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetCurrencyUsagePriority() const;
        TOptional<bool> GetSharedFreeCurrency() const;
        FString GetSharedFreeCurrencyString() const;
        TSharedPtr<FPlatformSetting> GetPlatformSetting() const;
        TSharedPtr<FScriptSetting> GetDepositBalanceScript() const;
        TSharedPtr<FScriptSetting> GetWithdrawBalanceScript() const;
        TOptional<FString> GetSubscribeScript() const;
        TOptional<FString> GetRenewScript() const;
        TOptional<FString> GetUnsubscribeScript() const;
        TSharedPtr<FScriptSetting> GetTakeOverScript() const;
        TSharedPtr<FNotificationSetting> GetChangeSubscriptionStatusNotification() const;
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