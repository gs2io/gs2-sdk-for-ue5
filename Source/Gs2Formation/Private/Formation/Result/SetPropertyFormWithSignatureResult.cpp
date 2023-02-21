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

#include "Formation/Result/SetPropertyFormWithSignatureResult.h"

namespace Gs2::Formation::Result
{
    FSetPropertyFormWithSignatureResult::FSetPropertyFormWithSignatureResult():
        ItemValue(nullptr),
        FormModelValue(nullptr)
    {
    }

    FSetPropertyFormWithSignatureResult::FSetPropertyFormWithSignatureResult(
        const FSetPropertyFormWithSignatureResult& From
    ):
        ItemValue(From.ItemValue),
        FormModelValue(From.FormModelValue)
    {
    }

    TSharedPtr<FSetPropertyFormWithSignatureResult> FSetPropertyFormWithSignatureResult::WithItem(
        const TSharedPtr<Model::FPropertyForm> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FSetPropertyFormWithSignatureResult> FSetPropertyFormWithSignatureResult::WithFormModel(
        const TSharedPtr<Model::FFormModel> FormModel
    )
    {
        this->FormModelValue = FormModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FPropertyForm> FSetPropertyFormWithSignatureResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FFormModel> FSetPropertyFormWithSignatureResult::GetFormModel() const
    {
        if (!FormModelValue.IsValid())
        {
            return nullptr;
        }
        return FormModelValue;
    }

    TSharedPtr<FSetPropertyFormWithSignatureResult> FSetPropertyFormWithSignatureResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetPropertyFormWithSignatureResult>()
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

    TSharedPtr<FJsonObject> FSetPropertyFormWithSignatureResult::ToJson() const
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