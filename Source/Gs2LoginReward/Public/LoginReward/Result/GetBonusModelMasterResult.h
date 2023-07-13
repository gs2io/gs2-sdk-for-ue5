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
#include "../Model/BonusModelMaster.h"

namespace Gs2::LoginReward::Result
{
    class GS2LOGINREWARD_API FGetBonusModelMasterResult final : public TSharedFromThis<FGetBonusModelMasterResult>
    {
        TSharedPtr<Model::FBonusModelMaster> ItemValue;
        
    public:
        
        FGetBonusModelMasterResult();
        FGetBonusModelMasterResult(
            const FGetBonusModelMasterResult& From
        );
        ~FGetBonusModelMasterResult() = default;

        TSharedPtr<FGetBonusModelMasterResult> WithItem(const TSharedPtr<Model::FBonusModelMaster> Item);

        TSharedPtr<Model::FBonusModelMaster> GetItem() const;

        static TSharedPtr<FGetBonusModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetBonusModelMasterResult, ESPMode::ThreadSafe> FGetBonusModelMasterResultPtr;
}