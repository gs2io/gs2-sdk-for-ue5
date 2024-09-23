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
#include "../Model/GitHubCheckoutSetting.h"

namespace Gs2::Script::Request
{
    class FUpdateScriptFromGitHubRequest;

    class GS2SCRIPT_API FUpdateScriptFromGitHubRequest final : public TSharedFromThis<FUpdateScriptFromGitHubRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ScriptNameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSettingValue;
        
    public:
        
        FUpdateScriptFromGitHubRequest();
        FUpdateScriptFromGitHubRequest(
            const FUpdateScriptFromGitHubRequest& From
        );
        ~FUpdateScriptFromGitHubRequest() = default;

        TSharedPtr<FUpdateScriptFromGitHubRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateScriptFromGitHubRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateScriptFromGitHubRequest> WithScriptName(const TOptional<FString> ScriptName);
        TSharedPtr<FUpdateScriptFromGitHubRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateScriptFromGitHubRequest> WithCheckoutSetting(const TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetScriptName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<Model::FGitHubCheckoutSetting> GetCheckoutSetting() const;

        static TSharedPtr<FUpdateScriptFromGitHubRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateScriptFromGitHubRequest, ESPMode::ThreadSafe> FUpdateScriptFromGitHubRequestPtr;
}