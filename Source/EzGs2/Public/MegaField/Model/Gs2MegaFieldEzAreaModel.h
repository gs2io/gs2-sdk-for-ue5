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
#include "MegaField/Model/AreaModel.h"
#include "Gs2MegaFieldEzLayerModel.h"

namespace Gs2::UE5::MegaField::Model
{
	class EZGS2_API FEzAreaModel final : public TSharedFromThis<FEzAreaModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::MegaField::Model::FEzLayerModel>>> LayerModelsValue;

	public:
        TSharedPtr<FEzAreaModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzAreaModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzAreaModel> WithLayerModels(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::MegaField::Model::FEzLayerModel>>> LayerModels);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::MegaField::Model::FEzLayerModel>>> GetLayerModels() const;

        Gs2::MegaField::Model::FAreaModelPtr ToModel() const;
        static TSharedPtr<FEzAreaModel> FromModel(Gs2::MegaField::Model::FAreaModelPtr Model);
    };
    typedef TSharedPtr<FEzAreaModel> FEzAreaModelPtr;
}