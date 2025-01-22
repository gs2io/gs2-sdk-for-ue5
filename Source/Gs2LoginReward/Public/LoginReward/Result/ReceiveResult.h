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
#include "Gs2Core/Public/Core/Model/TransactionResult.h"

namespace Gs2::LoginReward::Result
{
    class GS2LOGINREWARD_API FReceiveResult final : public TSharedFromThis<FReceiveResult>
    {
        TSharedPtr<Model::FReceiveStatus> ItemValue;
        TSharedPtr<Model::FBonusModel> BonusModelValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        TOptional<bool> AtomicCommitValue;
        TOptional<FString> TransactionValue;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResultValue;
        
    public:
        
        FReceiveResult();
        FReceiveResult(
            const FReceiveResult& From
        );
        ~FReceiveResult() = default;

        TSharedPtr<FReceiveResult> WithItem(const TSharedPtr<Model::FReceiveStatus> Item);
        TSharedPtr<FReceiveResult> WithBonusModel(const TSharedPtr<Model::FBonusModel> BonusModel);
        TSharedPtr<FReceiveResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FReceiveResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FReceiveResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FReceiveResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);
        TSharedPtr<FReceiveResult> WithAtomicCommit(const TOptional<bool> AtomicCommit);
        TSharedPtr<FReceiveResult> WithTransaction(const TOptional<FString> Transaction);
        TSharedPtr<FReceiveResult> WithTransactionResult(const TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResult);

        TSharedPtr<Model::FReceiveStatus> GetItem() const;
        TSharedPtr<Model::FBonusModel> GetBonusModel() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;
        TOptional<bool> GetAtomicCommit() const;
        FString GetAtomicCommitString() const;
        TOptional<FString> GetTransaction() const;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> GetTransactionResult() const;

        static TSharedPtr<FReceiveResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReceiveResult, ESPMode::ThreadSafe> FReceiveResultPtr;
}