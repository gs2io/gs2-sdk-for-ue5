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
#include "../Model/Stamina.h"
#include "../Model/StaminaModel.h"

namespace Gs2::Stamina::Result
{
    class GS2STAMINA_API FSetMaxValueByStampSheetResult final : public TSharedFromThis<FSetMaxValueByStampSheetResult>
    {
        TSharedPtr<Model::FStamina> ItemValue;
        TSharedPtr<Model::FStamina> OldValue;
        TSharedPtr<Model::FStaminaModel> StaminaModelValue;
        
    public:
        
        FSetMaxValueByStampSheetResult();
        FSetMaxValueByStampSheetResult(
            const FSetMaxValueByStampSheetResult& From
        );
        ~FSetMaxValueByStampSheetResult() = default;

        TSharedPtr<FSetMaxValueByStampSheetResult> WithItem(const TSharedPtr<Model::FStamina> Item);
        TSharedPtr<FSetMaxValueByStampSheetResult> WithOld(const TSharedPtr<Model::FStamina> Old);
        TSharedPtr<FSetMaxValueByStampSheetResult> WithStaminaModel(const TSharedPtr<Model::FStaminaModel> StaminaModel);

        TSharedPtr<Model::FStamina> GetItem() const;
        TSharedPtr<Model::FStamina> GetOld() const;
        TSharedPtr<Model::FStaminaModel> GetStaminaModel() const;

        static TSharedPtr<FSetMaxValueByStampSheetResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetMaxValueByStampSheetResult, ESPMode::ThreadSafe> FSetMaxValueByStampSheetResultPtr;
}