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
#include "LoginReward/Domain/Model/Gs2LoginRewardEzBonusModelDomain.h"
#include "LoginReward/Model/Gs2LoginRewardReward.h"
#include "LoginReward/Model/Gs2LoginRewardConsumeAction.h"
#include "Core/BpGs2Constant.h"
#include "Gs2LoginRewardBonusModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2LoginRewardBonusModel
{
    GENERATED_BODY()

    Gs2::UE5::LoginReward::Domain::Model::FEzBonusModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2LoginRewardBonusModelValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    FString Mode = "";
    UPROPERTY(BlueprintReadOnly)
    FString PeriodEventId = "";
    UPROPERTY(BlueprintReadOnly)
    int32 ResetHour = 0;
    UPROPERTY(BlueprintReadOnly)
    FString Repeat = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2LoginRewardReward> Rewards = TArray<FGs2LoginRewardReward>();
    UPROPERTY(BlueprintReadOnly)
    FString MissedReceiveRelief = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2LoginRewardConsumeAction> MissedReceiveReliefConsumeActions = TArray<FGs2LoginRewardConsumeAction>();
};

inline FGs2LoginRewardBonusModelValue EzBonusModelToFGs2LoginRewardBonusModelValue(
    const Gs2::UE5::LoginReward::Model::FEzBonusModelPtr Model
)
{
    FGs2LoginRewardBonusModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardBonusModelFunctionLibrary::EzBonusModelToFGs2LoginRewardBonusModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.Mode = Model->GetMode() ? *Model->GetMode() : "";
    Value.PeriodEventId = Model->GetPeriodEventId() ? *Model->GetPeriodEventId() : "";
    Value.ResetHour = Model->GetResetHour() ? *Model->GetResetHour() : 0;
    Value.Repeat = Model->GetRepeat() ? *Model->GetRepeat() : "";
    Value.Rewards = Model->GetRewards() ? [&]
    {
        TArray<FGs2LoginRewardReward> r;
        for (auto v : *Model->GetRewards())
        {
            r.Add(EzRewardToFGs2LoginRewardReward(v));
        }
        return r;
    }() : TArray<FGs2LoginRewardReward>();
    Value.MissedReceiveRelief = Model->GetMissedReceiveRelief() ? *Model->GetMissedReceiveRelief() : "";
    Value.MissedReceiveReliefConsumeActions = Model->GetMissedReceiveReliefConsumeActions() ? [&]
    {
        TArray<FGs2LoginRewardConsumeAction> r;
        for (auto v : *Model->GetMissedReceiveReliefConsumeActions())
        {
            r.Add(EzConsumeActionToFGs2LoginRewardConsumeAction(v));
        }
        return r;
    }() : TArray<FGs2LoginRewardConsumeAction>();
    return Value;
}

inline Gs2::UE5::LoginReward::Model::FEzBonusModelPtr FGs2LoginRewardBonusModelValueToEzBonusModel(
    const FGs2LoginRewardBonusModelValue Model
)
{
    return MakeShared<Gs2::UE5::LoginReward::Model::FEzBonusModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithMode(Model.Mode)
        ->WithPeriodEventId(Model.PeriodEventId)
        ->WithResetHour(Model.ResetHour)
        ->WithRepeat(Model.Repeat)
        ->WithRewards([&]{
            auto r = MakeShared<TArray<Gs2::UE5::LoginReward::Model::FEzRewardPtr>>();
            for (auto v : Model.Rewards) {
                r->Add(FGs2LoginRewardRewardToEzReward(v));
            }
            return r;
        }())
        ->WithMissedReceiveRelief(Model.MissedReceiveRelief)
        ->WithMissedReceiveReliefConsumeActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::LoginReward::Model::FEzConsumeActionPtr>>();
            for (auto v : Model.MissedReceiveReliefConsumeActions) {
                r->Add(FGs2LoginRewardConsumeActionToEzConsumeAction(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2LoginRewardBonusModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};