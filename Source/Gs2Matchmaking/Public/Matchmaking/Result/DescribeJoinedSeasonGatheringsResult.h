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
#include "../Model/JoinedSeasonGathering.h"

namespace Gs2::Matchmaking::Result
{
    class GS2MATCHMAKING_API FDescribeJoinedSeasonGatheringsResult final : public TSharedFromThis<FDescribeJoinedSeasonGatheringsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FJoinedSeasonGathering>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeJoinedSeasonGatheringsResult();
        FDescribeJoinedSeasonGatheringsResult(
            const FDescribeJoinedSeasonGatheringsResult& From
        );
        ~FDescribeJoinedSeasonGatheringsResult() = default;

        TSharedPtr<FDescribeJoinedSeasonGatheringsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FJoinedSeasonGathering>>> Items);
        TSharedPtr<FDescribeJoinedSeasonGatheringsResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FJoinedSeasonGathering>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeJoinedSeasonGatheringsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeJoinedSeasonGatheringsResult, ESPMode::ThreadSafe> FDescribeJoinedSeasonGatheringsResultPtr;
}