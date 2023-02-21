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
#include "../Model/PropertyForm.h"

namespace Gs2::Formation::Result
{
    class GS2FORMATION_API FDescribePropertyFormsByUserIdResult final : public TSharedFromThis<FDescribePropertyFormsByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FPropertyForm>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribePropertyFormsByUserIdResult();
        FDescribePropertyFormsByUserIdResult(
            const FDescribePropertyFormsByUserIdResult& From
        );
        ~FDescribePropertyFormsByUserIdResult() = default;

        TSharedPtr<FDescribePropertyFormsByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FPropertyForm>>> Items);
        TSharedPtr<FDescribePropertyFormsByUserIdResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FPropertyForm>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribePropertyFormsByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribePropertyFormsByUserIdResult, ESPMode::ThreadSafe> FDescribePropertyFormsByUserIdResultPtr;
}