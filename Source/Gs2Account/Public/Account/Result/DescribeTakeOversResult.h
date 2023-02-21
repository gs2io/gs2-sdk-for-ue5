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
#include "../Model/TakeOver.h"

namespace Gs2::Account::Result
{
    class GS2ACCOUNT_API FDescribeTakeOversResult final : public TSharedFromThis<FDescribeTakeOversResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FTakeOver>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeTakeOversResult();
        FDescribeTakeOversResult(
            const FDescribeTakeOversResult& From
        );
        ~FDescribeTakeOversResult() = default;

        TSharedPtr<FDescribeTakeOversResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FTakeOver>>> Items);
        TSharedPtr<FDescribeTakeOversResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FTakeOver>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeTakeOversResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeTakeOversResult, ESPMode::ThreadSafe> FDescribeTakeOversResultPtr;
}