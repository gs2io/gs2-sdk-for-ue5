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

namespace Gs2::Ranking2::Request
{
    class FGetGlobalRankingModelMasterRequest;

    class GS2RANKING2_API FGetGlobalRankingModelMasterRequest final : public TSharedFromThis<FGetGlobalRankingModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        
    public:
        
        FGetGlobalRankingModelMasterRequest();
        FGetGlobalRankingModelMasterRequest(
            const FGetGlobalRankingModelMasterRequest& From
        );
        ~FGetGlobalRankingModelMasterRequest() = default;

        TSharedPtr<FGetGlobalRankingModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetGlobalRankingModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetGlobalRankingModelMasterRequest> WithRankingName(const TOptional<FString> RankingName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;

        static TSharedPtr<FGetGlobalRankingModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetGlobalRankingModelMasterRequest, ESPMode::ThreadSafe> FGetGlobalRankingModelMasterRequestPtr;
}