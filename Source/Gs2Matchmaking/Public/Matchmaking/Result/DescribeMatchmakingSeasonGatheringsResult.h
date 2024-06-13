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
#include "../Model/SeasonGathering.h"

namespace Gs2::Matchmaking::Result
{
    class GS2MATCHMAKING_API FDescribeMatchmakingSeasonGatheringsResult final : public TSharedFromThis<FDescribeMatchmakingSeasonGatheringsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FSeasonGathering>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeMatchmakingSeasonGatheringsResult();
        FDescribeMatchmakingSeasonGatheringsResult(
            const FDescribeMatchmakingSeasonGatheringsResult& From
        );
        ~FDescribeMatchmakingSeasonGatheringsResult() = default;

        TSharedPtr<FDescribeMatchmakingSeasonGatheringsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FSeasonGathering>>> Items);
        TSharedPtr<FDescribeMatchmakingSeasonGatheringsResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FSeasonGathering>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeMatchmakingSeasonGatheringsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeMatchmakingSeasonGatheringsResult, ESPMode::ThreadSafe> FDescribeMatchmakingSeasonGatheringsResultPtr;
}