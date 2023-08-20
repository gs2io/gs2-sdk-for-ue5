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
#include "Inventory/Model/BigItemModel.h"

namespace Gs2::UE5::Inventory::Model
{
	class EZGS2_API FEzBigItemModel final : public TSharedFromThis<FEzBigItemModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;

	public:
        TSharedPtr<FEzBigItemModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzBigItemModel> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        Gs2::Inventory::Model::FBigItemModelPtr ToModel() const;
        static TSharedPtr<FEzBigItemModel> FromModel(Gs2::Inventory::Model::FBigItemModelPtr Model);
    };
    typedef TSharedPtr<FEzBigItemModel> FEzBigItemModelPtr;
}