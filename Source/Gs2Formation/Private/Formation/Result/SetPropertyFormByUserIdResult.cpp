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

#include "Formation/Result/SetPropertyFormByUserIdResult.h"

namespace Gs2::Formation::Result
{
    FSetPropertyFormByUserIdResult::FSetPropertyFormByUserIdResult():
        ItemValue(nullptr),
        PropertyFormModelValue(nullptr)
    {
    }

    FSetPropertyFormByUserIdResult::FSetPropertyFormByUserIdResult(
        const FSetPropertyFormByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        PropertyFormModelValue(From.PropertyFormModelValue)
    {
    }

    TSharedPtr<FSetPropertyFormByUserIdResult> FSetPropertyFormByUserIdResult::WithItem(
        const TSharedPtr<Model::FPropertyForm> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FSetPropertyFormByUserIdResult> FSetPropertyFormByUserIdResult::WithPropertyFormModel(
        const TSharedPtr<Model::FPropertyFormModel> PropertyFormModel
    )
    {
        this->PropertyFormModelValue = PropertyFormModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FPropertyForm> FSetPropertyFormByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FPropertyFormModel> FSetPropertyFormByUserIdResult::GetPropertyFormModel() const
    {
        if (!PropertyFormModelValue.IsValid())
        {
            return nullptr;
        }
        return PropertyFormModelValue;
    }

    TSharedPtr<FSetPropertyFormByUserIdResult> FSetPropertyFormByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetPropertyFormByUserIdResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FPropertyFormPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FPropertyForm::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithPropertyFormModel(Data->HasField(ANSI_TO_TCHAR("propertyFormModel")) ? [Data]() -> Model::FPropertyFormModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("propertyFormModel")))
                    {
                        return nullptr;
                    }
                    return Model::FPropertyFormModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("propertyFormModel")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FSetPropertyFormByUserIdResult::ToJson() const
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