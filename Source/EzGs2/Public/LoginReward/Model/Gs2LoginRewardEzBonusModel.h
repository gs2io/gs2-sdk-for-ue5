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
#include "LoginReward/Model/BonusModel.h"
#include "Gs2LoginRewardEzReward.h"
#include "Gs2LoginRewardEzVerifyAction.h"
#include "Gs2LoginRewardEzConsumeAction.h"

namespace Gs2::UE5::LoginReward::Model
{
	class EZGS2_API FEzBonusModel final : public TSharedFromThis<FEzBonusModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ModeValue;
        TOptional<FString> PeriodEventIdValue;
        TOptional<int32> ResetHourValue;
        TOptional<FString> RepeatValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzReward>>> RewardsValue;
        TOptional<FString> MissedReceiveReliefValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzVerifyAction>>> MissedReceiveReliefVerifyActionsValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConsumeAction>>> MissedReceiveReliefConsumeActionsValue;

	public:
        TSharedPtr<FEzBonusModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzBonusModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzBonusModel> WithMode(const TOptional<FString> Mode);
        TSharedPtr<FEzBonusModel> WithPeriodEventId(const TOptional<FString> PeriodEventId);
        TSharedPtr<FEzBonusModel> WithResetHour(const TOptional<int32> ResetHour);
        TSharedPtr<FEzBonusModel> WithRepeat(const TOptional<FString> Repeat);
        TSharedPtr<FEzBonusModel> WithRewards(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzReward>>> Rewards);
        TSharedPtr<FEzBonusModel> WithMissedReceiveRelief(const TOptional<FString> MissedReceiveRelief);
        TSharedPtr<FEzBonusModel> WithMissedReceiveReliefVerifyActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzVerifyAction>>> MissedReceiveReliefVerifyActions);
        TSharedPtr<FEzBonusModel> WithMissedReceiveReliefConsumeActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConsumeAction>>> MissedReceiveReliefConsumeActions);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetMode() const;

        TOptional<FString> GetPeriodEventId() const;

        TOptional<int32> GetResetHour() const;
        FString GetResetHourString() const;

        TOptional<FString> GetRepeat() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzReward>>> GetRewards() const;

        TOptional<FString> GetMissedReceiveRelief() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzVerifyAction>>> GetMissedReceiveReliefVerifyActions() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConsumeAction>>> GetMissedReceiveReliefConsumeActions() const;

        Gs2::LoginReward::Model::FBonusModelPtr ToModel() const;
        static TSharedPtr<FEzBonusModel> FromModel(Gs2::LoginReward::Model::FBonusModelPtr Model);
    };
    typedef TSharedPtr<FEzBonusModel> FEzBonusModelPtr;
}