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
#include "../Model/Like.h"

namespace Gs2::Dictionary::Result
{
    class GS2DICTIONARY_API FAddLikesByUserIdResult final : public TSharedFromThis<FAddLikesByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FLike>>> ItemsValue;
        
    public:
        
        FAddLikesByUserIdResult();
        FAddLikesByUserIdResult(
            const FAddLikesByUserIdResult& From
        );
        ~FAddLikesByUserIdResult() = default;

        TSharedPtr<FAddLikesByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FLike>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FLike>>> GetItems() const;

        static TSharedPtr<FAddLikesByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAddLikesByUserIdResult, ESPMode::ThreadSafe> FAddLikesByUserIdResultPtr;
}