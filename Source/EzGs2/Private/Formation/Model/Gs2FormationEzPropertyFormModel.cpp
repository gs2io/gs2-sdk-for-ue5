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

#include "EzGs2/Public/Formation/Model/Gs2FormationEzPropertyFormModel.h"

namespace Gs2::UE5::Formation::Model
{

    TSharedPtr<FEzPropertyFormModel> FEzPropertyFormModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzPropertyFormModel> FEzPropertyFormModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzPropertyFormModel> FEzPropertyFormModel::WithSlots(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlotModel>>> Slots
    )
    {
        this->SlotsValue = Slots;
        return SharedThis(this);
    }
    TOptional<FString> FEzPropertyFormModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzPropertyFormModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlotModel>>> FEzPropertyFormModel::GetSlots() const
    {
        return SlotsValue;
    }

    Gs2::Formation::Model::FPropertyFormModelPtr FEzPropertyFormModel::ToModel() const
    {
        return MakeShared<Gs2::Formation::Model::FPropertyFormModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithSlots([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Formation::Model::FSlotModel>>>();
                    if (SlotsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *SlotsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzPropertyFormModel> FEzPropertyFormModel::FromModel(const Gs2::Formation::Model::FPropertyFormModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzPropertyFormModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithSlots([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzSlotModel>>>();
                    if (Model->GetSlots() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetSlots())
                    {
                        v->Add(FEzSlotModel::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}