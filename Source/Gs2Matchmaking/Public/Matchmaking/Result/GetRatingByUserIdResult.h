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
#include "../Model/Rating.h"

namespace Gs2::Matchmaking::Result
{
    class GS2MATCHMAKING_API FGetRatingByUserIdResult final : public TSharedFromThis<FGetRatingByUserIdResult>
    {
        TSharedPtr<Model::FRating> ItemValue;
        
    public:
        
        FGetRatingByUserIdResult();
        FGetRatingByUserIdResult(
            const FGetRatingByUserIdResult& From
        );
        ~FGetRatingByUserIdResult() = default;

        TSharedPtr<FGetRatingByUserIdResult> WithItem(const TSharedPtr<Model::FRating> Item);

        TSharedPtr<Model::FRating> GetItem() const;

        static TSharedPtr<FGetRatingByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetRatingByUserIdResult, ESPMode::ThreadSafe> FGetRatingByUserIdResultPtr;
}