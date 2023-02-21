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
#include "../Model/EntryModel.h"

namespace Gs2::Dictionary::Result
{
    class GS2DICTIONARY_API FDescribeEntryModelsResult final : public TSharedFromThis<FDescribeEntryModelsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FEntryModel>>> ItemsValue;
        
    public:
        
        FDescribeEntryModelsResult();
        FDescribeEntryModelsResult(
            const FDescribeEntryModelsResult& From
        );
        ~FDescribeEntryModelsResult() = default;

        TSharedPtr<FDescribeEntryModelsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FEntryModel>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FEntryModel>>> GetItems() const;

        static TSharedPtr<FDescribeEntryModelsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeEntryModelsResult, ESPMode::ThreadSafe> FDescribeEntryModelsResultPtr;
}