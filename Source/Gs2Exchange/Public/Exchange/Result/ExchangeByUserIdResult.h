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
#include "../Model/RateModel.h"

namespace Gs2::Exchange::Result
{
    class GS2EXCHANGE_API FExchangeByUserIdResult final : public TSharedFromThis<FExchangeByUserIdResult>
    {
        TSharedPtr<Model::FRateModel> ItemValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FExchangeByUserIdResult();
        FExchangeByUserIdResult(
            const FExchangeByUserIdResult& From
        );
        ~FExchangeByUserIdResult() = default;

        TSharedPtr<FExchangeByUserIdResult> WithItem(const TSharedPtr<Model::FRateModel> Item);
        TSharedPtr<FExchangeByUserIdResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FExchangeByUserIdResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FExchangeByUserIdResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FExchangeByUserIdResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TSharedPtr<Model::FRateModel> GetItem() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FExchangeByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FExchangeByUserIdResult, ESPMode::ThreadSafe> FExchangeByUserIdResultPtr;
}