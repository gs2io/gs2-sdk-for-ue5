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
#include "../Model/RatingModel.h"

namespace Gs2::Matchmaking::Result
{
    class GS2MATCHMAKING_API FDescribeRatingModelsResult final : public TSharedFromThis<FDescribeRatingModelsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FRatingModel>>> ItemsValue;
        
    public:
        
        FDescribeRatingModelsResult();
        FDescribeRatingModelsResult(
            const FDescribeRatingModelsResult& From
        );
        ~FDescribeRatingModelsResult() = default;

        TSharedPtr<FDescribeRatingModelsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FRatingModel>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FRatingModel>>> GetItems() const;

        static TSharedPtr<FDescribeRatingModelsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeRatingModelsResult, ESPMode::ThreadSafe> FDescribeRatingModelsResultPtr;
}