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
#include "../Model/AcquireAction.h"
#include "../Model/Status.h"

namespace Gs2::Idle::Result
{
    class GS2IDLE_API FReceiveByStampSheetResult final : public TSharedFromThis<FReceiveByStampSheetResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> ItemsValue;
        TSharedPtr<Model::FStatus> StatusValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FReceiveByStampSheetResult();
        FReceiveByStampSheetResult(
            const FReceiveByStampSheetResult& From
        );
        ~FReceiveByStampSheetResult() = default;

        TSharedPtr<FReceiveByStampSheetResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> Items);
        TSharedPtr<FReceiveByStampSheetResult> WithStatus(const TSharedPtr<Model::FStatus> Status);
        TSharedPtr<FReceiveByStampSheetResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FReceiveByStampSheetResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FReceiveByStampSheetResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FReceiveByStampSheetResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetItems() const;
        TSharedPtr<Model::FStatus> GetStatus() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FReceiveByStampSheetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReceiveByStampSheetResult, ESPMode::ThreadSafe> FReceiveByStampSheetResultPtr;
}