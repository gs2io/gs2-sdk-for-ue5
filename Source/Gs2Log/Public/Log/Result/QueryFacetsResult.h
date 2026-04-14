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
#include "../Model/Facet.h"

namespace Gs2::Log::Result
{
    class GS2LOG_API FQueryFacetsResult final : public TSharedFromThis<FQueryFacetsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FFacet>>> ItemsValue;
        
    public:
        
        FQueryFacetsResult();
        FQueryFacetsResult(
            const FQueryFacetsResult& From
        );
        ~FQueryFacetsResult() = default;

        TSharedPtr<FQueryFacetsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FFacet>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FFacet>>> GetItems() const;

        static TSharedPtr<FQueryFacetsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FQueryFacetsResult, ESPMode::ThreadSafe> FQueryFacetsResultPtr;
}