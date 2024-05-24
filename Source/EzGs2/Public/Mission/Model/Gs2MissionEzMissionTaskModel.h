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
#include "Mission/Model/MissionTaskModel.h"
#include "Gs2MissionEzTargetCounterModel.h"
#include "Gs2MissionEzConsumeAction.h"
#include "Gs2MissionEzAcquireAction.h"

namespace Gs2::UE5::Mission::Model
{
	class EZGS2_API FEzMissionTaskModel final : public TSharedFromThis<FEzMissionTaskModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> VerifyCompleteTypeValue;
        TSharedPtr<Gs2::UE5::Mission::Model::FEzTargetCounterModel> TargetCounterValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzConsumeAction>>> VerifyCompleteConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzAcquireAction>>> CompleteAcquireActionsValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        TOptional<FString> PremiseMissionTaskNameValue;
        TOptional<FString> CounterNameValue;
        TOptional<FString> TargetResetTypeValue;
        TOptional<int64> TargetValueValue;

	public:
        TSharedPtr<FEzMissionTaskModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzMissionTaskModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzMissionTaskModel> WithVerifyCompleteType(const TOptional<FString> VerifyCompleteType);
        TSharedPtr<FEzMissionTaskModel> WithTargetCounter(const TSharedPtr<Gs2::UE5::Mission::Model::FEzTargetCounterModel> TargetCounter);
        TSharedPtr<FEzMissionTaskModel> WithVerifyCompleteConsumeActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzConsumeAction>>> VerifyCompleteConsumeActions);
        TSharedPtr<FEzMissionTaskModel> WithCompleteAcquireActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzAcquireAction>>> CompleteAcquireActions);
        TSharedPtr<FEzMissionTaskModel> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);
        TSharedPtr<FEzMissionTaskModel> WithPremiseMissionTaskName(const TOptional<FString> PremiseMissionTaskName);
        TSharedPtr<FEzMissionTaskModel> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FEzMissionTaskModel> WithTargetResetType(const TOptional<FString> TargetResetType);
        TSharedPtr<FEzMissionTaskModel> WithTargetValue(const TOptional<int64> TargetValue);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetVerifyCompleteType() const;

        TSharedPtr<Gs2::UE5::Mission::Model::FEzTargetCounterModel> GetTargetCounter() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzConsumeAction>>> GetVerifyCompleteConsumeActions() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzAcquireAction>>> GetCompleteAcquireActions() const;

        TOptional<FString> GetChallengePeriodEventId() const;

        TOptional<FString> GetPremiseMissionTaskName() const;

        TOptional<FString> GetCounterName() const;

        TOptional<FString> GetTargetResetType() const;

        TOptional<int64> GetTargetValue() const;
        FString GetTargetValueString() const;

        Gs2::Mission::Model::FMissionTaskModelPtr ToModel() const;
        static TSharedPtr<FEzMissionTaskModel> FromModel(Gs2::Mission::Model::FMissionTaskModelPtr Model);
    };
    typedef TSharedPtr<FEzMissionTaskModel> FEzMissionTaskModelPtr;
}