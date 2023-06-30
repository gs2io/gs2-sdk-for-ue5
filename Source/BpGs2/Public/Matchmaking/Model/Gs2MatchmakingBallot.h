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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Matchmaking/Domain/Model/Gs2MatchmakingEzBallotDomain.h"
#include "Matchmaking/Domain/Model/Gs2MatchmakingEzBallotGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2MatchmakingBallot.generated.h"

USTRUCT(BlueprintType)
struct FGs2MatchmakingOwnBallot
{
    GENERATED_BODY()

    Gs2::UE5::Matchmaking::Domain::Model::FEzBallotGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MatchmakingBallot
{
    GENERATED_BODY()

    Gs2::UE5::Matchmaking::Domain::Model::FEzBallotDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MatchmakingBallotValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(BlueprintReadOnly)
    FString RatingName = "";
    UPROPERTY(BlueprintReadOnly)
    FString GatheringName = "";
    UPROPERTY(BlueprintReadOnly)
    int32 NumberOfPlayer = 0;
};

inline FGs2MatchmakingBallotValue EzBallotToFGs2MatchmakingBallotValue(
    const Gs2::UE5::Matchmaking::Model::FEzBallotPtr Model
)
{
    FGs2MatchmakingBallotValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingBallotFunctionLibrary::EzBallotToFGs2MatchmakingBallotValue] Model parameter specification is missing."))
        return Value;
    }
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.RatingName = Model->GetRatingName() ? *Model->GetRatingName() : "";
    Value.GatheringName = Model->GetGatheringName() ? *Model->GetGatheringName() : "";
    Value.NumberOfPlayer = Model->GetNumberOfPlayer() ? *Model->GetNumberOfPlayer() : 0;
    return Value;
}

inline Gs2::UE5::Matchmaking::Model::FEzBallotPtr FGs2MatchmakingBallotValueToEzBallot(
    const FGs2MatchmakingBallotValue Model
)
{
    return MakeShared<Gs2::UE5::Matchmaking::Model::FEzBallot>()
        ->WithUserId(Model.UserId)
        ->WithRatingName(Model.RatingName)
        ->WithGatheringName(Model.GatheringName)
        ->WithNumberOfPlayer(Model.NumberOfPlayer);
}

UCLASS()
class BPGS2_API UGs2MatchmakingBallotFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};