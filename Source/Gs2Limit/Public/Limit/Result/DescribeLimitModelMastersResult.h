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
#include "../Model/LimitModelMaster.h"

namespace Gs2::Limit::Result
{
    class GS2LIMIT_API FDescribeLimitModelMastersResult final : public TSharedFromThis<FDescribeLimitModelMastersResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FLimitModelMaster>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeLimitModelMastersResult();
        FDescribeLimitModelMastersResult(
            const FDescribeLimitModelMastersResult& From
        );
        ~FDescribeLimitModelMastersResult() = default;

        TSharedPtr<FDescribeLimitModelMastersResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FLimitModelMaster>>> Items);
        TSharedPtr<FDescribeLimitModelMastersResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FLimitModelMaster>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeLimitModelMastersResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeLimitModelMastersResult, ESPMode::ThreadSafe> FDescribeLimitModelMastersResultPtr;
}