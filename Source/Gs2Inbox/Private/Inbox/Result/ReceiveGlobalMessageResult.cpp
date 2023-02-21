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

#include "Inbox/Result/ReceiveGlobalMessageResult.h"

namespace Gs2::Inbox::Result
{
    FReceiveGlobalMessageResult::FReceiveGlobalMessageResult():
        ItemValue(nullptr)
    {
    }

    FReceiveGlobalMessageResult::FReceiveGlobalMessageResult(
        const FReceiveGlobalMessageResult& From
    ):
        ItemValue(From.ItemValue)
    {
    }

    TSharedPtr<FReceiveGlobalMessageResult> FReceiveGlobalMessageResult::WithItem(
        const TSharedPtr<TArray<TSharedPtr<Model::FMessage>>> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FMessage>>> FReceiveGlobalMessageResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<FReceiveGlobalMessageResult> FReceiveGlobalMessageResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FReceiveGlobalMessageResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> TSharedPtr<TArray<Model::FMessagePtr>>
                 {
                    auto v = MakeShared<TArray<Model::FMessagePtr>>();
                    if (!Data->HasTypedField<EJson::Null>("item") && Data->HasTypedField<EJson::Array>("item"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("item"))
                        {
                            v->Add(Model::FMessage::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FReceiveGlobalMessageResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ItemValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("item", v);
        }
        return JsonRootObject;
    }
}