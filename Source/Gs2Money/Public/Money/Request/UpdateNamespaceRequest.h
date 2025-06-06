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
#include "../Model/ScriptSetting.h"
#include "../Model/LogSetting.h"

namespace Gs2::Money::Request
{
    class FUpdateNamespaceRequest;

    class GS2MONEY_API FUpdateNamespaceRequest final : public TSharedFromThis<FUpdateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> PriorityValue;
        TOptional<FString> AppleKeyValue;
        TOptional<FString> GoogleKeyValue;
        TOptional<bool> EnableFakeReceiptValue;
        TSharedPtr<Model::FScriptSetting> CreateWalletScriptValue;
        TSharedPtr<Model::FScriptSetting> DepositScriptValue;
        TSharedPtr<Model::FScriptSetting> WithdrawScriptValue;
        TSharedPtr<Model::FLogSetting> LogSettingValue;
        
    public:
        
        FUpdateNamespaceRequest();
        FUpdateNamespaceRequest(
            const FUpdateNamespaceRequest& From
        );
        ~FUpdateNamespaceRequest() = default;

        TSharedPtr<FUpdateNamespaceRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateNamespaceRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateNamespaceRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateNamespaceRequest> WithPriority(const TOptional<FString> Priority);
        TSharedPtr<FUpdateNamespaceRequest> WithAppleKey(const TOptional<FString> AppleKey);
        TSharedPtr<FUpdateNamespaceRequest> WithGoogleKey(const TOptional<FString> GoogleKey);
        TSharedPtr<FUpdateNamespaceRequest> WithEnableFakeReceipt(const TOptional<bool> EnableFakeReceipt);
        TSharedPtr<FUpdateNamespaceRequest> WithCreateWalletScript(const TSharedPtr<Model::FScriptSetting> CreateWalletScript);
        TSharedPtr<FUpdateNamespaceRequest> WithDepositScript(const TSharedPtr<Model::FScriptSetting> DepositScript);
        TSharedPtr<FUpdateNamespaceRequest> WithWithdrawScript(const TSharedPtr<Model::FScriptSetting> WithdrawScript);
        TSharedPtr<FUpdateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetPriority() const;
        TOptional<FString> GetAppleKey() const;
        TOptional<FString> GetGoogleKey() const;
        TOptional<bool> GetEnableFakeReceipt() const;
        FString GetEnableFakeReceiptString() const;
        TSharedPtr<Model::FScriptSetting> GetCreateWalletScript() const;
        TSharedPtr<Model::FScriptSetting> GetDepositScript() const;
        TSharedPtr<Model::FScriptSetting> GetWithdrawScript() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FUpdateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequestPtr;
}