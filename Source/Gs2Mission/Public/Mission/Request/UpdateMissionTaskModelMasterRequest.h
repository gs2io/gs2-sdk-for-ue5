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
#include "../Model/TargetCounterModel.h"
#include "../Model/ConsumeAction.h"
#include "../Model/AcquireAction.h"

namespace Gs2::Mission::Request
{
    class FUpdateMissionTaskModelMasterRequest;

    class GS2MISSION_API FUpdateMissionTaskModelMasterRequest final : public TSharedFromThis<FUpdateMissionTaskModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MissionGroupNameValue;
        TOptional<FString> MissionTaskNameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> VerifyCompleteTypeValue;
        TSharedPtr<Model::FTargetCounterModel> TargetCounterValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> VerifyCompleteConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> CompleteAcquireActionsValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        TOptional<FString> PremiseMissionTaskNameValue;
        TOptional<FString> CounterNameValue;
        TOptional<FString> TargetResetTypeValue;
        TOptional<int64> TargetValueValue;
        
    public:
        
        FUpdateMissionTaskModelMasterRequest();
        FUpdateMissionTaskModelMasterRequest(
            const FUpdateMissionTaskModelMasterRequest& From
        );
        ~FUpdateMissionTaskModelMasterRequest() = default;

        TSharedPtr<FUpdateMissionTaskModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateMissionTaskModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateMissionTaskModelMasterRequest> WithMissionGroupName(const TOptional<FString> MissionGroupName);
        TSharedPtr<FUpdateMissionTaskModelMasterRequest> WithMissionTaskName(const TOptional<FString> MissionTaskName);
        TSharedPtr<FUpdateMissionTaskModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateMissionTaskModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateMissionTaskModelMasterRequest> WithVerifyCompleteType(const TOptional<FString> VerifyCompleteType);
        TSharedPtr<FUpdateMissionTaskModelMasterRequest> WithTargetCounter(const TSharedPtr<Model::FTargetCounterModel> TargetCounter);
        TSharedPtr<FUpdateMissionTaskModelMasterRequest> WithVerifyCompleteConsumeActions(const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> VerifyCompleteConsumeActions);
        TSharedPtr<FUpdateMissionTaskModelMasterRequest> WithCompleteAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> CompleteAcquireActions);
        TSharedPtr<FUpdateMissionTaskModelMasterRequest> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);
        TSharedPtr<FUpdateMissionTaskModelMasterRequest> WithPremiseMissionTaskName(const TOptional<FString> PremiseMissionTaskName);
        TSharedPtr<FUpdateMissionTaskModelMasterRequest> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FUpdateMissionTaskModelMasterRequest> WithTargetResetType(const TOptional<FString> TargetResetType);
        TSharedPtr<FUpdateMissionTaskModelMasterRequest> WithTargetValue(const TOptional<int64> TargetValue);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMissionGroupName() const;
        TOptional<FString> GetMissionTaskName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetVerifyCompleteType() const;
        TSharedPtr<Model::FTargetCounterModel> GetTargetCounter() const;TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> GetVerifyCompleteConsumeActions() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetCompleteAcquireActions() const;
        TOptional<FString> GetChallengePeriodEventId() const;
        TOptional<FString> GetPremiseMissionTaskName() const;
        TOptional<FString> GetCounterName() const;
        TOptional<FString> GetTargetResetType() const;
        TOptional<int64> GetTargetValue() const;
        FString GetTargetValueString() const;

        static TSharedPtr<FUpdateMissionTaskModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateMissionTaskModelMasterRequest, ESPMode::ThreadSafe> FUpdateMissionTaskModelMasterRequestPtr;
}