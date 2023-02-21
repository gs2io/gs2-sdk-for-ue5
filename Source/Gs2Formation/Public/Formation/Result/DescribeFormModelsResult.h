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
#include "../Model/FormModel.h"

namespace Gs2::Formation::Result
{
    class GS2FORMATION_API FDescribeFormModelsResult final : public TSharedFromThis<FDescribeFormModelsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FFormModel>>> ItemsValue;
        
    public:
        
        FDescribeFormModelsResult();
        FDescribeFormModelsResult(
            const FDescribeFormModelsResult& From
        );
        ~FDescribeFormModelsResult() = default;

        TSharedPtr<FDescribeFormModelsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FFormModel>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FFormModel>>> GetItems() const;

        static TSharedPtr<FDescribeFormModelsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeFormModelsResult, ESPMode::ThreadSafe> FDescribeFormModelsResultPtr;
}