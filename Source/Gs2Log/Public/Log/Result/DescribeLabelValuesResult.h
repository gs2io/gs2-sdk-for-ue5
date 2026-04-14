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
#include "../Model/Label.h"

namespace Gs2::Log::Result
{
    class GS2LOG_API FDescribeLabelValuesResult final : public TSharedFromThis<FDescribeLabelValuesResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FLabel>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeLabelValuesResult();
        FDescribeLabelValuesResult(
            const FDescribeLabelValuesResult& From
        );
        ~FDescribeLabelValuesResult() = default;

        TSharedPtr<FDescribeLabelValuesResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FLabel>>> Items);
        TSharedPtr<FDescribeLabelValuesResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FLabel>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeLabelValuesResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeLabelValuesResult, ESPMode::ThreadSafe> FDescribeLabelValuesResultPtr;
}