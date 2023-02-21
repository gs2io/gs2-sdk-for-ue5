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

#include "Formation/Result/DeleteFormResult.h"

namespace Gs2::Formation::Result
{
    FDeleteFormResult::FDeleteFormResult():
        ItemValue(nullptr),
        MoldValue(nullptr),
        MoldModelValue(nullptr),
        FormModelValue(nullptr)
    {
    }

    FDeleteFormResult::FDeleteFormResult(
        const FDeleteFormResult& From
    ):
        ItemValue(From.ItemValue),
        MoldValue(From.MoldValue),
        MoldModelValue(From.MoldModelValue),
        FormModelValue(From.FormModelValue)
    {
    }

    TSharedPtr<FDeleteFormResult> FDeleteFormResult::WithItem(
        const TSharedPtr<Model::FForm> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteFormResult> FDeleteFormResult::WithMold(
        const TSharedPtr<Model::FMold> Mold
    )
    {
        this->MoldValue = Mold;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteFormResult> FDeleteFormResult::WithMoldModel(
        const TSharedPtr<Model::FMoldModel> MoldModel
    )
    {
        this->MoldModelValue = MoldModel;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteFormResult> FDeleteFormResult::WithFormModel(
        const TSharedPtr<Model::FFormModel> FormModel
    )
    {
        this->FormModelValue = FormModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FForm> FDeleteFormResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FMold> FDeleteFormResult::GetMold() const
    {
        if (!MoldValue.IsValid())
        {
            return nullptr;
        }
        return MoldValue;
    }

    TSharedPtr<Model::FMoldModel> FDeleteFormResult::GetMoldModel() const
    {
        if (!MoldModelValue.IsValid())
        {
            return nullptr;
        }
        return MoldModelValue;
    }

    TSharedPtr<Model::FFormModel> FDeleteFormResult::GetFormModel() const
    {
        if (!FormModelValue.IsValid())
        {
            return nullptr;
        }
        return FormModelValue;
    }

    TSharedPtr<FDeleteFormResult> FDeleteFormResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteFormResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FFormPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FForm::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithMold(Data->HasField("mold") ? [Data]() -> Model::FMoldPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("mold"))
                    {
                        return nullptr;
                    }
                    return Model::FMold::FromJson(Data->GetObjectField("mold"));
                 }() : nullptr)
            ->WithMoldModel(Data->HasField("moldModel") ? [Data]() -> Model::FMoldModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("moldModel"))
                    {
                        return nullptr;
                    }
                    return Model::FMoldModel::FromJson(Data->GetObjectField("moldModel"));
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

    TSharedPtr<FJsonObject> FDeleteFormResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (MoldValue != nullptr && MoldValue.IsValid())
        {
            JsonRootObject->SetObjectField("mold", MoldValue->ToJson());
        }
        if (MoldModelValue != nullptr && MoldModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("moldModel", MoldModelValue->ToJson());
        }
        if (FormModelValue != nullptr && FormModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("formModel", FormModelValue->ToJson());
        }
        return JsonRootObject;
    }
}