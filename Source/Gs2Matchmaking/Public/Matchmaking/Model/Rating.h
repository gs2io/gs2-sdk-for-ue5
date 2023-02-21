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

namespace Gs2::Matchmaking::Model
{
    class GS2MATCHMAKING_API FRating final : public TSharedFromThis<FRating>
    {
        TOptional<FString> RatingIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> UserIdValue;
        TOptional<float> RateValueValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FRating();
        FRating(
            const FRating& From
        );
        ~FRating() = default;

        TSharedPtr<FRating> WithRatingId(const TOptional<FString> RatingId);
        TSharedPtr<FRating> WithName(const TOptional<FString> Name);
        TSharedPtr<FRating> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FRating> WithRateValue(const TOptional<float> RateValue);
        TSharedPtr<FRating> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FRating> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetRatingId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetUserId() const;
        TOptional<float> GetRateValue() const;
        FString GetRateValueString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetRatingNameFromGrn(const FString Grn);

        static TSharedPtr<FRating> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRating, ESPMode::ThreadSafe> FRatingPtr;
}