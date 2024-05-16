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

#include "Quest/Result/GetProgressByUserIdResult.h"

namespace Gs2::Quest::Result
{
    FGetProgressByUserIdResult::FGetProgressByUserIdResult():
        ItemValue(nullptr),
        QuestGroupValue(nullptr),
        QuestValue(nullptr)
    {
    }

    FGetProgressByUserIdResult::FGetProgressByUserIdResult(
        const FGetProgressByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        QuestGroupValue(From.QuestGroupValue),
        QuestValue(From.QuestValue)
    {
    }

    TSharedPtr<FGetProgressByUserIdResult> FGetProgressByUserIdResult::WithItem(
        const TSharedPtr<Model::FProgress> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FGetProgressByUserIdResult> FGetProgressByUserIdResult::WithQuestGroup(
        const TSharedPtr<Model::FQuestGroupModel> QuestGroup
    )
    {
        this->QuestGroupValue = QuestGroup;
        return SharedThis(this);
    }

    TSharedPtr<FGetProgressByUserIdResult> FGetProgressByUserIdResult::WithQuest(
        const TSharedPtr<Model::FQuestModel> Quest
    )
    {
        this->QuestValue = Quest;
        return SharedThis(this);
    }

    TSharedPtr<Model::FProgress> FGetProgressByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FQuestGroupModel> FGetProgressByUserIdResult::GetQuestGroup() const
    {
        if (!QuestGroupValue.IsValid())
        {
            return nullptr;
        }
        return QuestGroupValue;
    }

    TSharedPtr<Model::FQuestModel> FGetProgressByUserIdResult::GetQuest() const
    {
        if (!QuestValue.IsValid())
        {
            return nullptr;
        }
        return QuestValue;
    }

    TSharedPtr<FGetProgressByUserIdResult> FGetProgressByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetProgressByUserIdResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FProgressPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FProgress::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithQuestGroup(Data->HasField(ANSI_TO_TCHAR("questGroup")) ? [Data]() -> Model::FQuestGroupModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("questGroup")))
                    {
                        return nullptr;
                    }
                    return Model::FQuestGroupModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("questGroup")));
                 }() : nullptr)
            ->WithQuest(Data->HasField(ANSI_TO_TCHAR("quest")) ? [Data]() -> Model::FQuestModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("quest")))
                    {
                        return nullptr;
                    }
                    return Model::FQuestModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("quest")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FGetProgressByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (QuestGroupValue != nullptr && QuestGroupValue.IsValid())
        {
            JsonRootObject->SetObjectField("questGroup", QuestGroupValue->ToJson());
        }
        if (QuestValue != nullptr && QuestValue.IsValid())
        {
            JsonRootObject->SetObjectField("quest", QuestValue->ToJson());
        }
        return JsonRootObject;
    }
}