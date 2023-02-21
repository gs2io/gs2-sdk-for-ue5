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
#include "Formation/Model/FormModel.h"
#include "Gs2FormationEzSlotModel.h"

namespace Gs2::UE5::Formation::Model
{
	class EZGS2_API FEzFormModel final : public TSharedFromThis<FEzFormModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlotModel>>> SlotsValue;

	public:
        TSharedPtr<FEzFormModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzFormModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzFormModel> WithSlots(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlotModel>>> Slots);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlotModel>>> GetSlots() const;

        Gs2::Formation::Model::FFormModelPtr ToModel() const;
        static TSharedPtr<FEzFormModel> FromModel(Gs2::Formation::Model::FFormModelPtr Model);
    };
    typedef TSharedPtr<FEzFormModel> FEzFormModelPtr;
}