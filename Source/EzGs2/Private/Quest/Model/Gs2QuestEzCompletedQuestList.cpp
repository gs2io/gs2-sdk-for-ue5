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

#include "EzGs2/Public/Quest/Model/Gs2QuestEzCompletedQuestList.h"

namespace Gs2::UE5::Quest::Model
{

    TSharedPtr<FEzCompletedQuestList> FEzCompletedQuestList::WithQuestGroupName(
        const TOptional<FString> QuestGroupName
    )
    {
        this->QuestGroupNameValue = QuestGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FEzCompletedQuestList> FEzCompletedQuestList::WithCompleteQuestNames(
        const TSharedPtr<TArray<FString>> CompleteQuestNames
    )
    {
        this->CompleteQuestNamesValue = CompleteQuestNames;
        return SharedThis(this);
    }
    TOptional<FString> FEzCompletedQuestList::GetQuestGroupName() const
    {
        return QuestGroupNameValue;
    }
    TSharedPtr<TArray<FString>> FEzCompletedQuestList::GetCompleteQuestNames() const
    {
        return CompleteQuestNamesValue;
    }

    Gs2::Quest::Model::FCompletedQuestListPtr FEzCompletedQuestList::ToModel() const
    {
        return MakeShared<Gs2::Quest::Model::FCompletedQuestList>()
            ->WithQuestGroupName(QuestGroupNameValue)
            ->WithCompleteQuestNames(CompleteQuestNamesValue);
    }

    TSharedPtr<FEzCompletedQuestList> FEzCompletedQuestList::FromModel(const Gs2::Quest::Model::FCompletedQuestListPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzCompletedQuestList>()
            ->WithQuestGroupName(Model->GetQuestGroupName())
            ->WithCompleteQuestNames(Model->GetCompleteQuestNames());
    }
}