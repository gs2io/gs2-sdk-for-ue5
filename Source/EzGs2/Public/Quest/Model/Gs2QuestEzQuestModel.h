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
#include "Quest/Model/QuestModel.h"
#include "Gs2QuestEzContents.h"
#include "Gs2QuestEzAcquireAction.h"
#include "Gs2QuestEzConsumeAction.h"
#include "Gs2QuestEzAcquireAction.h"

namespace Gs2::UE5::Quest::Model
{
	class EZGS2_API FEzQuestModel final : public TSharedFromThis<FEzQuestModel>
	{
        TOptional<FString> QuestModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzContents>>> ContentsValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzAcquireAction>>> FirstCompleteAcquireActionsValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConsumeAction>>> ConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzAcquireAction>>> FailedAcquireActionsValue;
        TSharedPtr<TArray<FString>> PremiseQuestNamesValue;

	public:
        TSharedPtr<FEzQuestModel> WithQuestModelId(const TOptional<FString> QuestModelId);
        TSharedPtr<FEzQuestModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzQuestModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzQuestModel> WithContents(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzContents>>> Contents);
        TSharedPtr<FEzQuestModel> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);
        TSharedPtr<FEzQuestModel> WithFirstCompleteAcquireActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzAcquireAction>>> FirstCompleteAcquireActions);
        TSharedPtr<FEzQuestModel> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConsumeAction>>> ConsumeActions);
        TSharedPtr<FEzQuestModel> WithFailedAcquireActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzAcquireAction>>> FailedAcquireActions);
        TSharedPtr<FEzQuestModel> WithPremiseQuestNames(const TSharedPtr<TArray<FString>> PremiseQuestNames);

        TOptional<FString> GetQuestModelId() const;

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzContents>>> GetContents() const;

        TOptional<FString> GetChallengePeriodEventId() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzAcquireAction>>> GetFirstCompleteAcquireActions() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConsumeAction>>> GetConsumeActions() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzAcquireAction>>> GetFailedAcquireActions() const;

        TSharedPtr<TArray<FString>> GetPremiseQuestNames() const;

        Gs2::Quest::Model::FQuestModelPtr ToModel() const;
        static TSharedPtr<FEzQuestModel> FromModel(Gs2::Quest::Model::FQuestModelPtr Model);
    };
    typedef TSharedPtr<FEzQuestModel> FEzQuestModelPtr;
}