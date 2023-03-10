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
#include "Quest/Domain/Model/Gs2QuestEzProgressGameSessionDomain.h"
#include "Quest/Model/Gs2QuestReward.h"
#include "Gs2QuestProgress.generated.h"

USTRUCT(BlueprintType)
struct FGs2QuestOwnProgress
{
    GENERATED_BODY()

    Gs2::UE5::Quest::Domain::Model::FEzProgressGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2QuestProgressValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString ProgressId = "";
    UPROPERTY(BlueprintReadOnly)
    FString TransactionId = "";
    UPROPERTY(BlueprintReadOnly)
    FString QuestModelId = "";
    UPROPERTY(BlueprintReadOnly)
    int64 RandomSeed = 0;
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2QuestReward> Rewards = TArray<FGs2QuestReward>();
};

inline FGs2QuestProgressValue EzProgressToFGs2QuestProgressValue(
    const Gs2::UE5::Quest::Model::FEzProgressPtr Model
)
{
    FGs2QuestProgressValue Value;
    Value.ProgressId = Model->GetProgressId() ? *Model->GetProgressId() : "";
    Value.TransactionId = Model->GetTransactionId() ? *Model->GetTransactionId() : "";
    Value.QuestModelId = Model->GetQuestModelId() ? *Model->GetQuestModelId() : "";
    Value.RandomSeed = Model->GetRandomSeed() ? *Model->GetRandomSeed() : 0;
    Value.Rewards = Model->GetRewards() ? [&]
    {
        TArray<FGs2QuestReward> r;
        for (auto v : *Model->GetRewards())
        {
            r.Add(EzRewardToFGs2QuestReward(v));
        }
        return r;
    }() : TArray<FGs2QuestReward>();
    return Value;
}

inline Gs2::UE5::Quest::Model::FEzProgressPtr FGs2QuestProgressValueToEzProgress(
    const FGs2QuestProgressValue Model
)
{
    return MakeShared<Gs2::UE5::Quest::Model::FEzProgress>()
        ->WithProgressId(Model.ProgressId)
        ->WithTransactionId(Model.TransactionId)
        ->WithQuestModelId(Model.QuestModelId)
        ->WithRandomSeed(Model.RandomSeed)
        ->WithRewards([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Quest::Model::FEzRewardPtr>>();
            for (auto v : Model.Rewards) {
                r->Add(FGs2QuestRewardToEzReward(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2QuestProgressFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};