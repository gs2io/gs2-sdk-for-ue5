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
#include "../Model/Message.h"

namespace Gs2::Chat::Result
{
    class GS2CHAT_API FDescribeLatestMessagesByUserIdResult final : public TSharedFromThis<FDescribeLatestMessagesByUserIdResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FMessage>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeLatestMessagesByUserIdResult();
        FDescribeLatestMessagesByUserIdResult(
            const FDescribeLatestMessagesByUserIdResult& From
        );
        ~FDescribeLatestMessagesByUserIdResult() = default;

        TSharedPtr<FDescribeLatestMessagesByUserIdResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FMessage>>> Items);
        TSharedPtr<FDescribeLatestMessagesByUserIdResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FMessage>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeLatestMessagesByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeLatestMessagesByUserIdResult, ESPMode::ThreadSafe> FDescribeLatestMessagesByUserIdResultPtr;
}