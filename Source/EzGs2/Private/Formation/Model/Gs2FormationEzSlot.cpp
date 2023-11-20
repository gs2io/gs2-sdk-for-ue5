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

#include "Formation/Model/Gs2FormationEzSlot.h"

namespace Gs2::UE5::Formation::Model
{

    TSharedPtr<FEzSlot> FEzSlot::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzSlot> FEzSlot::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FEzSlot> FEzSlot::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }
    TOptional<FString> FEzSlot::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzSlot::GetPropertyId() const
    {
        return PropertyIdValue;
    }
    TOptional<FString> FEzSlot::GetMetadata() const
    {
        return MetadataValue;
    }

    Gs2::Formation::Model::FSlotPtr FEzSlot::ToModel() const
    {
        return MakeShared<Gs2::Formation::Model::FSlot>()
            ->WithName(NameValue)
            ->WithPropertyId(PropertyIdValue)
            ->WithMetadata(MetadataValue);
    }

    TSharedPtr<FEzSlot> FEzSlot::FromModel(const Gs2::Formation::Model::FSlotPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSlot>()
            ->WithName(Model->GetName())
            ->WithPropertyId(Model->GetPropertyId())
            ->WithMetadata(Model->GetMetadata());
    }
}