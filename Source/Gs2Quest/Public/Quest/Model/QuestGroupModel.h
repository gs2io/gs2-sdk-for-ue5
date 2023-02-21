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
#include "QuestModel.h"

namespace Gs2::Quest::Model
{
    class GS2QUEST_API FQuestGroupModel final : public TSharedFromThis<FQuestGroupModel>
    {
        TOptional<FString> QuestGroupModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FQuestModel>>> QuestsValue;
        TOptional<FString> ChallengePeriodEventIdValue;

    public:
        FQuestGroupModel();
        FQuestGroupModel(
            const FQuestGroupModel& From
        );
        ~FQuestGroupModel() = default;

        TSharedPtr<FQuestGroupModel> WithQuestGroupModelId(const TOptional<FString> QuestGroupModelId);
        TSharedPtr<FQuestGroupModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FQuestGroupModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FQuestGroupModel> WithQuests(const TSharedPtr<TArray<TSharedPtr<FQuestModel>>> Quests);
        TSharedPtr<FQuestGroupModel> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);

        TOptional<FString> GetQuestGroupModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FQuestModel>>> GetQuests() const;
        TOptional<FString> GetChallengePeriodEventId() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetQuestGroupNameFromGrn(const FString Grn);

        static TSharedPtr<FQuestGroupModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FQuestGroupModel, ESPMode::ThreadSafe> FQuestGroupModelPtr;
}