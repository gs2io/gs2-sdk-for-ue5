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
    class GS2RANKING2_API FReceiveClusterRankingReceivedRewardResult final : public TSharedFromThis<FReceiveClusterRankingReceivedRewardResult>
    {
        TSharedPtr<Model::FClusterRankingModel> ItemValue;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActionsValue;
        TOptional<FString> TransactionIdValue;
        TOptional<FString> StampSheetValue;
        TOptional<FString> StampSheetEncryptionKeyIdValue;
        TOptional<bool> AutoRunStampSheetValue;
        
    public:
        
        FReceiveClusterRankingReceivedRewardResult();
        FReceiveClusterRankingReceivedRewardResult(
            const FReceiveClusterRankingReceivedRewardResult& From
        );
        ~FReceiveClusterRankingReceivedRewardResult() = default;

        TSharedPtr<FReceiveClusterRankingReceivedRewardResult> WithItem(const TSharedPtr<Model::FClusterRankingModel> Item);
        TSharedPtr<FReceiveClusterRankingReceivedRewardResult> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> AcquireActions);
        TSharedPtr<FReceiveClusterRankingReceivedRewardResult> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FReceiveClusterRankingReceivedRewardResult> WithStampSheet(const TOptional<FString> StampSheet);
        TSharedPtr<FReceiveClusterRankingReceivedRewardResult> WithStampSheetEncryptionKeyId(const TOptional<FString> StampSheetEncryptionKeyId);
        TSharedPtr<FReceiveClusterRankingReceivedRewardResult> WithAutoRunStampSheet(const TOptional<bool> AutoRunStampSheet);

        TSharedPtr<Model::FClusterRankingModel> GetItem() const;
        TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> GetAcquireActions() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<FString> GetStampSheet() const;
        TOptional<FString> GetStampSheetEncryptionKeyId() const;
        TOptional<bool> GetAutoRunStampSheet() const;
        FString GetAutoRunStampSheetString() const;

        static TSharedPtr<FReceiveClusterRankingReceivedRewardResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReceiveClusterRankingReceivedRewardResult, ESPMode::ThreadSafe> FReceiveClusterRankingReceivedRewardResultPtr;
}