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

namespace Gs2::MegaField::Request
{
    class FUpdateCurrentFieldMasterFromGitHubRequest;

    class GS2MEGAFIELD_API FUpdateCurrentFieldMasterFromGitHubRequest final : public TSharedFromThis<FUpdateCurrentFieldMasterFromGitHubRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSettingValue;
        
    public:
        
        FUpdateCurrentFieldMasterFromGitHubRequest();
        FUpdateCurrentFieldMasterFromGitHubRequest(
            const FUpdateCurrentFieldMasterFromGitHubRequest& From
        );
        ~FUpdateCurrentFieldMasterFromGitHubRequest() = default;

        TSharedPtr<FUpdateCurrentFieldMasterFromGitHubRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateCurrentFieldMasterFromGitHubRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateCurrentFieldMasterFromGitHubRequest> WithCheckoutSetting(const TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TSharedPtr<Model::FGitHubCheckoutSetting> GetCheckoutSetting() const;

        static TSharedPtr<FUpdateCurrentFieldMasterFromGitHubRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCurrentFieldMasterFromGitHubRequest> FUpdateCurrentFieldMasterFromGitHubRequestPtr;
}