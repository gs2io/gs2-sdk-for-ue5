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

namespace Gs2::Ranking::Model
{
    class GS2RANKING_API FScore final : public Gs2Object, public TSharedFromThis<FScore>
    {
        TOptional<FString> ScoreIdValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> UniqueIdValue;
        TOptional<FString> ScorerUserIdValue;
        TOptional<int64> ScoreValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FScore();
        FScore(
            const FScore& From
        );
        virtual ~FScore() override = default;

        TSharedPtr<FScore> WithScoreId(const TOptional<FString> ScoreId);
        TSharedPtr<FScore> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FScore> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FScore> WithUniqueId(const TOptional<FString> UniqueId);
        TSharedPtr<FScore> WithScorerUserId(const TOptional<FString> ScorerUserId);
        TSharedPtr<FScore> WithScore(const TOptional<int64> Score);
        TSharedPtr<FScore> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FScore> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FScore> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetScoreId() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetUniqueId() const;
        TOptional<FString> GetScorerUserId() const;
        TOptional<int64> GetScore() const;
        FString GetScoreString() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetCategoryNameFromGrn(const FString Grn);
        static TOptional<FString> GetScorerUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetUniqueIdFromGrn(const FString Grn);

        static TSharedPtr<FScore> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FScore, ESPMode::ThreadSafe> FScorePtr;
}