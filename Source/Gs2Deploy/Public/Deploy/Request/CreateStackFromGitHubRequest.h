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

namespace Gs2::Deploy::Request
{
    class FCreateStackFromGitHubRequest;

    class GS2DEPLOY_API FCreateStackFromGitHubRequest final : public TSharedFromThis<FCreateStackFromGitHubRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSettingValue;
        
    public:
        
        FCreateStackFromGitHubRequest();
        FCreateStackFromGitHubRequest(
            const FCreateStackFromGitHubRequest& From
        );
        ~FCreateStackFromGitHubRequest() = default;

        TSharedPtr<FCreateStackFromGitHubRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateStackFromGitHubRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateStackFromGitHubRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateStackFromGitHubRequest> WithCheckoutSetting(const TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<Model::FGitHubCheckoutSetting> GetCheckoutSetting() const;

        static TSharedPtr<FCreateStackFromGitHubRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateStackFromGitHubRequest> FCreateStackFromGitHubRequestPtr;
}