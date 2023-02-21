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
#include "../Model/Script.h"

namespace Gs2::Script::Result
{
    class GS2SCRIPT_API FDeleteScriptResult final : public TSharedFromThis<FDeleteScriptResult>
    {
        TSharedPtr<Model::FScript> ItemValue;
        
    public:
        
        FDeleteScriptResult();
        FDeleteScriptResult(
            const FDeleteScriptResult& From
        );
        ~FDeleteScriptResult() = default;

        TSharedPtr<FDeleteScriptResult> WithItem(const TSharedPtr<Model::FScript> Item);

        TSharedPtr<Model::FScript> GetItem() const;

        static TSharedPtr<FDeleteScriptResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteScriptResult, ESPMode::ThreadSafe> FDeleteScriptResultPtr;
}