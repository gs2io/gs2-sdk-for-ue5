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
#include "../Model/RandomDisplayItem.h"
#include "Gs2Core/Public/Core/Model/TransactionResult.h"

namespace Gs2::Showcase::Result
{
    class GS2SHOWCASE_API FRandomShowcaseBuyByUserIdResult final : public TSharedFromThis<FRandomShowcaseBuyByUserIdResult>
    {
        TSharedPtr<Model::FRandomDisplayItem> ItemValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        TOptional<bool> AtomicCommitValue;
        TOptional<FString> TransactionValue;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResultValue;
        
    public:
        
        FRandomShowcaseBuyByUserIdResult();
        FRandomShowcaseBuyByUserIdResult(
            const FRandomShowcaseBuyByUserIdResult& From
        );
        ~FRandomShowcaseBuyByUserIdResult() = default;

        TSharedPtr<FRandomShowcaseBuyByUserIdResult> WithItem(const TSharedPtr<Model::FRandomDisplayItem> Item);
        TSharedPtr<FRandomShowcaseBuyByUserIdResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FRandomShowcaseBuyByUserIdResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FRandomShowcaseBuyByUserIdResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FRandomShowcaseBuyByUserIdResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);
        TSharedPtr<FRandomShowcaseBuyByUserIdResult> WithAtomicCommit(const TOptional<bool> AtomicCommit);
        TSharedPtr<FRandomShowcaseBuyByUserIdResult> WithTransaction(const TOptional<FString> Transaction);
        TSharedPtr<FRandomShowcaseBuyByUserIdResult> WithTransactionResult(const TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResult);

        TSharedPtr<Model::FRandomDisplayItem> GetItem() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;
        TOptional<bool> GetAtomicCommit() const;
        FString GetAtomicCommitString() const;
        TOptional<FString> GetTransaction() const;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> GetTransactionResult() const;

        static TSharedPtr<FRandomShowcaseBuyByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FRandomShowcaseBuyByUserIdResult, ESPMode::ThreadSafe> FRandomShowcaseBuyByUserIdResultPtr;
}