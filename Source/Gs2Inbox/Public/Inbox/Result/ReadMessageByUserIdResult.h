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
#include "../Model/Message.h"

namespace Gs2::Inbox::Result
{
    class GS2INBOX_API FReadMessageByUserIdResult final : public TSharedFromThis<FReadMessageByUserIdResult>
    {
        TSharedPtr<Model::FMessage> ItemValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FReadMessageByUserIdResult();
        FReadMessageByUserIdResult(
            const FReadMessageByUserIdResult& From
        );
        ~FReadMessageByUserIdResult() = default;

        TSharedPtr<FReadMessageByUserIdResult> WithItem(const TSharedPtr<Model::FMessage> Item);
        TSharedPtr<FReadMessageByUserIdResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FReadMessageByUserIdResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FReadMessageByUserIdResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FReadMessageByUserIdResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TSharedPtr<Model::FMessage> GetItem() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FReadMessageByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReadMessageByUserIdResult, ESPMode::ThreadSafe> FReadMessageByUserIdResultPtr;
}