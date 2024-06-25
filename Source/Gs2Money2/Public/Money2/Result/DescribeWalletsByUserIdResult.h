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
#include "../Model/Wallet.h"

namespace Gs2::Money2::Result
{
    class GS2MONEY2_API FDescribeWalletsByUserIdResult final : public TSharedFromThis<FDescribeWalletsByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FWallet>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeWalletsByUserIdResult();
        FDescribeWalletsByUserIdResult(
            const FDescribeWalletsByUserIdResult& From
        );
        ~FDescribeWalletsByUserIdResult() = default;

        TSharedPtr<FDescribeWalletsByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FWallet>>> Items);
        TSharedPtr<FDescribeWalletsByUserIdResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FWallet>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeWalletsByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeWalletsByUserIdResult, ESPMode::ThreadSafe> FDescribeWalletsByUserIdResultPtr;
}