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

#include "Enhance/Model/Gs2EnhanceEzUnleashMaterialSelection.h"

namespace Gs2::UE5::Enhance::Model
{

    TSharedPtr<FEzUnleashMaterialSelection> FEzUnleashMaterialSelection::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashMaterialSelection> FEzUnleashMaterialSelection::WithItemSetIds(
        const TSharedPtr<TArray<FString>> ItemSetIds
    )
    {
        this->ItemSetIdsValue = ItemSetIds;
        return SharedThis(this);
    }
    TOptional<FString> FEzUnleashMaterialSelection::GetName() const
    {
        return NameValue;
    }
    TSharedPtr<TArray<FString>> FEzUnleashMaterialSelection::GetItemSetIds() const
    {
        return ItemSetIdsValue;
    }

    Gs2::Enhance::Model::FUnleashMaterialSelectionPtr FEzUnleashMaterialSelection::ToModel() const
    {
        return MakeShared<Gs2::Enhance::Model::FUnleashMaterialSelection>()
            ->WithName(NameValue)
            ->WithItemSetIds(ItemSetIdsValue);
    }

    TSharedPtr<FEzUnleashMaterialSelection> FEzUnleashMaterialSelection::FromModel(const Gs2::Enhance::Model::FUnleashMaterialSelectionPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzUnleashMaterialSelection>()
            ->WithName(Model->GetName())
            ->WithItemSetIds(Model->GetItemSetIds());
    }
}