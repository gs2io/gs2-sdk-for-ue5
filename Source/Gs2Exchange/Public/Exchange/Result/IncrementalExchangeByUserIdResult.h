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

namespace Gs2::Exchange::Result
{
    class GS2EXCHANGE_API FIncrementalExchangeByUserIdResult final : public TSharedFromThis<FIncrementalExchangeByUserIdResult>
    {
        TSharedPtr<Model::FIncrementalRateModel> ItemValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FIncrementalExchangeByUserIdResult();
        FIncrementalExchangeByUserIdResult(
            const FIncrementalExchangeByUserIdResult& From
        );
        ~FIncrementalExchangeByUserIdResult() = default;

        TSharedPtr<FIncrementalExchangeByUserIdResult> WithItem(const TSharedPtr<Model::FIncrementalRateModel> Item);
        TSharedPtr<FIncrementalExchangeByUserIdResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FIncrementalExchangeByUserIdResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FIncrementalExchangeByUserIdResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FIncrementalExchangeByUserIdResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TSharedPtr<Model::FIncrementalRateModel> GetItem() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FIncrementalExchangeByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FIncrementalExchangeByUserIdResult, ESPMode::ThreadSafe> FIncrementalExchangeByUserIdResultPtr;
}