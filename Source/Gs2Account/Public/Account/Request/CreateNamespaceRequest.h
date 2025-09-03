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

namespace Gs2::Account::Request
{
    class FCreateNamespaceRequest;

    class GS2ACCOUNT_API FCreateNamespaceRequest final : public TSharedFromThis<FCreateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<Model::FTransactionSetting> TransactionSettingValue;
        TOptional<bool> ChangePasswordIfTakeOverValue;
        TOptional<bool> DifferentUserIdForLoginAndDataRetentionValue;
        TSharedPtr<Model::FScriptSetting> CreateAccountScriptValue;
        TSharedPtr<Model::FScriptSetting> AuthenticationScriptValue;
        TSharedPtr<Model::FScriptSetting> CreateTakeOverScriptValue;
        TSharedPtr<Model::FScriptSetting> DoTakeOverScriptValue;
        TSharedPtr<Model::FScriptSetting> BanScriptValue;
        TSharedPtr<Model::FScriptSetting> UnBanScriptValue;
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
        TSharedPtr<FCreateNamespaceRequest> WithChangePasswordIfTakeOver(const TOptional<bool> ChangePasswordIfTakeOver);
        TSharedPtr<FCreateNamespaceRequest> WithDifferentUserIdForLoginAndDataRetention(const TOptional<bool> DifferentUserIdForLoginAndDataRetention);
        TSharedPtr<FCreateNamespaceRequest> WithCreateAccountScript(const TSharedPtr<Model::FScriptSetting> CreateAccountScript);
        TSharedPtr<FCreateNamespaceRequest> WithAuthenticationScript(const TSharedPtr<Model::FScriptSetting> AuthenticationScript);
        TSharedPtr<FCreateNamespaceRequest> WithCreateTakeOverScript(const TSharedPtr<Model::FScriptSetting> CreateTakeOverScript);
        TSharedPtr<FCreateNamespaceRequest> WithDoTakeOverScript(const TSharedPtr<Model::FScriptSetting> DoTakeOverScript);
        TSharedPtr<FCreateNamespaceRequest> WithBanScript(const TSharedPtr<Model::FScriptSetting> BanScript);
        TSharedPtr<FCreateNamespaceRequest> WithUnBanScript(const TSharedPtr<Model::FScriptSetting> UnBanScript);
        TSharedPtr<FCreateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<Model::FTransactionSetting> GetTransactionSetting() const;
        TOptional<bool> GetChangePasswordIfTakeOver() const;
        FString GetChangePasswordIfTakeOverString() const;
        TOptional<bool> GetDifferentUserIdForLoginAndDataRetention() const;
        FString GetDifferentUserIdForLoginAndDataRetentionString() const;
        TSharedPtr<Model::FScriptSetting> GetCreateAccountScript() const;
        TSharedPtr<Model::FScriptSetting> GetAuthenticationScript() const;
        TSharedPtr<Model::FScriptSetting> GetCreateTakeOverScript() const;
        TSharedPtr<Model::FScriptSetting> GetDoTakeOverScript() const;
        TSharedPtr<Model::FScriptSetting> GetBanScript() const;
        TSharedPtr<Model::FScriptSetting> GetUnBanScript() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FCreateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequestPtr;
}