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

#include "EzGs2/Public/Formation/Model/Gs2FormationEzForm.h"

namespace Gs2::UE5::Formation::Model
{

    TSharedPtr<FEzForm> FEzForm::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzForm> FEzForm::WithIndex(
        const TOptional<int32> Index
    )
    {
        this->IndexValue = Index;
        return SharedThis(this);
    }

    TSharedPtr<FEzForm> FEzForm::WithSlots(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlot>>> Slots
    )
    {
        this->SlotsValue = Slots;
        return SharedThis(this);
    }
    TOptional<FString> FEzForm::GetName() const
    {
        return NameValue;
    }
    TOptional<int32> FEzForm::GetIndex() const
    {
        return IndexValue;
    }

    FString FEzForm::GetIndexString() const
    {
        if (!IndexValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), IndexValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Formation::Model::FEzSlot>>> FEzForm::GetSlots() const
    {
        return SlotsValue;
    }

    Gs2::Formation::Model::FFormPtr FEzForm::ToModel() const
    {
        return MakeShared<Gs2::Formation::Model::FForm>()
            ->WithName(NameValue)
            ->WithIndex(IndexValue)
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

    TSharedPtr<FEzForm> FEzForm::FromModel(const Gs2::Formation::Model::FFormPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzForm>()
            ->WithName(Model->GetName())
            ->WithIndex(Model->GetIndex())
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