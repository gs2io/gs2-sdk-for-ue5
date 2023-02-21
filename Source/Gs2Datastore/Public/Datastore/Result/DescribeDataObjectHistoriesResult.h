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
#include "../Model/DataObjectHistory.h"

namespace Gs2::Datastore::Result
{
    class GS2DATASTORE_API FDescribeDataObjectHistoriesResult final : public TSharedFromThis<FDescribeDataObjectHistoriesResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FDataObjectHistory>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeDataObjectHistoriesResult();
        FDescribeDataObjectHistoriesResult(
            const FDescribeDataObjectHistoriesResult& From
        );
        ~FDescribeDataObjectHistoriesResult() = default;

        TSharedPtr<FDescribeDataObjectHistoriesResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FDataObjectHistory>>> Items);
        TSharedPtr<FDescribeDataObjectHistoriesResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FDataObjectHistory>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeDataObjectHistoriesResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeDataObjectHistoriesResult, ESPMode::ThreadSafe> FDescribeDataObjectHistoriesResultPtr;
}