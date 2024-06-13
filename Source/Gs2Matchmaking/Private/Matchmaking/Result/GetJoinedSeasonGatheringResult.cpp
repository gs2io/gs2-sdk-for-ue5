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

#include "Matchmaking/Result/GetJoinedSeasonGatheringResult.h"

namespace Gs2::Matchmaking::Result
{
    FGetJoinedSeasonGatheringResult::FGetJoinedSeasonGatheringResult():
        ItemValue(nullptr)
    {
    }

    FGetJoinedSeasonGatheringResult::FGetJoinedSeasonGatheringResult(
        const FGetJoinedSeasonGatheringResult& From
    ):
        ItemValue(From.ItemValue)
    {
    }

    TSharedPtr<FGetJoinedSeasonGatheringResult> FGetJoinedSeasonGatheringResult::WithItem(
        const TSharedPtr<Model::FJoinedSeasonGathering> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<Model::FJoinedSeasonGathering> FGetJoinedSeasonGatheringResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<FGetJoinedSeasonGatheringResult> FGetJoinedSeasonGatheringResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetJoinedSeasonGatheringResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FJoinedSeasonGatheringPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FJoinedSeasonGathering::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FGetJoinedSeasonGatheringResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        return JsonRootObject;
    }
}