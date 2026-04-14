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

#include "Log/Request/QueryMetricsTimeseriesRequest.h"

namespace Gs2::Log::Request
{
    FQueryMetricsTimeseriesRequest::FQueryMetricsTimeseriesRequest():
        NamespaceNameValue(TOptional<FString>()),
        BeginValue(TOptional<int64>()),
        EndValue(TOptional<int64>()),
        QueryValue(TOptional<FString>()),
        GroupByValue(nullptr),
        AggregationsValue(nullptr),
        IntervalValue(TOptional<int32>()),
        SeriesLimitValue(TOptional<int32>()),
        OrderKeyValue(TOptional<FString>()),
        OrderByValue(TOptional<FString>())
    {
    }

    FQueryMetricsTimeseriesRequest::FQueryMetricsTimeseriesRequest(
        const FQueryMetricsTimeseriesRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        BeginValue(From.BeginValue),
        EndValue(From.EndValue),
        QueryValue(From.QueryValue),
        GroupByValue(From.GroupByValue),
        AggregationsValue(From.AggregationsValue),
        IntervalValue(From.IntervalValue),
        SeriesLimitValue(From.SeriesLimitValue),
        OrderKeyValue(From.OrderKeyValue),
        OrderByValue(From.OrderByValue)
    {
    }

    TSharedPtr<FQueryMetricsTimeseriesRequest> FQueryMetricsTimeseriesRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FQueryMetricsTimeseriesRequest> FQueryMetricsTimeseriesRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FQueryMetricsTimeseriesRequest> FQueryMetricsTimeseriesRequest::WithBegin(
        const TOptional<int64> Begin
    )
    {
        this->BeginValue = Begin;
        return SharedThis(this);
    }

    TSharedPtr<FQueryMetricsTimeseriesRequest> FQueryMetricsTimeseriesRequest::WithEnd(
        const TOptional<int64> End
    )
    {
        this->EndValue = End;
        return SharedThis(this);
    }

    TSharedPtr<FQueryMetricsTimeseriesRequest> FQueryMetricsTimeseriesRequest::WithQuery(
        const TOptional<FString> Query
    )
    {
        this->QueryValue = Query;
        return SharedThis(this);
    }

    TSharedPtr<FQueryMetricsTimeseriesRequest> FQueryMetricsTimeseriesRequest::WithGroupBy(
        const TSharedPtr<TArray<FString>> GroupBy
    )
    {
        this->GroupByValue = GroupBy;
        return SharedThis(this);
    }

    TSharedPtr<FQueryMetricsTimeseriesRequest> FQueryMetricsTimeseriesRequest::WithAggregations(
        const TSharedPtr<TArray<TSharedPtr<Model::FAggregationConfig>>> Aggregations
    )
    {
        this->AggregationsValue = Aggregations;
        return SharedThis(this);
    }

    TSharedPtr<FQueryMetricsTimeseriesRequest> FQueryMetricsTimeseriesRequest::WithInterval(
        const TOptional<int32> Interval
    )
    {
        this->IntervalValue = Interval;
        return SharedThis(this);
    }

    TSharedPtr<FQueryMetricsTimeseriesRequest> FQueryMetricsTimeseriesRequest::WithSeriesLimit(
        const TOptional<int32> SeriesLimit
    )
    {
        this->SeriesLimitValue = SeriesLimit;
        return SharedThis(this);
    }

    TSharedPtr<FQueryMetricsTimeseriesRequest> FQueryMetricsTimeseriesRequest::WithOrderKey(
        const TOptional<FString> OrderKey
    )
    {
        this->OrderKeyValue = OrderKey;
        return SharedThis(this);
    }

    TSharedPtr<FQueryMetricsTimeseriesRequest> FQueryMetricsTimeseriesRequest::WithOrderBy(
        const TOptional<FString> OrderBy
    )
    {
        this->OrderByValue = OrderBy;
        return SharedThis(this);
    }

    TOptional<FString> FQueryMetricsTimeseriesRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FQueryMetricsTimeseriesRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<int64> FQueryMetricsTimeseriesRequest::GetBegin() const
    {
        return BeginValue;
    }

    FString FQueryMetricsTimeseriesRequest::GetBeginString() const
    {
        if (!BeginValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), BeginValue.GetValue());
    }

    TOptional<int64> FQueryMetricsTimeseriesRequest::GetEnd() const
    {
        return EndValue;
    }

