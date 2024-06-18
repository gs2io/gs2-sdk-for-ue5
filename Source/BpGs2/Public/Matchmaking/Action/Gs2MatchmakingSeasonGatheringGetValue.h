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
#include "Matchmaking/Model/Gs2MatchmakingSeasonGathering.h"
#include "Matchmaking/Model/Gs2MatchmakingSeasonGathering.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MatchmakingSeasonGatheringGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingSeasonGatheringGetValueSuccessDelegate, FGs2MatchmakingSeasonGatheringValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingSeasonGatheringGetValueErrorDelegate, FGs2MatchmakingSeasonGatheringValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MatchmakingSeasonGatheringGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MatchmakingSeasonGathering SeasonGathering;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingSeasonGatheringGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingSeasonGatheringGetValueErrorDelegate OnError;

    UGs2MatchmakingSeasonGatheringGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::Fetch::GetValueOfSeasonGathering", Category="Game Server Services|GS2-Matchmaking|Namespace|User|Season|SeasonGathering|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MatchmakingSeasonGatheringGetValueAsyncFunction* SeasonGatheringGetValue(
        UObject* WorldContextObject,
        FGs2MatchmakingSeasonGathering SeasonGathering
    );

    virtual void Activate() override;
};