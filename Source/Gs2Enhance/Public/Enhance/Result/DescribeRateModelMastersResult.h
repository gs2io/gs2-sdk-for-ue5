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
#include "../Model/RateModelMaster.h"

namespace Gs2::Enhance::Result
{
    class GS2ENHANCE_API FDescribeRateModelMastersResult final : public TSharedFromThis<FDescribeRateModelMastersResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FRateModelMaster>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeRateModelMastersResult();
        FDescribeRateModelMastersResult(
            const FDescribeRateModelMastersResult& From
        );
        ~FDescribeRateModelMastersResult() = default;

        TSharedPtr<FDescribeRateModelMastersResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FRateModelMaster>>> Items);
        TSharedPtr<FDescribeRateModelMastersResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FRateModelMaster>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeRateModelMastersResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeRateModelMastersResult, ESPMode::ThreadSafe> FDescribeRateModelMastersResultPtr;
}