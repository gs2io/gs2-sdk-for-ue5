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

#include "MegaField/Result/GetAreaModelMasterResult.h"

namespace Gs2::MegaField::Result
{
    FGetAreaModelMasterResult::FGetAreaModelMasterResult():
        ItemValue(nullptr)
    {
    }

    FGetAreaModelMasterResult::FGetAreaModelMasterResult(
        const FGetAreaModelMasterResult& From
    ):
        ItemValue(From.ItemValue)
    {
    }

    TSharedPtr<FGetAreaModelMasterResult> FGetAreaModelMasterResult::WithItem(
        const TSharedPtr<Model::FAreaModelMaster> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<Model::FAreaModelMaster> FGetAreaModelMasterResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<FGetAreaModelMasterResult> FGetAreaModelMasterResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetAreaModelMasterResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FAreaModelMasterPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FAreaModelMaster::FromJson(Data->GetObjectField("item"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FGetAreaModelMasterResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        return JsonRootObject;
    }
}