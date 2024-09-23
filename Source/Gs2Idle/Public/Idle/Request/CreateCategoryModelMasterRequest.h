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
    class FCreateCategoryModelMasterRequest;

    class GS2IDLE_API FCreateCategoryModelMasterRequest final : public TSharedFromThis<FCreateCategoryModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> RewardIntervalMinutesValue;
        TOptional<int32> DefaultMaximumIdleMinutesValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionList>>> AcquireActionsValue;
        TOptional<FString> IdlePeriodScheduleIdValue;
        TOptional<FString> ReceivePeriodScheduleIdValue;
        
    public:
        
        FCreateCategoryModelMasterRequest();
        FCreateCategoryModelMasterRequest(
            const FCreateCategoryModelMasterRequest& From
        );
        ~FCreateCategoryModelMasterRequest() = default;

        TSharedPtr<FCreateCategoryModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithRewardIntervalMinutes(const TOptional<int32> RewardIntervalMinutes);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithDefaultMaximumIdleMinutes(const TOptional<int32> DefaultMaximumIdleMinutes);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionList>>> AcquireActions);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithIdlePeriodScheduleId(const TOptional<FString> IdlePeriodScheduleId);
        TSharedPtr<FCreateCategoryModelMasterRequest> WithReceivePeriodScheduleId(const TOptional<FString> ReceivePeriodScheduleId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetRewardIntervalMinutes() const;
        FString GetRewardIntervalMinutesString() const;
        TOptional<int32> GetDefaultMaximumIdleMinutes() const;
        FString GetDefaultMaximumIdleMinutesString() const;TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionList>>> GetAcquireActions() const;
        TOptional<FString> GetIdlePeriodScheduleId() const;
        TOptional<FString> GetReceivePeriodScheduleId() const;

        static TSharedPtr<FCreateCategoryModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateCategoryModelMasterRequest, ESPMode::ThreadSafe> FCreateCategoryModelMasterRequestPtr;
}