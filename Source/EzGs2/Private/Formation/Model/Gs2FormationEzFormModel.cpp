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

#include "Formation/Model/Gs2FormationEzFormModel.h"

namespace Gs2::UE5::Formation::Model
{

    TSharedPtr<FEzFormModel> FEzFormModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzFormModel> FEzFormModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzFormModel> FEzFormModel::WithSlots(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlotModel>>> Slots
    )
    {
        this->SlotsValue = Slots;
        return SharedThis(this);
    }
    TOptional<FString> FEzFormModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzFormModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlotModel>>> FEzFormModel::GetSlots() const
    {
        return SlotsValue;
    }

    Gs2::Formation::Model::FFormModelPtr FEzFormModel::ToModel() const
    {
        return MakeShared<Gs2::Formation::Model::FFormModel>()
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

    TSharedPtr<FEzFormModel> FEzFormModel::FromModel(const Gs2::Formation::Model::FFormModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzFormModel>()
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