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
#include "../Model/Guild.h"

namespace Gs2::Guild::Result
{
    class GS2GUILD_API FSearchGuildsByUserIdResult final : public TSharedFromThis<FSearchGuildsByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FGuild>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FSearchGuildsByUserIdResult();
        FSearchGuildsByUserIdResult(
            const FSearchGuildsByUserIdResult& From
        );
        ~FSearchGuildsByUserIdResult() = default;

        TSharedPtr<FSearchGuildsByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FGuild>>> Items);
        TSharedPtr<FSearchGuildsByUserIdResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FGuild>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FSearchGuildsByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSearchGuildsByUserIdResult, ESPMode::ThreadSafe> FSearchGuildsByUserIdResultPtr;
}