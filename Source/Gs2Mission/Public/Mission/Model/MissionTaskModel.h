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
#include "TargetCounterModel.h"
#include "VerifyAction.h"
#include "AcquireAction.h"

namespace Gs2::Mission::Model
{
    class GS2MISSION_API FMissionTaskModel final : public FGs2Object, public TSharedFromThis<FMissionTaskModel>
    {
        TOptional<FString> MissionTaskIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> VerifyCompleteTypeValue;
        TSharedPtr<FTargetCounterModel> TargetCounterValue;
        TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> VerifyCompleteConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> CompleteAcquireActionsValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        TOptional<FString> PremiseMissionTaskNameValue;
        TOptional<FString> CounterNameValue;
        TOptional<FString> TargetResetTypeValue;
        TOptional<int64> TargetValueValue;

    public:
        FMissionTaskModel();
        FMissionTaskModel(
            const FMissionTaskModel& From
        );
        virtual ~FMissionTaskModel() override = default;

        TSharedPtr<FMissionTaskModel> WithMissionTaskId(const TOptional<FString> MissionTaskId);
        TSharedPtr<FMissionTaskModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FMissionTaskModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FMissionTaskModel> WithVerifyCompleteType(const TOptional<FString> VerifyCompleteType);
        TSharedPtr<FMissionTaskModel> WithTargetCounter(const TSharedPtr<FTargetCounterModel> TargetCounter);
        TSharedPtr<FMissionTaskModel> WithVerifyCompleteConsumeActions(const TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> VerifyCompleteConsumeActions);
        TSharedPtr<FMissionTaskModel> WithCompleteAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> CompleteAcquireActions);
        TSharedPtr<FMissionTaskModel> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);
        TSharedPtr<FMissionTaskModel> WithPremiseMissionTaskName(const TOptional<FString> PremiseMissionTaskName);
        TSharedPtr<FMissionTaskModel> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FMissionTaskModel> WithTargetResetType(const TOptional<FString> TargetResetType);
        TSharedPtr<FMissionTaskModel> WithTargetValue(const TOptional<int64> TargetValue);

        TOptional<FString> GetMissionTaskId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetVerifyCompleteType() const;
        TSharedPtr<FTargetCounterModel> GetTargetCounter() const;
        TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> GetVerifyCompleteConsumeActions() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetCompleteAcquireActions() const;
        TOptional<FString> GetChallengePeriodEventId() const;
        TOptional<FString> GetPremiseMissionTaskName() const;
        TOptional<FString> GetCounterName() const;
        TOptional<FString> GetTargetResetType() const;
        TOptional<int64> GetTargetValue() const;
        FString GetTargetValueString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetMissionGroupNameFromGrn(const FString Grn);
        static TOptional<FString> GetMissionTaskNameFromGrn(const FString Grn);

        static TSharedPtr<FMissionTaskModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FMissionTaskModel, ESPMode::ThreadSafe> FMissionTaskModelPtr;
}