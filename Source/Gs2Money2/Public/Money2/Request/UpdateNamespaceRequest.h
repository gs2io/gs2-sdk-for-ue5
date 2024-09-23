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
#include "../Model/PlatformSetting.h"
#include "../Model/ScriptSetting.h"
#include "../Model/LogSetting.h"

namespace Gs2::Money2::Request
{
    class FUpdateNamespaceRequest;

    class GS2MONEY2_API FUpdateNamespaceRequest final : public TSharedFromThis<FUpdateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CurrencyUsagePriorityValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<Model::FPlatformSetting> PlatformSettingValue;
        TSharedPtr<Model::FScriptSetting> DepositBalanceScriptValue;
        TSharedPtr<Model::FScriptSetting> WithdrawBalanceScriptValue;
        TSharedPtr<Model::FLogSetting> LogSettingValue;
        
    public:
        
        FUpdateNamespaceRequest();
        FUpdateNamespaceRequest(
            const FUpdateNamespaceRequest& From
        );
        ~FUpdateNamespaceRequest() = default;

        TSharedPtr<FUpdateNamespaceRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateNamespaceRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateNamespaceRequest> WithCurrencyUsagePriority(const TOptional<FString> CurrencyUsagePriority);
        TSharedPtr<FUpdateNamespaceRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateNamespaceRequest> WithPlatformSetting(const TSharedPtr<Model::FPlatformSetting> PlatformSetting);
        TSharedPtr<FUpdateNamespaceRequest> WithDepositBalanceScript(const TSharedPtr<Model::FScriptSetting> DepositBalanceScript);
        TSharedPtr<FUpdateNamespaceRequest> WithWithdrawBalanceScript(const TSharedPtr<Model::FScriptSetting> WithdrawBalanceScript);
        TSharedPtr<FUpdateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCurrencyUsagePriority() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<Model::FPlatformSetting> GetPlatformSetting() const;
        TSharedPtr<Model::FScriptSetting> GetDepositBalanceScript() const;
        TSharedPtr<Model::FScriptSetting> GetWithdrawBalanceScript() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FUpdateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateNamespaceRequest, ESPMode::ThreadSafe> FUpdateNamespaceRequestPtr;
}