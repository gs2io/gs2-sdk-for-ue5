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

namespace Gs2::Quest::Model
{
    class GS2QUEST_API FQuestGroupModelMaster final : public FGs2Object, public TSharedFromThis<FQuestGroupModelMaster>
    {
        TOptional<FString> QuestGroupModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ChallengePeriodEventIdValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FQuestGroupModelMaster();
        FQuestGroupModelMaster(
            const FQuestGroupModelMaster& From
        );
        virtual ~FQuestGroupModelMaster() override = default;

        TSharedPtr<FQuestGroupModelMaster> WithQuestGroupModelId(const TOptional<FString> QuestGroupModelId);
        TSharedPtr<FQuestGroupModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FQuestGroupModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FQuestGroupModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FQuestGroupModelMaster> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);
        TSharedPtr<FQuestGroupModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FQuestGroupModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FQuestGroupModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetQuestGroupModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetChallengePeriodEventId() const;
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

        static TSharedPtr<FQuestGroupModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FQuestGroupModelMaster, ESPMode::ThreadSafe> FQuestGroupModelMasterPtr;
}