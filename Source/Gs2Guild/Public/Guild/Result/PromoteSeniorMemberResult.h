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
#include "../Model/LastGuildMasterActivity.h"
#include "../Model/Guild.h"

namespace Gs2::Guild::Result
{
    class GS2GUILD_API FPromoteSeniorMemberResult final : public TSharedFromThis<FPromoteSeniorMemberResult>
    {
        TSharedPtr<Model::FLastGuildMasterActivity> ItemValue;
        TSharedPtr<Model::FGuild> GuildValue;
        
    public:
        
        FPromoteSeniorMemberResult();
        FPromoteSeniorMemberResult(
            const FPromoteSeniorMemberResult& From
        );
        ~FPromoteSeniorMemberResult() = default;

        TSharedPtr<FPromoteSeniorMemberResult> WithItem(const TSharedPtr<Model::FLastGuildMasterActivity> Item);
        TSharedPtr<FPromoteSeniorMemberResult> WithGuild(const TSharedPtr<Model::FGuild> Guild);

        TSharedPtr<Model::FLastGuildMasterActivity> GetItem() const;
        TSharedPtr<Model::FGuild> GetGuild() const;

        static TSharedPtr<FPromoteSeniorMemberResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPromoteSeniorMemberResult, ESPMode::ThreadSafe> FPromoteSeniorMemberResultPtr;
}