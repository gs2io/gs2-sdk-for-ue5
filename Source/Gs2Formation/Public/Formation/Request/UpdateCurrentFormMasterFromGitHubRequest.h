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

namespace Gs2::Formation::Request
{
    class FUpdateCurrentFormMasterFromGitHubRequest;

    class GS2FORMATION_API FUpdateCurrentFormMasterFromGitHubRequest final : public TSharedFromThis<FUpdateCurrentFormMasterFromGitHubRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSettingValue;
        
    public:
        
        FUpdateCurrentFormMasterFromGitHubRequest();
        FUpdateCurrentFormMasterFromGitHubRequest(
            const FUpdateCurrentFormMasterFromGitHubRequest& From
        );
        ~FUpdateCurrentFormMasterFromGitHubRequest() = default;

        TSharedPtr<FUpdateCurrentFormMasterFromGitHubRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateCurrentFormMasterFromGitHubRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateCurrentFormMasterFromGitHubRequest> WithCheckoutSetting(const TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TSharedPtr<Model::FGitHubCheckoutSetting> GetCheckoutSetting() const;

        static TSharedPtr<FUpdateCurrentFormMasterFromGitHubRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCurrentFormMasterFromGitHubRequest, ESPMode::ThreadSafe> FUpdateCurrentFormMasterFromGitHubRequestPtr;
}