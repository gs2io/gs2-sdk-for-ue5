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
#include "MegaField/Model/LayerModel.h"

namespace Gs2::UE5::MegaField::Model
{
	class EZGS2_API FEzLayerModel final : public TSharedFromThis<FEzLayerModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;

	public:
        TSharedPtr<FEzLayerModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzLayerModel> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        Gs2::MegaField::Model::FLayerModelPtr ToModel() const;
        static TSharedPtr<FEzLayerModel> FromModel(Gs2::MegaField::Model::FLayerModelPtr Model);
    };
    typedef TSharedPtr<FEzLayerModel> FEzLayerModelPtr;
}