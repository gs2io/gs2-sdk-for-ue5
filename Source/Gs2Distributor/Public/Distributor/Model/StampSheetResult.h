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
#include "ConsumeAction.h"
#include "AcquireAction.h"

namespace Gs2::Distributor::Model
{
    class GS2DISTRIBUTOR_API FStampSheetResult final : public Gs2Object, public TSharedFromThis<FStampSheetResult>
    {
        TOptional<FString> StampSheetResultIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TransactionIdValue;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> TaskRequestsValue;
        TSharedPtr<FAcquireAction> SheetRequestValue;
        TSharedPtr<TArray<FString>> TaskResultsValue;
        TOptional<FString> SheetResultValue;
        TOptional<FString> NextTransactionIdValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FStampSheetResult();
        FStampSheetResult(
            const FStampSheetResult& From
        );
        virtual ~FStampSheetResult() override = default;

        TSharedPtr<FStampSheetResult> WithStampSheetResultId(const TOptional<FString> StampSheetResultId);
        TSharedPtr<FStampSheetResult> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FStampSheetResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FStampSheetResult> WithTaskRequests(const TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> TaskRequests);
        TSharedPtr<FStampSheetResult> WithSheetRequest(const TSharedPtr<FAcquireAction> SheetRequest);
        TSharedPtr<FStampSheetResult> WithTaskResults(const TSharedPtr<TArray<FString>> TaskResults);
        TSharedPtr<FStampSheetResult> WithSheetResult(const TOptional<FString> SheetResult);
        TSharedPtr<FStampSheetResult> WithNextTransactionId(const TOptional<FString> NextTransactionId);
        TSharedPtr<FStampSheetResult> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FStampSheetResult> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetStampSheetResultId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTransactionId() const;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> GetTaskRequests() const;
        TSharedPtr<FAcquireAction> GetSheetRequest() const;
        TSharedPtr<TArray<FString>> GetTaskResults() const;
        TOptional<FString> GetSheetResult() const;
        TOptional<FString> GetNextTransactionId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetTransactionIdFromGrn(const FString Grn);

        static TSharedPtr<FStampSheetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FStampSheetResult, ESPMode::ThreadSafe> FStampSheetResultPtr;
}