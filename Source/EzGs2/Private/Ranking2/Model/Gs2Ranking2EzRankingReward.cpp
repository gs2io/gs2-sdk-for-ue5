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

#include "Ranking2/Model/Gs2Ranking2EzRankingReward.h"

namespace Gs2::UE5::Ranking2::Model
{

    TSharedPtr<FEzRankingReward> FEzRankingReward::WithThresholdRank(
        const TOptional<int32> ThresholdRank
    )
    {
        this->ThresholdRankValue = ThresholdRank;
        return SharedThis(this);
    }

    TSharedPtr<FEzRankingReward> FEzRankingReward::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzRankingReward> FEzRankingReward::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }
    TOptional<int32> FEzRankingReward::GetThresholdRank() const
    {
        return ThresholdRankValue;
    }

    FString FEzRankingReward::GetThresholdRankString() const
    {
        if (!ThresholdRankValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ThresholdRankValue.GetValue());
    }
    TOptional<FString> FEzRankingReward::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzAcquireAction>>> FEzRankingReward::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }

    Gs2::Ranking2::Model::FRankingRewardPtr FEzRankingReward::ToModel() const
    {
        return MakeShared<Gs2::Ranking2::Model::FRankingReward>()
            ->WithThresholdRank(ThresholdRankValue)
            ->WithMetadata(MetadataValue)
            ->WithAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Ranking2::Model::FAcquireAction>>>();
                    if (AcquireActionsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *AcquireActionsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzRankingReward> FEzRankingReward::FromModel(const Gs2::Ranking2::Model::FRankingRewardPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRankingReward>()
            ->WithThresholdRank(Model->GetThresholdRank())
            ->WithMetadata(Model->GetMetadata())
            ->WithAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzAcquireAction>>>();
                    if (Model->GetAcquireActions() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetAcquireActions())
                    {
                        v->Add(FEzAcquireAction::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}