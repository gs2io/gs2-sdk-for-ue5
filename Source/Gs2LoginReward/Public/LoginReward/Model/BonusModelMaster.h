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
#include "ConsumeAction.h"

namespace Gs2::LoginReward::Model
{
    class GS2LOGINREWARD_API FBonusModelMaster final : public Gs2Object, public TSharedFromThis<FBonusModelMaster>
    {
        TOptional<FString> BonusModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ModeValue;
        TOptional<FString> PeriodEventIdValue;
        TOptional<int32> ResetHourValue;
        TOptional<FString> RepeatValue;
        TSharedPtr<TArray<TSharedPtr<FReward>>> RewardsValue;
        TOptional<FString> MissedReceiveReliefValue;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> MissedReceiveReliefConsumeActionsValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FBonusModelMaster();
        FBonusModelMaster(
            const FBonusModelMaster& From
        );
        virtual ~FBonusModelMaster() override = default;

        TSharedPtr<FBonusModelMaster> WithBonusModelId(const TOptional<FString> BonusModelId);
        TSharedPtr<FBonusModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FBonusModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FBonusModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FBonusModelMaster> WithMode(const TOptional<FString> Mode);
        TSharedPtr<FBonusModelMaster> WithPeriodEventId(const TOptional<FString> PeriodEventId);
        TSharedPtr<FBonusModelMaster> WithResetHour(const TOptional<int32> ResetHour);
        TSharedPtr<FBonusModelMaster> WithRepeat(const TOptional<FString> Repeat);
        TSharedPtr<FBonusModelMaster> WithRewards(const TSharedPtr<TArray<TSharedPtr<FReward>>> Rewards);
        TSharedPtr<FBonusModelMaster> WithMissedReceiveRelief(const TOptional<FString> MissedReceiveRelief);
        TSharedPtr<FBonusModelMaster> WithMissedReceiveReliefConsumeActions(const TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> MissedReceiveReliefConsumeActions);
        TSharedPtr<FBonusModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FBonusModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FBonusModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetBonusModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetMode() const;
        TOptional<FString> GetPeriodEventId() const;
        TOptional<int32> GetResetHour() const;
        FString GetResetHourString() const;
        TOptional<FString> GetRepeat() const;
        TSharedPtr<TArray<TSharedPtr<FReward>>> GetRewards() const;
        TOptional<FString> GetMissedReceiveRelief() const;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> GetMissedReceiveReliefConsumeActions() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetBonusModelNameFromGrn(const FString Grn);

        static TSharedPtr<FBonusModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBonusModelMaster, ESPMode::ThreadSafe> FBonusModelMasterPtr;
}