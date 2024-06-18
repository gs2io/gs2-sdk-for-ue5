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
#include "Matchmaking/Domain/Model/Gs2MatchmakingEzSeasonGatheringGameSessionDomain.h"
#include "Matchmaking/Domain/Model/Gs2MatchmakingEzSeasonGatheringDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2MatchmakingSeasonGathering.generated.h"

USTRUCT(BlueprintType)
struct FGs2MatchmakingOwnSeasonGathering
{
    GENERATED_BODY()

    Gs2::UE5::Matchmaking::Domain::Model::FEzSeasonGatheringGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MatchmakingSeasonGathering
{
    GENERATED_BODY()

    Gs2::UE5::Matchmaking::Domain::Model::FEzSeasonGatheringDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MatchmakingSeasonGatheringValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString SeasonGatheringId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString SeasonName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 Season = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 Tier = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FString> Participants = TArray<FString>();
};

inline FGs2MatchmakingSeasonGatheringValue EzSeasonGatheringToFGs2MatchmakingSeasonGatheringValue(
    const Gs2::UE5::Matchmaking::Model::FEzSeasonGatheringPtr Model
)
{
    FGs2MatchmakingSeasonGatheringValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingSeasonGatheringFunctionLibrary::EzSeasonGatheringToFGs2MatchmakingSeasonGatheringValue] Model parameter specification is missing."))
        return Value;
    }
    Value.SeasonGatheringId = Model->GetSeasonGatheringId() ? *Model->GetSeasonGatheringId() : "";
    Value.SeasonName = Model->GetSeasonName() ? *Model->GetSeasonName() : "";
    Value.Season = Model->GetSeason() ? *Model->GetSeason() : 0;
    Value.Tier = Model->GetTier() ? *Model->GetTier() : 0;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Participants = Model->GetParticipants() ? [&]
    {
        TArray<FString> r;
        for (auto v : *Model->GetParticipants())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<FString>();
    return Value;
}

inline Gs2::UE5::Matchmaking::Model::FEzSeasonGatheringPtr FGs2MatchmakingSeasonGatheringValueToEzSeasonGathering(
    const FGs2MatchmakingSeasonGatheringValue Model
)
{
    return MakeShared<Gs2::UE5::Matchmaking::Model::FEzSeasonGathering>()
        ->WithSeasonGatheringId(Model.SeasonGatheringId)
        ->WithSeasonName(Model.SeasonName)
        ->WithSeason(Model.Season)
        ->WithTier(Model.Tier)
        ->WithName(Model.Name)
        ->WithParticipants([&]{
            auto r = MakeShared<TArray<FString>>();
            for (auto v : Model.Participants) {
                r->Add(v);
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2MatchmakingSeasonGatheringFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};