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
#include "../Model/LimitModel.h"

namespace Gs2::Limit::Result
{
    class GS2LIMIT_API FDescribeLimitModelsResult final : public TSharedFromThis<FDescribeLimitModelsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FLimitModel>>> ItemsValue;
        
    public:
        
        FDescribeLimitModelsResult();
        FDescribeLimitModelsResult(
            const FDescribeLimitModelsResult& From
        );
        ~FDescribeLimitModelsResult() = default;

        TSharedPtr<FDescribeLimitModelsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FLimitModel>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FLimitModel>>> GetItems() const;

        static TSharedPtr<FDescribeLimitModelsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeLimitModelsResult, ESPMode::ThreadSafe> FDescribeLimitModelsResultPtr;
}