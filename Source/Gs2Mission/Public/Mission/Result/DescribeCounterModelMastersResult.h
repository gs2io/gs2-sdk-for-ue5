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
#include "../Model/CounterModelMaster.h"

namespace Gs2::Mission::Result
{
    class GS2MISSION_API FDescribeCounterModelMastersResult final : public TSharedFromThis<FDescribeCounterModelMastersResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FCounterModelMaster>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeCounterModelMastersResult();
        FDescribeCounterModelMastersResult(
            const FDescribeCounterModelMastersResult& From
        );
        ~FDescribeCounterModelMastersResult() = default;

        TSharedPtr<FDescribeCounterModelMastersResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FCounterModelMaster>>> Items);
        TSharedPtr<FDescribeCounterModelMastersResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FCounterModelMaster>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeCounterModelMastersResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeCounterModelMastersResult, ESPMode::ThreadSafe> FDescribeCounterModelMastersResultPtr;
}