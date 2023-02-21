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
#include "../Model/MaxStaminaTableMaster.h"

namespace Gs2::Stamina::Result
{
    class GS2STAMINA_API FDeleteMaxStaminaTableMasterResult final : public TSharedFromThis<FDeleteMaxStaminaTableMasterResult>
    {
        TSharedPtr<Model::FMaxStaminaTableMaster> ItemValue;
        
    public:
        
        FDeleteMaxStaminaTableMasterResult();
        FDeleteMaxStaminaTableMasterResult(
            const FDeleteMaxStaminaTableMasterResult& From
        );
        ~FDeleteMaxStaminaTableMasterResult() = default;

        TSharedPtr<FDeleteMaxStaminaTableMasterResult> WithItem(const TSharedPtr<Model::FMaxStaminaTableMaster> Item);

        TSharedPtr<Model::FMaxStaminaTableMaster> GetItem() const;

        static TSharedPtr<FDeleteMaxStaminaTableMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteMaxStaminaTableMasterResult, ESPMode::ThreadSafe> FDeleteMaxStaminaTableMasterResultPtr;
}