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

#include "Enhance/Model/Gs2EnhanceEzUnleashQuantityMaterialSetting.h"

namespace Gs2::UE5::Enhance::Model
{

    TSharedPtr<FEzUnleashQuantityMaterialSetting> FEzUnleashQuantityMaterialSetting::WithMatchType(
        const TOptional<FString> MatchType
    )
    {
        this->MatchTypeValue = MatchType;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashQuantityMaterialSetting> FEzUnleashQuantityMaterialSetting::WithMaterialInventoryModelId(
        const TOptional<FString> MaterialInventoryModelId
    )
    {
        this->MaterialInventoryModelIdValue = MaterialInventoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashQuantityMaterialSetting> FEzUnleashQuantityMaterialSetting::WithItemModelId(
        const TOptional<FString> ItemModelId
    )
    {
        this->ItemModelIdValue = ItemModelId;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashQuantityMaterialSetting> FEzUnleashQuantityMaterialSetting::WithCount(
        const TOptional<int32> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }
    TOptional<FString> FEzUnleashQuantityMaterialSetting::GetMatchType() const
    {
        return MatchTypeValue;
    }
    TOptional<FString> FEzUnleashQuantityMaterialSetting::GetMaterialInventoryModelId() const
    {
        return MaterialInventoryModelIdValue;
    }
    TOptional<FString> FEzUnleashQuantityMaterialSetting::GetItemModelId() const
    {
        return ItemModelIdValue;
    }
    TOptional<int32> FEzUnleashQuantityMaterialSetting::GetCount() const
    {
        return CountValue;
    }

    FString FEzUnleashQuantityMaterialSetting::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountValue.GetValue());
    }

    Gs2::Enhance::Model::FUnleashQuantityMaterialSettingPtr FEzUnleashQuantityMaterialSetting::ToModel() const
    {
        return MakeShared<Gs2::Enhance::Model::FUnleashQuantityMaterialSetting>()
            ->WithMatchType(MatchTypeValue)
            ->WithMaterialInventoryModelId(MaterialInventoryModelIdValue)
            ->WithItemModelId(ItemModelIdValue)
            ->WithCount(CountValue);
    }

    TSharedPtr<FEzUnleashQuantityMaterialSetting> FEzUnleashQuantityMaterialSetting::FromModel(const Gs2::Enhance::Model::FUnleashQuantityMaterialSettingPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzUnleashQuantityMaterialSetting>()
            ->WithMatchType(Model->GetMatchType())
            ->WithMaterialInventoryModelId(Model->GetMaterialInventoryModelId())
            ->WithItemModelId(Model->GetItemModelId())
            ->WithCount(Model->GetCount());
    }
}