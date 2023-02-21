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
#include "../Model/Identifier.h"

namespace Gs2::Identifier::Result
{
    class GS2IDENTIFIER_API FDescribeIdentifiersResult final : public TSharedFromThis<FDescribeIdentifiersResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FIdentifier>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeIdentifiersResult();
        FDescribeIdentifiersResult(
            const FDescribeIdentifiersResult& From
        );
        ~FDescribeIdentifiersResult() = default;

        TSharedPtr<FDescribeIdentifiersResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FIdentifier>>> Items);
        TSharedPtr<FDescribeIdentifiersResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FIdentifier>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeIdentifiersResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeIdentifiersResult, ESPMode::ThreadSafe> FDescribeIdentifiersResultPtr;
}