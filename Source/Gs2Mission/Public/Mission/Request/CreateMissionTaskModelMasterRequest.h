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
#include "../Model/AcquireAction.h"

namespace Gs2::Mission::Request
{
    class FCreateMissionTaskModelMasterRequest;

    class GS2MISSION_API FCreateMissionTaskModelMasterRequest final : public TSharedFromThis<FCreateMissionTaskModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> MissionGroupNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> CounterNameValue;
        TOptional<int64> TargetValueValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> CompleteAcquireActionsValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        TOptional<FString> PremiseMissionTaskNameValue;
        
    public:
        
        FCreateMissionTaskModelMasterRequest();
        FCreateMissionTaskModelMasterRequest(
            const FCreateMissionTaskModelMasterRequest& From
        );
        ~FCreateMissionTaskModelMasterRequest() = default;

        TSharedPtr<FCreateMissionTaskModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateMissionTaskModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateMissionTaskModelMasterRequest> WithMissionGroupName(const TOptional<FString> MissionGroupName);
        TSharedPtr<FCreateMissionTaskModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateMissionTaskModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateMissionTaskModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateMissionTaskModelMasterRequest> WithCounterName(const TOptional<FString> CounterName);
        TSharedPtr<FCreateMissionTaskModelMasterRequest> WithTargetValue(const TOptional<int64> TargetValue);
        TSharedPtr<FCreateMissionTaskModelMasterRequest> WithCompleteAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> CompleteAcquireActions);
        TSharedPtr<FCreateMissionTaskModelMasterRequest> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);
        TSharedPtr<FCreateMissionTaskModelMasterRequest> WithPremiseMissionTaskName(const TOptional<FString> PremiseMissionTaskName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetMissionGroupName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetCounterName() const;
        TOptional<int64> GetTargetValue() const;
        FString GetTargetValueString() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetCompleteAcquireActions() const;
        TOptional<FString> GetChallengePeriodEventId() const;
        TOptional<FString> GetPremiseMissionTaskName() const;

        static TSharedPtr<FCreateMissionTaskModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateMissionTaskModelMasterRequest, ESPMode::ThreadSafe> FCreateMissionTaskModelMasterRequestPtr;
}