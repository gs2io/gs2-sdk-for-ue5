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
#include "Enhance/Model/RateModel.h"

namespace Gs2::UE5::Enhance::Model
{
	class EZGS2_API FEzRateModel final : public TSharedFromThis<FEzRateModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> TargetInventoryModelIdValue;
        TOptional<FString> AcquireExperienceSuffixValue;
        TOptional<FString> MaterialInventoryModelIdValue;
        TOptional<FString> ExperienceModelIdValue;

	public:
        TSharedPtr<FEzRateModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzRateModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzRateModel> WithTargetInventoryModelId(const TOptional<FString> TargetInventoryModelId);
        TSharedPtr<FEzRateModel> WithAcquireExperienceSuffix(const TOptional<FString> AcquireExperienceSuffix);
        TSharedPtr<FEzRateModel> WithMaterialInventoryModelId(const TOptional<FString> MaterialInventoryModelId);
        TSharedPtr<FEzRateModel> WithExperienceModelId(const TOptional<FString> ExperienceModelId);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetTargetInventoryModelId() const;

        TOptional<FString> GetAcquireExperienceSuffix() const;

        TOptional<FString> GetMaterialInventoryModelId() const;

        TOptional<FString> GetExperienceModelId() const;

        Gs2::Enhance::Model::FRateModelPtr ToModel() const;
        static TSharedPtr<FEzRateModel> FromModel(Gs2::Enhance::Model::FRateModelPtr Model);
    };
    typedef TSharedPtr<FEzRateModel> FEzRateModelPtr;
}