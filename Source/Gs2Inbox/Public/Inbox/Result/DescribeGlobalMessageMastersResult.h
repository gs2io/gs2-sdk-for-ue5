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
#include "../Model/GlobalMessageMaster.h"

namespace Gs2::Inbox::Result
{
    class GS2INBOX_API FDescribeGlobalMessageMastersResult final : public TSharedFromThis<FDescribeGlobalMessageMastersResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FGlobalMessageMaster>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeGlobalMessageMastersResult();
        FDescribeGlobalMessageMastersResult(
            const FDescribeGlobalMessageMastersResult& From
        );
        ~FDescribeGlobalMessageMastersResult() = default;

        TSharedPtr<FDescribeGlobalMessageMastersResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FGlobalMessageMaster>>> Items);
        TSharedPtr<FDescribeGlobalMessageMastersResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FGlobalMessageMaster>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeGlobalMessageMastersResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeGlobalMessageMastersResult, ESPMode::ThreadSafe> FDescribeGlobalMessageMastersResultPtr;
}