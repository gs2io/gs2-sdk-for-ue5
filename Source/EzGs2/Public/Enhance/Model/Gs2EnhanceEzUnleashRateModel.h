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
#include "Enhance/Model/UnleashRateModel.h"
#include "Gs2EnhanceEzUnleashRateEntryModel.h"

namespace Gs2::UE5::Enhance::Model
{
	class EZGS2_API FEzUnleashRateModel final : public TSharedFromThis<FEzUnleashRateModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> TargetInventoryModelIdValue;
        TOptional<FString> GradeModelIdValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashRateEntryModel>>> GradeEntriesValue;

	public:
        TSharedPtr<FEzUnleashRateModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzUnleashRateModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzUnleashRateModel> WithTargetInventoryModelId(const TOptional<FString> TargetInventoryModelId);
        TSharedPtr<FEzUnleashRateModel> WithGradeModelId(const TOptional<FString> GradeModelId);
        TSharedPtr<FEzUnleashRateModel> WithGradeEntries(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashRateEntryModel>>> GradeEntries);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetTargetInventoryModelId() const;

        TOptional<FString> GetGradeModelId() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashRateEntryModel>>> GetGradeEntries() const;

        Gs2::Enhance::Model::FUnleashRateModelPtr ToModel() const;
        static TSharedPtr<FEzUnleashRateModel> FromModel(Gs2::Enhance::Model::FUnleashRateModelPtr Model);
    };
    typedef TSharedPtr<FEzUnleashRateModel> FEzUnleashRateModelPtr;
}