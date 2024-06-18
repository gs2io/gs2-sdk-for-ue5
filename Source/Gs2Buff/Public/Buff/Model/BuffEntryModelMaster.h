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
#include "BuffTargetModel.h"
#include "BuffTargetAction.h"

namespace Gs2::Buff::Model
{
    class GS2BUFF_API FBuffEntryModelMaster final : public Gs2Object, public TSharedFromThis<FBuffEntryModelMaster>
    {
        TOptional<FString> BuffEntryModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ExpressionValue;
        TOptional<FString> TargetTypeValue;
        TSharedPtr<FBuffTargetModel> TargetModelValue;
        TSharedPtr<FBuffTargetAction> TargetActionValue;
        TOptional<int32> PriorityValue;
        TOptional<FString> ApplyPeriodScheduleEventIdValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FBuffEntryModelMaster();
        FBuffEntryModelMaster(
            const FBuffEntryModelMaster& From
        );
        virtual ~FBuffEntryModelMaster() override = default;

        TSharedPtr<FBuffEntryModelMaster> WithBuffEntryModelId(const TOptional<FString> BuffEntryModelId);
        TSharedPtr<FBuffEntryModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FBuffEntryModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FBuffEntryModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FBuffEntryModelMaster> WithExpression(const TOptional<FString> Expression);
        TSharedPtr<FBuffEntryModelMaster> WithTargetType(const TOptional<FString> TargetType);
        TSharedPtr<FBuffEntryModelMaster> WithTargetModel(const TSharedPtr<FBuffTargetModel> TargetModel);
        TSharedPtr<FBuffEntryModelMaster> WithTargetAction(const TSharedPtr<FBuffTargetAction> TargetAction);
        TSharedPtr<FBuffEntryModelMaster> WithPriority(const TOptional<int32> Priority);
        TSharedPtr<FBuffEntryModelMaster> WithApplyPeriodScheduleEventId(const TOptional<FString> ApplyPeriodScheduleEventId);
        TSharedPtr<FBuffEntryModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FBuffEntryModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FBuffEntryModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetBuffEntryModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetExpression() const;
        TOptional<FString> GetTargetType() const;
        TSharedPtr<FBuffTargetModel> GetTargetModel() const;
        TSharedPtr<FBuffTargetAction> GetTargetAction() const;
        TOptional<int32> GetPriority() const;
        FString GetPriorityString() const;
        TOptional<FString> GetApplyPeriodScheduleEventId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetBuffEntryNameFromGrn(const FString Grn);

        static TSharedPtr<FBuffEntryModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBuffEntryModelMaster, ESPMode::ThreadSafe> FBuffEntryModelMasterPtr;
}