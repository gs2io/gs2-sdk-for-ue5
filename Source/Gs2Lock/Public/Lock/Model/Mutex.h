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

namespace Gs2::Lock::Model
{
    class GS2LOCK_API FMutex final : public TSharedFromThis<FMutex>
    {
        TOptional<FString> MutexIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> PropertyIdValue;
        TOptional<FString> TransactionIdValue;
        TOptional<int64> CreatedAtValue;

    public:
        FMutex();
        FMutex(
            const FMutex& From
        );
        ~FMutex() = default;

        TSharedPtr<FMutex> WithMutexId(const TOptional<FString> MutexId);
        TSharedPtr<FMutex> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FMutex> WithPropertyId(const TOptional<FString> PropertyId);
        TSharedPtr<FMutex> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FMutex> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetMutexId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetPropertyId() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetPropertyIdFromGrn(const FString Grn);

        static TSharedPtr<FMutex> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FMutex, ESPMode::ThreadSafe> FMutexPtr;
}