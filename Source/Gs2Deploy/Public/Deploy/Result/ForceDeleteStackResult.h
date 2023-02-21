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
#include "../Model/Stack.h"

namespace Gs2::Deploy::Result
{
    class GS2DEPLOY_API FForceDeleteStackResult final : public TSharedFromThis<FForceDeleteStackResult>
    {
        TSharedPtr<Model::FStack> ItemValue;
        
    public:
        
        FForceDeleteStackResult();
        FForceDeleteStackResult(
            const FForceDeleteStackResult& From
        );
        ~FForceDeleteStackResult() = default;

        TSharedPtr<FForceDeleteStackResult> WithItem(const TSharedPtr<Model::FStack> Item);

        TSharedPtr<Model::FStack> GetItem() const;

        static TSharedPtr<FForceDeleteStackResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FForceDeleteStackResult, ESPMode::ThreadSafe> FForceDeleteStackResultPtr;
}