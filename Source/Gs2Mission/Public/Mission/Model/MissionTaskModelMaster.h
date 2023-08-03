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
#include "AcquireAction.h"

namespace Gs2::Mission::Model
{
    class GS2MISSION_API FMissionTaskModelMaster final : public Gs2Object, public TSharedFromThis<FMissionTaskModelMaster>
    {
        TOptional<FString> MissionTaskIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> CounterNameValue;
        TOptional<FString> TargetResetTypeValue;
        TOptional<int64> TargetValueValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> CompleteAcquireActionsValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        TOptional<FString> PremiseMissionTaskNameValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FMissionTaskModelMaster();
        FMissionTaskModelMaster(
            const FMissionTaskModelMaster& From
        );
        virtual ~FMissionTaskModelMaster() override = default;

        TSharedPtr<FMissionTaskModelMaster> WithMissionTaskId(const TOptional<FString> MissionTaskId);
        TSharedPtr<FMissionTaskModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FMissionTaskModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FMissionTaskModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FMissionTaskModelMaster> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FMissionTaskModelMaster> WithTargetResetType(const TOptional<FString> TargetResetType);
        TSharedPtr<FMissionTaskModelMaster> WithTargetValue(const TOptional<int64> TargetValue);
        TSharedPtr<FMissionTaskModelMaster> WithCompleteAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> CompleteAcquireActions);
        TSharedPtr<FMissionTaskModelMaster> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);
        TSharedPtr<FMissionTaskModelMaster> WithPremiseMissionTaskName(const TOptional<FString> PremiseMissionTaskName);
        TSharedPtr<FMissionTaskModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FMissionTaskModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetMissionTaskId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetCounterName() const;
        TOptional<FString> GetTargetResetType() const;
        TOptional<int64> GetTargetValue() const;
        FString GetTargetValueString() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetCompleteAcquireActions() const;
        TOptional<FString> GetChallengePeriodEventId() const;
        TOptional<FString> GetPremiseMissionTaskName() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetMissionGroupNameFromGrn(const FString Grn);
        static TOptional<FString> GetMissionTaskNameFromGrn(const FString Grn);

        static TSharedPtr<FMissionTaskModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FMissionTaskModelMaster, ESPMode::ThreadSafe> FMissionTaskModelMasterPtr;
}