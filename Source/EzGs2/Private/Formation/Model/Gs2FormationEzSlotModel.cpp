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

#include "Formation/Model/Gs2FormationEzSlotModel.h"

namespace Gs2::UE5::Formation::Model
{

    TSharedPtr<FEzSlotModel> FEzSlotModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzSlotModel> FEzSlotModel::WithPropertyRegex(
        const TOptional<FString> PropertyRegex
    )
    {
        this->PropertyRegexValue = PropertyRegex;
        return SharedThis(this);
    }

    TSharedPtr<FEzSlotModel> FEzSlotModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }
    TOptional<FString> FEzSlotModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzSlotModel::GetPropertyRegex() const
    {
        return PropertyRegexValue;
    }
    TOptional<FString> FEzSlotModel::GetMetadata() const
    {
        return MetadataValue;
    }

    Gs2::Formation::Model::FSlotModelPtr FEzSlotModel::ToModel() const
    {
        return MakeShared<Gs2::Formation::Model::FSlotModel>()
            ->WithName(NameValue)
            ->WithPropertyRegex(PropertyRegexValue)
            ->WithMetadata(MetadataValue);
    }

    TSharedPtr<FEzSlotModel> FEzSlotModel::FromModel(const Gs2::Formation::Model::FSlotModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSlotModel>()
            ->WithName(Model->GetName())
            ->WithPropertyRegex(Model->GetPropertyRegex())
            ->WithMetadata(Model->GetMetadata());
    }
}