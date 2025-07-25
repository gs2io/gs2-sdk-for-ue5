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
#include "Matchmaking/Model/Gs2MatchmakingGathering.h"
#include "Matchmaking/Model/Gs2MatchmakingGathering.h"
#include "../../Core/Model/Gs2Error.h"
#include "Core/Model/Gs2CoreTransaction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MatchmakingActionEarlyCompleteMatchmaking.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingEarlyCompleteMatchmakingSuccessDelegate, FGs2MatchmakingOwnGathering, Gathering, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingEarlyCompleteMatchmakingErrorDelegate, FGs2MatchmakingOwnGathering, Gathering, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MatchmakingEarlyCompleteMatchmakingAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MatchmakingOwnGathering Gathering;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingEarlyCompleteMatchmakingSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingEarlyCompleteMatchmakingErrorDelegate OnError;

    UGs2MatchmakingEarlyCompleteMatchmakingAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::Gathering::Action::EarlyCompleteMatchmaking", Category="Game Server Services|GS2-Matchmaking|Namespace|User|Gathering|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MatchmakingEarlyCompleteMatchmakingAsyncFunction* EarlyCompleteMatchmaking(
        UObject* WorldContextObject,
        FGs2MatchmakingOwnGathering Gathering
    );

    virtual void Activate() override;
};