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
#include "../Model/Receipt.h"

namespace Gs2::Money::Result
{
    class GS2MONEY_API FDescribeReceiptsResult final : public TSharedFromThis<FDescribeReceiptsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FReceipt>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeReceiptsResult();
        FDescribeReceiptsResult(
            const FDescribeReceiptsResult& From
        );
        ~FDescribeReceiptsResult() = default;

        TSharedPtr<FDescribeReceiptsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FReceipt>>> Items);
        TSharedPtr<FDescribeReceiptsResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FReceipt>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeReceiptsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeReceiptsResult, ESPMode::ThreadSafe> FDescribeReceiptsResultPtr;
}