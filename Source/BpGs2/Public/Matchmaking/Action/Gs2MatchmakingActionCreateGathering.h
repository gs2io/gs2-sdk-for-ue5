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
#include "BpGs2/Public/Matchmaking/Model/Gs2MatchmakingGathering.h"
#include "BpGs2/Public/Matchmaking/Model/Gs2MatchmakingPlayer.h"
#include "BpGs2/Public/Matchmaking/Model/Gs2MatchmakingAttributeRange.h"
#include "BpGs2/Public/Matchmaking/Model/Gs2MatchmakingCapacityOfRole.h"
#include "BpGs2/Public/Matchmaking/Model/Gs2MatchmakingTimeSpan.h"
#include "BpGs2/Public/Matchmaking/Model/Gs2MatchmakingUser.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MatchmakingActionCreateGathering.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingCreateGatheringSuccessDelegate, FGs2MatchmakingOwnGathering, Gathering, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingCreateGatheringErrorDelegate, FGs2MatchmakingOwnGathering, Gathering, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MatchmakingCreateGatheringAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MatchmakingOwnUser User;
    FGs2MatchmakingPlayer Player;
    TArray<FGs2MatchmakingAttributeRange> AttributeRanges;
    TArray<FGs2MatchmakingCapacityOfRole> CapacityOfRoles;
    TArray<FString> AllowUserIds;
    int64 ExpiresAt;
    FGs2MatchmakingTimeSpan ExpiresAtTimeSpan;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2MatchmakingCreateGatheringSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2MatchmakingCreateGatheringErrorDelegate OnError;

    UGs2MatchmakingCreateGatheringAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::Gathering::Action::CreateGathering", Category="Game Server Services|GS2-Matchmaking|Namespace|User|Gathering|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MatchmakingCreateGatheringAsyncFunction* CreateGathering(
        UObject* WorldContextObject,
        FGs2MatchmakingOwnUser User,
        FGs2MatchmakingPlayer Player,
        TArray<FGs2MatchmakingAttributeRange> AttributeRanges,
        TArray<FGs2MatchmakingCapacityOfRole> CapacityOfRoles,
        TArray<FString> AllowUserIds,
        int64 ExpiresAt,
        FGs2MatchmakingTimeSpan ExpiresAtTimeSpan
    );

    virtual void Activate() override;
};