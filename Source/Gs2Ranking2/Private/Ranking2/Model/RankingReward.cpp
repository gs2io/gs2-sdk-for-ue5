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

#include "Ranking2/Model/RankingReward.h"

namespace Gs2::Ranking2::Model
{
    FRankingReward::FRankingReward():
        ThresholdRankValue(TOptional<int32>()),
        MetadataValue(TOptional<FString>()),
        AcquireActionsValue(nullptr)
    {
    }

    FRankingReward::FRankingReward(
        const FRankingReward& From
    ):
        ThresholdRankValue(From.ThresholdRankValue),
        MetadataValue(From.MetadataValue),
        AcquireActionsValue(From.AcquireActionsValue)
    {
    }

    TSharedPtr<FRankingReward> FRankingReward::WithThresholdRank(
        const TOptional<int32> ThresholdRank
    )
    {
        this->ThresholdRankValue = ThresholdRank;
        return SharedThis(this);
    }

    TSharedPtr<FRankingReward> FRankingReward::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FRankingReward> FRankingReward::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }
    TOptional<int32> FRankingReward::GetThresholdRank() const
    {
        return ThresholdRankValue;
    }

    FString FRankingReward::GetThresholdRankString() const
    {
        if (!ThresholdRankValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ThresholdRankValue.GetValue());
    }
    TOptional<FString> FRankingReward::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FRankingReward::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }

    TSharedPtr<FRankingReward> FRankingReward::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRankingReward>()
            ->WithThresholdRank(Data->HasField(ANSI_TO_TCHAR("thresholdRank")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("thresholdRank"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAcquireActions(Data->HasField(ANSI_TO_TCHAR("acquireActions")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("acquireActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("acquireActions")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("acquireActions")))
                        {
                            v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAcquireActionPtr>>());
    }

    TSharedPtr<FJsonObject> FRankingReward::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ThresholdRankValue.IsSet())
        {
            JsonRootObject->SetNumberField("thresholdRank", ThresholdRankValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (AcquireActionsValue != nullptr && AcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("acquireActions", v);
        }
        return JsonRootObject;
    }

    FString FRankingReward::TypeName = "RankingReward";
}