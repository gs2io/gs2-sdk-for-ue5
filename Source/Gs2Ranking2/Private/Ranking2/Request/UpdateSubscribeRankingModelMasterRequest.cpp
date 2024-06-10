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

#include "Ranking2/Request/UpdateSubscribeRankingModelMasterRequest.h"

namespace Gs2::Ranking2::Request
{
    FUpdateSubscribeRankingModelMasterRequest::FUpdateSubscribeRankingModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        RankingNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        MinimumValueValue(TOptional<int64>()),
        MaximumValueValue(TOptional<int64>()),
        SumValue(TOptional<bool>()),
        ScoreTtlDaysValue(TOptional<int32>()),
        OrderDirectionValue(TOptional<FString>()),
        EntryPeriodEventIdValue(TOptional<FString>()),
        AccessPeriodEventIdValue(TOptional<FString>())
    {
    }

    FUpdateSubscribeRankingModelMasterRequest::FUpdateSubscribeRankingModelMasterRequest(
        const FUpdateSubscribeRankingModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RankingNameValue(From.RankingNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        MinimumValueValue(From.MinimumValueValue),
        MaximumValueValue(From.MaximumValueValue),
        SumValue(From.SumValue),
        ScoreTtlDaysValue(From.ScoreTtlDaysValue),
        OrderDirectionValue(From.OrderDirectionValue),
        EntryPeriodEventIdValue(From.EntryPeriodEventIdValue),
        AccessPeriodEventIdValue(From.AccessPeriodEventIdValue)
    {
    }

    TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> FUpdateSubscribeRankingModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> FUpdateSubscribeRankingModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> FUpdateSubscribeRankingModelMasterRequest::WithRankingName(
        const TOptional<FString> RankingName
    )
    {
        this->RankingNameValue = RankingName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> FUpdateSubscribeRankingModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> FUpdateSubscribeRankingModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> FUpdateSubscribeRankingModelMasterRequest::WithMinimumValue(
        const TOptional<int64> MinimumValue
    )
    {
        this->MinimumValueValue = MinimumValue;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> FUpdateSubscribeRankingModelMasterRequest::WithMaximumValue(
        const TOptional<int64> MaximumValue
    )
    {
        this->MaximumValueValue = MaximumValue;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> FUpdateSubscribeRankingModelMasterRequest::WithSum(
        const TOptional<bool> Sum
    )
    {
        this->SumValue = Sum;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> FUpdateSubscribeRankingModelMasterRequest::WithScoreTtlDays(
        const TOptional<int32> ScoreTtlDays
    )
    {
        this->ScoreTtlDaysValue = ScoreTtlDays;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> FUpdateSubscribeRankingModelMasterRequest::WithOrderDirection(
        const TOptional<FString> OrderDirection
    )
    {
        this->OrderDirectionValue = OrderDirection;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> FUpdateSubscribeRankingModelMasterRequest::WithEntryPeriodEventId(
        const TOptional<FString> EntryPeriodEventId
    )
    {
        this->EntryPeriodEventIdValue = EntryPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> FUpdateSubscribeRankingModelMasterRequest::WithAccessPeriodEventId(
        const TOptional<FString> AccessPeriodEventId
    )
    {
        this->AccessPeriodEventIdValue = AccessPeriodEventId;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateSubscribeRankingModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateSubscribeRankingModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateSubscribeRankingModelMasterRequest::GetRankingName() const
    {
        return RankingNameValue;
    }

    TOptional<FString> FUpdateSubscribeRankingModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateSubscribeRankingModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<int64> FUpdateSubscribeRankingModelMasterRequest::GetMinimumValue() const
    {
        return MinimumValueValue;
    }

    FString FUpdateSubscribeRankingModelMasterRequest::GetMinimumValueString() const
    {
        if (!MinimumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MinimumValueValue.GetValue());
    }

    TOptional<int64> FUpdateSubscribeRankingModelMasterRequest::GetMaximumValue() const
    {
        return MaximumValueValue;
    }

    FString FUpdateSubscribeRankingModelMasterRequest::GetMaximumValueString() const
    {
        if (!MaximumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MaximumValueValue.GetValue());
    }

    TOptional<bool> FUpdateSubscribeRankingModelMasterRequest::GetSum() const
    {
        return SumValue;
    }

    FString FUpdateSubscribeRankingModelMasterRequest::GetSumString() const
    {
        if (!SumValue.IsSet())
        {
            return FString("null");
        }
        return FString(SumValue.GetValue() ? "true" : "false");
    }

    TOptional<int32> FUpdateSubscribeRankingModelMasterRequest::GetScoreTtlDays() const
    {
        return ScoreTtlDaysValue;
    }

    FString FUpdateSubscribeRankingModelMasterRequest::GetScoreTtlDaysString() const
    {
        if (!ScoreTtlDaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ScoreTtlDaysValue.GetValue());
    }

    TOptional<FString> FUpdateSubscribeRankingModelMasterRequest::GetOrderDirection() const
    {
        return OrderDirectionValue;
    }

    TOptional<FString> FUpdateSubscribeRankingModelMasterRequest::GetEntryPeriodEventId() const
    {
        return EntryPeriodEventIdValue;
    }

    TOptional<FString> FUpdateSubscribeRankingModelMasterRequest::GetAccessPeriodEventId() const
    {
        return AccessPeriodEventIdValue;
    }

    TSharedPtr<FUpdateSubscribeRankingModelMasterRequest> FUpdateSubscribeRankingModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateSubscribeRankingModelMasterRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithRankingName(Data->HasField(ANSI_TO_TCHAR("rankingName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("rankingName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMinimumValue(Data->HasField(ANSI_TO_TCHAR("minimumValue")) ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("minimumValue"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithMaximumValue(Data->HasField(ANSI_TO_TCHAR("maximumValue")) ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("maximumValue"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithSum(Data->HasField(ANSI_TO_TCHAR("sum")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("sum"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithScoreTtlDays(Data->HasField(ANSI_TO_TCHAR("scoreTtlDays")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("scoreTtlDays"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithOrderDirection(Data->HasField(ANSI_TO_TCHAR("orderDirection")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("orderDirection"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithEntryPeriodEventId(Data->HasField(ANSI_TO_TCHAR("entryPeriodEventId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("entryPeriodEventId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessPeriodEventId(Data->HasField(ANSI_TO_TCHAR("accessPeriodEventId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("accessPeriodEventId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateSubscribeRankingModelMasterRequest::ToJson() const
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
        if (RankingNameValue.IsSet())
        {
            JsonRootObject->SetStringField("rankingName", RankingNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (MinimumValueValue.IsSet())
        {
            JsonRootObject->SetStringField("minimumValue", FString::Printf(TEXT("%lld"), MinimumValueValue.GetValue()));
        }
        if (MaximumValueValue.IsSet())
        {
            JsonRootObject->SetStringField("maximumValue", FString::Printf(TEXT("%lld"), MaximumValueValue.GetValue()));
        }
        if (SumValue.IsSet())
        {
            JsonRootObject->SetBoolField("sum", SumValue.GetValue());
        }
        if (ScoreTtlDaysValue.IsSet())
        {
            JsonRootObject->SetNumberField("scoreTtlDays", ScoreTtlDaysValue.GetValue());
        }
        if (OrderDirectionValue.IsSet())
        {
            JsonRootObject->SetStringField("orderDirection", OrderDirectionValue.GetValue());
        }
        if (EntryPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("entryPeriodEventId", EntryPeriodEventIdValue.GetValue());
        }
        if (AccessPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("accessPeriodEventId", AccessPeriodEventIdValue.GetValue());
        }
        return JsonRootObject;
    }
}