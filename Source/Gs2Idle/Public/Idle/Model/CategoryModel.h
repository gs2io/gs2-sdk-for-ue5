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
#include "AcquireActionList.h"

namespace Gs2::Idle::Model
{
    class GS2IDLE_API FCategoryModel final : public FGs2Object, public TSharedFromThis<FCategoryModel>
    {
        TOptional<FString> CategoryModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> RewardIntervalMinutesValue;
        TOptional<int32> DefaultMaximumIdleMinutesValue;
        TOptional<FString> RewardResetModeValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireActionList>>> AcquireActionsValue;
        TOptional<FString> IdlePeriodScheduleIdValue;
        TOptional<FString> ReceivePeriodScheduleIdValue;

    public:
        FCategoryModel();
        FCategoryModel(
            const FCategoryModel& From
        );
        virtual ~FCategoryModel() override = default;

        TSharedPtr<FCategoryModel> WithCategoryModelId(const TOptional<FString> CategoryModelId);
        TSharedPtr<FCategoryModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FCategoryModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCategoryModel> WithRewardIntervalMinutes(const TOptional<int32> RewardIntervalMinutes);
        TSharedPtr<FCategoryModel> WithDefaultMaximumIdleMinutes(const TOptional<int32> DefaultMaximumIdleMinutes);
        TSharedPtr<FCategoryModel> WithRewardResetMode(const TOptional<FString> RewardResetMode);
        TSharedPtr<FCategoryModel> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireActionList>>> AcquireActions);
        TSharedPtr<FCategoryModel> WithIdlePeriodScheduleId(const TOptional<FString> IdlePeriodScheduleId);
        TSharedPtr<FCategoryModel> WithReceivePeriodScheduleId(const TOptional<FString> ReceivePeriodScheduleId);

        TOptional<FString> GetCategoryModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetRewardIntervalMinutes() const;
        FString GetRewardIntervalMinutesString() const;
        TOptional<int32> GetDefaultMaximumIdleMinutes() const;
        FString GetDefaultMaximumIdleMinutesString() const;
        TOptional<FString> GetRewardResetMode() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireActionList>>> GetAcquireActions() const;
        TOptional<FString> GetIdlePeriodScheduleId() const;
        TOptional<FString> GetReceivePeriodScheduleId() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetCategoryNameFromGrn(const FString Grn);

        static TSharedPtr<FCategoryModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCategoryModel, ESPMode::ThreadSafe> FCategoryModelPtr;
}