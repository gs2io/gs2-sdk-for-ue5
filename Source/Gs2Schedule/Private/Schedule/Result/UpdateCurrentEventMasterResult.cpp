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

#include "Schedule/Result/UpdateCurrentEventMasterResult.h"

namespace Gs2::Schedule::Result
{
    FUpdateCurrentEventMasterResult::FUpdateCurrentEventMasterResult():
        ItemValue(nullptr)
    {
    }

    FUpdateCurrentEventMasterResult::FUpdateCurrentEventMasterResult(
        const FUpdateCurrentEventMasterResult& From
    ):
        ItemValue(From.ItemValue)
    {
    }

    TSharedPtr<FUpdateCurrentEventMasterResult> FUpdateCurrentEventMasterResult::WithItem(
        const TSharedPtr<Model::FCurrentEventMaster> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<Model::FCurrentEventMaster> FUpdateCurrentEventMasterResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<FUpdateCurrentEventMasterResult> FUpdateCurrentEventMasterResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateCurrentEventMasterResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FCurrentEventMasterPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FCurrentEventMaster::FromJson(Data->GetObjectField("item"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUpdateCurrentEventMasterResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        return JsonRootObject;
    }
}