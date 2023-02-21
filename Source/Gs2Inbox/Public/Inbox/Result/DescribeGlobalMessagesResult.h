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
#include "../Model/GlobalMessage.h"

namespace Gs2::Inbox::Result
{
    class GS2INBOX_API FDescribeGlobalMessagesResult final : public TSharedFromThis<FDescribeGlobalMessagesResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FGlobalMessage>>> ItemsValue;
        
    public:
        
        FDescribeGlobalMessagesResult();
        FDescribeGlobalMessagesResult(
            const FDescribeGlobalMessagesResult& From
        );
        ~FDescribeGlobalMessagesResult() = default;

        TSharedPtr<FDescribeGlobalMessagesResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FGlobalMessage>>> Items);

        TSharedPtr<TArray<TSharedPtr<Model::FGlobalMessage>>> GetItems() const;

        static TSharedPtr<FDescribeGlobalMessagesResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeGlobalMessagesResult, ESPMode::ThreadSafe> FDescribeGlobalMessagesResultPtr;
}