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
    class GS2FORMATION_API FAcquireActionsToFormPropertiesResult final : public TSharedFromThis<FAcquireActionsToFormPropertiesResult>
    {
        TSharedPtr<Model::FForm> ItemValue;
        TSharedPtr<Model::FMold> MoldValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FAcquireActionsToFormPropertiesResult();
        FAcquireActionsToFormPropertiesResult(
            const FAcquireActionsToFormPropertiesResult& From
        );
        ~FAcquireActionsToFormPropertiesResult() = default;

        TSharedPtr<FAcquireActionsToFormPropertiesResult> WithItem(const TSharedPtr<Model::FForm> Item);
        TSharedPtr<FAcquireActionsToFormPropertiesResult> WithMold(const TSharedPtr<Model::FMold> Mold);
        TSharedPtr<FAcquireActionsToFormPropertiesResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FAcquireActionsToFormPropertiesResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FAcquireActionsToFormPropertiesResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FAcquireActionsToFormPropertiesResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TSharedPtr<Model::FForm> GetItem() const;
        TSharedPtr<Model::FMold> GetMold() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FAcquireActionsToFormPropertiesResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAcquireActionsToFormPropertiesResult, ESPMode::ThreadSafe> FAcquireActionsToFormPropertiesResultPtr;
}