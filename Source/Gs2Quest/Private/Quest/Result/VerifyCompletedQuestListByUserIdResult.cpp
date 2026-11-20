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

#include "Quest/Result/VerifyCompletedQuestListByUserIdResult.h"

namespace Gs2::Quest::Result
{
    FVerifyCompletedQuestListByUserIdResult::FVerifyCompletedQuestListByUserIdResult():
        ItemValue(nullptr)
    {
    }

    FVerifyCompletedQuestListByUserIdResult::FVerifyCompletedQuestListByUserIdResult(
        const FVerifyCompletedQuestListByUserIdResult& From
    ):
        ItemValue(From.ItemValue)
    {
    }

    TSharedPtr<FVerifyCompletedQuestListByUserIdResult> FVerifyCompletedQuestListByUserIdResult::WithItem(
        const TSharedPtr<Model::FCompletedQuestList> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<Model::FCompletedQuestList> FVerifyCompletedQuestListByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<FVerifyCompletedQuestListByUserIdResult> FVerifyCompletedQuestListByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyCompletedQuestListByUserIdResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FCompletedQuestListPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FCompletedQuestList::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FVerifyCompletedQuestListByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("item"), ItemValue->ToJson());
        }
        return JsonRootObject;
    }
}