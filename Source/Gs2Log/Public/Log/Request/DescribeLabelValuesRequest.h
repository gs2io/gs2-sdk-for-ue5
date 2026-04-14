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

namespace Gs2::Log::Request
{
    class FDescribeLabelValuesRequest;

    class GS2LOG_API FDescribeLabelValuesRequest final : public TSharedFromThis<FDescribeLabelValuesRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MetricNameValue;
        TOptional<FString> LabelNamePrefixValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeLabelValuesRequest();
        FDescribeLabelValuesRequest(
            const FDescribeLabelValuesRequest& From
        );
        ~FDescribeLabelValuesRequest() = default;

        TSharedPtr<FDescribeLabelValuesRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeLabelValuesRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeLabelValuesRequest> WithMetricName(const TOptional<FString> MetricName);
        TSharedPtr<FDescribeLabelValuesRequest> WithLabelNamePrefix(const TOptional<FString> LabelNamePrefix);
        TSharedPtr<FDescribeLabelValuesRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeLabelValuesRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMetricName() const;
        TOptional<FString> GetLabelNamePrefix() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeLabelValuesRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeLabelValuesRequest> FDescribeLabelValuesRequestPtr;
}