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
#include "SkillTree/Model/NodeModel.h"
#include "Gs2SkillTreeEzConsumeAction.h"
#include "Gs2SkillTreeEzAcquireAction.h"

namespace Gs2::UE5::SkillTree::Model
{
	class EZGS2_API FEzNodeModel final : public TSharedFromThis<FEzNodeModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::SkillTree::Model::FEzConsumeAction>>> ReleaseConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::SkillTree::Model::FEzAcquireAction>>> ReturnAcquireActionsValue;
        TOptional<float> RestrainReturnRateValue;

	public:
        TSharedPtr<FEzNodeModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzNodeModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzNodeModel> WithReleaseConsumeActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::SkillTree::Model::FEzConsumeAction>>> ReleaseConsumeActions);
        TSharedPtr<FEzNodeModel> WithReturnAcquireActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::SkillTree::Model::FEzAcquireAction>>> ReturnAcquireActions);
        TSharedPtr<FEzNodeModel> WithRestrainReturnRate(const TOptional<float> RestrainReturnRate);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::SkillTree::Model::FEzConsumeAction>>> GetReleaseConsumeActions() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::SkillTree::Model::FEzAcquireAction>>> GetReturnAcquireActions() const;

        TOptional<float> GetRestrainReturnRate() const;
        FString GetRestrainReturnRateString() const;

        Gs2::SkillTree::Model::FNodeModelPtr ToModel() const;
        static TSharedPtr<FEzNodeModel> FromModel(Gs2::SkillTree::Model::FNodeModelPtr Model);
    };
    typedef TSharedPtr<FEzNodeModel> FEzNodeModelPtr;
}