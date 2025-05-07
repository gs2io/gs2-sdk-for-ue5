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
#include "Quest/Model/Gs2QuestReward.h"
#include "Core/BpGs2Constant.h"
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

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ProgressId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString TransactionId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString QuestModelId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 RandomSeed = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2QuestReward> Rewards = TArray<FGs2QuestReward>();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2QuestReward> FailedRewards = TArray<FGs2QuestReward>();
};

inline FGs2QuestProgressValue EzProgressToFGs2QuestProgressValue(
    const Gs2::UE5::Quest::Model::FEzProgressPtr Model
)
{
    FGs2QuestProgressValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestProgressFunctionLibrary::EzProgressToFGs2QuestProgressValue] Model parameter specification is missing."))
        return Value;
    }
    Value.ProgressId = Model->GetProgressId() ? *Model->GetProgressId() : "";
    Value.TransactionId = Model->GetTransactionId() ? *Model->GetTransactionId() : "";
    Value.QuestModelId = Model->GetQuestModelId() ? *Model->GetQuestModelId() : "";
    Value.RandomSeed = Model->GetRandomSeed() ? *Model->GetRandomSeed() : 0;
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.Rewards = Model->GetRewards() ? [&]
    {
        TArray<FGs2QuestReward> r;
        for (auto v : *Model->GetRewards())
        {
            r.Add(EzRewardToFGs2QuestReward(v));
        }
        return r;
    }() : TArray<FGs2QuestReward>();
    Value.FailedRewards = Model->GetFailedRewards() ? [&]
    {
        TArray<FGs2QuestReward> r;
        for (auto v : *Model->GetFailedRewards())
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
        ->WithMetadata(Model.Metadata)
        ->WithRewards([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Quest::Model::FEzRewardPtr>>();
            for (auto v : Model.Rewards) {
                r->Add(FGs2QuestRewardToEzReward(v));
            }
            return r;
        }())
        ->WithFailedRewards([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Quest::Model::FEzRewardPtr>>();
            for (auto v : Model.FailedRewards) {
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