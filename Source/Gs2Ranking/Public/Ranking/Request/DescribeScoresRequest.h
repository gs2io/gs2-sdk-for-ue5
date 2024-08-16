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

namespace Gs2::Ranking::Request
{
    class FDescribeScoresRequest;

    class GS2RANKING_API FDescribeScoresRequest final : public TSharedFromThis<FDescribeScoresRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> ScorerUserIdValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeScoresRequest();
        FDescribeScoresRequest(
            const FDescribeScoresRequest& From
        );
        ~FDescribeScoresRequest() = default;

        TSharedPtr<FDescribeScoresRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeScoresRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeScoresRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FDescribeScoresRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDescribeScoresRequest> WithScorerUserId(const TOptional<FString> ScorerUserId);
        TSharedPtr<FDescribeScoresRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeScoresRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetScorerUserId() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeScoresRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeScoresRequest> FDescribeScoresRequestPtr;
}