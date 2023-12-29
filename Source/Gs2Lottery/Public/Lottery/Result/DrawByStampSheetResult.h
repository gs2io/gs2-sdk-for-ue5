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
#include "../Model/BoxItems.h"

namespace Gs2::Lottery::Result
{
    class GS2LOTTERY_API FDrawByStampSheetResult final : public TSharedFromThis<FDrawByStampSheetResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FDrawnPrize>>> ItemsValue;
        TSharedPtr<Model::FBoxItems> BoxItemsValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FDrawByStampSheetResult();
        FDrawByStampSheetResult(
            const FDrawByStampSheetResult& From
        );
        ~FDrawByStampSheetResult() = default;

        TSharedPtr<FDrawByStampSheetResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FDrawnPrize>>> Items);
        TSharedPtr<FDrawByStampSheetResult> WithBoxItems(const TSharedPtr<Model::FBoxItems> BoxItems);
        TSharedPtr<FDrawByStampSheetResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FDrawByStampSheetResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FDrawByStampSheetResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FDrawByStampSheetResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TSharedPtr<TArray<TSharedPtr<Model::FDrawnPrize>>> GetItems() const;
        TSharedPtr<Model::FBoxItems> GetBoxItems() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FDrawByStampSheetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDrawByStampSheetResult, ESPMode::ThreadSafe> FDrawByStampSheetResultPtr;
}