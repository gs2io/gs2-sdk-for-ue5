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

#include "Formation/Result/SetMoldCapacityByUserIdResult.h"

namespace Gs2::Formation::Result
{
    FSetMoldCapacityByUserIdResult::FSetMoldCapacityByUserIdResult():
        ItemValue(nullptr),
        OldValue(nullptr),
        MoldModelValue(nullptr)
    {
    }

    FSetMoldCapacityByUserIdResult::FSetMoldCapacityByUserIdResult(
        const FSetMoldCapacityByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        OldValue(From.OldValue),
        MoldModelValue(From.MoldModelValue)
    {
    }

    TSharedPtr<FSetMoldCapacityByUserIdResult> FSetMoldCapacityByUserIdResult::WithItem(
        const TSharedPtr<Model::FMold> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FSetMoldCapacityByUserIdResult> FSetMoldCapacityByUserIdResult::WithOld(
        const TSharedPtr<Model::FMold> Old
    )
    {
        this->OldValue = Old;
        return SharedThis(this);
    }

    TSharedPtr<FSetMoldCapacityByUserIdResult> FSetMoldCapacityByUserIdResult::WithMoldModel(
        const TSharedPtr<Model::FMoldModel> MoldModel
    )
    {
        this->MoldModelValue = MoldModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FMold> FSetMoldCapacityByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FMold> FSetMoldCapacityByUserIdResult::GetOld() const
    {
        if (!OldValue.IsValid())
        {
            return nullptr;
        }
        return OldValue;
    }

    TSharedPtr<Model::FMoldModel> FSetMoldCapacityByUserIdResult::GetMoldModel() const
    {
        if (!MoldModelValue.IsValid())
        {
            return nullptr;
        }
        return MoldModelValue;
    }

    TSharedPtr<FSetMoldCapacityByUserIdResult> FSetMoldCapacityByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetMoldCapacityByUserIdResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FMoldPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FMold::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithOld(Data->HasField(ANSI_TO_TCHAR("old")) ? [Data]() -> Model::FMoldPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("old")))
                    {
                        return nullptr;
                    }
                    return Model::FMold::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("old")));
                 }() : nullptr)
            ->WithMoldModel(Data->HasField(ANSI_TO_TCHAR("moldModel")) ? [Data]() -> Model::FMoldModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("moldModel")))
                    {
                        return nullptr;
                    }
                    return Model::FMoldModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("moldModel")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FSetMoldCapacityByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (OldValue != nullptr && OldValue.IsValid())
        {
            JsonRootObject->SetObjectField("old", OldValue->ToJson());
        }
        if (MoldModelValue != nullptr && MoldModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("moldModel", MoldModelValue->ToJson());
        }
        return JsonRootObject;
    }
}