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
#include "../Model/FollowUser.h"

namespace Gs2::Friend::Result
{
    class GS2FRIEND_API FDescribeFollowsResult final : public TSharedFromThis<FDescribeFollowsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FFollowUser>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeFollowsResult();
        FDescribeFollowsResult(
            const FDescribeFollowsResult& From
        );
        ~FDescribeFollowsResult() = default;

        TSharedPtr<FDescribeFollowsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FFollowUser>>> Items);
        TSharedPtr<FDescribeFollowsResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FFollowUser>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeFollowsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeFollowsResult, ESPMode::ThreadSafe> FDescribeFollowsResultPtr;
}