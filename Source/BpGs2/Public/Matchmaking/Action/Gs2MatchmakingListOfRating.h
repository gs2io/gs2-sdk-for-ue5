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
#include "Matchmaking/Model/Gs2MatchmakingUser.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MatchmakingListOfRating.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingListOfRatingSuccessDelegate, const TArray<FGs2MatchmakingRatingValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingListOfRatingErrorDelegate, const TArray<FGs2MatchmakingRatingValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MatchmakingListOfRatingAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MatchmakingOwnUser User;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingListOfRatingSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingListOfRatingErrorDelegate OnError;

    UGs2MatchmakingListOfRatingAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::Fetch::ListOfRating", Category="Game Server Services|GS2-Matchmaking|Namespace|User|Rating|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MatchmakingListOfRatingAsyncFunction* ListOfRating(
        UObject* WorldContextObject,
        FGs2MatchmakingOwnUser User
    );

    virtual void Activate() override;
};