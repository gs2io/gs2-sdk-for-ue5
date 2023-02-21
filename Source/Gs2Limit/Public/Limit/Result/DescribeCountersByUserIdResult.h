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
#include "../Model/Counter.h"

namespace Gs2::Limit::Result
{
    class GS2LIMIT_API FDescribeCountersByUserIdResult final : public TSharedFromThis<FDescribeCountersByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FCounter>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeCountersByUserIdResult();
        FDescribeCountersByUserIdResult(
            const FDescribeCountersByUserIdResult& From
        );
        ~FDescribeCountersByUserIdResult() = default;

        TSharedPtr<FDescribeCountersByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FCounter>>> Items);
        TSharedPtr<FDescribeCountersByUserIdResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FCounter>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeCountersByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeCountersByUserIdResult, ESPMode::ThreadSafe> FDescribeCountersByUserIdResultPtr;
}