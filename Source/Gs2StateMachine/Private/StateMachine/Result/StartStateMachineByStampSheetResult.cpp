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

#include "StateMachine/Result/StartStateMachineByStampSheetResult.h"

namespace Gs2::StateMachine::Result
{
    FStartStateMachineByStampSheetResult::FStartStateMachineByStampSheetResult():
        ItemValue(nullptr)
    {
    }

    FStartStateMachineByStampSheetResult::FStartStateMachineByStampSheetResult(
        const FStartStateMachineByStampSheetResult& From
    ):
        ItemValue(From.ItemValue)
    {
    }

    TSharedPtr<FStartStateMachineByStampSheetResult> FStartStateMachineByStampSheetResult::WithItem(
        const TSharedPtr<Model::FStatus> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<Model::FStatus> FStartStateMachineByStampSheetResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<FStartStateMachineByStampSheetResult> FStartStateMachineByStampSheetResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FStartStateMachineByStampSheetResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FStatus::FromJson(Data->GetObjectField("item"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FStartStateMachineByStampSheetResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        return JsonRootObject;
    }
}