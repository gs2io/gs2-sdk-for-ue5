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

#include "Log/Request/DescribeLabelValuesRequest.h"

namespace Gs2::Log::Request
{
    FDescribeLabelValuesRequest::FDescribeLabelValuesRequest():
        NamespaceNameValue(TOptional<FString>()),
        MetricNameValue(TOptional<FString>()),
        LabelNamePrefixValue(TOptional<FString>()),
        PageTokenValue(TOptional<FString>()),
        LimitValue(TOptional<int32>())
    {
    }

    FDescribeLabelValuesRequest::FDescribeLabelValuesRequest(
        const FDescribeLabelValuesRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        MetricNameValue(From.MetricNameValue),
        LabelNamePrefixValue(From.LabelNamePrefixValue),
        PageTokenValue(From.PageTokenValue),
        LimitValue(From.LimitValue)
    {
    }

    TSharedPtr<FDescribeLabelValuesRequest> FDescribeLabelValuesRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeLabelValuesRequest> FDescribeLabelValuesRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeLabelValuesRequest> FDescribeLabelValuesRequest::WithMetricName(
        const TOptional<FString> MetricName
    )
    {
        this->MetricNameValue = MetricName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeLabelValuesRequest> FDescribeLabelValuesRequest::WithLabelNamePrefix(
        const TOptional<FString> LabelNamePrefix
    )
    {
        this->LabelNamePrefixValue = LabelNamePrefix;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeLabelValuesRequest> FDescribeLabelValuesRequest::WithPageToken(
        const TOptional<FString> PageToken
    )
    {
        this->PageTokenValue = PageToken;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeLabelValuesRequest> FDescribeLabelValuesRequest::WithLimit(
        const TOptional<int32> Limit
    )
    {
        this->LimitValue = Limit;
        return SharedThis(this);
    }

    TOptional<FString> FDescribeLabelValuesRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDescribeLabelValuesRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDescribeLabelValuesRequest::GetMetricName() const
    {
        return MetricNameValue;
    }

    TOptional<FString> FDescribeLabelValuesRequest::GetLabelNamePrefix() const
    {
        return LabelNamePrefixValue;
    }

    TOptional<FString> FDescribeLabelValuesRequest::GetPageToken() const
    {
        return PageTokenValue;
    }

    TOptional<int32> FDescribeLabelValuesRequest::GetLimit() const
    {
        return LimitValue;
    }

    FString FDescribeLabelValuesRequest::GetLimitString() const
    {
        if (!LimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LimitValue.GetValue());
    }

    TSharedPtr<FDescribeLabelValuesRequest> FDescribeLabelValuesRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeLabelValuesRequest>()
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
            ->WithMetricName(Data->HasField(ANSI_TO_TCHAR("metricName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metricName"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithLabelNamePrefix(Data->HasField(ANSI_TO_TCHAR("labelNamePrefix")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("labelNamePrefix"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
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

    TSharedPtr<FJsonObject> FDescribeLabelValuesRequest::ToJson() const
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
        if (MetricNameValue.IsSet())
        {
            JsonRootObject->SetStringField("metricName", MetricNameValue.GetValue());
        }
        if (LabelNamePrefixValue.IsSet())
        {
            JsonRootObject->SetStringField("labelNamePrefix", LabelNamePrefixValue.GetValue());
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