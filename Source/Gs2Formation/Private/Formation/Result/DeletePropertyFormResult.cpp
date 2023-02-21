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

#include "Formation/Result/DeletePropertyFormResult.h"

namespace Gs2::Formation::Result
{
    FDeletePropertyFormResult::FDeletePropertyFormResult():
        ItemValue(nullptr),
        FormModelValue(nullptr)
    {
    }

    FDeletePropertyFormResult::FDeletePropertyFormResult(
        const FDeletePropertyFormResult& From
    ):
        ItemValue(From.ItemValue),
        FormModelValue(From.FormModelValue)
    {
    }

    TSharedPtr<FDeletePropertyFormResult> FDeletePropertyFormResult::WithItem(
        const TSharedPtr<Model::FPropertyForm> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FDeletePropertyFormResult> FDeletePropertyFormResult::WithFormModel(
        const TSharedPtr<Model::FFormModel> FormModel
    )
    {
        this->FormModelValue = FormModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FPropertyForm> FDeletePropertyFormResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FFormModel> FDeletePropertyFormResult::GetFormModel() const
    {
        if (!FormModelValue.IsValid())
        {
            return nullptr;
        }
        return FormModelValue;
    }

    TSharedPtr<FDeletePropertyFormResult> FDeletePropertyFormResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeletePropertyFormResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FPropertyFormPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FPropertyForm::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithFormModel(Data->HasField("formModel") ? [Data]() -> Model::FFormModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("formModel"))
                    {
                        return nullptr;
                    }
                    return Model::FFormModel::FromJson(Data->GetObjectField("formModel"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FDeletePropertyFormResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (FormModelValue != nullptr && FormModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("formModel", FormModelValue->ToJson());
        }
        return JsonRootObject;
    }
}