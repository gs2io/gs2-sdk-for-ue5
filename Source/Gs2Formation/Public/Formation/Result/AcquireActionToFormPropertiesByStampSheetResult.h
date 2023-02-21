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
#include "../Model/Form.h"
#include "../Model/Mold.h"

namespace Gs2::Formation::Result
{
    class GS2FORMATION_API FAcquireActionToFormPropertiesByStampSheetResult final : public TSharedFromThis<FAcquireActionToFormPropertiesByStampSheetResult>
    {
        TSharedPtr<Model::FForm> ItemValue;
        TSharedPtr<Model::FMold> MoldValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FAcquireActionToFormPropertiesByStampSheetResult();
        FAcquireActionToFormPropertiesByStampSheetResult(
            const FAcquireActionToFormPropertiesByStampSheetResult& From
        );
        ~FAcquireActionToFormPropertiesByStampSheetResult() = default;

        TSharedPtr<FAcquireActionToFormPropertiesByStampSheetResult> WithItem(const TSharedPtr<Model::FForm> Item);
        TSharedPtr<FAcquireActionToFormPropertiesByStampSheetResult> WithMold(const TSharedPtr<Model::FMold> Mold);
        TSharedPtr<FAcquireActionToFormPropertiesByStampSheetResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FAcquireActionToFormPropertiesByStampSheetResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FAcquireActionToFormPropertiesByStampSheetResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FAcquireActionToFormPropertiesByStampSheetResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TSharedPtr<Model::FForm> GetItem() const;
        TSharedPtr<Model::FMold> GetMold() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FAcquireActionToFormPropertiesByStampSheetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcquireActionToFormPropertiesByStampSheetResult, ESPMode::ThreadSafe> FAcquireActionToFormPropertiesByStampSheetResultPtr;
}