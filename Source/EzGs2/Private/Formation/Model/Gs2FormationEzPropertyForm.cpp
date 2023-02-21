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

#include "EzGs2/Public/Formation/Model/Gs2FormationEzPropertyForm.h"

namespace Gs2::UE5::Formation::Model
{

    TSharedPtr<FEzPropertyForm> FEzPropertyForm::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzPropertyForm> FEzPropertyForm::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FEzPropertyForm> FEzPropertyForm::WithSlots(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlot>>> Slots
    )
    {
        this->SlotsValue = Slots;
        return SharedThis(this);
    }
    TOptional<FString> FEzPropertyForm::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzPropertyForm::GetPropertyId() const
    {
        return PropertyIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlot>>> FEzPropertyForm::GetSlots() const
    {
        return SlotsValue;
    }

    Gs2::Formation::Model::FPropertyFormPtr FEzPropertyForm::ToModel() const
    {
        return MakeShared<Gs2::Formation::Model::FPropertyForm>()
            ->WithName(NameValue)
            ->WithPropertyId(PropertyIdValue)
            ->WithSlots([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Formation::Model::FSlot>>>();
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

    TSharedPtr<FEzPropertyForm> FEzPropertyForm::FromModel(const Gs2::Formation::Model::FPropertyFormPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzPropertyForm>()
            ->WithName(Model->GetName())
            ->WithPropertyId(Model->GetPropertyId())
            ->WithSlots([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzSlot>>>();
                    if (Model->GetSlots() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetSlots())
                    {
                        v->Add(FEzSlot::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}