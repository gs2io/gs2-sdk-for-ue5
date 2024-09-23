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
#include "../Model/AcquireActionList.h"

namespace Gs2::Idle::Request
{
    class FUpdateCategoryModelMasterRequest;

    class GS2IDLE_API FUpdateCategoryModelMasterRequest final : public TSharedFromThis<FUpdateCategoryModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> RewardIntervalMinutesValue;
        TOptional<int32> DefaultMaximumIdleMinutesValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionList>>> AcquireActionsValue;
        TOptional<FString> IdlePeriodScheduleIdValue;
        TOptional<FString> ReceivePeriodScheduleIdValue;
        
    public:
        
        FUpdateCategoryModelMasterRequest();
        FUpdateCategoryModelMasterRequest(
            const FUpdateCategoryModelMasterRequest& From
        );
        ~FUpdateCategoryModelMasterRequest() = default;

        TSharedPtr<FUpdateCategoryModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithRewardIntervalMinutes(const TOptional<int32> RewardIntervalMinutes);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithDefaultMaximumIdleMinutes(const TOptional<int32> DefaultMaximumIdleMinutes);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionList>>> AcquireActions);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithIdlePeriodScheduleId(const TOptional<FString> IdlePeriodScheduleId);
        TSharedPtr<FUpdateCategoryModelMasterRequest> WithReceivePeriodScheduleId(const TOptional<FString> ReceivePeriodScheduleId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetRewardIntervalMinutes() const;
        FString GetRewardIntervalMinutesString() const;
        TOptional<int32> GetDefaultMaximumIdleMinutes() const;
        FString GetDefaultMaximumIdleMinutesString() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionList>>> GetAcquireActions() const;
        TOptional<FString> GetIdlePeriodScheduleId() const;
        TOptional<FString> GetReceivePeriodScheduleId() const;

        static TSharedPtr<FUpdateCategoryModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateCategoryModelMasterRequest, ESPMode::ThreadSafe> FUpdateCategoryModelMasterRequestPtr;
}