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
#include "Buff/Model/BuffEntryModel.h"
#include "Gs2BuffEzBuffTargetModel.h"
#include "Gs2BuffEzBuffTargetAction.h"

namespace Gs2::UE5::Buff::Model
{
	class EZGS2_API FEzBuffEntryModel final : public TSharedFromThis<FEzBuffEntryModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> TargetTypeValue;
        TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffTargetModel> TargetModelValue;
        TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffTargetAction> TargetActionValue;
        TOptional<FString> ExpressionValue;
        TOptional<FString> ApplyPeriodScheduleEventIdValue;

	public:
        TSharedPtr<FEzBuffEntryModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzBuffEntryModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzBuffEntryModel> WithTargetType(const TOptional<FString> TargetType);
        TSharedPtr<FEzBuffEntryModel> WithTargetModel(const TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffTargetModel> TargetModel);
        TSharedPtr<FEzBuffEntryModel> WithTargetAction(const TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffTargetAction> TargetAction);
        TSharedPtr<FEzBuffEntryModel> WithExpression(const TOptional<FString> Expression);
        TSharedPtr<FEzBuffEntryModel> WithApplyPeriodScheduleEventId(const TOptional<FString> ApplyPeriodScheduleEventId);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetTargetType() const;

        TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffTargetModel> GetTargetModel() const;

        TSharedPtr<Gs2::UE5::Buff::Model::FEzBuffTargetAction> GetTargetAction() const;

        TOptional<FString> GetExpression() const;

        TOptional<FString> GetApplyPeriodScheduleEventId() const;

        Gs2::Buff::Model::FBuffEntryModelPtr ToModel() const;
        static TSharedPtr<FEzBuffEntryModel> FromModel(Gs2::Buff::Model::FBuffEntryModelPtr Model);
    };
    typedef TSharedPtr<FEzBuffEntryModel> FEzBuffEntryModelPtr;
}