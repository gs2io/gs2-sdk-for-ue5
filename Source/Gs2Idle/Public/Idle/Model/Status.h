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

namespace Gs2::Idle::Model
{
    class GS2IDLE_API FStatus final : public Gs2Object, public TSharedFromThis<FStatus>
    {
        TOptional<FString> StatusIdValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> RandomSeedValue;
        TOptional<int32> IdleMinutesValue;
        TOptional<int32> MaximumIdleMinutesValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FStatus();
        FStatus(
            const FStatus& From
        );
        virtual ~FStatus() override = default;

        TSharedPtr<FStatus> WithStatusId(const TOptional<FString> StatusId);
        TSharedPtr<FStatus> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FStatus> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FStatus> WithRandomSeed(const TOptional<int64> RandomSeed);
        TSharedPtr<FStatus> WithIdleMinutes(const TOptional<int32> IdleMinutes);
        TSharedPtr<FStatus> WithMaximumIdleMinutes(const TOptional<int32> MaximumIdleMinutes);
        TSharedPtr<FStatus> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FStatus> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetStatusId() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetRandomSeed() const;
        FString GetRandomSeedString() const;
        TOptional<int32> GetIdleMinutes() const;
        FString GetIdleMinutesString() const;
        TOptional<int32> GetMaximumIdleMinutes() const;
        FString GetMaximumIdleMinutesString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetCategoryNameFromGrn(const FString Grn);

        static TSharedPtr<FStatus> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FStatus, ESPMode::ThreadSafe> FStatusPtr;
}