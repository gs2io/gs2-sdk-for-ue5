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
#include "Gs2Core/Public/Core/Model/TransactionResult.h"

namespace Gs2::Mission::Result
{
    class GS2MISSION_API FBatchCompleteResult final : public TSharedFromThis<FBatchCompleteResult>
    {
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        TOptional<bool> AtomicCommitValue;
        TOptional<FString> TransactionValue;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResultValue;
        
    public:
        
        FBatchCompleteResult();
        FBatchCompleteResult(
            const FBatchCompleteResult& From
        );
        ~FBatchCompleteResult() = default;

        TSharedPtr<FBatchCompleteResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FBatchCompleteResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FBatchCompleteResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FBatchCompleteResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);
        TSharedPtr<FBatchCompleteResult> WithAtomicCommit(const TOptional<bool> AtomicCommit);
        TSharedPtr<FBatchCompleteResult> WithTransaction(const TOptional<FString> Transaction);
        TSharedPtr<FBatchCompleteResult> WithTransactionResult(const TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResult);

        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;
        TOptional<bool> GetAtomicCommit() const;
        FString GetAtomicCommitString() const;
        TOptional<FString> GetTransaction() const;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> GetTransactionResult() const;

        static TSharedPtr<FBatchCompleteResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FBatchCompleteResult, ESPMode::ThreadSafe> FBatchCompleteResultPtr;
}