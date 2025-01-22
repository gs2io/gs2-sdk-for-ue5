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
#include "../Model/GlobalRankingModel.h"
#include "../Model/AcquireAction.h"
#include "Gs2Core/Public/Core/Model/TransactionResult.h"

namespace Gs2::Ranking2::Result
{
    class GS2RANKING2_API FReceiveGlobalRankingReceivedRewardByUserIdResult final : public TSharedFromThis<FReceiveGlobalRankingReceivedRewardByUserIdResult>
    {
        TSharedPtr<Model::FGlobalRankingModel> ItemValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActionsValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        TOptional<bool> AtomicCommitValue;
        TOptional<FString> TransactionValue;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResultValue;
        
    public:
        
        FReceiveGlobalRankingReceivedRewardByUserIdResult();
        FReceiveGlobalRankingReceivedRewardByUserIdResult(
            const FReceiveGlobalRankingReceivedRewardByUserIdResult& From
        );
        ~FReceiveGlobalRankingReceivedRewardByUserIdResult() = default;

        TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdResult> WithItem(const TSharedPtr<Model::FGlobalRankingModel> Item);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdResult> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdResult> WithAtomicCommit(const TOptional<bool> AtomicCommit);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdResult> WithTransaction(const TOptional<FString> Transaction);
        TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdResult> WithTransactionResult(const TSharedPtr<Gs2::Core::Model::FTransactionResult> TransactionResult);

        TSharedPtr<Model::FGlobalRankingModel> GetItem() const;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetAcquireActions() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;
        TOptional<bool> GetAtomicCommit() const;
        FString GetAtomicCommitString() const;
        TOptional<FString> GetTransaction() const;
        TSharedPtr<Gs2::Core::Model::FTransactionResult> GetTransactionResult() const;

        static TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReceiveGlobalRankingReceivedRewardByUserIdResult, ESPMode::ThreadSafe> FReceiveGlobalRankingReceivedRewardByUserIdResultPtr;
}