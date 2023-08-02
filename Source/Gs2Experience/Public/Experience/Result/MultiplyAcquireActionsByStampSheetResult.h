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

namespace Gs2::Experience::Result
{
    class GS2EXPERIENCE_API FMultiplyAcquireActionsByStampSheetResult final : public TSharedFromThis<FMultiplyAcquireActionsByStampSheetResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> ItemsValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FMultiplyAcquireActionsByStampSheetResult();
        FMultiplyAcquireActionsByStampSheetResult(
            const FMultiplyAcquireActionsByStampSheetResult& From
        );
        ~FMultiplyAcquireActionsByStampSheetResult() = default;

        TSharedPtr<FMultiplyAcquireActionsByStampSheetResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> Items);
        TSharedPtr<FMultiplyAcquireActionsByStampSheetResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FMultiplyAcquireActionsByStampSheetResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FMultiplyAcquireActionsByStampSheetResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FMultiplyAcquireActionsByStampSheetResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetItems() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FMultiplyAcquireActionsByStampSheetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FMultiplyAcquireActionsByStampSheetResult, ESPMode::ThreadSafe> FMultiplyAcquireActionsByStampSheetResultPtr;
}