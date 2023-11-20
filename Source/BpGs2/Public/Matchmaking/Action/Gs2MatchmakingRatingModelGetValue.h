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
#include "Matchmaking/Model/Gs2MatchmakingRatingModel.h"
#include "Matchmaking/Model/Gs2MatchmakingRatingModel.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MatchmakingRatingModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingRatingModelGetValueSuccessDelegate, FGs2MatchmakingRatingModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingRatingModelGetValueErrorDelegate, FGs2MatchmakingRatingModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MatchmakingRatingModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MatchmakingRatingModel RatingModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingRatingModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingRatingModelGetValueErrorDelegate OnError;

    UGs2MatchmakingRatingModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::Fetch::GetValueOfRatingModel", Category="Game Server Services|GS2-Matchmaking|Namespace|RatingModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MatchmakingRatingModelGetValueAsyncFunction* RatingModelGetValue(
        UObject* WorldContextObject,
        FGs2MatchmakingRatingModel RatingModel
    );

    virtual void Activate() override;
};