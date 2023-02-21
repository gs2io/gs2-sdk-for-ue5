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

#include "Exchange/Result/DeleteAwaitResult.h"

namespace Gs2::Exchange::Result
{
    FDeleteAwaitResult::FDeleteAwaitResult():
        ItemValue(nullptr)
    {
    }

    FDeleteAwaitResult::FDeleteAwaitResult(
        const FDeleteAwaitResult& From
    ):
        ItemValue(From.ItemValue)
    {
    }

    TSharedPtr<FDeleteAwaitResult> FDeleteAwaitResult::WithItem(
        const TSharedPtr<Model::FAwait> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<Model::FAwait> FDeleteAwaitResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<FDeleteAwaitResult> FDeleteAwaitResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteAwaitResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FAwaitPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FAwait::FromJson(Data->GetObjectField("item"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FDeleteAwaitResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        return JsonRootObject;
    }
}