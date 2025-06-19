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
#include "Matchmaking/Model/Gs2MatchmakingAttributeRange.h"
#include "Matchmaking/Model/Gs2MatchmakingGathering.h"
#include "../../Core/Model/Gs2Error.h"
#include "Core/Model/Gs2CoreTransaction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MatchmakingActionUpdateGathering.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingUpdateGatheringSuccessDelegate, FGs2MatchmakingOwnGathering, Gathering, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingUpdateGatheringErrorDelegate, FGs2MatchmakingOwnGathering, Gathering, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MatchmakingUpdateGatheringAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MatchmakingOwnGathering Gathering;
    TArray<FGs2MatchmakingAttributeRange> AttributeRanges;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingUpdateGatheringSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingUpdateGatheringErrorDelegate OnError;

    UGs2MatchmakingUpdateGatheringAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::Gathering::Action::UpdateGathering", Category="Game Server Services|GS2-Matchmaking|Namespace|User|Gathering|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MatchmakingUpdateGatheringAsyncFunction* UpdateGathering(
        UObject* WorldContextObject,
        FGs2MatchmakingOwnGathering Gathering,
        TArray<FGs2MatchmakingAttributeRange> AttributeRanges
    );

    virtual void Activate() override;
};