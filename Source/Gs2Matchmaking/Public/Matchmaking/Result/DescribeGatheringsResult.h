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
#include "../Model/Gathering.h"

namespace Gs2::Matchmaking::Result
{
    class GS2MATCHMAKING_API FDescribeGatheringsResult final : public TSharedFromThis<FDescribeGatheringsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FGathering>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeGatheringsResult();
        FDescribeGatheringsResult(
            const FDescribeGatheringsResult& From
        );
        ~FDescribeGatheringsResult() = default;

        TSharedPtr<FDescribeGatheringsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FGathering>>> Items);
        TSharedPtr<FDescribeGatheringsResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FGathering>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeGatheringsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeGatheringsResult, ESPMode::ThreadSafe> FDescribeGatheringsResultPtr;
}