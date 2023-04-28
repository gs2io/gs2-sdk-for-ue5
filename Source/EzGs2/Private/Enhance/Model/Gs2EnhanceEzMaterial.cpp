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

#include "EzGs2/Public/Enhance/Model/Gs2EnhanceEzMaterial.h"

namespace Gs2::UE5::Enhance::Model
{

    TSharedPtr<FEzMaterial> FEzMaterial::WithMaterialItemSetId(
        const TOptional<FString> MaterialItemSetId
    )
    {
        this->MaterialItemSetIdValue = MaterialItemSetId;
        return SharedThis(this);
    }

    TSharedPtr<FEzMaterial> FEzMaterial::WithCount(
        const TOptional<int32> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }
    TOptional<FString> FEzMaterial::GetMaterialItemSetId() const
    {
        return MaterialItemSetIdValue;
    }
    TOptional<int32> FEzMaterial::GetCount() const
    {
        return CountValue;
    }

    FString FEzMaterial::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountValue.GetValue());
    }

    Gs2::Enhance::Model::FMaterialPtr FEzMaterial::ToModel() const
    {
        return MakeShared<Gs2::Enhance::Model::FMaterial>()
            ->WithMaterialItemSetId(MaterialItemSetIdValue)
            ->WithCount(CountValue);
    }

    TSharedPtr<FEzMaterial> FEzMaterial::FromModel(const Gs2::Enhance::Model::FMaterialPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzMaterial>()
            ->WithMaterialItemSetId(Model->GetMaterialItemSetId())
            ->WithCount(Model->GetCount());
    }
}