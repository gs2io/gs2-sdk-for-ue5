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

#include "Guild/Result/IncreaseMaximumCurrentMaximumMemberCountByStampSheetResult.h"

namespace Gs2::Guild::Result
{
    FIncreaseMaximumCurrentMaximumMemberCountByStampSheetResult::FIncreaseMaximumCurrentMaximumMemberCountByStampSheetResult():
        ItemValue(nullptr)
    {
    }

    FIncreaseMaximumCurrentMaximumMemberCountByStampSheetResult::FIncreaseMaximumCurrentMaximumMemberCountByStampSheetResult(
        const FIncreaseMaximumCurrentMaximumMemberCountByStampSheetResult& From
    ):
        ItemValue(From.ItemValue)
    {
    }

    TSharedPtr<FIncreaseMaximumCurrentMaximumMemberCountByStampSheetResult> FIncreaseMaximumCurrentMaximumMemberCountByStampSheetResult::WithItem(
        const TSharedPtr<Model::FGuild> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<Model::FGuild> FIncreaseMaximumCurrentMaximumMemberCountByStampSheetResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<FIncreaseMaximumCurrentMaximumMemberCountByStampSheetResult> FIncreaseMaximumCurrentMaximumMemberCountByStampSheetResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FIncreaseMaximumCurrentMaximumMemberCountByStampSheetResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FGuildPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FGuild::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FIncreaseMaximumCurrentMaximumMemberCountByStampSheetResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        return JsonRootObject;
    }
}