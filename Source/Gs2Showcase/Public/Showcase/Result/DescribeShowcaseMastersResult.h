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
#include "../Model/ShowcaseMaster.h"

namespace Gs2::Showcase::Result
{
    class GS2SHOWCASE_API FDescribeShowcaseMastersResult final : public TSharedFromThis<FDescribeShowcaseMastersResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FShowcaseMaster>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeShowcaseMastersResult();
        FDescribeShowcaseMastersResult(
            const FDescribeShowcaseMastersResult& From
        );
        ~FDescribeShowcaseMastersResult() = default;

        TSharedPtr<FDescribeShowcaseMastersResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FShowcaseMaster>>> Items);
        TSharedPtr<FDescribeShowcaseMastersResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FShowcaseMaster>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeShowcaseMastersResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeShowcaseMastersResult, ESPMode::ThreadSafe> FDescribeShowcaseMastersResultPtr;
}