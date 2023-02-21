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
#include "ScopedValue.h"

namespace Gs2::Mission::Model
{
    class GS2MISSION_API FCounter final : public TSharedFromThis<FCounter>
    {
        TOptional<FString> CounterIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> NameValue;
        TSharedPtr<TArray<TSharedPtr<FScopedValue>>> ValuesValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FCounter();
        FCounter(
            const FCounter& From
        );
        ~FCounter() = default;

        TSharedPtr<FCounter> WithCounterId(const TOptional<FString> CounterId);
        TSharedPtr<FCounter> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCounter> WithName(const TOptional<FString> Name);
        TSharedPtr<FCounter> WithValues(const TSharedPtr<TArray<TSharedPtr<FScopedValue>>> Values);
        TSharedPtr<FCounter> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FCounter> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetCounterId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetName() const;
        TSharedPtr<TArray<TSharedPtr<FScopedValue>>> GetValues() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetCounterNameFromGrn(const FString Grn);

        static TSharedPtr<FCounter> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCounter, ESPMode::ThreadSafe> FCounterPtr;
}