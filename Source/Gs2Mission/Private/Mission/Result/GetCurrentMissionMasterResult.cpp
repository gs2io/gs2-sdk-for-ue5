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

#include "Mission/Result/GetCurrentMissionMasterResult.h"

namespace Gs2::Mission::Result
{
    FGetCurrentMissionMasterResult::FGetCurrentMissionMasterResult():
        ItemValue(nullptr)
    {
    }

    FGetCurrentMissionMasterResult::FGetCurrentMissionMasterResult(
        const FGetCurrentMissionMasterResult& From
    ):
        ItemValue(From.ItemValue)
    {
    }

    TSharedPtr<FGetCurrentMissionMasterResult> FGetCurrentMissionMasterResult::WithItem(
        const TSharedPtr<Model::FCurrentMissionMaster> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<Model::FCurrentMissionMaster> FGetCurrentMissionMasterResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<FGetCurrentMissionMasterResult> FGetCurrentMissionMasterResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetCurrentMissionMasterResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FCurrentMissionMasterPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FCurrentMissionMaster::FromJson(Data->GetObjectField("item"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FGetCurrentMissionMasterResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        return JsonRootObject;
    }
}