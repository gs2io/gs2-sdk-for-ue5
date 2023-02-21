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
#include "Contents.h"
#include "AcquireAction.h"
#include "ConsumeAction.h"

namespace Gs2::Quest::Model
{
    class GS2QUEST_API FQuestModel final : public TSharedFromThis<FQuestModel>
    {
        TOptional<FString> QuestModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FContents>>> ContentsValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> FirstCompleteAcquireActionsValue;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> FailedAcquireActionsValue;
        TSharedPtr<TArray<FString>> PremiseQuestNamesValue;

    public:
        FQuestModel();
        FQuestModel(
            const FQuestModel& From
        );
        ~FQuestModel() = default;

        TSharedPtr<FQuestModel> WithQuestModelId(const TOptional<FString> QuestModelId);
        TSharedPtr<FQuestModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FQuestModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FQuestModel> WithContents(const TSharedPtr<TArray<TSharedPtr<FContents>>> Contents);
        TSharedPtr<FQuestModel> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);
        TSharedPtr<FQuestModel> WithFirstCompleteAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> FirstCompleteAcquireActions);
        TSharedPtr<FQuestModel> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ConsumeActions);
        TSharedPtr<FQuestModel> WithFailedAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> FailedAcquireActions);
        TSharedPtr<FQuestModel> WithPremiseQuestNames(const TSharedPtr<TArray<FString>> PremiseQuestNames);

        TOptional<FString> GetQuestModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FContents>>> GetContents() const;
        TOptional<FString> GetChallengePeriodEventId() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetFirstCompleteAcquireActions() const;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> GetConsumeActions() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetFailedAcquireActions() const;
        TSharedPtr<TArray<FString>> GetPremiseQuestNames() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetQuestGroupNameFromGrn(const FString Grn);
        static TOptional<FString> GetQuestNameFromGrn(const FString Grn);

        static TSharedPtr<FQuestModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FQuestModel, ESPMode::ThreadSafe> FQuestModelPtr;
}