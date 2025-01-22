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
#include "../Model/DrawnPrize.h"
#include "Gs2Core/Public/Core/Model/TransactionResult.h"

namespace Gs2::Lottery::Result
{
    class GS2LOTTERY_API FDrawWithRandomSeedByUserIdResult final : public TSharedFromThis<FDrawWithRandomSeedByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FDrawnPrize>>> ItemsValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        TOptional<bool> AtomicCommitValue;
        TOptional<FString> TransactionValue;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResultValue;
        
    public:
        
        FDrawWithRandomSeedByUserIdResult();
        FDrawWithRandomSeedByUserIdResult(
            const FDrawWithRandomSeedByUserIdResult& From
        );
        ~FDrawWithRandomSeedByUserIdResult() = default;

        TSharedPtr<FDrawWithRandomSeedByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FDrawnPrize>>> Items);
        TSharedPtr<FDrawWithRandomSeedByUserIdResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FDrawWithRandomSeedByUserIdResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FDrawWithRandomSeedByUserIdResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FDrawWithRandomSeedByUserIdResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);
        TSharedPtr<FDrawWithRandomSeedByUserIdResult> WithAtomicCommit(const TOptional<bool> AtomicCommit);
        TSharedPtr<FDrawWithRandomSeedByUserIdResult> WithTransaction(const TOptional<FString> Transaction);
        TSharedPtr<FDrawWithRandomSeedByUserIdResult> WithTransactionResult(const TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResult);

        TSharedPtr<TArray<TSharedPtr<Model::FDrawnPrize>>> GetItems() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;
        TOptional<bool> GetAtomicCommit() const;
        FString GetAtomicCommitString() const;
        TOptional<FString> GetTransaction() const;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> GetTransactionResult() const;

        static TSharedPtr<FDrawWithRandomSeedByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDrawWithRandomSeedByUserIdResult, ESPMode::ThreadSafe> FDrawWithRandomSeedByUserIdResultPtr;
}