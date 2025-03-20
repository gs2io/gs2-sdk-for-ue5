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
    class GS2BUFF_API FBuffEntryModel final : public FGs2Object, public TSharedFromThis<FBuffEntryModel>
    {
        TOptional<FString> BuffEntryModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ExpressionValue;
        TOptional<FString> TargetTypeValue;
        TSharedPtr<FBuffTargetModel> TargetModelValue;
        TSharedPtr<FBuffTargetAction> TargetActionValue;
        TOptional<int32> PriorityValue;
        TOptional<FString> ApplyPeriodScheduleEventIdValue;

    public:
        FBuffEntryModel();
        FBuffEntryModel(
            const FBuffEntryModel& From
        );
        virtual ~FBuffEntryModel() override = default;

        TSharedPtr<FBuffEntryModel> WithBuffEntryModelId(const TOptional<FString> BuffEntryModelId);
        TSharedPtr<FBuffEntryModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FBuffEntryModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FBuffEntryModel> WithExpression(const TOptional<FString> Expression);
        TSharedPtr<FBuffEntryModel> WithTargetType(const TOptional<FString> TargetType);
        TSharedPtr<FBuffEntryModel> WithTargetModel(const TSharedPtr<FBuffTargetModel> TargetModel);
        TSharedPtr<FBuffEntryModel> WithTargetAction(const TSharedPtr<FBuffTargetAction> TargetAction);
        TSharedPtr<FBuffEntryModel> WithPriority(const TOptional<int32> Priority);
        TSharedPtr<FBuffEntryModel> WithApplyPeriodScheduleEventId(const TOptional<FString> ApplyPeriodScheduleEventId);

        TOptional<FString> GetBuffEntryModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetExpression() const;
        TOptional<FString> GetTargetType() const;
        TSharedPtr<FBuffTargetModel> GetTargetModel() const;
        TSharedPtr<FBuffTargetAction> GetTargetAction() const;
        TOptional<int32> GetPriority() const;
        FString GetPriorityString() const;
        TOptional<FString> GetApplyPeriodScheduleEventId() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetBuffEntryNameFromGrn(const FString Grn);

        static TSharedPtr<FBuffEntryModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBuffEntryModel, ESPMode::ThreadSafe> FBuffEntryModelPtr;
}