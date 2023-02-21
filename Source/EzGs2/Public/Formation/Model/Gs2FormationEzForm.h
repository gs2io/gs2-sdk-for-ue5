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
#include "Formation/Model/Form.h"
#include "Gs2FormationEzSlot.h"

namespace Gs2::UE5::Formation::Model
{
	class EZGS2_API FEzForm final : public TSharedFromThis<FEzForm>
	{
        TOptional<FString> NameValue;
        TOptional<int32> IndexValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlot>>> SlotsValue;

	public:
        TSharedPtr<FEzForm> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzForm> WithIndex(const TOptional<int32> Index);
        TSharedPtr<FEzForm> WithSlots(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlot>>> Slots);

        TOptional<FString> GetName() const;

        TOptional<int32> GetIndex() const;
        FString GetIndexString() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlot>>> GetSlots() const;

        Gs2::Formation::Model::FFormPtr ToModel() const;
        static TSharedPtr<FEzForm> FromModel(Gs2::Formation::Model::FFormPtr Model);
    };
    typedef TSharedPtr<FEzForm> FEzFormPtr;
}