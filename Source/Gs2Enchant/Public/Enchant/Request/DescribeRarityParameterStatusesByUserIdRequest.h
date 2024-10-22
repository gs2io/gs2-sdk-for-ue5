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

namespace Gs2::Enchant::Request
{
    class FDescribeRarityParameterStatusesByUserIdRequest;

    class GS2ENCHANT_API FDescribeRarityParameterStatusesByUserIdRequest final : public TSharedFromThis<FDescribeRarityParameterStatusesByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> ParameterNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FDescribeRarityParameterStatusesByUserIdRequest();
        FDescribeRarityParameterStatusesByUserIdRequest(
            const FDescribeRarityParameterStatusesByUserIdRequest& From
        );
        ~FDescribeRarityParameterStatusesByUserIdRequest() = default;

        TSharedPtr<FDescribeRarityParameterStatusesByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeRarityParameterStatusesByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeRarityParameterStatusesByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeRarityParameterStatusesByUserIdRequest> WithParameterName(const TOptional<FString> ParameterName);
        TSharedPtr<FDescribeRarityParameterStatusesByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeRarityParameterStatusesByUserIdRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FDescribeRarityParameterStatusesByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetParameterName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FDescribeRarityParameterStatusesByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeRarityParameterStatusesByUserIdRequest> FDescribeRarityParameterStatusesByUserIdRequestPtr;
}