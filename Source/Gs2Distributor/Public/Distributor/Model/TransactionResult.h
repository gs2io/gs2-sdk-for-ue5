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
#include "VerifyActionResult.h"
#include "ConsumeActionResult.h"
#include "AcquireActionResult.h"

namespace Gs2::Distributor::Model
{
    class GS2DISTRIBUTOR_API FTransactionResult final : public FGs2Object, public TSharedFromThis<FTransactionResult>
    {
        TOptional<FString> TransactionResultIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TransactionIdValue;
        TSharedPtr<TArray<TSharedPtr<FVerifyActionResult>>> VerifyResultsValue;
        TSharedPtr<TArray<TSharedPtr<FConsumeActionResult>>> ConsumeResultsValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireActionResult>>> AcquireResultsValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FTransactionResult();
        FTransactionResult(
            const FTransactionResult& From
        );
        virtual ~FTransactionResult() override = default;

        TSharedPtr<FTransactionResult> WithTransactionResultId(const TOptional<FString> TransactionResultId);
        TSharedPtr<FTransactionResult> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FTransactionResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FTransactionResult> WithVerifyResults(const TSharedPtr<TArray<TSharedPtr<FVerifyActionResult>>> VerifyResults);
        TSharedPtr<FTransactionResult> WithConsumeResults(const TSharedPtr<TArray<TSharedPtr<FConsumeActionResult>>> ConsumeResults);
        TSharedPtr<FTransactionResult> WithAcquireResults(const TSharedPtr<TArray<TSharedPtr<FAcquireActionResult>>> AcquireResults);
        TSharedPtr<FTransactionResult> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FTransactionResult> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetTransactionResultId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTransactionId() const;
        TSharedPtr<TArray<TSharedPtr<FVerifyActionResult>>> GetVerifyResults() const;
        TSharedPtr<TArray<TSharedPtr<FConsumeActionResult>>> GetConsumeResults() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireActionResult>>> GetAcquireResults() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetTransactionIdFromGrn(const FString Grn);

        static TSharedPtr<FTransactionResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FTransactionResult, ESPMode::ThreadSafe> FTransactionResultPtr;
}