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
#include "Matchmaking/Domain/Model/Gs2MatchmakingEzRatingModelDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2MatchmakingRatingModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2MatchmakingRatingModel
{
    GENERATED_BODY()

    Gs2::UE5::Matchmaking::Domain::Model::FEzRatingModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MatchmakingRatingModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 Volatility = 0;
};

inline FGs2MatchmakingRatingModelValue EzRatingModelToFGs2MatchmakingRatingModelValue(
    const Gs2::UE5::Matchmaking::Model::FEzRatingModelPtr Model
)
{
    FGs2MatchmakingRatingModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingRatingModelFunctionLibrary::EzRatingModelToFGs2MatchmakingRatingModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.Volatility = Model->GetVolatility() ? *Model->GetVolatility() : 0;
    return Value;
}

inline Gs2::UE5::Matchmaking::Model::FEzRatingModelPtr FGs2MatchmakingRatingModelValueToEzRatingModel(
    const FGs2MatchmakingRatingModelValue Model
)
{
    return MakeShared<Gs2::UE5::Matchmaking::Model::FEzRatingModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithVolatility(Model.Volatility);
}

UCLASS()
class BPGS2_API UGs2MatchmakingRatingModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};