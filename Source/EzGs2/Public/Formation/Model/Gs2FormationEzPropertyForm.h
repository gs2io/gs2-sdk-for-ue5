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
#include "Formation/Model/PropertyForm.h"
#include "Gs2FormationEzSlot.h"

namespace Gs2::UE5::Formation::Model
{
	class EZGS2_API FEzPropertyForm final : public TSharedFromThis<FEzPropertyForm>
	{
        TOptional<FString> NameValue;
        TOptional<FString> PropertyIdValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlot>>> SlotsValue;

	public:
        TSharedPtr<FEzPropertyForm> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzPropertyForm> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FEzPropertyForm> WithSlots(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlot>>> Slots);

        TOptional<FString> GetName() const;

        TOptional<FString> GetPropertyId() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlot>>> GetSlots() const;

        Gs2::Formation::Model::FPropertyFormPtr ToModel() const;
        static TSharedPtr<FEzPropertyForm> FromModel(Gs2::Formation::Model::FPropertyFormPtr Model);
    };
    typedef TSharedPtr<FEzPropertyForm> FEzPropertyFormPtr;
}