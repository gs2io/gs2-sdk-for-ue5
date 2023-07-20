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
#include "../Model/BalanceParameterModel.h"

namespace Gs2::Enchant::Result
{
    class GS2ENCHANT_API FDescribeBalanceParameterModelsResult final : public TSharedFromThis<FDescribeBalanceParameterModelsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterModel>>> ItemsValue;
        
    public:
        
        FDescribeBalanceParameterModelsResult();
        FDescribeBalanceParameterModelsResult(
            const FDescribeBalanceParameterModelsResult& From
        );
        ~FDescribeBalanceParameterModelsResult() = default;

        TSharedPtr<FDescribeBalanceParameterModelsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterModel>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FBalanceParameterModel>>> GetItems() const;

        static TSharedPtr<FDescribeBalanceParameterModelsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeBalanceParameterModelsResult, ESPMode::ThreadSafe> FDescribeBalanceParameterModelsResultPtr;
}