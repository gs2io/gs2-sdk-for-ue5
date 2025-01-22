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
#include "../Model/IncrementalRateModel.h"
#include "Gs2Core/Public/Core/Model/TransactionResult.h"

namespace Gs2::Exchange::Result
{
    class GS2EXCHANGE_API FIncrementalExchangeResult final : public TSharedFromThis<FIncrementalExchangeResult>
    {
        TSharedPtr<Model::FIncrementalRateModel> ItemValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        TOptional<bool> AtomicCommitValue;
        TOptional<FString> TransactionValue;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResultValue;
        
    public:
        
        FIncrementalExchangeResult();
        FIncrementalExchangeResult(
            const FIncrementalExchangeResult& From
        );
        ~FIncrementalExchangeResult() = default;

        TSharedPtr<FIncrementalExchangeResult> WithItem(const TSharedPtr<Model::FIncrementalRateModel> Item);
        TSharedPtr<FIncrementalExchangeResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FIncrementalExchangeResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FIncrementalExchangeResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FIncrementalExchangeResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);
        TSharedPtr<FIncrementalExchangeResult> WithAtomicCommit(const TOptional<bool> AtomicCommit);
        TSharedPtr<FIncrementalExchangeResult> WithTransaction(const TOptional<FString> Transaction);
        TSharedPtr<FIncrementalExchangeResult> WithTransactionResult(const TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResult);

        TSharedPtr<Model::FIncrementalRateModel> GetItem() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;
        TOptional<bool> GetAtomicCommit() const;
        FString GetAtomicCommitString() const;
        TOptional<FString> GetTransaction() const;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> GetTransactionResult() const;

        static TSharedPtr<FIncrementalExchangeResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FIncrementalExchangeResult, ESPMode::ThreadSafe> FIncrementalExchangeResultPtr;
}