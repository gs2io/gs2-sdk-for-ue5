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
#include "../Model/Status.h"

namespace Gs2::SkillTree::Result
{
    class GS2SKILLTREE_API FMarkRestrainResult final : public TSharedFromThis<FMarkRestrainResult>
    {
        TSharedPtr<Model::FStatus> ItemValue;
        
    public:
        
        FMarkRestrainResult();
        FMarkRestrainResult(
            const FMarkRestrainResult& From
        );
        ~FMarkRestrainResult() = default;

        TSharedPtr<FMarkRestrainResult> WithItem(const TSharedPtr<Model::FStatus> Item);

        TSharedPtr<Model::FStatus> GetItem() const;

        static TSharedPtr<FMarkRestrainResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FMarkRestrainResult, ESPMode::ThreadSafe> FMarkRestrainResultPtr;
}