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

namespace Gs2::Quest::Result
{
    class GS2QUEST_API FEndByUserIdResult final : public TSharedFromThis<FEndByUserIdResult>
    {
        TSharedPtr<Model::FProgress> ItemValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FEndByUserIdResult();
        FEndByUserIdResult(
            const FEndByUserIdResult& From
        );
        ~FEndByUserIdResult() = default;

        TSharedPtr<FEndByUserIdResult> WithItem(const TSharedPtr<Model::FProgress> Item);
        TSharedPtr<FEndByUserIdResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FEndByUserIdResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FEndByUserIdResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FEndByUserIdResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TSharedPtr<Model::FProgress> GetItem() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FEndByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FEndByUserIdResult, ESPMode::ThreadSafe> FEndByUserIdResultPtr;
}