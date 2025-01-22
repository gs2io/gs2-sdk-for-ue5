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
#include "../Model/Progress.h"
#include "Gs2Core/Public/Core/Model/TransactionResult.h"

namespace Gs2::Enhance::Result
{
    class GS2ENHANCE_API FEndResult final : public TSharedFromThis<FEndResult>
    {
        TSharedPtr<Model::FProgress> ItemValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        TOptional<bool> AtomicCommitValue;
        TOptional<FString> TransactionValue;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResultValue;
        TOptional<int64> AcquireExperienceValue;
        TOptional<float> BonusRateValue;
        
    public:
        
        FEndResult();
        FEndResult(
            const FEndResult& From
        );
        ~FEndResult() = default;

        TSharedPtr<FEndResult> WithItem(const TSharedPtr<Model::FProgress> Item);
        TSharedPtr<FEndResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FEndResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FEndResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FEndResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);
        TSharedPtr<FEndResult> WithAtomicCommit(const TOptional<bool> AtomicCommit);
        TSharedPtr<FEndResult> WithTransaction(const TOptional<FString> Transaction);
        TSharedPtr<FEndResult> WithTransactionResult(const TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResult);
        TSharedPtr<FEndResult> WithAcquireExperience(const TOptional<int64> AcquireExperience);
        TSharedPtr<FEndResult> WithBonusRate(const TOptional<float> BonusRate);

        TSharedPtr<Model::FProgress> GetItem() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;
        TOptional<bool> GetAtomicCommit() const;
        FString GetAtomicCommitString() const;
        TOptional<FString> GetTransaction() const;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> GetTransactionResult() const;
        TOptional<int64> GetAcquireExperience() const;
        FString GetAcquireExperienceString() const;
        TOptional<float> GetBonusRate() const;
        FString GetBonusRateString() const;

        static TSharedPtr<FEndResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FEndResult, ESPMode::ThreadSafe> FEndResultPtr;
}