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
#include "../Model/SalesItem.h"

namespace Gs2::Showcase::Result
{
    class GS2SHOWCASE_API FBuyByUserIdResult final : public TSharedFromThis<FBuyByUserIdResult>
    {
        TSharedPtr<Model::FSalesItem> ItemValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FBuyByUserIdResult();
        FBuyByUserIdResult(
            const FBuyByUserIdResult& From
        );
        ~FBuyByUserIdResult() = default;

        TSharedPtr<FBuyByUserIdResult> WithItem(const TSharedPtr<Model::FSalesItem> Item);
        TSharedPtr<FBuyByUserIdResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FBuyByUserIdResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FBuyByUserIdResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FBuyByUserIdResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TSharedPtr<Model::FSalesItem> GetItem() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FBuyByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FBuyByUserIdResult, ESPMode::ThreadSafe> FBuyByUserIdResultPtr;
}