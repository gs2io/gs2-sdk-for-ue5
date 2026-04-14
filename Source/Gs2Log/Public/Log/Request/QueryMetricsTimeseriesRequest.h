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
    class FQueryMetricsTimeseriesRequest;

    class GS2LOG_API FQueryMetricsTimeseriesRequest final : public TSharedFromThis<FQueryMetricsTimeseriesRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<int64> BeginValue;
        TOptional<int64> EndValue;
        TOptional<FString> QueryValue;
        TSharedPtr<TArray<FString>> GroupByValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAggregationConfig>>> AggregationsValue;
        TOptional<int32> IntervalValue;
        TOptional<int32> SeriesLimitValue;
        TOptional<FString> OrderKeyValue;
        TOptional<FString> OrderByValue;
        
    public:
        
        FQueryMetricsTimeseriesRequest();
        FQueryMetricsTimeseriesRequest(
            const FQueryMetricsTimeseriesRequest& From
        );
        ~FQueryMetricsTimeseriesRequest() = default;

        TSharedPtr<FQueryMetricsTimeseriesRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FQueryMetricsTimeseriesRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FQueryMetricsTimeseriesRequest> WithBegin(const TOptional<int64> Begin);
        TSharedPtr<FQueryMetricsTimeseriesRequest> WithEnd(const TOptional<int64> End);
        TSharedPtr<FQueryMetricsTimeseriesRequest> WithQuery(const TOptional<FString> Query);
        TSharedPtr<FQueryMetricsTimeseriesRequest> WithGroupBy(
            const TSharedPtr<TArray<FString>> GroupBy);
        TSharedPtr<FQueryMetricsTimeseriesRequest> WithAggregations(const TSharedPtr<TArray<TSharedPtr<Model::FAggregationConfig>>> Aggregations);
        TSharedPtr<FQueryMetricsTimeseriesRequest> WithInterval(const TOptional<int32> Interval);
        TSharedPtr<FQueryMetricsTimeseriesRequest> WithSeriesLimit(const TOptional<int32> SeriesLimit);
        TSharedPtr<FQueryMetricsTimeseriesRequest> WithOrderKey(const TOptional<FString> OrderKey);
        TSharedPtr<FQueryMetricsTimeseriesRequest> WithOrderBy(const TOptional<FString> OrderBy);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<int64> GetBegin() const;
        FString GetBeginString() const;
        TOptional<int64> GetEnd() const;
        FString GetEndString() const;
        TOptional<FString> GetQuery() const;
        TSharedPtr<TArray<FString>> GetGroupBy() const;TSharedPtr<TArray<TSharedPtr<Model::FAggregationConfig>>> GetAggregations() const;
        TOptional<int32> GetInterval() const;
        FString GetIntervalString() const;
        TOptional<int32> GetSeriesLimit() const;
        FString GetSeriesLimitString() const;
        TOptional<FString> GetOrderKey() const;
        TOptional<FString> GetOrderBy() const;

        static TSharedPtr<FQueryMetricsTimeseriesRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FQueryMetricsTimeseriesRequest> FQueryMetricsTimeseriesRequestPtr;
}