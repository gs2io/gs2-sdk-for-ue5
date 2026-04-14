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

#include "Log/Request/QueryTimeseriesRequest.h"

namespace Gs2::Log::Request
{
    FQueryTimeseriesRequest::FQueryTimeseriesRequest():
        NamespaceNameValue(TOptional<FString>()),
        BeginValue(TOptional<int64>()),
        EndValue(TOptional<int64>()),
        QueryValue(TOptional<FString>()),
        GroupByValue(nullptr),
        AggregationValue(nullptr),
        IntervalValue(TOptional<int32>()),
        SeriesLimitValue(TOptional<int32>()),
        PageTokenValue(TOptional<FString>()),
        LimitValue(TOptional<int32>())
    {
    }

    FQueryTimeseriesRequest::FQueryTimeseriesRequest(
        const FQueryTimeseriesRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        BeginValue(From.BeginValue),
        EndValue(From.EndValue),
        QueryValue(From.QueryValue),
        GroupByValue(From.GroupByValue),
        AggregationValue(From.AggregationValue),
        IntervalValue(From.IntervalValue),
        SeriesLimitValue(From.SeriesLimitValue),
        PageTokenValue(From.PageTokenValue),
        LimitValue(From.LimitValue)
    {
    }

    TSharedPtr<FQueryTimeseriesRequest> FQueryTimeseriesRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FQueryTimeseriesRequest> FQueryTimeseriesRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FQueryTimeseriesRequest> FQueryTimeseriesRequest::WithBegin(
        const TOptional<int64> Begin
    )
    {
        this->BeginValue = Begin;
        return SharedThis(this);
    }

    TSharedPtr<FQueryTimeseriesRequest> FQueryTimeseriesRequest::WithEnd(
        const TOptional<int64> End
    )
    {
        this->EndValue = End;
        return SharedThis(this);
    }

    TSharedPtr<FQueryTimeseriesRequest> FQueryTimeseriesRequest::WithQuery(
        const TOptional<FString> Query
    )
    {
        this->QueryValue = Query;
        return SharedThis(this);
    }

    TSharedPtr<FQueryTimeseriesRequest> FQueryTimeseriesRequest::WithGroupBy(
        const TSharedPtr<TArray<FString>> GroupBy
    )
    {
        this->GroupByValue = GroupBy;
        return SharedThis(this);
    }

    TSharedPtr<FQueryTimeseriesRequest> FQueryTimeseriesRequest::WithAggregation(
        const TSharedPtr<Model::FAggregationConfig> Aggregation
    )
    {
        this->AggregationValue = Aggregation;
        return SharedThis(this);
    }

    TSharedPtr<FQueryTimeseriesRequest> FQueryTimeseriesRequest::WithInterval(
        const TOptional<int32> Interval
    )
    {
        this->IntervalValue = Interval;
        return SharedThis(this);
    }

    TSharedPtr<FQueryTimeseriesRequest> FQueryTimeseriesRequest::WithSeriesLimit(
        const TOptional<int32> SeriesLimit
    )
    {
        this->SeriesLimitValue = SeriesLimit;
        return SharedThis(this);
    }

    TSharedPtr<FQueryTimeseriesRequest> FQueryTimeseriesRequest::WithPageToken(
        const TOptional<FString> PageToken
    )
    {
        this->PageTokenValue = PageToken;
        return SharedThis(this);
    }

    TSharedPtr<FQueryTimeseriesRequest> FQueryTimeseriesRequest::WithLimit(
        const TOptional<int32> Limit
    )
    {
        this->LimitValue = Limit;
        return SharedThis(this);
    }

    TOptional<FString> FQueryTimeseriesRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FQueryTimeseriesRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<int64> FQueryTimeseriesRequest::GetBegin() const
    {
        return BeginValue;
    }

    FString FQueryTimeseriesRequest::GetBeginString() const
    {
        if (!BeginValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), BeginValue.GetValue());
    }

    TOptional<int64> FQueryTimeseriesRequest::GetEnd() const
    {
        return EndValue;
    }

    FString FQueryTimeseriesRequest::GetEndString() const
    {
        if (!EndValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), EndValue.GetValue());
    }

    TOptional<FString> FQueryTimeseriesRequest::GetQuery() const
    {
        return QueryValue;
    }

    TSharedPtr<TArray<FString>> FQueryTimeseriesRequest::GetGroupBy() const
    {
        if (!GroupByValue.IsValid())
        {
            return nullptr;
        }
        return GroupByValue;
    }

    TSharedPtr<Model::FAggregationConfig> FQueryTimeseriesRequest::GetAggregation() const
    {
        if (!AggregationValue.IsValid())
        {
            return nullptr;
        }
        return AggregationValue;
    }

    TOptional<int32> FQueryTimeseriesRequest::GetInterval() const
    {
        return IntervalValue;
    }

    FString FQueryTimeseriesRequest::GetIntervalString() const
    {
        if (!IntervalValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), IntervalValue.GetValue());
    }

    TOptional<int32> FQueryTimeseriesRequest::GetSeriesLimit() const
    {
        return SeriesLimitValue;
    }

    FString FQueryTimeseriesRequest::GetSeriesLimitString() const
    {
        if (!SeriesLimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), SeriesLimitValue.GetValue());
    }

    TOptional<FString> FQueryTimeseriesRequest::GetPageToken() const
    {
        return PageTokenValue;
    }

    TOptional<int32> FQueryTimeseriesRequest::GetLimit() const
    {
        return LimitValue;
    }

    FString FQueryTimeseriesRequest::GetLimitString() const
    {
        if (!LimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LimitValue.GetValue());
    }

    TSharedPtr<FQueryTimeseriesRequest> FQueryTimeseriesRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FQueryTimeseriesRequest>()
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
          ->WithAggregation(Data->HasField(ANSI_TO_TCHAR("aggregation")) ? [Data]() -> Model::FAggregationConfigPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("aggregation")))
                  {
                      return nullptr;
                  }
                  return Model::FAggregationConfig::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("aggregation")));
              }() : nullptr)
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
            ->WithPageToken(Data->HasField(ANSI_TO_TCHAR("pageToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("pageToken"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithLimit(Data->HasField(ANSI_TO_TCHAR("limit")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("limit"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FQueryTimeseriesRequest::ToJson() const
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
        if (AggregationValue != nullptr && AggregationValue.IsValid())
        {
            JsonRootObject->SetObjectField("aggregation", AggregationValue->ToJson());
        }
        if (IntervalValue.IsSet())
        {
            JsonRootObject->SetNumberField("interval", IntervalValue.GetValue());
        }
        if (SeriesLimitValue.IsSet())
        {
            JsonRootObject->SetNumberField("seriesLimit", SeriesLimitValue.GetValue());
        }
        if (PageTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("pageToken", PageTokenValue.GetValue());
        }
        if (LimitValue.IsSet())
        {
            JsonRootObject->SetNumberField("limit", LimitValue.GetValue());
        }
        return JsonRootObject;
    }
}