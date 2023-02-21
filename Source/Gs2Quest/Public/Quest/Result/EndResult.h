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
    class GS2QUEST_API FEndResult final : public TSharedFromThis<FEndResult>
    {
        TSharedPtr<Model::FProgress> ItemValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
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

        TSharedPtr<Model::FProgress> GetItem() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FEndResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FEndResult, ESPMode::ThreadSafe> FEndResultPtr;
}