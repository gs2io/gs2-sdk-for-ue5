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

#include "Formation/Result/GetPropertyFormByUserIdResult.h"

namespace Gs2::Formation::Result
{
    FGetPropertyFormByUserIdResult::FGetPropertyFormByUserIdResult():
        ItemValue(nullptr),
        PropertyFormModelValue(nullptr)
    {
    }

    FGetPropertyFormByUserIdResult::FGetPropertyFormByUserIdResult(
        const FGetPropertyFormByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        PropertyFormModelValue(From.PropertyFormModelValue)
    {
    }

    TSharedPtr<FGetPropertyFormByUserIdResult> FGetPropertyFormByUserIdResult::WithItem(
        const TSharedPtr<Model::FPropertyForm> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FGetPropertyFormByUserIdResult> FGetPropertyFormByUserIdResult::WithPropertyFormModel(
        const TSharedPtr<Model::FPropertyFormModel> PropertyFormModel
    )
    {
        this->PropertyFormModelValue = PropertyFormModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FPropertyForm> FGetPropertyFormByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FPropertyFormModel> FGetPropertyFormByUserIdResult::GetPropertyFormModel() const
    {
        if (!PropertyFormModelValue.IsValid())
        {
            return nullptr;
        }
        return PropertyFormModelValue;
    }

    TSharedPtr<FGetPropertyFormByUserIdResult> FGetPropertyFormByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetPropertyFormByUserIdResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FPropertyFormPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FPropertyForm::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithPropertyFormModel(Data->HasField("propertyFormModel") ? [Data]() -> Model::FPropertyFormModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("propertyFormModel"))
                    {
                        return nullptr;
                    }
                    return Model::FPropertyFormModel::FromJson(Data->GetObjectField("propertyFormModel"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FGetPropertyFormByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (PropertyFormModelValue != nullptr && PropertyFormModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("propertyFormModel", PropertyFormModelValue->ToJson());
        }
        return JsonRootObject;
    }
}