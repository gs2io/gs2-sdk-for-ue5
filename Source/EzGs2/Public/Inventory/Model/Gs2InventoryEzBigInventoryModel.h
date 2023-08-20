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
#include "Inventory/Model/BigInventoryModel.h"

namespace Gs2::UE5::Inventory::Model
{
	class EZGS2_API FEzBigInventoryModel final : public TSharedFromThis<FEzBigInventoryModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;

	public:
        TSharedPtr<FEzBigInventoryModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzBigInventoryModel> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        Gs2::Inventory::Model::FBigInventoryModelPtr ToModel() const;
        static TSharedPtr<FEzBigInventoryModel> FromModel(Gs2::Inventory::Model::FBigInventoryModelPtr Model);
    };
    typedef TSharedPtr<FEzBigInventoryModel> FEzBigInventoryModelPtr;
}