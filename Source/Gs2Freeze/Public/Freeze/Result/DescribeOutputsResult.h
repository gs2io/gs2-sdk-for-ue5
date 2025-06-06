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
#include "../Model/Output.h"

namespace Gs2::Freeze::Result
{
    class GS2FREEZE_API FDescribeOutputsResult final : public TSharedFromThis<FDescribeOutputsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FOutput>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeOutputsResult();
        FDescribeOutputsResult(
            const FDescribeOutputsResult& From
        );
        ~FDescribeOutputsResult() = default;

        TSharedPtr<FDescribeOutputsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FOutput>>> Items);
        TSharedPtr<FDescribeOutputsResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FOutput>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeOutputsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeOutputsResult, ESPMode::ThreadSafe> FDescribeOutputsResultPtr;
}