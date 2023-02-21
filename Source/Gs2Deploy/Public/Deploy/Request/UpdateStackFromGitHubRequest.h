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

namespace Gs2::Deploy::Request
{
    class FUpdateStackFromGitHubRequest;

    class GS2DEPLOY_API FUpdateStackFromGitHubRequest final : public TSharedFromThis<FUpdateStackFromGitHubRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StackNameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSettingValue;
        
    public:
        
        FUpdateStackFromGitHubRequest();
        FUpdateStackFromGitHubRequest(
            const FUpdateStackFromGitHubRequest& From
        );
        ~FUpdateStackFromGitHubRequest() = default;

        TSharedPtr<FUpdateStackFromGitHubRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateStackFromGitHubRequest> WithStackName(const TOptional<FString> StackName);
        TSharedPtr<FUpdateStackFromGitHubRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateStackFromGitHubRequest> WithCheckoutSetting(const TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStackName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<Model::FGitHubCheckoutSetting> GetCheckoutSetting() const;

        static TSharedPtr<FUpdateStackFromGitHubRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateStackFromGitHubRequest, ESPMode::ThreadSafe> FUpdateStackFromGitHubRequestPtr;
}