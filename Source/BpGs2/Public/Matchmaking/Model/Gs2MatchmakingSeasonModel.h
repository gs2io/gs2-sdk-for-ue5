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
#include "Matchmaking/Domain/Model/Gs2MatchmakingEzSeasonModelDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2MatchmakingSeasonModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2MatchmakingSeasonModel
{
    GENERATED_BODY()

    Gs2::UE5::Matchmaking::Domain::Model::FEzSeasonModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MatchmakingSeasonModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 MaximumParticipants = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ExperienceModelId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ChallengePeriodEventId = "";
};

inline FGs2MatchmakingSeasonModelValue EzSeasonModelToFGs2MatchmakingSeasonModelValue(
    const Gs2::UE5::Matchmaking::Model::FEzSeasonModelPtr Model
)
{
    FGs2MatchmakingSeasonModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingSeasonModelFunctionLibrary::EzSeasonModelToFGs2MatchmakingSeasonModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.MaximumParticipants = Model->GetMaximumParticipants() ? *Model->GetMaximumParticipants() : 0;
    Value.ExperienceModelId = Model->GetExperienceModelId() ? *Model->GetExperienceModelId() : "";
    Value.ChallengePeriodEventId = Model->GetChallengePeriodEventId() ? *Model->GetChallengePeriodEventId() : "";
    return Value;
}

inline Gs2::UE5::Matchmaking::Model::FEzSeasonModelPtr FGs2MatchmakingSeasonModelValueToEzSeasonModel(
    const FGs2MatchmakingSeasonModelValue Model
)
{
    return MakeShared<Gs2::UE5::Matchmaking::Model::FEzSeasonModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithMaximumParticipants(Model.MaximumParticipants)
        ->WithExperienceModelId(Model.ExperienceModelId)
        ->WithChallengePeriodEventId(Model.ChallengePeriodEventId);
}

UCLASS()
class BPGS2_API UGs2MatchmakingSeasonModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};