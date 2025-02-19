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
#include "../Model/Message.h"
#include "Gs2Core/Public/Core/Model/TransactionResult.h"

namespace Gs2::Inbox::Result
{
    class GS2INBOX_API FBatchReadMessagesResult final : public TSharedFromThis<FBatchReadMessagesResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FMessage>>> ItemsValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        TOptional<bool> AtomicCommitValue;
        TOptional<FString> TransactionValue;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResultValue;
        
    public:
        
        FBatchReadMessagesResult();
        FBatchReadMessagesResult(
            const FBatchReadMessagesResult& From
        );
        ~FBatchReadMessagesResult() = default;

        TSharedPtr<FBatchReadMessagesResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FMessage>>> Items);
        TSharedPtr<FBatchReadMessagesResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FBatchReadMessagesResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FBatchReadMessagesResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FBatchReadMessagesResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);
        TSharedPtr<FBatchReadMessagesResult> WithAtomicCommit(const TOptional<bool> AtomicCommit);
        TSharedPtr<FBatchReadMessagesResult> WithTransaction(const TOptional<FString> Transaction);
        TSharedPtr<FBatchReadMessagesResult> WithTransactionResult(const TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResult);

        TSharedPtr<TArray<TSharedPtr<Model::FMessage>>> GetItems() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;
        TOptional<bool> GetAtomicCommit() const;
        FString GetAtomicCommitString() const;
        TOptional<FString> GetTransaction() const;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> GetTransactionResult() const;

        static TSharedPtr<FBatchReadMessagesResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FBatchReadMessagesResult, ESPMode::ThreadSafe> FBatchReadMessagesResultPtr;
}