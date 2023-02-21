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

namespace Gs2::Quest::Model
{
    class GS2QUEST_API FCompletedQuestList final : public TSharedFromThis<FCompletedQuestList>
    {
        TOptional<FString> CompletedQuestListIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> QuestGroupNameValue;
        TSharedPtr<TArray<FString>> CompleteQuestNamesValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FCompletedQuestList();
        FCompletedQuestList(
            const FCompletedQuestList& From
        );
        ~FCompletedQuestList() = default;

        TSharedPtr<FCompletedQuestList> WithCompletedQuestListId(const TOptional<FString> CompletedQuestListId);
        TSharedPtr<FCompletedQuestList> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCompletedQuestList> WithQuestGroupName(const TOptional<FString> QuestGroupName);
        TSharedPtr<FCompletedQuestList> WithCompleteQuestNames(const TSharedPtr<TArray<FString>> CompleteQuestNames);
        TSharedPtr<FCompletedQuestList> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FCompletedQuestList> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetCompletedQuestListId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetQuestGroupName() const;
        TSharedPtr<TArray<FString>> GetCompleteQuestNames() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetQuestGroupNameFromGrn(const FString Grn);

        static TSharedPtr<FCompletedQuestList> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCompletedQuestList, ESPMode::ThreadSafe> FCompletedQuestListPtr;
}