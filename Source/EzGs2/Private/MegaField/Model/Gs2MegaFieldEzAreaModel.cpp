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

#include "MegaField/Model/Gs2MegaFieldEzAreaModel.h"

namespace Gs2::UE5::MegaField::Model
{

    TSharedPtr<FEzAreaModel> FEzAreaModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzAreaModel> FEzAreaModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzAreaModel> FEzAreaModel::WithLayerModels(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::MegaField::Model::FEzLayerModel>>> LayerModels
    )
    {
        this->LayerModelsValue = LayerModels;
        return SharedThis(this);
    }
    TOptional<FString> FEzAreaModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzAreaModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::MegaField::Model::FEzLayerModel>>> FEzAreaModel::GetLayerModels() const
    {
        return LayerModelsValue;
    }

    Gs2::MegaField::Model::FAreaModelPtr FEzAreaModel::ToModel() const
    {
        return MakeShared<Gs2::MegaField::Model::FAreaModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithLayerModels([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::MegaField::Model::FLayerModel>>>();
                    if (LayerModelsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *LayerModelsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzAreaModel> FEzAreaModel::FromModel(const Gs2::MegaField::Model::FAreaModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzAreaModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithLayerModels([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzLayerModel>>>();
                    if (Model->GetLayerModels() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetLayerModels())
                    {
                        v->Add(FEzLayerModel::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}