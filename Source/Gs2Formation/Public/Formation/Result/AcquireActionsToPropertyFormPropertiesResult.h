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
#include "../Model/PropertyForm.h"

namespace Gs2::Formation::Result
{
    class GS2FORMATION_API FAcquireActionsToPropertyFormPropertiesResult final : public TSharedFromThis<FAcquireActionsToPropertyFormPropertiesResult>
    {
        TSharedPtr<Model::FPropertyForm> ItemValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FAcquireActionsToPropertyFormPropertiesResult();
        FAcquireActionsToPropertyFormPropertiesResult(
            const FAcquireActionsToPropertyFormPropertiesResult& From
        );
        ~FAcquireActionsToPropertyFormPropertiesResult() = default;

        TSharedPtr<FAcquireActionsToPropertyFormPropertiesResult> WithItem(const TSharedPtr<Model::FPropertyForm> Item);
        TSharedPtr<FAcquireActionsToPropertyFormPropertiesResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FAcquireActionsToPropertyFormPropertiesResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FAcquireActionsToPropertyFormPropertiesResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FAcquireActionsToPropertyFormPropertiesResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TSharedPtr<Model::FPropertyForm> GetItem() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FAcquireActionsToPropertyFormPropertiesResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcquireActionsToPropertyFormPropertiesResult, ESPMode::ThreadSafe> FAcquireActionsToPropertyFormPropertiesResultPtr;
}