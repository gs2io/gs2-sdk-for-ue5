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
#include "../Model/TransactionSetting.h"
#include "../Model/ScriptSetting.h"
#include "../Model/LogSetting.h"

namespace Gs2::Money::Request
{
    class FCreateNamespaceRequest;

    class GS2MONEY_API FCreateNamespaceRequest final : public TSharedFromThis<FCreateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<Model::FTransactionSetting> TransactionSettingValue;
        TOptional<FString> PriorityValue;
        TOptional<bool> ShareFreeValue;
        TOptional<FString> CurrencyValue;
        TOptional<FString> AppleKeyValue;
        TOptional<FString> GoogleKeyValue;
        TOptional<bool> EnableFakeReceiptValue;
        TSharedPtr<Model::FScriptSetting> CreateWalletScriptValue;
        TSharedPtr<Model::FScriptSetting> DepositScriptValue;
        TSharedPtr<Model::FScriptSetting> WithdrawScriptValue;
        TSharedPtr<Model::FLogSetting> LogSettingValue;
        
    public:
        
        FCreateNamespaceRequest();
        FCreateNamespaceRequest(
            const FCreateNamespaceRequest& From
        );
        ~FCreateNamespaceRequest() = default;

        TSharedPtr<FCreateNamespaceRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateNamespaceRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateNamespaceRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateNamespaceRequest> WithTransactionSetting(const TSharedPtr<Model::FTransactionSetting> TransactionSetting);
        TSharedPtr<FCreateNamespaceRequest> WithPriority(const TOptional<FString> Priority);
        TSharedPtr<FCreateNamespaceRequest> WithShareFree(const TOptional<bool> ShareFree);
        TSharedPtr<FCreateNamespaceRequest> WithCurrency(const TOptional<FString> Currency);
        TSharedPtr<FCreateNamespaceRequest> WithAppleKey(const TOptional<FString> AppleKey);
        TSharedPtr<FCreateNamespaceRequest> WithGoogleKey(const TOptional<FString> GoogleKey);
        TSharedPtr<FCreateNamespaceRequest> WithEnableFakeReceipt(const TOptional<bool> EnableFakeReceipt);
        TSharedPtr<FCreateNamespaceRequest> WithCreateWalletScript(const TSharedPtr<Model::FScriptSetting> CreateWalletScript);
        TSharedPtr<FCreateNamespaceRequest> WithDepositScript(const TSharedPtr<Model::FScriptSetting> DepositScript);
        TSharedPtr<FCreateNamespaceRequest> WithWithdrawScript(const TSharedPtr<Model::FScriptSetting> WithdrawScript);
        TSharedPtr<FCreateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<Model::FTransactionSetting> GetTransactionSetting() const;
        TOptional<FString> GetPriority() const;
        TOptional<bool> GetShareFree() const;
        FString GetShareFreeString() const;
        TOptional<FString> GetCurrency() const;
        TOptional<FString> GetAppleKey() const;
        TOptional<FString> GetGoogleKey() const;
        TOptional<bool> GetEnableFakeReceipt() const;
        FString GetEnableFakeReceiptString() const;
        TSharedPtr<Model::FScriptSetting> GetCreateWalletScript() const;
        TSharedPtr<Model::FScriptSetting> GetDepositScript() const;
        TSharedPtr<Model::FScriptSetting> GetWithdrawScript() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FCreateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequestPtr;
}