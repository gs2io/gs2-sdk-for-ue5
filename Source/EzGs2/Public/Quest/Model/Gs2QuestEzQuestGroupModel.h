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
#include "Quest/Model/QuestGroupModel.h"
#include "Gs2QuestEzQuestModel.h"

namespace Gs2::UE5::Quest::Model
{
	class EZGS2_API FEzQuestGroupModel final : public TSharedFromThis<FEzQuestGroupModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzQuestModel>>> QuestsValue;
        TOptional<FString> ChallengePeriodEventIdValue;

	public:
        TSharedPtr<FEzQuestGroupModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzQuestGroupModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzQuestGroupModel> WithQuests(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzQuestModel>>> Quests);
        TSharedPtr<FEzQuestGroupModel> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzQuestModel>>> GetQuests() const;

        TOptional<FString> GetChallengePeriodEventId() const;

        Gs2::Quest::Model::FQuestGroupModelPtr ToModel() const;
        static TSharedPtr<FEzQuestGroupModel> FromModel(Gs2::Quest::Model::FQuestGroupModelPtr Model);
    };
    typedef TSharedPtr<FEzQuestGroupModel> FEzQuestGroupModelPtr;
}