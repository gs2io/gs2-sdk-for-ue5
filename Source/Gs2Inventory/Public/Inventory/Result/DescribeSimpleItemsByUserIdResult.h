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
#include "../Model/SimpleItem.h"

namespace Gs2::Inventory::Result
{
    class GS2INVENTORY_API FDescribeSimpleItemsByUserIdResult final : public TSharedFromThis<FDescribeSimpleItemsByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FSimpleItem>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeSimpleItemsByUserIdResult();
        FDescribeSimpleItemsByUserIdResult(
            const FDescribeSimpleItemsByUserIdResult& From
        );
        ~FDescribeSimpleItemsByUserIdResult() = default;

        TSharedPtr<FDescribeSimpleItemsByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FSimpleItem>>> Items);
        TSharedPtr<FDescribeSimpleItemsByUserIdResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FSimpleItem>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeSimpleItemsByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeSimpleItemsByUserIdResult, ESPMode::ThreadSafe> FDescribeSimpleItemsByUserIdResultPtr;
}