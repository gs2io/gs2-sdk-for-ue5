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

#include "Quest/Model/Gs2QuestEzProgress.h"

namespace Gs2::UE5::Quest::Model
{

    TSharedPtr<FEzProgress> FEzProgress::WithProgressId(
        const TOptional<FString> ProgressId
    )
    {
        this->ProgressIdValue = ProgressId;
        return SharedThis(this);
    }

    TSharedPtr<FEzProgress> FEzProgress::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FEzProgress> FEzProgress::WithQuestModelId(
        const TOptional<FString> QuestModelId
    )
    {
        this->QuestModelIdValue = QuestModelId;
        return SharedThis(this);
    }

    TSharedPtr<FEzProgress> FEzProgress::WithRandomSeed(
        const TOptional<int64> RandomSeed
    )
    {
        this->RandomSeedValue = RandomSeed;
        return SharedThis(this);
    }

    TSharedPtr<FEzProgress> FEzProgress::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzProgress> FEzProgress::WithRewards(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> Rewards
    )
    {
        this->RewardsValue = Rewards;
        return SharedThis(this);
    }

    TSharedPtr<FEzProgress> FEzProgress::WithFailedRewards(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> FailedRewards
    )
    {
        this->FailedRewardsValue = FailedRewards;
        return SharedThis(this);
    }
    TOptional<FString> FEzProgress::GetProgressId() const
    {
        return ProgressIdValue;
    }
    TOptional<FString> FEzProgress::GetTransactionId() const
    {
        return TransactionIdValue;
    }
    TOptional<FString> FEzProgress::GetQuestModelId() const
    {
        return QuestModelIdValue;
    }
    TOptional<int64> FEzProgress::GetRandomSeed() const
    {
        return RandomSeedValue;
    }

    FString FEzProgress::GetRandomSeedString() const
    {
        if (!RandomSeedValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RandomSeedValue.GetValue());
    }
    TOptional<FString> FEzProgress::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> FEzProgress::GetRewards() const
    {
        return RewardsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> FEzProgress::GetFailedRewards() const
    {
        return FailedRewardsValue;
    }

    Gs2::Quest::Model::FProgressPtr FEzProgress::ToModel() const
    {
        return MakeShared<Gs2::Quest::Model::FProgress>()
            ->WithProgressId(ProgressIdValue)
            ->WithTransactionId(TransactionIdValue)
            ->WithQuestModelId(QuestModelIdValue)
            ->WithRandomSeed(RandomSeedValue)
            ->WithMetadata(MetadataValue)
            ->WithRewards([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Quest::Model::FReward>>>();
                    if (RewardsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *RewardsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithFailedRewards([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Quest::Model::FReward>>>();
                    if (FailedRewardsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *FailedRewardsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzProgress> FEzProgress::FromModel(const Gs2::Quest::Model::FProgressPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzProgress>()
            ->WithProgressId(Model->GetProgressId())
            ->WithTransactionId(Model->GetTransactionId())
            ->WithQuestModelId(Model->GetQuestModelId())
            ->WithRandomSeed(Model->GetRandomSeed())
            ->WithMetadata(Model->GetMetadata())
            ->WithRewards([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzReward>>>();
                    if (Model->GetRewards() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetRewards())
                    {
                        v->Add(FEzReward::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithFailedRewards([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzReward>>>();
                    if (Model->GetFailedRewards() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetFailedRewards())
                    {
                        v->Add(FEzReward::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}