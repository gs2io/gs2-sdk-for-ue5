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
#include "Core/Gs2Object.h"
#include "AcquireAction.h"

namespace Gs2::Ranking2::Model
{
    class GS2RANKING2_API FRankingReward final : public FGs2Object, public TSharedFromThis<FRankingReward>
    {
        TOptional<int32> ThresholdRankValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActionsValue;

    public:
        FRankingReward();
        FRankingReward(
            const FRankingReward& From
        );
        virtual ~FRankingReward() override = default;

        TSharedPtr<FRankingReward> WithThresholdRank(const TOptional<int32> ThresholdRank);
        TSharedPtr<FRankingReward> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRankingReward> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActions);

        TOptional<int32> GetThresholdRank() const;
        FString GetThresholdRankString() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetAcquireActions() const;


        static TSharedPtr<FRankingReward> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRankingReward, ESPMode::ThreadSafe> FRankingRewardPtr;
}