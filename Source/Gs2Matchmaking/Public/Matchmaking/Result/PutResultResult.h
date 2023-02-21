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
    class GS2MATCHMAKING_API FPutResultResult final : public TSharedFromThis<FPutResultResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FRating>>> ItemsValue;
        
    public:
        
        FPutResultResult();
        FPutResultResult(
            const FPutResultResult& From
        );
        ~FPutResultResult() = default;

        TSharedPtr<FPutResultResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FRating>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FRating>>> GetItems() const;

        static TSharedPtr<FPutResultResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPutResultResult, ESPMode::ThreadSafe> FPutResultResultPtr;
}