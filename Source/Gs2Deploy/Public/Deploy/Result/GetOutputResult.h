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
#include "../Model/Output.h"

namespace Gs2::Deploy::Result
{
    class GS2DEPLOY_API FGetOutputResult final : public TSharedFromThis<FGetOutputResult>
    {
        TSharedPtr<Model::FOutput> ItemValue;
        
    public:
        
        FGetOutputResult();
        FGetOutputResult(
            const FGetOutputResult& From
        );
        ~FGetOutputResult() = default;

        TSharedPtr<FGetOutputResult> WithItem(const TSharedPtr<Model::FOutput> Item);

        TSharedPtr<Model::FOutput> GetItem() const;

        static TSharedPtr<FGetOutputResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetOutputResult, ESPMode::ThreadSafe> FGetOutputResultPtr;
}