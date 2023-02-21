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
    class FGetRankingRequest;

    class GS2RANKING_API FGetRankingRequest final : public TSharedFromThis<FGetRankingRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ScorerUserIdValue;
        TOptional<FString> UniqueIdValue;
        
    public:
        
        FGetRankingRequest();
        FGetRankingRequest(
            const FGetRankingRequest& From
        );
        ~FGetRankingRequest() = default;

        TSharedPtr<FGetRankingRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetRankingRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetRankingRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FGetRankingRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetRankingRequest> WithScorerUserId(const TOptional<FString> ScorerUserId);
        TSharedPtr<FGetRankingRequest> WithUniqueId(const TOptional<FString> UniqueId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetScorerUserId() const;
        TOptional<FString> GetUniqueId() const;

        static TSharedPtr<FGetRankingRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetRankingRequest, ESPMode::ThreadSafe> FGetRankingRequestPtr;
}