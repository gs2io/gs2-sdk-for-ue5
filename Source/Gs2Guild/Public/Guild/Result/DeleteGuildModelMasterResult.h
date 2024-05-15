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
#include "../Model/GuildModelMaster.h"

namespace Gs2::Guild::Result
{
    class GS2GUILD_API FDeleteGuildModelMasterResult final : public TSharedFromThis<FDeleteGuildModelMasterResult>
    {
        TSharedPtr<Model::FGuildModelMaster> ItemValue;
        
    public:
        
        FDeleteGuildModelMasterResult();
        FDeleteGuildModelMasterResult(
            const FDeleteGuildModelMasterResult& From
        );
        ~FDeleteGuildModelMasterResult() = default;

        TSharedPtr<FDeleteGuildModelMasterResult> WithItem(const TSharedPtr<Model::FGuildModelMaster> Item);

        TSharedPtr<Model::FGuildModelMaster> GetItem() const;

        static TSharedPtr<FDeleteGuildModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteGuildModelMasterResult, ESPMode::ThreadSafe> FDeleteGuildModelMasterResultPtr;
}