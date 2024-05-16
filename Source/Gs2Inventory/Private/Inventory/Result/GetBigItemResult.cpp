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

#include "Inventory/Result/GetBigItemResult.h"

namespace Gs2::Inventory::Result
{
    FGetBigItemResult::FGetBigItemResult():
        ItemValue(nullptr),
        ItemModelValue(nullptr)
    {
    }

    FGetBigItemResult::FGetBigItemResult(
        const FGetBigItemResult& From
    ):
        ItemValue(From.ItemValue),
        ItemModelValue(From.ItemModelValue)
    {
    }

    TSharedPtr<FGetBigItemResult> FGetBigItemResult::WithItem(
        const TSharedPtr<Model::FBigItem> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FGetBigItemResult> FGetBigItemResult::WithItemModel(
        const TSharedPtr<Model::FBigItemModel> ItemModel
    )
    {
        this->ItemModelValue = ItemModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FBigItem> FGetBigItemResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FBigItemModel> FGetBigItemResult::GetItemModel() const
    {
        if (!ItemModelValue.IsValid())
        {
            return nullptr;
        }
        return ItemModelValue;
    }

    TSharedPtr<FGetBigItemResult> FGetBigItemResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetBigItemResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FBigItemPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FBigItem::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithItemModel(Data->HasField(ANSI_TO_TCHAR("itemModel")) ? [Data]() -> Model::FBigItemModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("itemModel")))
                    {
                        return nullptr;
                    }
                    return Model::FBigItemModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("itemModel")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FGetBigItemResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (ItemModelValue != nullptr && ItemModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("itemModel", ItemModelValue->ToJson());
        }
        return JsonRootObject;
    }
}