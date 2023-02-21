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
#include "../Model/Showcase.h"

namespace Gs2::Showcase::Result
{
    class GS2SHOWCASE_API FGetShowcaseByUserIdResult final : public TSharedFromThis<FGetShowcaseByUserIdResult>
    {
        TSharedPtr<Model::FShowcase> ItemValue;
        
    public:
        
        FGetShowcaseByUserIdResult();
        FGetShowcaseByUserIdResult(
            const FGetShowcaseByUserIdResult& From
        );
        ~FGetShowcaseByUserIdResult() = default;

        TSharedPtr<FGetShowcaseByUserIdResult> WithItem(const TSharedPtr<Model::FShowcase> Item);

        TSharedPtr<Model::FShowcase> GetItem() const;

        static TSharedPtr<FGetShowcaseByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetShowcaseByUserIdResult, ESPMode::ThreadSafe> FGetShowcaseByUserIdResultPtr;
}