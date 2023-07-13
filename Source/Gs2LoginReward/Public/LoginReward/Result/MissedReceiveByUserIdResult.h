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
#include "../Model/ReceiveStatus.h"
#include "../Model/BonusModel.h"

namespace Gs2::LoginReward::Result
{
    class GS2LOGINREWARD_API FMissedReceiveByUserIdResult final : public TSharedFromThis<FMissedReceiveByUserIdResult>
    {
        TSharedPtr<Model::FReceiveStatus> ItemValue;
        TSharedPtr<Model::FBonusModel> BonusModelValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FMissedReceiveByUserIdResult();
        FMissedReceiveByUserIdResult(
            const FMissedReceiveByUserIdResult& From
        );
        ~FMissedReceiveByUserIdResult() = default;

        TSharedPtr<FMissedReceiveByUserIdResult> WithItem(const TSharedPtr<Model::FReceiveStatus> Item);
        TSharedPtr<FMissedReceiveByUserIdResult> WithBonusModel(const TSharedPtr<Model::FBonusModel> BonusModel);
        TSharedPtr<FMissedReceiveByUserIdResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FMissedReceiveByUserIdResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FMissedReceiveByUserIdResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FMissedReceiveByUserIdResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TSharedPtr<Model::FReceiveStatus> GetItem() const;
        TSharedPtr<Model::FBonusModel> GetBonusModel() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FMissedReceiveByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FMissedReceiveByUserIdResult, ESPMode::ThreadSafe> FMissedReceiveByUserIdResultPtr;
}