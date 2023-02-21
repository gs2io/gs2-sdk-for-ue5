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
#include "../Model/ScriptSetting.h"
#include "../Model/LogSetting.h"

namespace Gs2::Account::Request
{
    class FUpdateNamespaceRequest;

    class GS2ACCOUNT_API FUpdateNamespaceRequest final : public TSharedFromThis<FUpdateNamespaceRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<bool> ChangePasswordIfTakeOverValue;
        TOptional<bool> DifferentUserIdForLoginAndDataRetentionValue;
        TSharedPtr<Model::FScriptSetting> CreateAccountScriptValue;
        TSharedPtr<Model::FScriptSetting> AuthenticationScriptValue;
        TSharedPtr<Model::FScriptSetting> CreateTakeOverScriptValue;
        TSharedPtr<Model::FScriptSetting> DoTakeOverScriptValue;
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
        TSharedPtr<FUpdateNamespaceRequest> WithChangePasswordIfTakeOver(const TOptional<bool> ChangePasswordIfTakeOver);
        TSharedPtr<FUpdateNamespaceRequest> WithDifferentUserIdForLoginAndDataRetention(const TOptional<bool> DifferentUserIdForLoginAndDataRetention);
        TSharedPtr<FUpdateNamespaceRequest> WithCreateAccountScript(const TSharedPtr<Model::FScriptSetting> CreateAccountScript);
        TSharedPtr<FUpdateNamespaceRequest> WithAuthenticationScript(const TSharedPtr<Model::FScriptSetting> AuthenticationScript);
        TSharedPtr<FUpdateNamespaceRequest> WithCreateTakeOverScript(const TSharedPtr<Model::FScriptSetting> CreateTakeOverScript);
        TSharedPtr<FUpdateNamespaceRequest> WithDoTakeOverScript(const TSharedPtr<Model::FScriptSetting> DoTakeOverScript);
        TSharedPtr<FUpdateNamespaceRequest> WithLogSetting(const TSharedPtr<Model::FLogSetting> LogSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDescription() const;
        TOptional<bool> GetChangePasswordIfTakeOver() const;
        FString GetChangePasswordIfTakeOverString() const;
        TOptional<bool> GetDifferentUserIdForLoginAndDataRetention() const;
        FString GetDifferentUserIdForLoginAndDataRetentionString() const;
        TSharedPtr<Model::FScriptSetting> GetCreateAccountScript() const;
        TSharedPtr<Model::FScriptSetting> GetAuthenticationScript() const;
        TSharedPtr<Model::FScriptSetting> GetCreateTakeOverScript() const;
        TSharedPtr<Model::FScriptSetting> GetDoTakeOverScript() const;
        TSharedPtr<Model::FLogSetting> GetLogSetting() const;

        static TSharedPtr<FUpdateNamespaceRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateNamespaceRequest, ESPMode::ThreadSafe> FUpdateNamespaceRequestPtr;
}