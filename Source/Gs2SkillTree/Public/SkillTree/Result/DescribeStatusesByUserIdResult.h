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
#include "../Model/Status.h"

namespace Gs2::SkillTree::Result
{
    class GS2SKILLTREE_API FDescribeStatusesByUserIdResult final : public TSharedFromThis<FDescribeStatusesByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FStatus>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeStatusesByUserIdResult();
        FDescribeStatusesByUserIdResult(
            const FDescribeStatusesByUserIdResult& From
        );
        ~FDescribeStatusesByUserIdResult() = default;

        TSharedPtr<FDescribeStatusesByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FStatus>>> Items);
        TSharedPtr<FDescribeStatusesByUserIdResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FStatus>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeStatusesByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeStatusesByUserIdResult, ESPMode::ThreadSafe> FDescribeStatusesByUserIdResultPtr;
}