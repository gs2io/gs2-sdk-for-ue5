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
#include "../Model/NodeModel.h"

namespace Gs2::SkillTree::Result
{
    class GS2SKILLTREE_API FDescribeStatusModelsResult final : public TSharedFromThis<FDescribeStatusModelsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FNodeModel>>> ItemsValue;
        
    public:
        
        FDescribeStatusModelsResult();
        FDescribeStatusModelsResult(
            const FDescribeStatusModelsResult& From
        );
        ~FDescribeStatusModelsResult() = default;

        TSharedPtr<FDescribeStatusModelsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FNodeModel>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FNodeModel>>> GetItems() const;

        static TSharedPtr<FDescribeStatusModelsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeStatusModelsResult, ESPMode::ThreadSafe> FDescribeStatusModelsResultPtr;
}