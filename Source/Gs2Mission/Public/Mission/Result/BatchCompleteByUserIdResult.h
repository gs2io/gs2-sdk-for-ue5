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
    class GS2MISSION_API FBatchCompleteByUserIdResult final : public TSharedFromThis<FBatchCompleteByUserIdResult>
    {
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        TOptional<bool> AtomicCommitValue;
        TOptional<FString> TransactionValue;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResultValue;
        
    public:
        
        FBatchCompleteByUserIdResult();
        FBatchCompleteByUserIdResult(
            const FBatchCompleteByUserIdResult& From
        );
        ~FBatchCompleteByUserIdResult() = default;

        TSharedPtr<FBatchCompleteByUserIdResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FBatchCompleteByUserIdResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FBatchCompleteByUserIdResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FBatchCompleteByUserIdResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);
        TSharedPtr<FBatchCompleteByUserIdResult> WithAtomicCommit(const TOptional<bool> AtomicCommit);
        TSharedPtr<FBatchCompleteByUserIdResult> WithTransaction(const TOptional<FString> Transaction);
        TSharedPtr<FBatchCompleteByUserIdResult> WithTransactionResult(const TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResult);

        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;
        TOptional<bool> GetAtomicCommit() const;
        FString GetAtomicCommitString() const;
        TOptional<FString> GetTransaction() const;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> GetTransactionResult() const;

        static TSharedPtr<FBatchCompleteByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FBatchCompleteByUserIdResult, ESPMode::ThreadSafe> FBatchCompleteByUserIdResultPtr;
}