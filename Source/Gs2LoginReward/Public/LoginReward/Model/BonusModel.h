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
#include "Core/Gs2Object.h"
#include "Reward.h"
#include "VerifyAction.h"
#include "ConsumeAction.h"

namespace Gs2::LoginReward::Model
{
    class GS2LOGINREWARD_API FBonusModel final : public FGs2Object, public TSharedFromThis<FBonusModel>
    {
        TOptional<FString> BonusModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ModeValue;
        TOptional<FString> PeriodEventIdValue;
        TOptional<int32> ResetHourValue;
        TOptional<FString> RepeatValue;
        TSharedPtr<TArray<TSharedPtr<FReward>>> RewardsValue;
        TOptional<FString> MissedReceiveReliefValue;
        TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> MissedReceiveReliefVerifyActionsValue;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> MissedReceiveReliefConsumeActionsValue;

    public:
        FBonusModel();
        FBonusModel(
            const FBonusModel& From
        );
        virtual ~FBonusModel() override = default;

        TSharedPtr<FBonusModel> WithBonusModelId(const TOptional<FString> BonusModelId);
        TSharedPtr<FBonusModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FBonusModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FBonusModel> WithMode(const TOptional<FString> Mode);
        TSharedPtr<FBonusModel> WithPeriodEventId(const TOptional<FString> PeriodEventId);
        TSharedPtr<FBonusModel> WithResetHour(const TOptional<int32> ResetHour);
        TSharedPtr<FBonusModel> WithRepeat(const TOptional<FString> Repeat);
        TSharedPtr<FBonusModel> WithRewards(const TSharedPtr<TArray<TSharedPtr<FReward>>> Rewards);
        TSharedPtr<FBonusModel> WithMissedReceiveRelief(const TOptional<FString> MissedReceiveRelief);
        TSharedPtr<FBonusModel> WithMissedReceiveReliefVerifyActions(const TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> MissedReceiveReliefVerifyActions);
        TSharedPtr<FBonusModel> WithMissedReceiveReliefConsumeActions(const TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> MissedReceiveReliefConsumeActions);

        TOptional<FString> GetBonusModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetMode() const;
        TOptional<FString> GetPeriodEventId() const;
        TOptional<int32> GetResetHour() const;
        FString GetResetHourString() const;
        TOptional<FString> GetRepeat() const;
        TSharedPtr<TArray<TSharedPtr<FReward>>> GetRewards() const;
        TOptional<FString> GetMissedReceiveRelief() const;
        TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> GetMissedReceiveReliefVerifyActions() const;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> GetMissedReceiveReliefConsumeActions() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetBonusModelNameFromGrn(const FString Grn);

        static TSharedPtr<FBonusModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBonusModel, ESPMode::ThreadSafe> FBonusModelPtr;
}