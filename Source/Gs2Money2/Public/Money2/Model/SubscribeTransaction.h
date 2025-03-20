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

namespace Gs2::Money2::Model
{
    class GS2MONEY2_API FSubscribeTransaction final : public FGs2Object, public TSharedFromThis<FSubscribeTransaction>
    {
        TOptional<FString> SubscribeTransactionIdValue;
        TOptional<FString> ContentNameValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StoreValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> StatusDetailValue;
        TOptional<int64> ExpiresAtValue;
        TOptional<int64> LastAllocatedAtValue;
        TOptional<int64> LastTakeOverAtValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FSubscribeTransaction();
        FSubscribeTransaction(
            const FSubscribeTransaction& From
        );
        virtual ~FSubscribeTransaction() override = default;

        TSharedPtr<FSubscribeTransaction> WithSubscribeTransactionId(const TOptional<FString> SubscribeTransactionId);
        TSharedPtr<FSubscribeTransaction> WithContentName(const TOptional<FString> ContentName);
        TSharedPtr<FSubscribeTransaction> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FSubscribeTransaction> WithStore(const TOptional<FString> Store);
        TSharedPtr<FSubscribeTransaction> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSubscribeTransaction> WithStatusDetail(const TOptional<FString> StatusDetail);
        TSharedPtr<FSubscribeTransaction> WithExpiresAt(const TOptional<int64> ExpiresAt);
        TSharedPtr<FSubscribeTransaction> WithLastAllocatedAt(const TOptional<int64> LastAllocatedAt);
        TSharedPtr<FSubscribeTransaction> WithLastTakeOverAt(const TOptional<int64> LastTakeOverAt);
        TSharedPtr<FSubscribeTransaction> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FSubscribeTransaction> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FSubscribeTransaction> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetSubscribeTransactionId() const;
        TOptional<FString> GetContentName() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStore() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetStatusDetail() const;
        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;
        TOptional<int64> GetLastAllocatedAt() const;
        FString GetLastAllocatedAtString() const;
        TOptional<int64> GetLastTakeOverAt() const;
        FString GetLastTakeOverAtString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetContentNameFromGrn(const FString Grn);
        static TOptional<FString> GetTransactionIdFromGrn(const FString Grn);

        static TSharedPtr<FSubscribeTransaction> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSubscribeTransaction, ESPMode::ThreadSafe> FSubscribeTransactionPtr;
}