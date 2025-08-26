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
#include "Dom/JsonObject.h"
#include "../Model/PlatformSetting.h"
#include "../Model/ScriptSetting.h"
#include "../Model/NotificationSetting.h"
#include "../Model/LogSetting.h"

namespace Gs2::Money2::Request
{
    class FCreateNamespaceRequest;

    class GS2MONEY2_API FCreateNamespaceRequest final : public TSharedFromThis<FCreateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NameValue;
        TOptional<FString> CurrencyUsagePriorityValue;
        TOptional<FString> DescriptionValue;
        TOptional<bool> SharedFreeCurrencyValue;
        TSharedPtr<Model::FPlatformSetting> PlatformSettingValue;
        TSharedPtr<Model::FScriptSetting> DepositBalanceScriptValue;
        TSharedPtr<Model::FScriptSetting> WithdrawBalanceScriptValue;
        TSharedPtr<Model::FScriptSetting> VerifyReceiptScriptValue;
        TOptional<FString> SubscribeScriptValue;
        TOptional<FString> RenewScriptValue;
        TOptional<FString> UnsubscribeScriptValue;
        TSharedPtr<Model::FScriptSetting> TakeOverScriptValue;
        TSharedPtr<Model::FNotificationSetting> ChangeSubscriptionStatusNotificationValue;
        TSharedPtr<Model::FLogSetting> LogSettingValue;
        
    public:
        
        FCreateNamespaceRequest();
        FCreateNamespaceRequest(
            const FCreateNamespaceRequest& From
        );
        ~FCreateNamespaceRequest() = default;

        TSharedPtr<FCreateNamespaceRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateNamespaceRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateNamespaceRequest> WithCurrencyUsagePriority(const TOptional<FString> CurrencyUsagePriority);
        TSharedPtr<FCreateNamespaceRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateNamespaceRequest> WithSharedFreeCurrency(const TOptional<bool> SharedFreeCurrency);
        TSharedPtr<FCreateNamespaceRequest> WithPlatformSetting(const TSharedPtr<Model::FPlatformSetting> PlatformSetting);
        TSharedPtr<FCreateNamespaceRequest> WithDepositBalanceScript(const TSharedPtr<Model::FScriptSetting> DepositBalanceScript);
        TSharedPtr<FCreateNamespaceRequest> WithWithdrawBalanceScript(const TSharedPtr<Model::FScriptSetting> WithdrawBalanceScript);
        TSharedPtr<FCreateNamespaceRequest> WithVerifyReceiptScript(const TSharedPtr<Model::FScriptSetting> VerifyReceiptScript);
        TSharedPtr<FCreateNamespaceRequest> WithSubscribeScript(const TOptional<FString> SubscribeScript);
        TSharedPtr<FCreateNamespaceRequest> WithRenewScript(const TOptional<FString> RenewScript);
        TSharedPtr<FCreateNamespaceRequest> WithUnsubscribeScript(const TOptional<FString> UnsubscribeScript);
        TSharedPtr<FCreateNamespaceRequest> WithTakeOverScript(const TSharedPtr<Model::FScriptSetting> TakeOverScript);
        TSharedPtr<FCreateNamespaceRequest> WithChangeSubscriptionStatusNotification(const TSharedPtr<Model::FNotificationSetting> ChangeSubscriptionStatusNotification);
        TSharedPtr<FCreateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetCurrencyUsagePriority() const;
        TOptional<FString> GetDescription() const;
        TOptional<bool> GetSharedFreeCurrency() const;
        FString GetSharedFreeCurrencyString() const;
        TSharedPtr<Model::FPlatformSetting> GetPlatformSetting() const;
        TSharedPtr<Model::FScriptSetting> GetDepositBalanceScript() const;
        TSharedPtr<Model::FScriptSetting> GetWithdrawBalanceScript() const;
        TSharedPtr<Model::FScriptSetting> GetVerifyReceiptScript() const;
        TOptional<FString> GetSubscribeScript() const;
        TOptional<FString> GetRenewScript() const;
        TOptional<FString> GetUnsubscribeScript() const;
        TSharedPtr<Model::FScriptSetting> GetTakeOverScript() const;
        TSharedPtr<Model::FNotificationSetting> GetChangeSubscriptionStatusNotification() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FCreateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequestPtr;
}