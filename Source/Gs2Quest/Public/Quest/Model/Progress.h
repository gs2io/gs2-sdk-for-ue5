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
#include "Reward.h"

namespace Gs2::Quest::Model
{
    class GS2QUEST_API FProgress final : public TSharedFromThis<FProgress>
    {
        TOptional<FString> ProgressIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> QuestModelIdValue;
        TOptional<int64> RandomSeedValue;
        TSharedPtr<TArray<TSharedPtr<FReward>>> RewardsValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FProgress();
        FProgress(
            const FProgress& From
        );
        ~FProgress() = default;

        TSharedPtr<FProgress> WithProgressId(const TOptional<FString> ProgressId);
        TSharedPtr<FProgress> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FProgress> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FProgress> WithQuestModelId(const TOptional<FString> QuestModelId);
        TSharedPtr<FProgress> WithRandomSeed(const TOptional<int64> RandomSeed);
        TSharedPtr<FProgress> WithRewards(const TSharedPtr<TArray<TSharedPtr<FReward>>> Rewards);
        TSharedPtr<FProgress> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FProgress> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FProgress> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetProgressId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetQuestModelId() const;
        TOptional<int64> GetRandomSeed() const;
        FString GetRandomSeedString() const;
        TSharedPtr<TArray<TSharedPtr<FReward>>> GetRewards() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);

        static TSharedPtr<FProgress> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FProgress, ESPMode::ThreadSafe> FProgressPtr;
}