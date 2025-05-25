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

namespace Gs2::Ranking2::Result
{
    class GS2RANKING2_API FGetServiceVersionResult final : public TSharedFromThis<FGetServiceVersionResult>
    {
        TOptional<FString> ItemValue;
        
    public:
        
        FGetServiceVersionResult();
        FGetServiceVersionResult(
            const FGetServiceVersionResult& From
        );
        ~FGetServiceVersionResult() = default;

        TSharedPtr<FGetServiceVersionResult> WithItem(const TOptional<FString> Item);

        TOptional<FString> GetItem() const;

        static TSharedPtr<FGetServiceVersionResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetServiceVersionResult, ESPMode::ThreadSafe> FGetServiceVersionResultPtr;
}