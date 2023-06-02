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
#include "Core/Gs2Object.h"

namespace Gs2::Matchmaking::Model
{
    class GS2MATCHMAKING_API FGameResult final : public Gs2Object, public TSharedFromThis<FGameResult>
    {
        TOptional<int32> RankValue;
        TOptional<FString> UserIdValue;

    public:
        FGameResult();
        FGameResult(
            const FGameResult& From
        );
        virtual ~FGameResult() override = default;

        TSharedPtr<FGameResult> WithRank(const TOptional<int32> Rank);
        TSharedPtr<FGameResult> WithUserId(const TOptional<FString> UserId);

        TOptional<int32> GetRank() const;
        FString GetRankString() const;
        TOptional<FString> GetUserId() const;


        static TSharedPtr<FGameResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FGameResult, ESPMode::ThreadSafe> FGameResultPtr;
}