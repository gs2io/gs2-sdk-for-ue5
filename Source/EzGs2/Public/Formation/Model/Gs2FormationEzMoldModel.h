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
#include "Formation/Model/MoldModel.h"
#include "Gs2FormationEzFormModel.h"

namespace Gs2::UE5::Formation::Model
{
	class EZGS2_API FEzMoldModel final : public TSharedFromThis<FEzMoldModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<Gs2::UE5::Formation::Model::FEzFormModel> FormModelValue;
        TOptional<int32> InitialMaxCapacityValue;
        TOptional<int32> MaxCapacityValue;

	public:
        TSharedPtr<FEzMoldModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzMoldModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzMoldModel> WithFormModel(const TSharedPtr<Gs2::UE5::Formation::Model::FEzFormModel> FormModel);
        TSharedPtr<FEzMoldModel> WithInitialMaxCapacity(const TOptional<int32> InitialMaxCapacity);
        TSharedPtr<FEzMoldModel> WithMaxCapacity(const TOptional<int32> MaxCapacity);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<Gs2::UE5::Formation::Model::FEzFormModel> GetFormModel() const;

        TOptional<int32> GetInitialMaxCapacity() const;
        FString GetInitialMaxCapacityString() const;

        TOptional<int32> GetMaxCapacity() const;
        FString GetMaxCapacityString() const;

        Gs2::Formation::Model::FMoldModelPtr ToModel() const;
        static TSharedPtr<FEzMoldModel> FromModel(Gs2::Formation::Model::FMoldModelPtr Model);
    };
    typedef TSharedPtr<FEzMoldModel> FEzMoldModelPtr;
}