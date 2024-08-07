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
#include "Matchmaking/Domain/Model/Gs2MatchmakingEzNamespaceDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2MatchmakingNamespace.generated.h"

USTRUCT(BlueprintType)
struct FGs2MatchmakingNamespace
{
    GENERATED_BODY()

    Gs2::UE5::Matchmaking::Domain::Model::FEzNamespaceDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2MatchmakingNamespaceFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::User", Category="Game Server Services|GS2-Matchmaking|Namespace|User", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="User") FGs2MatchmakingUser User(
        FGs2MatchmakingNamespace Namespace,
        FString UserId
    );
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::Me", Category="Game Server Services|GS2-Matchmaking|Namespace|User", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="User") FGs2MatchmakingOwnUser Me(
        FGs2MatchmakingNamespace Namespace,
        FGs2AccessToken AccessToken
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::RatingModel", Category="Game Server Services|GS2-Matchmaking|Namespace|RatingModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="RatingModel") FGs2MatchmakingRatingModel RatingModel(
        FGs2MatchmakingNamespace Namespace,
        FString RatingName
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::SeasonModel", Category="Game Server Services|GS2-Matchmaking|Namespace|SeasonModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="SeasonModel") FGs2MatchmakingSeasonModel SeasonModel(
        FGs2MatchmakingNamespace Namespace,
        FString SeasonName
    );
};