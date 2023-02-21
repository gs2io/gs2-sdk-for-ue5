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

#include "Formation/Result/AddCapacityByStampSheetResult.h"

namespace Gs2::Formation::Result
{
    FAddCapacityByStampSheetResult::FAddCapacityByStampSheetResult():
        ItemValue(nullptr),
        MoldModelValue(nullptr)
    {
    }

    FAddCapacityByStampSheetResult::FAddCapacityByStampSheetResult(
        const FAddCapacityByStampSheetResult& From
    ):
        ItemValue(From.ItemValue),
        MoldModelValue(From.MoldModelValue)
    {
    }

    TSharedPtr<FAddCapacityByStampSheetResult> FAddCapacityByStampSheetResult::WithItem(
        const TSharedPtr<Model::FMold> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FAddCapacityByStampSheetResult> FAddCapacityByStampSheetResult::WithMoldModel(
        const TSharedPtr<Model::FMoldModel> MoldModel
    )
    {
        this->MoldModelValue = MoldModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FMold> FAddCapacityByStampSheetResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FMoldModel> FAddCapacityByStampSheetResult::GetMoldModel() const
    {
        if (!MoldModelValue.IsValid())
        {
            return nullptr;
        }
        return MoldModelValue;
    }

    TSharedPtr<FAddCapacityByStampSheetResult> FAddCapacityByStampSheetResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAddCapacityByStampSheetResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FMoldPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FMold::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithMoldModel(Data->HasField("moldModel") ? [Data]() -> Model::FMoldModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("moldModel"))
                    {
                        return nullptr;
                    }
                    return Model::FMoldModel::FromJson(Data->GetObjectField("moldModel"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FAddCapacityByStampSheetResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (MoldModelValue != nullptr && MoldModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("moldModel", MoldModelValue->ToJson());
        }
        return JsonRootObject;
    }
}