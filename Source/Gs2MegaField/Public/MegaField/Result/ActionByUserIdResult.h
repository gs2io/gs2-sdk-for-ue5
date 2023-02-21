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
#include "../Model/Spatial.h"

namespace Gs2::MegaField::Result
{
    class GS2MEGAFIELD_API FActionByUserIdResult final : public TSharedFromThis<FActionByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FSpatial>>> ItemsValue;
        
    public:
        
        FActionByUserIdResult();
        FActionByUserIdResult(
            const FActionByUserIdResult& From
        );
        ~FActionByUserIdResult() = default;

        TSharedPtr<FActionByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FSpatial>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FSpatial>>> GetItems() const;

        static TSharedPtr<FActionByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FActionByUserIdResult, ESPMode::ThreadSafe> FActionByUserIdResultPtr;
}