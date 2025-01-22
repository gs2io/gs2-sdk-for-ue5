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
    class GS2EXCHANGE_API FIncrementalExchangeByStampSheetResult final : public TSharedFromThis<FIncrementalExchangeByStampSheetResult>
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
        
        FIncrementalExchangeByStampSheetResult();
        FIncrementalExchangeByStampSheetResult(
            const FIncrementalExchangeByStampSheetResult& From
        );
        ~FIncrementalExchangeByStampSheetResult() = default;

        TSharedPtr<FIncrementalExchangeByStampSheetResult> WithItem(const TSharedPtr<Model::FIncrementalRateModel> Item);
        TSharedPtr<FIncrementalExchangeByStampSheetResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FIncrementalExchangeByStampSheetResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FIncrementalExchangeByStampSheetResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FIncrementalExchangeByStampSheetResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);
        TSharedPtr<FIncrementalExchangeByStampSheetResult> WithAtomicCommit(const TOptional<bool> AtomicCommit);
        TSharedPtr<FIncrementalExchangeByStampSheetResult> WithTransaction(const TOptional<FString> Transaction);
        TSharedPtr<FIncrementalExchangeByStampSheetResult> WithTransactionResult(const TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResult);

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

        static TSharedPtr<FIncrementalExchangeByStampSheetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FIncrementalExchangeByStampSheetResult, ESPMode::ThreadSafe> FIncrementalExchangeByStampSheetResultPtr;
}