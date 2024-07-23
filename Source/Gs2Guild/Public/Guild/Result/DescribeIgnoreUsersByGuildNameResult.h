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
#include "../Model/IgnoreUser.h"

namespace Gs2::Guild::Result
{
    class GS2GUILD_API FDescribeIgnoreUsersByGuildNameResult final : public TSharedFromThis<FDescribeIgnoreUsersByGuildNameResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FIgnoreUser>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeIgnoreUsersByGuildNameResult();
        FDescribeIgnoreUsersByGuildNameResult(
            const FDescribeIgnoreUsersByGuildNameResult& From
        );
        ~FDescribeIgnoreUsersByGuildNameResult() = default;

        TSharedPtr<FDescribeIgnoreUsersByGuildNameResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FIgnoreUser>>> Items);
        TSharedPtr<FDescribeIgnoreUsersByGuildNameResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FIgnoreUser>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeIgnoreUsersByGuildNameResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeIgnoreUsersByGuildNameResult, ESPMode::ThreadSafe> FDescribeIgnoreUsersByGuildNameResultPtr;
}