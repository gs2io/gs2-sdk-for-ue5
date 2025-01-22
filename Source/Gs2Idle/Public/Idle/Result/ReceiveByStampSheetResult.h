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
#include "../Model/AcquireAction.h"
#include "../Model/Status.h"
#include "Gs2Core/Public/Core/Model/TransactionResult.h"

namespace Gs2::Idle::Result
{
    class GS2IDLE_API FReceiveByStampSheetResult final : public TSharedFromThis<FReceiveByStampSheetResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> ItemsValue;
        TSharedPtr<Model::FStatus> StatusValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        TOptional<bool> AtomicCommitValue;
        TOptional<FString> TransactionValue;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResultValue;
        
    public:
        
        FReceiveByStampSheetResult();
        FReceiveByStampSheetResult(
            const FReceiveByStampSheetResult& From
        );
        ~FReceiveByStampSheetResult() = default;

        TSharedPtr<FReceiveByStampSheetResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> Items);
        TSharedPtr<FReceiveByStampSheetResult> WithStatus(const TSharedPtr<Model::FStatus> Status);
        TSharedPtr<FReceiveByStampSheetResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FReceiveByStampSheetResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FReceiveByStampSheetResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FReceiveByStampSheetResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);
        TSharedPtr<FReceiveByStampSheetResult> WithAtomicCommit(const TOptional<bool> AtomicCommit);
        TSharedPtr<FReceiveByStampSheetResult> WithTransaction(const TOptional<FString> Transaction);
        TSharedPtr<FReceiveByStampSheetResult> WithTransactionResult(const TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResult);

        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetItems() const;
        TSharedPtr<Model::FStatus> GetStatus() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;
        TOptional<bool> GetAtomicCommit() const;
        FString GetAtomicCommitString() const;
        TOptional<FString> GetTransaction() const;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> GetTransactionResult() const;

        static TSharedPtr<FReceiveByStampSheetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReceiveByStampSheetResult, ESPMode::ThreadSafe> FReceiveByStampSheetResultPtr;
}