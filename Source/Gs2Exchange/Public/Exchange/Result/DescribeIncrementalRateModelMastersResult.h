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
#include "../Model/IncrementalRateModelMaster.h"

namespace Gs2::Exchange::Result
{
    class GS2EXCHANGE_API FDescribeIncrementalRateModelMastersResult final : public TSharedFromThis<FDescribeIncrementalRateModelMastersResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FIncrementalRateModelMaster>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeIncrementalRateModelMastersResult();
        FDescribeIncrementalRateModelMastersResult(
            const FDescribeIncrementalRateModelMastersResult& From
        );
        ~FDescribeIncrementalRateModelMastersResult() = default;

        TSharedPtr<FDescribeIncrementalRateModelMastersResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FIncrementalRateModelMaster>>> Items);
        TSharedPtr<FDescribeIncrementalRateModelMastersResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FIncrementalRateModelMaster>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeIncrementalRateModelMastersResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeIncrementalRateModelMastersResult, ESPMode::ThreadSafe> FDescribeIncrementalRateModelMastersResultPtr;
}