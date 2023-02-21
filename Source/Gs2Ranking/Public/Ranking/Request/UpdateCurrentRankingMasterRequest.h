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

namespace Gs2::Ranking::Request
{
    class FUpdateCurrentRankingMasterRequest;

    class GS2RANKING_API FUpdateCurrentRankingMasterRequest final : public TSharedFromThis<FUpdateCurrentRankingMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> SettingsValue;
        
    public:
        
        FUpdateCurrentRankingMasterRequest();
        FUpdateCurrentRankingMasterRequest(
            const FUpdateCurrentRankingMasterRequest& From
        );
        ~FUpdateCurrentRankingMasterRequest() = default;

        TSharedPtr<FUpdateCurrentRankingMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateCurrentRankingMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateCurrentRankingMasterRequest> WithSettings(const TOptional<FString> Settings);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetSettings() const;

        static TSharedPtr<FUpdateCurrentRankingMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCurrentRankingMasterRequest, ESPMode::ThreadSafe> FUpdateCurrentRankingMasterRequestPtr;
}