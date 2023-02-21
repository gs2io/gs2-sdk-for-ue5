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

namespace Gs2::Matchmaking::Request
{
    class FUpdateCurrentRatingModelMasterFromGitHubRequest;

    class GS2MATCHMAKING_API FUpdateCurrentRatingModelMasterFromGitHubRequest final : public TSharedFromThis<FUpdateCurrentRatingModelMasterFromGitHubRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSettingValue;
        
    public:
        
        FUpdateCurrentRatingModelMasterFromGitHubRequest();
        FUpdateCurrentRatingModelMasterFromGitHubRequest(
            const FUpdateCurrentRatingModelMasterFromGitHubRequest& From
        );
        ~FUpdateCurrentRatingModelMasterFromGitHubRequest() = default;

        TSharedPtr<FUpdateCurrentRatingModelMasterFromGitHubRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateCurrentRatingModelMasterFromGitHubRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateCurrentRatingModelMasterFromGitHubRequest> WithCheckoutSetting(const TSharedPtr<Model::FGitHubCheckoutSetting> CheckoutSetting);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TSharedPtr<Model::FGitHubCheckoutSetting> GetCheckoutSetting() const;

        static TSharedPtr<FUpdateCurrentRatingModelMasterFromGitHubRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCurrentRatingModelMasterFromGitHubRequest, ESPMode::ThreadSafe> FUpdateCurrentRatingModelMasterFromGitHubRequestPtr;
}