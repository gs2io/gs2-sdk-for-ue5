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

namespace Gs2::Enhance::Result
{
    class GS2ENHANCE_API FStartByUserIdResult final : public TSharedFromThis<FStartByUserIdResult>
    {
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FStartByUserIdResult();
        FStartByUserIdResult(
            const FStartByUserIdResult& From
        );
        ~FStartByUserIdResult() = default;

        TSharedPtr<FStartByUserIdResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FStartByUserIdResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FStartByUserIdResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FStartByUserIdResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FStartByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FStartByUserIdResult, ESPMode::ThreadSafe> FStartByUserIdResultPtr;
}