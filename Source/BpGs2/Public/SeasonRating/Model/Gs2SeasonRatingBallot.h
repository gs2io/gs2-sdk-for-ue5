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
#include "SeasonRating/Domain/Model/Gs2SeasonRatingEzBallotGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2SeasonRatingBallot.generated.h"

USTRUCT(BlueprintType)
struct FGs2SeasonRatingOwnBallot
{
    GENERATED_BODY()

    Gs2::UE5::SeasonRating::Domain::Model::FEzBallotGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2SeasonRatingBallotValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString SeasonName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString SessionName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 NumberOfPlayer = 0;
};

inline FGs2SeasonRatingBallotValue EzBallotToFGs2SeasonRatingBallotValue(
    const Gs2::UE5::SeasonRating::Model::FEzBallotPtr Model
)
{
    FGs2SeasonRatingBallotValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SeasonRatingBallotFunctionLibrary::EzBallotToFGs2SeasonRatingBallotValue] Model parameter specification is missing."))
        return Value;
    }
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.SeasonName = Model->GetSeasonName() ? *Model->GetSeasonName() : "";
    Value.SessionName = Model->GetSessionName() ? *Model->GetSessionName() : "";
    Value.NumberOfPlayer = Model->GetNumberOfPlayer() ? *Model->GetNumberOfPlayer() : 0;
    return Value;
}

inline Gs2::UE5::SeasonRating::Model::FEzBallotPtr FGs2SeasonRatingBallotValueToEzBallot(
    const FGs2SeasonRatingBallotValue Model
)
{
    return MakeShared<Gs2::UE5::SeasonRating::Model::FEzBallot>()
        ->WithUserId(Model.UserId)
        ->WithSeasonName(Model.SeasonName)
        ->WithSessionName(Model.SessionName)
        ->WithNumberOfPlayer(Model.NumberOfPlayer);
}

UCLASS()
class BPGS2_API UGs2SeasonRatingBallotFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};