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
#include "../Model/Room.h"

namespace Gs2::Realtime::Result
{
    class GS2REALTIME_API FDescribeRoomsResult final : public TSharedFromThis<FDescribeRoomsResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FRoom>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeRoomsResult();
        FDescribeRoomsResult(
            const FDescribeRoomsResult& From
        );
        ~FDescribeRoomsResult() = default;

        TSharedPtr<FDescribeRoomsResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FRoom>>> Items);
        TSharedPtr<FDescribeRoomsResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FRoom>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeRoomsResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeRoomsResult, ESPMode::ThreadSafe> FDescribeRoomsResultPtr;
}