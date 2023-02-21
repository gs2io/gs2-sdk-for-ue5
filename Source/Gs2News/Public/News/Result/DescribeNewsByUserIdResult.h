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
#include "../Model/News.h"

namespace Gs2::News::Result
{
    class GS2NEWS_API FDescribeNewsByUserIdResult final : public TSharedFromThis<FDescribeNewsByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FNews>>> ItemsValue;
        TOptional<FString> ContentHashValue;
        TOptional<FString> TemplateHashValue;
        
    public:
        
        FDescribeNewsByUserIdResult();
        FDescribeNewsByUserIdResult(
            const FDescribeNewsByUserIdResult& From
        );
        ~FDescribeNewsByUserIdResult() = default;

        TSharedPtr<FDescribeNewsByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FNews>>> Items);
        TSharedPtr<FDescribeNewsByUserIdResult> WithContentHash(const TOptional<FString> ContentHash);
        TSharedPtr<FDescribeNewsByUserIdResult> WithTemplateHash(const TOptional<FString> TemplateHash);

        TSharedPtr<TArray<TSharedPtr<Model::FNews>>> GetItems() const;
        TOptional<FString> GetContentHash() const;
        TOptional<FString> GetTemplateHash() const;

        static TSharedPtr<FDescribeNewsByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeNewsByUserIdResult, ESPMode::ThreadSafe> FDescribeNewsByUserIdResultPtr;
}