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
#include "../Model/Resource.h"

namespace Gs2::Deploy::Result
{
    class GS2DEPLOY_API FGetResourceResult final : public TSharedFromThis<FGetResourceResult>
    {
        TSharedPtr<Model::FResource> ItemValue;
        
    public:
        
        FGetResourceResult();
        FGetResourceResult(
            const FGetResourceResult& From
        );
        ~FGetResourceResult() = default;

        TSharedPtr<FGetResourceResult> WithItem(const TSharedPtr<Model::FResource> Item);

        TSharedPtr<Model::FResource> GetItem() const;

        static TSharedPtr<FGetResourceResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetResourceResult, ESPMode::ThreadSafe> FGetResourceResultPtr;
}