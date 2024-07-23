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
    class GS2GUILD_API FDeleteIgnoreUserByGuildNameResult final : public TSharedFromThis<FDeleteIgnoreUserByGuildNameResult>
    {
        TSharedPtr<Model::FIgnoreUser> ItemValue;
        
    public:
        
        FDeleteIgnoreUserByGuildNameResult();
        FDeleteIgnoreUserByGuildNameResult(
            const FDeleteIgnoreUserByGuildNameResult& From
        );
        ~FDeleteIgnoreUserByGuildNameResult() = default;

        TSharedPtr<FDeleteIgnoreUserByGuildNameResult> WithItem(const TSharedPtr<Model::FIgnoreUser> Item);

        TSharedPtr<Model::FIgnoreUser> GetItem() const;

        static TSharedPtr<FDeleteIgnoreUserByGuildNameResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteIgnoreUserByGuildNameResult, ESPMode::ThreadSafe> FDeleteIgnoreUserByGuildNameResultPtr;
}