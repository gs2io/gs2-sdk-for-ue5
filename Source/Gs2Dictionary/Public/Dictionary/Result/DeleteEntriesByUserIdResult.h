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
#include "../Model/Entry.h"

namespace Gs2::Dictionary::Result
{
    class GS2DICTIONARY_API FDeleteEntriesByUserIdResult final : public TSharedFromThis<FDeleteEntriesByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FEntry>>> ItemsValue;
        
    public:
        
        FDeleteEntriesByUserIdResult();
        FDeleteEntriesByUserIdResult(
            const FDeleteEntriesByUserIdResult& From
        );
        ~FDeleteEntriesByUserIdResult() = default;

        TSharedPtr<FDeleteEntriesByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FEntry>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FEntry>>> GetItems() const;

        static TSharedPtr<FDeleteEntriesByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteEntriesByUserIdResult, ESPMode::ThreadSafe> FDeleteEntriesByUserIdResultPtr;
}