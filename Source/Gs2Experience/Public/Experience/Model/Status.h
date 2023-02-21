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

namespace Gs2::Experience::Model
{
    class GS2EXPERIENCE_API FStatus final : public TSharedFromThis<FStatus>
    {
        TOptional<FString> StatusIdValue;
        TOptional<FString> ExperienceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> ExperienceValueValue;
        TOptional<int64> RankValueValue;
        TOptional<int64> RankCapValueValue;
        TOptional<int64> NextRankUpExperienceValueValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FStatus();
        FStatus(
            const FStatus& From
        );
        ~FStatus() = default;

        TSharedPtr<FStatus> WithStatusId(const TOptional<FString> StatusId);
        TSharedPtr<FStatus> WithExperienceName(const TOptional<FString> ExperienceName);
        TSharedPtr<FStatus> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FStatus> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FStatus> WithExperienceValue(const TOptional<int64> ExperienceValue);
        TSharedPtr<FStatus> WithRankValue(const TOptional<int64> RankValue);
        TSharedPtr<FStatus> WithRankCapValue(const TOptional<int64> RankCapValue);
        TSharedPtr<FStatus> WithNextRankUpExperienceValue(const TOptional<int64> NextRankUpExperienceValue);
        TSharedPtr<FStatus> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FStatus> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetStatusId() const;
        TOptional<FString> GetExperienceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<int64> GetExperienceValue() const;
        FString GetExperienceValueString() const;
        TOptional<int64> GetRankValue() const;
        FString GetRankValueString() const;
        TOptional<int64> GetRankCapValue() const;
        FString GetRankCapValueString() const;
        TOptional<int64> GetNextRankUpExperienceValue() const;
        FString GetNextRankUpExperienceValueString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetExperienceNameFromGrn(const FString Grn);
        static TOptional<FString> GetPropertyIdFromGrn(const FString Grn);

        static TSharedPtr<FStatus> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FStatus, ESPMode::ThreadSafe> FStatusPtr;
}