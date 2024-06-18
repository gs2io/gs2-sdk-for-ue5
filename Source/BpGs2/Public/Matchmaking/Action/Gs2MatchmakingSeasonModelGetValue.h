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
#include "Matchmaking/Model/Gs2MatchmakingSeasonModel.h"
#include "Matchmaking/Model/Gs2MatchmakingSeasonModel.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MatchmakingSeasonModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingSeasonModelGetValueSuccessDelegate, FGs2MatchmakingSeasonModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingSeasonModelGetValueErrorDelegate, FGs2MatchmakingSeasonModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MatchmakingSeasonModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MatchmakingSeasonModel SeasonModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingSeasonModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingSeasonModelGetValueErrorDelegate OnError;

    UGs2MatchmakingSeasonModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::Fetch::GetValueOfSeasonModel", Category="Game Server Services|GS2-Matchmaking|Namespace|SeasonModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MatchmakingSeasonModelGetValueAsyncFunction* SeasonModelGetValue(
        UObject* WorldContextObject,
        FGs2MatchmakingSeasonModel SeasonModel
    );

    virtual void Activate() override;
};