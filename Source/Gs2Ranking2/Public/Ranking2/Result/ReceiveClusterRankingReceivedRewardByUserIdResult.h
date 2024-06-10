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
#include "../Model/ClusterRankingModel.h"
#include "../Model/AcquireAction.h"

namespace Gs2::Ranking2::Result
{
    class GS2RANKING2_API FReceiveClusterRankingReceivedRewardByUserIdResult final : public TSharedFromThis<FReceiveClusterRankingReceivedRewardByUserIdResult>
    {
        TSharedPtr<Model::FClusterRankingModel> ItemValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActionsValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FReceiveClusterRankingReceivedRewardByUserIdResult();
        FReceiveClusterRankingReceivedRewardByUserIdResult(
            const FReceiveClusterRankingReceivedRewardByUserIdResult& From
        );
        ~FReceiveClusterRankingReceivedRewardByUserIdResult() = default;

        TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdResult> WithItem(const TSharedPtr<Model::FClusterRankingModel> Item);
        TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdResult> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions);
        TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TSharedPtr<Model::FClusterRankingModel> GetItem() const;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetAcquireActions() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdResult, ESPMode::ThreadSafe> FReceiveClusterRankingReceivedRewardByUserIdResultPtr;
}