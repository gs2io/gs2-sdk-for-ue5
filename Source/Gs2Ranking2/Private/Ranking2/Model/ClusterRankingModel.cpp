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

#include "Ranking2/Model/ClusterRankingModel.h"

namespace Gs2::Ranking2::Model
{
    FClusterRankingModel::FClusterRankingModel():
        ClusterRankingModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ClusterTypeValue(TOptional<FString>()),
        MinimumValueValue(TOptional<int64>()),
        MaximumValueValue(TOptional<int64>()),
        SumValue(TOptional<bool>()),
        OrderDirectionValue(TOptional<FString>()),
        EntryPeriodEventIdValue(TOptional<FString>()),
        RankingRewardsValue(nullptr),
        AccessPeriodEventIdValue(TOptional<FString>())
    {
    }

    FClusterRankingModel::FClusterRankingModel(
        const FClusterRankingModel& From
    ):
        ClusterRankingModelIdValue(From.ClusterRankingModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        ClusterTypeValue(From.ClusterTypeValue),
        MinimumValueValue(From.MinimumValueValue),
        MaximumValueValue(From.MaximumValueValue),
        SumValue(From.SumValue),
        OrderDirectionValue(From.OrderDirectionValue),
        EntryPeriodEventIdValue(From.EntryPeriodEventIdValue),
        RankingRewardsValue(From.RankingRewardsValue),
        AccessPeriodEventIdValue(From.AccessPeriodEventIdValue)
    {
    }

    TSharedPtr<FClusterRankingModel> FClusterRankingModel::WithClusterRankingModelId(
        const TOptional<FString> ClusterRankingModelId
    )
    {
        this->ClusterRankingModelIdValue = ClusterRankingModelId;
        return SharedThis(this);
    }

    TSharedPtr<FClusterRankingModel> FClusterRankingModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FClusterRankingModel> FClusterRankingModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FClusterRankingModel> FClusterRankingModel::WithClusterType(
        const TOptional<FString> ClusterType
    )
    {
        this->ClusterTypeValue = ClusterType;
        return SharedThis(this);
    }

    TSharedPtr<FClusterRankingModel> FClusterRankingModel::WithMinimumValue(
        const TOptional<int64> MinimumValue
    )
    {
        this->MinimumValueValue = MinimumValue;
        return SharedThis(this);
    }

    TSharedPtr<FClusterRankingModel> FClusterRankingModel::WithMaximumValue(
        const TOptional<int64> MaximumValue
    )
    {
        this->MaximumValueValue = MaximumValue;
        return SharedThis(this);
    }

    TSharedPtr<FClusterRankingModel> FClusterRankingModel::WithSum(
        const TOptional<bool> Sum
    )
    {
        this->SumValue = Sum;
        return SharedThis(this);
    }

    TSharedPtr<FClusterRankingModel> FClusterRankingModel::WithOrderDirection(
        const TOptional<FString> OrderDirection
    )
    {
        this->OrderDirectionValue = OrderDirection;
        return SharedThis(this);
    }

    TSharedPtr<FClusterRankingModel> FClusterRankingModel::WithEntryPeriodEventId(
        const TOptional<FString> EntryPeriodEventId
    )
    {
        this->EntryPeriodEventIdValue = EntryPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FClusterRankingModel> FClusterRankingModel::WithRankingRewards(
        const TSharedPtr<TArray<TSharedPtr<Model::FRankingReward>>> RankingRewards
    )
    {
        this->RankingRewardsValue = RankingRewards;
        return SharedThis(this);
    }

    TSharedPtr<FClusterRankingModel> FClusterRankingModel::WithAccessPeriodEventId(
        const TOptional<FString> AccessPeriodEventId
    )
    {
        this->AccessPeriodEventIdValue = AccessPeriodEventId;
        return SharedThis(this);
    }
    TOptional<FString> FClusterRankingModel::GetClusterRankingModelId() const
    {
        return ClusterRankingModelIdValue;
    }
    TOptional<FString> FClusterRankingModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FClusterRankingModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FClusterRankingModel::GetClusterType() const
    {
        return ClusterTypeValue;
    }
    TOptional<int64> FClusterRankingModel::GetMinimumValue() const
    {
        return MinimumValueValue;
    }

    FString FClusterRankingModel::GetMinimumValueString() const
    {
        if (!MinimumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MinimumValueValue.GetValue());
    }
    TOptional<int64> FClusterRankingModel::GetMaximumValue() const
    {
        return MaximumValueValue;
    }

    FString FClusterRankingModel::GetMaximumValueString() const
    {
        if (!MaximumValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MaximumValueValue.GetValue());
    }
    TOptional<bool> FClusterRankingModel::GetSum() const
    {
        return SumValue;
    }

    FString FClusterRankingModel::GetSumString() const
    {
        if (!SumValue.IsSet())
        {
            return FString("null");
        }
        return FString(SumValue.GetValue() ? "true" : "false");
    }
    TOptional<FString> FClusterRankingModel::GetOrderDirection() const
    {
        return OrderDirectionValue;
    }
    TOptional<FString> FClusterRankingModel::GetEntryPeriodEventId() const
    {
        return EntryPeriodEventIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FRankingReward>>> FClusterRankingModel::GetRankingRewards() const
    {
        return RankingRewardsValue;
    }
    TOptional<FString> FClusterRankingModel::GetAccessPeriodEventId() const
    {
        return AccessPeriodEventIdValue;
    }

    TOptional<FString> FClusterRankingModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):cluster:(?<rankingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FClusterRankingModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):cluster:(?<rankingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FClusterRankingModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):cluster:(?<rankingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FClusterRankingModel::GetRankingNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):ranking2:(?<namespaceName>.+):cluster:(?<rankingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FClusterRankingModel> FClusterRankingModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FClusterRankingModel>()
            ->WithClusterRankingModelId(Data->HasField(ANSI_TO_TCHAR("clusterRankingModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("clusterRankingModelId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
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

    TSharedPtr<FJsonObject> FClusterRankingModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ClusterRankingModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("clusterRankingModelId", ClusterRankingModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
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
        if (OrderDirectionValue.IsSet())
        {
            JsonRootObject->SetStringField("orderDirection", OrderDirectionValue.GetValue());
        }
        if (EntryPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("entryPeriodEventId", EntryPeriodEventIdValue.GetValue());
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
        if (AccessPeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("accessPeriodEventId", AccessPeriodEventIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FClusterRankingModel::TypeName = "ClusterRankingModel";
}