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

#include "Formation/Result/SetFormByUserIdResult.h"

namespace Gs2::Formation::Result
{
    FSetFormByUserIdResult::FSetFormByUserIdResult():
        ItemValue(nullptr),
        MoldValue(nullptr),
        MoldModelValue(nullptr),
        FormModelValue(nullptr)
    {
    }

    FSetFormByUserIdResult::FSetFormByUserIdResult(
        const FSetFormByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        MoldValue(From.MoldValue),
        MoldModelValue(From.MoldModelValue),
        FormModelValue(From.FormModelValue)
    {
    }

    TSharedPtr<FSetFormByUserIdResult> FSetFormByUserIdResult::WithItem(
        const TSharedPtr<Model::FForm> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FSetFormByUserIdResult> FSetFormByUserIdResult::WithMold(
        const TSharedPtr<Model::FMold> Mold
    )
    {
        this->MoldValue = Mold;
        return SharedThis(this);
    }

    TSharedPtr<FSetFormByUserIdResult> FSetFormByUserIdResult::WithMoldModel(
        const TSharedPtr<Model::FMoldModel> MoldModel
    )
    {
        this->MoldModelValue = MoldModel;
        return SharedThis(this);
    }

    TSharedPtr<FSetFormByUserIdResult> FSetFormByUserIdResult::WithFormModel(
        const TSharedPtr<Model::FFormModel> FormModel
    )
    {
        this->FormModelValue = FormModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FForm> FSetFormByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FMold> FSetFormByUserIdResult::GetMold() const
    {
        if (!MoldValue.IsValid())
        {
            return nullptr;
        }
        return MoldValue;
    }

    TSharedPtr<Model::FMoldModel> FSetFormByUserIdResult::GetMoldModel() const
    {
        if (!MoldModelValue.IsValid())
        {
            return nullptr;
        }
        return MoldModelValue;
    }

    TSharedPtr<Model::FFormModel> FSetFormByUserIdResult::GetFormModel() const
    {
        if (!FormModelValue.IsValid())
        {
            return nullptr;
        }
        return FormModelValue;
    }

    TSharedPtr<FSetFormByUserIdResult> FSetFormByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetFormByUserIdResult>()
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

    TSharedPtr<FJsonObject> FSetFormByUserIdResult::ToJson() const
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