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

#include "Quest/Result/GetProgressResult.h"

namespace Gs2::Quest::Result
{
    FGetProgressResult::FGetProgressResult():
        ItemValue(nullptr),
        QuestGroupValue(nullptr),
        QuestValue(nullptr)
    {
    }

    FGetProgressResult::FGetProgressResult(
        const FGetProgressResult& From
    ):
        ItemValue(From.ItemValue),
        QuestGroupValue(From.QuestGroupValue),
        QuestValue(From.QuestValue)
    {
    }

    TSharedPtr<FGetProgressResult> FGetProgressResult::WithItem(
        const TSharedPtr<Model::FProgress> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FGetProgressResult> FGetProgressResult::WithQuestGroup(
        const TSharedPtr<Model::FQuestGroupModel> QuestGroup
    )
    {
        this->QuestGroupValue = QuestGroup;
        return SharedThis(this);
    }

    TSharedPtr<FGetProgressResult> FGetProgressResult::WithQuest(
        const TSharedPtr<Model::FQuestModel> Quest
    )
    {
        this->QuestValue = Quest;
        return SharedThis(this);
    }

    TSharedPtr<Model::FProgress> FGetProgressResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FQuestGroupModel> FGetProgressResult::GetQuestGroup() const
    {
        if (!QuestGroupValue.IsValid())
        {
            return nullptr;
        }
        return QuestGroupValue;
    }

    TSharedPtr<Model::FQuestModel> FGetProgressResult::GetQuest() const
    {
        if (!QuestValue.IsValid())
        {
            return nullptr;
        }
        return QuestValue;
    }

    TSharedPtr<FGetProgressResult> FGetProgressResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetProgressResult>()
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

    TSharedPtr<FJsonObject> FGetProgressResult::ToJson() const
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