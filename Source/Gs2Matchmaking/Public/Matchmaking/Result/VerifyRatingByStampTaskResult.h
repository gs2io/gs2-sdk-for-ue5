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
    class GS2MATCHMAKING_API FVerifyRatingByStampTaskResult final : public TSharedFromThis<FVerifyRatingByStampTaskResult>
    {
        TSharedPtr<Model::FRating> ItemValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FVerifyRatingByStampTaskResult();
        FVerifyRatingByStampTaskResult(
            const FVerifyRatingByStampTaskResult& From
        );
        ~FVerifyRatingByStampTaskResult() = default;

        TSharedPtr<FVerifyRatingByStampTaskResult> WithItem(const TSharedPtr<Model::FRating> Item);
        TSharedPtr<FVerifyRatingByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FRating> GetItem() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FVerifyRatingByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyRatingByStampTaskResult, ESPMode::ThreadSafe> FVerifyRatingByStampTaskResultPtr;
}