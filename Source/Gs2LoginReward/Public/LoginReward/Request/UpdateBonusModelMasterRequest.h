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
#include "Dom/JsonObject.h"
#include "../Model/Reward.h"
#include "../Model/VerifyAction.h"
#include "../Model/ConsumeAction.h"

namespace Gs2::LoginReward::Request
{
    class FUpdateBonusModelMasterRequest;

    class GS2LOGINREWARD_API FUpdateBonusModelMasterRequest final : public TSharedFromThis<FUpdateBonusModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> BonusModelNameValue;
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
        
        FUpdateBonusModelMasterRequest();
        FUpdateBonusModelMasterRequest(
            const FUpdateBonusModelMasterRequest& From
        );
        ~FUpdateBonusModelMasterRequest() = default;

        TSharedPtr<FUpdateBonusModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateBonusModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateBonusModelMasterRequest> WithBonusModelName(const TOptional<FString> BonusModelName);
        TSharedPtr<FUpdateBonusModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateBonusModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateBonusModelMasterRequest> WithMode(const TOptional<FString> Mode);
        TSharedPtr<FUpdateBonusModelMasterRequest> WithPeriodEventId(const TOptional<FString> PeriodEventId);
        TSharedPtr<FUpdateBonusModelMasterRequest> WithResetHour(const TOptional<int32> ResetHour);
        TSharedPtr<FUpdateBonusModelMasterRequest> WithRepeat(const TOptional<FString> Repeat);
        TSharedPtr<FUpdateBonusModelMasterRequest> WithRewards(const TSharedPtr<TArray<TSharedPtr<Model::FReward>>> Rewards);
        TSharedPtr<FUpdateBonusModelMasterRequest> WithMissedReceiveRelief(const TOptional<FString> MissedReceiveRelief);
        TSharedPtr<FUpdateBonusModelMasterRequest> WithMissedReceiveReliefVerifyActions(const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> MissedReceiveReliefVerifyActions);
        TSharedPtr<FUpdateBonusModelMasterRequest> WithMissedReceiveReliefConsumeActions(const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> MissedReceiveReliefConsumeActions);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetBonusModelName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetMode() const;
        TOptional<FString> GetPeriodEventId() const;
        TOptional<int32> GetResetHour() const;
        FString GetResetHourString() const;
        TOptional<FString> GetRepeat() const;TSharedPtr<TArray<TSharedPtr<Model::FReward>>> GetRewards() const;
        TOptional<FString> GetMissedReceiveRelief() const;TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> GetMissedReceiveReliefVerifyActions() const;TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> GetMissedReceiveReliefConsumeActions() const;

        static TSharedPtr<FUpdateBonusModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateBonusModelMasterRequest> FUpdateBonusModelMasterRequestPtr;
}