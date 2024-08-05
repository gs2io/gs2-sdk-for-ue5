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
#include "../Model/Insight.h"

namespace Gs2::Log::Result
{
    class GS2LOG_API FCreateInsightResult final : public TSharedFromThis<FCreateInsightResult>
    {
        TSharedPtr<Model::FInsight> ItemValue;
        
    public:
        
        FCreateInsightResult();
        FCreateInsightResult(
            const FCreateInsightResult& From
        );
        ~FCreateInsightResult() = default;

        TSharedPtr<FCreateInsightResult> WithItem(const TSharedPtr<Model::FInsight> Item);

        TSharedPtr<Model::FInsight> GetItem() const;

        static TSharedPtr<FCreateInsightResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateInsightResult, ESPMode::ThreadSafe> FCreateInsightResultPtr;
}