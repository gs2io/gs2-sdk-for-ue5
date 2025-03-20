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
#include "Core/Gs2Object.h"
#include "Contents.h"
#include "AcquireAction.h"
#include "VerifyAction.h"
#include "ConsumeAction.h"

namespace Gs2::Quest::Model
{
    class GS2QUEST_API FQuestModelMaster final : public FGs2Object, public TSharedFromThis<FQuestModelMaster>
    {
        TOptional<FString> QuestModelIdValue;
        TOptional<FString> QuestGroupNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FContents>>> ContentsValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> FirstCompleteAcquireActionsValue;
        TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> VerifyActionsValue;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> FailedAcquireActionsValue;
        TSharedPtr<TArray<FString>> PremiseQuestNamesValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FQuestModelMaster();
        FQuestModelMaster(
            const FQuestModelMaster& From
        );
        virtual ~FQuestModelMaster() override = default;

        TSharedPtr<FQuestModelMaster> WithQuestModelId(const TOptional<FString> QuestModelId);
        TSharedPtr<FQuestModelMaster> WithQuestGroupName(const TOptional<FString> QuestGroupName);
        TSharedPtr<FQuestModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FQuestModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FQuestModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FQuestModelMaster> WithContents(const TSharedPtr<TArray<TSharedPtr<FContents>>> Contents);
        TSharedPtr<FQuestModelMaster> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);
        TSharedPtr<FQuestModelMaster> WithFirstCompleteAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> FirstCompleteAcquireActions);
        TSharedPtr<FQuestModelMaster> WithVerifyActions(const TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> VerifyActions);
        TSharedPtr<FQuestModelMaster> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ConsumeActions);
        TSharedPtr<FQuestModelMaster> WithFailedAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> FailedAcquireActions);
        TSharedPtr<FQuestModelMaster> WithPremiseQuestNames(const TSharedPtr<TArray<FString>> PremiseQuestNames);
        TSharedPtr<FQuestModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FQuestModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FQuestModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetQuestModelId() const;
        TOptional<FString> GetQuestGroupName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FContents>>> GetContents() const;
        TOptional<FString> GetChallengePeriodEventId() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetFirstCompleteAcquireActions() const;
        TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> GetVerifyActions() const;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> GetConsumeActions() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetFailedAcquireActions() const;
        TSharedPtr<TArray<FString>> GetPremiseQuestNames() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetQuestGroupNameFromGrn(const FString Grn);
        static TOptional<FString> GetQuestNameFromGrn(const FString Grn);

        static TSharedPtr<FQuestModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FQuestModelMaster, ESPMode::ThreadSafe> FQuestModelMasterPtr;
}