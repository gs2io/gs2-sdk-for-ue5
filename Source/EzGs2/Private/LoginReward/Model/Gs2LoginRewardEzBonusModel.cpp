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

#include "LoginReward/Model/Gs2LoginRewardEzBonusModel.h"

namespace Gs2::UE5::LoginReward::Model
{

    TSharedPtr<FEzBonusModel> FEzBonusModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzBonusModel> FEzBonusModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzBonusModel> FEzBonusModel::WithMode(
        const TOptional<FString> Mode
    )
    {
        this->ModeValue = Mode;
        return SharedThis(this);
    }

    TSharedPtr<FEzBonusModel> FEzBonusModel::WithPeriodEventId(
        const TOptional<FString> PeriodEventId
    )
    {
        this->PeriodEventIdValue = PeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FEzBonusModel> FEzBonusModel::WithResetHour(
        const TOptional<int32> ResetHour
    )
    {
        this->ResetHourValue = ResetHour;
        return SharedThis(this);
    }

    TSharedPtr<FEzBonusModel> FEzBonusModel::WithRepeat(
        const TOptional<FString> Repeat
    )
    {
        this->RepeatValue = Repeat;
        return SharedThis(this);
    }

    TSharedPtr<FEzBonusModel> FEzBonusModel::WithRewards(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzReward>>> Rewards
    )
    {
        this->RewardsValue = Rewards;
        return SharedThis(this);
    }

    TSharedPtr<FEzBonusModel> FEzBonusModel::WithMissedReceiveRelief(
        const TOptional<FString> MissedReceiveRelief
    )
    {
        this->MissedReceiveReliefValue = MissedReceiveRelief;
        return SharedThis(this);
    }

    TSharedPtr<FEzBonusModel> FEzBonusModel::WithMissedReceiveReliefConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConsumeAction>>> MissedReceiveReliefConsumeActions
    )
    {
        this->MissedReceiveReliefConsumeActionsValue = MissedReceiveReliefConsumeActions;
        return SharedThis(this);
    }
    TOptional<FString> FEzBonusModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzBonusModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzBonusModel::GetMode() const
    {
        return ModeValue;
    }
    TOptional<FString> FEzBonusModel::GetPeriodEventId() const
    {
        return PeriodEventIdValue;
    }
    TOptional<int32> FEzBonusModel::GetResetHour() const
    {
        return ResetHourValue;
    }

    FString FEzBonusModel::GetResetHourString() const
    {
        if (!ResetHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetHourValue.GetValue());
    }
    TOptional<FString> FEzBonusModel::GetRepeat() const
    {
        return RepeatValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzReward>>> FEzBonusModel::GetRewards() const
    {
        return RewardsValue;
    }
    TOptional<FString> FEzBonusModel::GetMissedReceiveRelief() const
    {
        return MissedReceiveReliefValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConsumeAction>>> FEzBonusModel::GetMissedReceiveReliefConsumeActions() const
    {
        return MissedReceiveReliefConsumeActionsValue;
    }

    Gs2::LoginReward::Model::FBonusModelPtr FEzBonusModel::ToModel() const
    {
        return MakeShared<Gs2::LoginReward::Model::FBonusModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithMode(ModeValue)
            ->WithPeriodEventId(PeriodEventIdValue)
            ->WithResetHour(ResetHourValue)
            ->WithRepeat(RepeatValue)
            ->WithRewards([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::LoginReward::Model::FReward>>>();
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
            ->WithMissedReceiveRelief(MissedReceiveReliefValue)
            ->WithMissedReceiveReliefConsumeActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::LoginReward::Model::FConsumeAction>>>();
                    if (MissedReceiveReliefConsumeActionsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *MissedReceiveReliefConsumeActionsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzBonusModel> FEzBonusModel::FromModel(const Gs2::LoginReward::Model::FBonusModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBonusModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithMode(Model->GetMode())
            ->WithPeriodEventId(Model->GetPeriodEventId())
            ->WithResetHour(Model->GetResetHour())
            ->WithRepeat(Model->GetRepeat())
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
            ->WithMissedReceiveRelief(Model->GetMissedReceiveRelief())
            ->WithMissedReceiveReliefConsumeActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzConsumeAction>>>();
                    if (Model->GetMissedReceiveReliefConsumeActions() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetMissedReceiveReliefConsumeActions())
                    {
                        v->Add(FEzConsumeAction::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}