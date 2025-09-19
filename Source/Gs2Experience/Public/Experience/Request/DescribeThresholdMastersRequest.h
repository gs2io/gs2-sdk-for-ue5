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

namespace Gs2::Experience::Request
{
    class FDescribeThresholdMastersRequest;

    class GS2EXPERIENCE_API FDescribeThresholdMastersRequest final : public TSharedFromThis<FDescribeThresholdMastersRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NamePrefixValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeThresholdMastersRequest();
        FDescribeThresholdMastersRequest(
            const FDescribeThresholdMastersRequest& From
        );
        ~FDescribeThresholdMastersRequest() = default;

        TSharedPtr<FDescribeThresholdMastersRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeThresholdMastersRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeThresholdMastersRequest> WithNamePrefix(const TOptional<FString> NamePrefix);
        TSharedPtr<FDescribeThresholdMastersRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeThresholdMastersRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetNamePrefix() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeThresholdMastersRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeThresholdMastersRequest> FDescribeThresholdMastersRequestPtr;
}