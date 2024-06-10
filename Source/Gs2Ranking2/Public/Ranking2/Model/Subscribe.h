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

namespace Gs2::Ranking2::Model
{
    class GS2RANKING2_API FSubscribe final : public Gs2Object, public TSharedFromThis<FSubscribe>
    {
        TOptional<FString> SubscribeIdValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<FString>> TargetUserIdsValue;
        TSharedPtr<TArray<FString>> FromUserIdsValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FSubscribe();
        FSubscribe(
            const FSubscribe& From
        );
        virtual ~FSubscribe() override = default;

        TSharedPtr<FSubscribe> WithSubscribeId(const TOptional<FString> SubscribeId);
        TSharedPtr<FSubscribe> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FSubscribe> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSubscribe> WithTargetUserIds(const TSharedPtr<TArray<FString>> TargetUserIds);
        TSharedPtr<FSubscribe> WithFromUserIds(const TSharedPtr<TArray<FString>> FromUserIds);
        TSharedPtr<FSubscribe> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FSubscribe> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FSubscribe> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetSubscribeId() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<TArray<FString>> GetTargetUserIds() const;
        TSharedPtr<TArray<FString>> GetFromUserIds() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetRankingNameFromGrn(const FString Grn);

        static TSharedPtr<FSubscribe> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSubscribe, ESPMode::ThreadSafe> FSubscribePtr;
}