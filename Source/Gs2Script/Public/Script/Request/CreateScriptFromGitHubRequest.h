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
#include "../Model/GitHubCheckoutSetting.h"

namespace Gs2::Script::Request
{
    class FCreateScriptFromGitHubRequest;

    class GS2SCRIPT_API FCreateScriptFromGitHubRequest final : public TSharedFromThis<FCreateScriptFromGitHubRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSettingValue;
        TOptional<bool> DisableStringNumberToNumberValue;
        
    public:
        
        FCreateScriptFromGitHubRequest();
        FCreateScriptFromGitHubRequest(
            const FCreateScriptFromGitHubRequest& From
        );
        ~FCreateScriptFromGitHubRequest() = default;

        TSharedPtr<FCreateScriptFromGitHubRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateScriptFromGitHubRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateScriptFromGitHubRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateScriptFromGitHubRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateScriptFromGitHubRequest> WithCheckoutSetting(const TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSetting);
        TSharedPtr<FCreateScriptFromGitHubRequest> WithDisableStringNumberToNumber(const TOptional<bool> DisableStringNumberToNumber);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<Model::FGitHubCheckoutSetting> GetCheckoutSetting() const;
        TOptional<bool> GetDisableStringNumberToNumber() const;
        FString GetDisableStringNumberToNumberString() const;

        static TSharedPtr<FCreateScriptFromGitHubRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateScriptFromGitHubRequest> FCreateScriptFromGitHubRequestPtr;
}