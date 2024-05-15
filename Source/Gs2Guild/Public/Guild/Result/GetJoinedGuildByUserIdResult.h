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
#include "../Model/JoinedGuild.h"

namespace Gs2::Guild::Result
{
    class GS2GUILD_API FGetJoinedGuildByUserIdResult final : public TSharedFromThis<FGetJoinedGuildByUserIdResult>
    {
        TSharedPtr<Model::FJoinedGuild> ItemValue;
        
    public:
        
        FGetJoinedGuildByUserIdResult();
        FGetJoinedGuildByUserIdResult(
            const FGetJoinedGuildByUserIdResult& From
        );
        ~FGetJoinedGuildByUserIdResult() = default;

        TSharedPtr<FGetJoinedGuildByUserIdResult> WithItem(const TSharedPtr<Model::FJoinedGuild> Item);

        TSharedPtr<Model::FJoinedGuild> GetItem() const;

        static TSharedPtr<FGetJoinedGuildByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetJoinedGuildByUserIdResult, ESPMode::ThreadSafe> FGetJoinedGuildByUserIdResultPtr;
}