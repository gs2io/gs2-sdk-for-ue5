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
#include "Ballot.h"
#include "GameResult.h"

namespace Gs2::Matchmaking::Model
{
    class GS2MATCHMAKING_API FWrittenBallot final : public FGs2Object, public TSharedFromThis<FWrittenBallot>
    {
        TSharedPtr<FBallot> BallotValue;
        TSharedPtr<TArray<TSharedPtr<FGameResult>>> GameResultsValue;

    public:
        FWrittenBallot();
        FWrittenBallot(
            const FWrittenBallot& From
        );
        virtual ~FWrittenBallot() override = default;

        TSharedPtr<FWrittenBallot> WithBallot(const TSharedPtr<FBallot> Ballot);
        TSharedPtr<FWrittenBallot> WithGameResults(const TSharedPtr<TArray<TSharedPtr<FGameResult>>> GameResults);

        TSharedPtr<FBallot> GetBallot() const;
        TSharedPtr<TArray<TSharedPtr<FGameResult>>> GetGameResults() const;


        static TSharedPtr<FWrittenBallot> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FWrittenBallot, ESPMode::ThreadSafe> FWrittenBallotPtr;
}