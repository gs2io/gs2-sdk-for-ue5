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
#include "../Model/WebSocketSession.h"

namespace Gs2::Gateway::Result
{
    class GS2GATEWAY_API FDescribeWebSocketSessionsByUserIdResult final : public TSharedFromThis<FDescribeWebSocketSessionsByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FWebSocketSession>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeWebSocketSessionsByUserIdResult();
        FDescribeWebSocketSessionsByUserIdResult(
            const FDescribeWebSocketSessionsByUserIdResult& From
        );
        ~FDescribeWebSocketSessionsByUserIdResult() = default;

        TSharedPtr<FDescribeWebSocketSessionsByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FWebSocketSession>>> Items);
        TSharedPtr<FDescribeWebSocketSessionsByUserIdResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FWebSocketSession>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeWebSocketSessionsByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeWebSocketSessionsByUserIdResult, ESPMode::ThreadSafe> FDescribeWebSocketSessionsByUserIdResultPtr;
}