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
#include "Quest/Model/Progress.h"
#include "Gs2QuestEzReward.h"
#include "Gs2QuestEzReward.h"

namespace Gs2::UE5::Quest::Model
{
	class EZGS2_API FEzProgress final : public TSharedFromThis<FEzProgress>
	{
        TOptional<FString> ProgressIdValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> QuestModelIdValue;
        TOptional<int64> RandomSeedValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> RewardsValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> FailedRewardsValue;

	public:
        TSharedPtr<FEzProgress> WithProgressId(const TOptional<FString> ProgressId);
        TSharedPtr<FEzProgress> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FEzProgress> WithQuestModelId(const TOptional<FString> QuestModelId);
        TSharedPtr<FEzProgress> WithRandomSeed(const TOptional<int64> RandomSeed);
        TSharedPtr<FEzProgress> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzProgress> WithRewards(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> Rewards);
        TSharedPtr<FEzProgress> WithFailedRewards(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> FailedRewards);

        TOptional<FString> GetProgressId() const;

        TOptional<FString> GetTransactionId() const;

        TOptional<FString> GetQuestModelId() const;

        TOptional<int64> GetRandomSeed() const;
        FString GetRandomSeedString() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> GetRewards() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> GetFailedRewards() const;

        Gs2::Quest::Model::FProgressPtr ToModel() const;
        static TSharedPtr<FEzProgress> FromModel(Gs2::Quest::Model::FProgressPtr Model);
    };
    typedef TSharedPtr<FEzProgress> FEzProgressPtr;
}