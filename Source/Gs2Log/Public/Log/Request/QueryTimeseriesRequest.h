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
#include "../Model/AggregationConfig.h"

namespace Gs2::Log::Request
{
    class FQueryTimeseriesRequest;

    class GS2LOG_API FQueryTimeseriesRequest final : public TSharedFromThis<FQueryTimeseriesRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<int64> BeginValue;
        TOptional<int64> EndValue;
        TOptional<FString> QueryValue;
        TSharedPtr<TArray<FString>> GroupByValue;
        TSharedPtr<Model::FAggregationConfig> AggregationValue;
        TOptional<int32> IntervalValue;
        TOptional<int32> SeriesLimitValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FQueryTimeseriesRequest();
        FQueryTimeseriesRequest(
            const FQueryTimeseriesRequest& From
        );
        ~FQueryTimeseriesRequest() = default;

        TSharedPtr<FQueryTimeseriesRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FQueryTimeseriesRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FQueryTimeseriesRequest> WithBegin(const TOptional<int64> Begin);
        TSharedPtr<FQueryTimeseriesRequest> WithEnd(const TOptional<int64> End);
        TSharedPtr<FQueryTimeseriesRequest> WithQuery(const TOptional<FString> Query);
        TSharedPtr<FQueryTimeseriesRequest> WithGroupBy(
            const TSharedPtr<TArray<FString>> GroupBy);
        TSharedPtr<FQueryTimeseriesRequest> WithAggregation(const TSharedPtr<Model::FAggregationConfig> Aggregation);
        TSharedPtr<FQueryTimeseriesRequest> WithInterval(const TOptional<int32> Interval);
        TSharedPtr<FQueryTimeseriesRequest> WithSeriesLimit(const TOptional<int32> SeriesLimit);
        TSharedPtr<FQueryTimeseriesRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FQueryTimeseriesRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<int64> GetBegin() const;
        FString GetBeginString() const;
        TOptional<int64> GetEnd() const;
        FString GetEndString() const;
        TOptional<FString> GetQuery() const;
        TSharedPtr<TArray<FString>> GetGroupBy() const;
        TSharedPtr<Model::FAggregationConfig> GetAggregation() const;
        TOptional<int32> GetInterval() const;
        FString GetIntervalString() const;
        TOptional<int32> GetSeriesLimit() const;
        FString GetSeriesLimitString() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FQueryTimeseriesRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FQueryTimeseriesRequest> FQueryTimeseriesRequestPtr;
}