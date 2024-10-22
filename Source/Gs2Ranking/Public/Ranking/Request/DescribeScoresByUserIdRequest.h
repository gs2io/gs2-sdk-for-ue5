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
    class FDescribeScoresByUserIdRequest;

    class GS2RANKING_API FDescribeScoresByUserIdRequest final : public TSharedFromThis<FDescribeScoresByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ScorerUserIdValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FDescribeScoresByUserIdRequest();
        FDescribeScoresByUserIdRequest(
            const FDescribeScoresByUserIdRequest& From
        );
        ~FDescribeScoresByUserIdRequest() = default;

        TSharedPtr<FDescribeScoresByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeScoresByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeScoresByUserIdRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FDescribeScoresByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeScoresByUserIdRequest> WithScorerUserId(const TOptional<FString> ScorerUserId);
        TSharedPtr<FDescribeScoresByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeScoresByUserIdRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FDescribeScoresByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetScorerUserId() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FDescribeScoresByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeScoresByUserIdRequest> FDescribeScoresByUserIdRequestPtr;
}