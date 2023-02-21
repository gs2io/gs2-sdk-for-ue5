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

namespace Gs2::Lottery::Result
{
    class GS2LOTTERY_API FDrawByUserIdResult final : public TSharedFromThis<FDrawByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FDrawnPrize>>> ItemsValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FDrawByUserIdResult();
        FDrawByUserIdResult(
            const FDrawByUserIdResult& From
        );
        ~FDrawByUserIdResult() = default;

        TSharedPtr<FDrawByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FDrawnPrize>>> Items);
        TSharedPtr<FDrawByUserIdResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FDrawByUserIdResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FDrawByUserIdResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FDrawByUserIdResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TSharedPtr<TArray<TSharedPtr<Model::FDrawnPrize>>> GetItems() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FDrawByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDrawByUserIdResult, ESPMode::ThreadSafe> FDrawByUserIdResultPtr;
}