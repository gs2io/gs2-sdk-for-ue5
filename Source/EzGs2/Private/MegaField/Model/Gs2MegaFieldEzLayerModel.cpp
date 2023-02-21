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

#include "EzGs2/Public/MegaField/Model/Gs2MegaFieldEzLayerModel.h"

namespace Gs2::UE5::MegaField::Model
{

    TSharedPtr<FEzLayerModel> FEzLayerModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzLayerModel> FEzLayerModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }
    TOptional<FString> FEzLayerModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzLayerModel::GetMetadata() const
    {
        return MetadataValue;
    }

    Gs2::MegaField::Model::FLayerModelPtr FEzLayerModel::ToModel() const
    {
        return MakeShared<Gs2::MegaField::Model::FLayerModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue);
    }

    TSharedPtr<FEzLayerModel> FEzLayerModel::FromModel(const Gs2::MegaField::Model::FLayerModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzLayerModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata());
    }
}