    FString FQueryMetricsTimeseriesRequest::GetEndString() const
    {
        if (!EndValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), EndValue.GetValue());
    }

    TOptional<FString> FQueryMetricsTimeseriesRequest::GetQuery() const
    {
        return QueryValue;
    }

    TSharedPtr<TArray<FString>> FQueryMetricsTimeseriesRequest::GetGroupBy() const
    {
        if (!GroupByValue.IsValid())
        {
            return nullptr;
        }
        return GroupByValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAggregationConfig>>> FQueryMetricsTimeseriesRequest::GetAggregations() const
    {
        if (!AggregationsValue.IsValid())
        {
            return nullptr;
        }
        return AggregationsValue;
    }

    TOptional<int32> FQueryMetricsTimeseriesRequest::GetInterval() const
    {
        return IntervalValue;
    }

    FString FQueryMetricsTimeseriesRequest::GetIntervalString() const
    {
        if (!IntervalValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), IntervalValue.GetValue());
    }

    TOptional<int32> FQueryMetricsTimeseriesRequest::GetSeriesLimit() const
    {
        return SeriesLimitValue;
    }

    FString FQueryMetricsTimeseriesRequest::GetSeriesLimitString() const
    {
        if (!SeriesLimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), SeriesLimitValue.GetValue());
    }

    TOptional<FString> FQueryMetricsTimeseriesRequest::GetOrderKey() const
    {
        return OrderKeyValue;
    }

    TOptional<FString> FQueryMetricsTimeseriesRequest::GetOrderBy() const
    {
        return OrderByValue;
    }

    TSharedPtr<FQueryMetricsTimeseriesRequest> FQueryMetricsTimeseriesRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FQueryMetricsTimeseriesRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithBegin(Data->HasField(ANSI_TO_TCHAR("begin")) ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("begin"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithEnd(Data->HasField(ANSI_TO_TCHAR("end")) ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("end"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithQuery(Data->HasField(ANSI_TO_TCHAR("query")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("query"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithGroupBy(Data->HasField(ANSI_TO_TCHAR("groupBy")) ? [Data]() -> TSharedPtr<TArray<FString>>
              {
                  auto v = MakeShared<TArray<FString>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("groupBy")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("groupBy")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("groupBy")))
                      {
                          v->Add(JsonObjectValue->AsString());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<FString>>())
          ->WithAggregations(Data->HasField(ANSI_TO_TCHAR("aggregations")) ? [Data]() -> TSharedPtr<TArray<Model::FAggregationConfigPtr>>
              {
                  auto v = MakeShared<TArray<Model::FAggregationConfigPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("aggregations")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("aggregations")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("aggregations")))
                      {
                          v->Add(Model::FAggregationConfig::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FAggregationConfigPtr>>())
            ->WithInterval(Data->HasField(ANSI_TO_TCHAR("interval")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("interval"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithSeriesLimit(Data->HasField(ANSI_TO_TCHAR("seriesLimit")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("seriesLimit"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithOrderKey(Data->HasField(ANSI_TO_TCHAR("orderKey")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("orderKey"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithOrderBy(Data->HasField(ANSI_TO_TCHAR("orderBy")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("orderBy"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FQueryMetricsTimeseriesRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (BeginValue.IsSet())
        {
            JsonRootObject->SetStringField("begin", FString::Printf(TEXT("%lld"), BeginValue.GetValue()));
        }
        if (EndValue.IsSet())
        {
            JsonRootObject->SetStringField("end", FString::Printf(TEXT("%lld"), EndValue.GetValue()));
        }
        if (QueryValue.IsSet())
        {
            JsonRootObject->SetStringField("query", QueryValue.GetValue());
        }
        if (GroupByValue != nullptr && GroupByValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *GroupByValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("groupBy", v);
        }
        if (AggregationsValue != nullptr && AggregationsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AggregationsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("aggregations", v);
        }
        if (IntervalValue.IsSet())
        {
            JsonRootObject->SetNumberField("interval", IntervalValue.GetValue());
        }
        if (SeriesLimitValue.IsSet())
        {
            JsonRootObject->SetNumberField("seriesLimit", SeriesLimitValue.GetValue());
        }
        if (OrderKeyValue.IsSet())
        {
            JsonRootObject->SetStringField("orderKey", OrderKeyValue.GetValue());
        }
        if (OrderByValue.IsSet())
        {
            JsonRootObject->SetStringField("orderBy", OrderByValue.GetValue());
        }
        return JsonRootObject;
    }
}