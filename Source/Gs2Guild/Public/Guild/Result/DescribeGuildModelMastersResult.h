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
#include "../Model/GuildModelMaster.h"

namespace Gs2::Guild::Result
{
    class GS2GUILD_API FDescribeGuildModelMastersResult final : public TSharedFromThis<FDescribeGuildModelMastersResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FGuildModelMaster>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeGuildModelMastersResult();
        FDescribeGuildModelMastersResult(
            const FDescribeGuildModelMastersResult& From
        );
        ~FDescribeGuildModelMastersResult() = default;

        TSharedPtr<FDescribeGuildModelMastersResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FGuildModelMaster>>> Items);
        TSharedPtr<FDescribeGuildModelMastersResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FGuildModelMaster>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeGuildModelMastersResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeGuildModelMastersResult, ESPMode::ThreadSafe> FDescribeGuildModelMastersResultPtr;
}