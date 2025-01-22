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

#include "Ranking2/Request/UpdateClusterRankingModelMasterRequest.h"

namespace Gs2::Ranking2::Request
{
    FUpdateClusterRankingModelMasterRequest::FUpdateClusterRankingModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        RankingNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ClusterTypeValue(TOptional<FString>()),
        MinimumValueValue(TOptional<int64>()),
        MaximumValueValue(TOptional<int64>()),
        SumValue(TOptional<bool>()),
        ScoreTtlDaysValue(TOptional<int32>()),
        OrderDirectionValue(TOptional<FString>()),
        RankingRewardsValue(nullptr),
        RewardCalculationIndexValue(TOptional<FString>()),
        EntryPeriodEventIdValue(TOptional<FString>()),
        AccessPeriodEventIdValue(TOptional<FString>())
    {
    }

    FUpdateClusterRankingModelMasterRequest::FUpdateClusterRankingModelMasterRequest(
        const FUpdateClusterRankingModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RankingNameValue(From.RankingNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ClusterTypeValue(From.ClusterTypeValue),
        MinimumValueValue(From.MinimumValueValue),
        MaximumValueValue(From.MaximumValueValue),
        SumValue(From.SumValue),
        ScoreTtlDaysValue(From.ScoreTtlDaysValue),
        OrderDirectionValue(From.OrderDirectionValue),
        RankingRewardsValue(From.RankingRewardsValue),
        RewardCalculationIndexValue(From.RewardCalculationIndexValue),
        EntryPeriodEventIdValue(From.EntryPeriodEventIdValue),
        AccessPeriodEventIdValue(From.AccessPeriodEventIdValue)
    {
    }

    TSharedPtr<FUpdateClusterRankingModelMasterRequest> FUpdateClusterRankingModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateClusterRankingModelMasterRequest> FUpdateClusterRankingModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateClusterRankingModelMasterRequest> FUpdateClusterRankingModelMasterRequest::WithRankingName(
        const TOptional<FString> RankingName
    )
    {
        this->RankingNameValue = RankingName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateClusterRankingModelMasterRequest> FUpdateClusterRankingModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateClusterRankingModelMasterRequest> FUpdateClusterRankingModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateClusterRankingModelMasterRequest> FUpdateClusterRankingModelMasterRequest::WithClusterType(
        const TOptional<FString> ClusterType
    )
    {
        this->ClusterTypeValue = ClusterType;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateClusterRankingModelMasterRequest> FUpdateClusterRankingModelMasterRequest::WithMinimumValue(
        const TOptional<int64> MinimumValue
    )
    {
        this->MinimumValueValue = MinimumValue;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateClusterRankingModelMasterRequest> FUpdateClusterRankingModelMasterRequest::WithMaximumValue(
        const TOptional<int64> MaximumValue
    )
    {
        this->MaximumValueValue = MaximumValue;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateClusterRankingModelMasterRequest> FUpdateClusterRankingModelMasterRequest::WithSum(
        const TOptional<bool> Sum
    )
    {
        this->SumValue = Sum;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateClusterRankingModelMasterRequest> FUpdateClusterRankingModelMasterRequest::WithScoreTtlDays(
        const TOptional<int32> ScoreTtlDays
    )
    {
        this->ScoreTtlDaysValue = ScoreTtlDays;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateClusterRankingModelMasterRequest> FUpdateClusterRankingModelMasterRequest::WithOrderDirection(
        const TOptional<FString> OrderDirection
    )
    {
        this->OrderDirectionValue = OrderDirection;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateClusterRankingModelMasterRequest> FUpdateClusterRankingModelMasterRequest::WithRankingRewards(
        const TSharedPtr<TArray<TSharedPtr<Model::FRankingReward>>> RankingRewards
    )
    {
        this->RankingRewardsValue = RankingRewards;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateClusterRankingModelMasterRequest> FUpdateClusterRankingModelMasterRequest::WithRewardCalculationIndex(
        const TOptional<FString> RewardCalculationIndex
    )
    {
        this->RewardCalculationIndexValue = RewardCalculationIndex;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateClusterRankingModelMasterRequest> FUpdateClusterRankingModelMasterRequest::WithEntryPeriodEventId(
        const TOptional<FString> EntryPeriodEventId
    )
    {
        this->EntryPeriodEventIdValue = EntryPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateClusterRankingModelMasterRequest> FUpdateClusterRankingModelMasterRequest::WithAccessPeriodEventId(
        const TOptional<FString> AccessPeriodEventId
    )
    {
        this->AccessPeriodEventIdValue = AccessPeriodEventId;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateClusterRankingModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateClusterRankingModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateClusterRankingModelMasterRequest::GetRankingName() const
    {
        return RankingNameValue;
    }

    TOptional<FString> FUpdateClusterRankingModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateClusterRankingModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateClusterRankingModelMasterRequest::GetClusterType() const
    {
        return ClusterTypeValue;
    }

    TOptional<int64> FUpdateClusterRankingModelMasterRequest::GetMinimumValue() const
    {
        return MinimumValueValue;
    }

    FString FUpdateClusterRankingModelMasterRequest::GetMinimumValueString() const
    {
        if (!MinimumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MinimumValueValue.GetValue());
    }

    TOptional<int64> FUpdateClusterRankingModelMasterRequest::GetMaximumValue() const
    {
        return MaximumValueValue;
    }

    FString FUpdateClusterRankingModelMasterRequest::GetMaximumValueString() const
    {
        if (!MaximumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MaximumValueValue.GetValue());
    }

    TOptional<bool> FUpdateClusterRankingModelMasterRequest::GetSum() const
    {
        return SumValue;
    }

    FString FUpdateClusterRankingModelMasterRequest::GetSumString() const
    {
        if (!SumValue.IsSet())
        {
            return FString("null");
        }
        return FString(SumValue.GetValue() ? "true" : "false");
    }

    TOptional<int32> FUpdateClusterRankingModelMasterRequest::GetScoreTtlDays() const
    {
        return ScoreTtlDaysValue;
    }

    FString FUpdateClusterRankingModelMasterRequest::GetScoreTtlDaysString() const
    {
        if (!ScoreTtlDaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ScoreTtlDaysValue.GetValue());
    }

    TOptional<FString> FUpdateClusterRankingModelMasterRequest::GetOrderDirection() const
    {
        return OrderDirectionValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FRankingReward>>> FUpdateClusterRankingModelMasterRequest::GetRankingRewards() const
    {
        if (!RankingRewardsValue.IsValid())
        {
            return nullptr;
        }
        return RankingRewardsValue;
    }

    TOptional<FString> FUpdateClusterRankingModelMasterRequest::GetRewardCalculationIndex() const
    {
        return RewardCalculationIndexValue;
    }

    TOptional<FString> FUpdateClusterRankingModelMasterRequest::GetEntryPeriodEventId() const
    {
        return EntryPeriodEventIdValue;
    }

    TOptional<FString> FUpdateClusterRankingModelMasterRequest::GetAccessPeriodEventId() const
    {
        return AccessPeriodEventIdValue;
    }

    TSharedPtr<FUpdateClusterRankingModelMasterRequest> FUpdateClusterRankingModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateClusterRankingModelMasterRequest>()
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
            ->WithClusterType(Data->HasField(ANSI_TO_TCHAR("clusterType")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("clusterType"), v))
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
          ->WithRankingRewards(Data->HasField(ANSI_TO_TCHAR("rankingRewards")) ? [Data]() -> TSharedPtr<TArray<Model::FRankingRewardPtr>>
              {
                  auto v = MakeShared<TArray<Model::FRankingRewardPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("rankingRewards")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("rankingRewards")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("rankingRewards")))
                      {
                          v->Add(Model::FRankingReward::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FRankingRewardPtr>>())
            ->WithRewardCalculationIndex(Data->HasField(ANSI_TO_TCHAR("rewardCalculationIndex")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("rewardCalculationIndex"), v))
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

    TSharedPtr<FJsonObject> FUpdateClusterRankingModelMasterRequest::ToJson() const
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
        if (ClusterTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("clusterType", ClusterTypeValue.GetValue());
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
        if (RankingRewardsValue != nullptr && RankingRewardsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *RankingRewardsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("rankingRewards", v);
        }
        if (RewardCalculationIndexValue.IsSet())
        {
            JsonRootObject->SetStringField("rewardCalculationIndex", RewardCalculationIndexValue.GetValue());
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