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
#include "../Model/StaminaModel.h"

namespace Gs2::Stamina::Result
{
    class GS2STAMINA_API FDescribeStaminaModelsResult final : public TSharedFromThis<FDescribeStaminaModelsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FStaminaModel>>> ItemsValue;
        
    public:
        
        FDescribeStaminaModelsResult();
        FDescribeStaminaModelsResult(
            const FDescribeStaminaModelsResult& From
        );
        ~FDescribeStaminaModelsResult() = default;

        TSharedPtr<FDescribeStaminaModelsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FStaminaModel>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FStaminaModel>>> GetItems() const;

        static TSharedPtr<FDescribeStaminaModelsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeStaminaModelsResult, ESPMode::ThreadSafe> FDescribeStaminaModelsResultPtr;
}