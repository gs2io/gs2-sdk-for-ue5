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
    class GS2IDLE_API FCategoryModelMaster final : public Gs2Object, public TSharedFromThis<FCategoryModelMaster>
    {
        TOptional<FString> CategoryModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> RewardIntervalMinutesValue;
        TOptional<int32> DefaultMaximumIdleMinutesValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireActionList>>> AcquireActionsValue;
        TOptional<FString> IdlePeriodScheduleIdValue;
        TOptional<FString> ReceivePeriodScheduleIdValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FCategoryModelMaster();
        FCategoryModelMaster(
            const FCategoryModelMaster& From
        );
        virtual ~FCategoryModelMaster() override = default;

        TSharedPtr<FCategoryModelMaster> WithCategoryModelId(const TOptional<FString> CategoryModelId);
        TSharedPtr<FCategoryModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FCategoryModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCategoryModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCategoryModelMaster> WithRewardIntervalMinutes(const TOptional<int32> RewardIntervalMinutes);
        TSharedPtr<FCategoryModelMaster> WithDefaultMaximumIdleMinutes(const TOptional<int32> DefaultMaximumIdleMinutes);
        TSharedPtr<FCategoryModelMaster> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireActionList>>> AcquireActions);
        TSharedPtr<FCategoryModelMaster> WithIdlePeriodScheduleId(const TOptional<FString> IdlePeriodScheduleId);
        TSharedPtr<FCategoryModelMaster> WithReceivePeriodScheduleId(const TOptional<FString> ReceivePeriodScheduleId);
        TSharedPtr<FCategoryModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FCategoryModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FCategoryModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetCategoryModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetRewardIntervalMinutes() const;
        FString GetRewardIntervalMinutesString() const;
        TOptional<int32> GetDefaultMaximumIdleMinutes() const;
        FString GetDefaultMaximumIdleMinutesString() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireActionList>>> GetAcquireActions() const;
        TOptional<FString> GetIdlePeriodScheduleId() const;
        TOptional<FString> GetReceivePeriodScheduleId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetCategoryNameFromGrn(const FString Grn);

        static TSharedPtr<FCategoryModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCategoryModelMaster, ESPMode::ThreadSafe> FCategoryModelMasterPtr;
}