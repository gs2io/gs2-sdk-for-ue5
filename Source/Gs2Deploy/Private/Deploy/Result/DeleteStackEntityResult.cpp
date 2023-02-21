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

#include "Deploy/Result/DeleteStackEntityResult.h"

namespace Gs2::Deploy::Result
{
    FDeleteStackEntityResult::FDeleteStackEntityResult():
        ItemValue(nullptr)
    {
    }

    FDeleteStackEntityResult::FDeleteStackEntityResult(
        const FDeleteStackEntityResult& From
    ):
        ItemValue(From.ItemValue)
    {
    }

    TSharedPtr<FDeleteStackEntityResult> FDeleteStackEntityResult::WithItem(
        const TSharedPtr<Model::FStack> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<Model::FStack> FDeleteStackEntityResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<FDeleteStackEntityResult> FDeleteStackEntityResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteStackEntityResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FStackPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FStack::FromJson(Data->GetObjectField("item"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FDeleteStackEntityResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        return JsonRootObject;
    }
}