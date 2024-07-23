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
    class GS2GUILD_API FGetIgnoreUserByGuildNameResult final : public TSharedFromThis<FGetIgnoreUserByGuildNameResult>
    {
        TSharedPtr<Model::FIgnoreUser> ItemValue;
        
    public:
        
        FGetIgnoreUserByGuildNameResult();
        FGetIgnoreUserByGuildNameResult(
            const FGetIgnoreUserByGuildNameResult& From
        );
        ~FGetIgnoreUserByGuildNameResult() = default;

        TSharedPtr<FGetIgnoreUserByGuildNameResult> WithItem(const TSharedPtr<Model::FIgnoreUser> Item);

        TSharedPtr<Model::FIgnoreUser> GetItem() const;

        static TSharedPtr<FGetIgnoreUserByGuildNameResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetIgnoreUserByGuildNameResult, ESPMode::ThreadSafe> FGetIgnoreUserByGuildNameResultPtr;
}