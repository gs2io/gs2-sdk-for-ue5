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

#pragma once

#include "CoreMinimal.h"
#include "Quest/Model/CompletedQuestList.h"

namespace Gs2::UE5::Quest::Model
{
	class EZGS2_API FEzCompletedQuestList final : public TSharedFromThis<FEzCompletedQuestList>
	{
        TOptional<FString> QuestGroupNameValue;
        TSharedPtr<TArray<FString>> CompleteQuestNamesValue;

	public:
        TSharedPtr<FEzCompletedQuestList> WithQuestGroupName(const TOptional<FString> QuestGroupName);
        TSharedPtr<FEzCompletedQuestList> WithCompleteQuestNames(const TSharedPtr<TArray<FString>> CompleteQuestNames);

        TOptional<FString> GetQuestGroupName() const;

        TSharedPtr<TArray<FString>> GetCompleteQuestNames() const;

        Gs2::Quest::Model::FCompletedQuestListPtr ToModel() const;
        static TSharedPtr<FEzCompletedQuestList> FromModel(Gs2::Quest::Model::FCompletedQuestListPtr Model);
    };
    typedef TSharedPtr<FEzCompletedQuestList> FEzCompletedQuestListPtr;
}