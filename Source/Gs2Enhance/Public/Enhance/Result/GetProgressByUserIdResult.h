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
#include "../Model/Progress.h"

namespace Gs2::Enhance::Result
{
    class GS2ENHANCE_API FGetProgressByUserIdResult final : public TSharedFromThis<FGetProgressByUserIdResult>
    {
        TSharedPtr<Model::FProgress> ItemValue;
        
    public:
        
        FGetProgressByUserIdResult();
        FGetProgressByUserIdResult(
            const FGetProgressByUserIdResult& From
        );
        ~FGetProgressByUserIdResult() = default;

        TSharedPtr<FGetProgressByUserIdResult> WithItem(const TSharedPtr<Model::FProgress> Item);

        TSharedPtr<Model::FProgress> GetItem() const;

        static TSharedPtr<FGetProgressByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetProgressByUserIdResult, ESPMode::ThreadSafe> FGetProgressByUserIdResultPtr;
}