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

namespace Gs2::Enhance::Model
{
    class GS2ENHANCE_API FProgress final : public FGs2Object, public TSharedFromThis<FProgress>
    {
        TOptional<FString> ProgressIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> PropertyIdValue;
        TOptional<int64> ExperienceValueValue;
        TOptional<float> RateValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FProgress();
        FProgress(
            const FProgress& From
        );
        virtual ~FProgress() override = default;

        TSharedPtr<FProgress> WithProgressId(const TOptional<FString> ProgressId);
        TSharedPtr<FProgress> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FProgress> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FProgress> WithName(const TOptional<FString> Name);
        TSharedPtr<FProgress> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FProgress> WithExperienceValue(const TOptional<int64> ExperienceValue);
        TSharedPtr<FProgress> WithRate(const TOptional<float> Rate);
        TSharedPtr<FProgress> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FProgress> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FProgress> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetProgressId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRateName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<int64> GetExperienceValue() const;
        FString GetExperienceValueString() const;
        TOptional<float> GetRate() const;
        FString GetRateString() const;
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

        static TSharedPtr<FProgress> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FProgress, ESPMode::ThreadSafe> FProgressPtr;
}