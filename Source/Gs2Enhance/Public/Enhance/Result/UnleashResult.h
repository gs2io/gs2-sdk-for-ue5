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
#include "../Model/UnleashRateModel.h"

namespace Gs2::Enhance::Result
{
    class GS2ENHANCE_API FUnleashResult final : public TSharedFromThis<FUnleashResult>
    {
        TSharedPtr<Model::FUnleashRateModel> ItemValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FUnleashResult();
        FUnleashResult(
            const FUnleashResult& From
        );
        ~FUnleashResult() = default;

        TSharedPtr<FUnleashResult> WithItem(const TSharedPtr<Model::FUnleashRateModel> Item);
        TSharedPtr<FUnleashResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FUnleashResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FUnleashResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FUnleashResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TSharedPtr<Model::FUnleashRateModel> GetItem() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FUnleashResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUnleashResult, ESPMode::ThreadSafe> FUnleashResultPtr;
}