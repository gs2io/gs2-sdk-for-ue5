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
#include "../Model/Reward.h"
#include "../Model/VerifyAction.h"
#include "../Model/ConsumeAction.h"

namespace Gs2::LoginReward::Request
{
    class FCreateBonusModelMasterRequest;

    class GS2LOGINREWARD_API FCreateBonusModelMasterRequest final : public TSharedFromThis<FCreateBonusModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ModeValue;
        TOptional<FString> PeriodEventIdValue;
        TOptional<int32> ResetHourValue;
        TOptional<FString> RepeatValue;
        TSharedPtr<TArray<TSharedPtr<Model::FReward>>> RewardsValue;
        TOptional<FString> MissedReceiveReliefValue;
        TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> MissedReceiveReliefVerifyActionsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> MissedReceiveReliefConsumeActionsValue;
        
    public:
        
        FCreateBonusModelMasterRequest();
        FCreateBonusModelMasterRequest(
            const FCreateBonusModelMasterRequest& From
        );
        ~FCreateBonusModelMasterRequest() = default;

        TSharedPtr<FCreateBonusModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateBonusModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateBonusModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateBonusModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateBonusModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateBonusModelMasterRequest> WithMode(const TOptional<FString> Mode);
        TSharedPtr<FCreateBonusModelMasterRequest> WithPeriodEventId(const TOptional<FString> PeriodEventId);
        TSharedPtr<FCreateBonusModelMasterRequest> WithResetHour(const TOptional<int32> ResetHour);
        TSharedPtr<FCreateBonusModelMasterRequest> WithRepeat(const TOptional<FString> Repeat);
        TSharedPtr<FCreateBonusModelMasterRequest> WithRewards(const TSharedPtr<TArray<TSharedPtr<Model::FReward>>> Rewards);
        TSharedPtr<FCreateBonusModelMasterRequest> WithMissedReceiveRelief(const TOptional<FString> MissedReceiveRelief);
        TSharedPtr<FCreateBonusModelMasterRequest> WithMissedReceiveReliefVerifyActions(const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> MissedReceiveReliefVerifyActions);
        TSharedPtr<FCreateBonusModelMasterRequest> WithMissedReceiveReliefConsumeActions(const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> MissedReceiveReliefConsumeActions);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetMode() const;
        TOptional<FString> GetPeriodEventId() const;
        TOptional<int32> GetResetHour() const;
        FString GetResetHourString() const;
        TOptional<FString> GetRepeat() const;TSharedPtr<TArray<TSharedPtr<Model::FReward>>> GetRewards() const;
        TOptional<FString> GetMissedReceiveRelief() const;TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> GetMissedReceiveReliefVerifyActions() const;TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> GetMissedReceiveReliefConsumeActions() const;

        static TSharedPtr<FCreateBonusModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateBonusModelMasterRequest, ESPMode::ThreadSafe> FCreateBonusModelMasterRequestPtr;
}