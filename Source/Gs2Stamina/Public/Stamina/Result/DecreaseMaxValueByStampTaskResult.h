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
    class GS2STAMINA_API FDecreaseMaxValueByStampTaskResult final : public TSharedFromThis<FDecreaseMaxValueByStampTaskResult>
    {
        TSharedPtr<Model::FStamina> ItemValue;
        TSharedPtr<Model::FStaminaModel> StaminaModelValue;
        TOptional<FString> NewContextStackValue;
        
    public:
        
        FDecreaseMaxValueByStampTaskResult();
        FDecreaseMaxValueByStampTaskResult(
            const FDecreaseMaxValueByStampTaskResult& From
        );
        ~FDecreaseMaxValueByStampTaskResult() = default;

        TSharedPtr<FDecreaseMaxValueByStampTaskResult> WithItem(const TSharedPtr<Model::FStamina> Item);
        TSharedPtr<FDecreaseMaxValueByStampTaskResult> WithStaminaModel(const TSharedPtr<Model::FStaminaModel> StaminaModel);
        TSharedPtr<FDecreaseMaxValueByStampTaskResult> WithNewContextStack(const TOptional<FString> NewContextStack);

        TSharedPtr<Model::FStamina> GetItem() const;
        TSharedPtr<Model::FStaminaModel> GetStaminaModel() const;
        TOptional<FString> GetNewContextStack() const;

        static TSharedPtr<FDecreaseMaxValueByStampTaskResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDecreaseMaxValueByStampTaskResult, ESPMode::ThreadSafe> FDecreaseMaxValueByStampTaskResultPtr;
}