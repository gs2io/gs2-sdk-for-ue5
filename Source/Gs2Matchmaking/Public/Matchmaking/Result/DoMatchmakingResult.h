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
#include "../Model/Gathering.h"

namespace Gs2::Matchmaking::Result
{
    class GS2MATCHMAKING_API FDoMatchmakingResult final : public TSharedFromThis<FDoMatchmakingResult>
    {
        TSharedPtr<Model::FGathering> ItemValue;
        TOptional<FString> MatchmakingContextTokenValue;
        
    public:
        
        FDoMatchmakingResult();
        FDoMatchmakingResult(
            const FDoMatchmakingResult& From
        );
        ~FDoMatchmakingResult() = default;

        TSharedPtr<FDoMatchmakingResult> WithItem(const TSharedPtr<Model::FGathering> Item);
        TSharedPtr<FDoMatchmakingResult> WithMatchmakingContextToken(const TOptional<FString> MatchmakingContextToken);

        TSharedPtr<Model::FGathering> GetItem() const;
        TOptional<FString> GetMatchmakingContextToken() const;

        static TSharedPtr<FDoMatchmakingResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDoMatchmakingResult, ESPMode::ThreadSafe> FDoMatchmakingResultPtr;
}