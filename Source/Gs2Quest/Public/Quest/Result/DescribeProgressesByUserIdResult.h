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
#include "../Model/Progress.h"

namespace Gs2::Quest::Result
{
    class GS2QUEST_API FDescribeProgressesByUserIdResult final : public TSharedFromThis<FDescribeProgressesByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FProgress>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeProgressesByUserIdResult();
        FDescribeProgressesByUserIdResult(
            const FDescribeProgressesByUserIdResult& From
        );
        ~FDescribeProgressesByUserIdResult() = default;

        TSharedPtr<FDescribeProgressesByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FProgress>>> Items);
        TSharedPtr<FDescribeProgressesByUserIdResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FProgress>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeProgressesByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeProgressesByUserIdResult, ESPMode::ThreadSafe> FDescribeProgressesByUserIdResultPtr;
}