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
 *
 * deny overwrite
 */

#include "Matchmaking/Action/Gs2MatchmakingActionDoMatchmaking.h"
#include "Core/BpGs2Constant.h"

UGs2MatchmakingDoMatchmakingAsyncFunction::UGs2MatchmakingDoMatchmakingAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MatchmakingDoMatchmakingAsyncFunction* UGs2MatchmakingDoMatchmakingAsyncFunction::DoMatchmaking(
    UObject* WorldContextObject,
    FGs2MatchmakingOwnUser User,
    FGs2MatchmakingPlayer Player
)
{
    UGs2MatchmakingDoMatchmakingAsyncFunction* Action = NewObject<UGs2MatchmakingDoMatchmakingAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingDoMatchmakingAsyncFunction::DoMatchmaking] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->Player = Player;
    return Action;
}

void UGs2MatchmakingDoMatchmakingAsyncFunction::Activate()
{
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingDoMatchmakingAsyncFunction] User parameter specification is missing."))
        return;
    }

    auto Future = User.Value->DoMatchmaking(
        FGs2MatchmakingPlayerToEzPlayer(Player)
    );
    for (auto Gathering : *Future)
    {
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(EzGatheringToFGs2MatchmakingGatheringValue(Gathering.Current()), ReturnError);
        SetReadyToDestroy();
        return;
    }
    
    FGs2MatchmakingGatheringValue ReturnGathering;
    FGs2Error ReturnError;
    auto Detail = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
    Detail->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(
        "gathering",
        "matchmaking.gathering.gathering.error.notFound",
        ""
    ));
    ReturnError.Value = MakeShared<Gs2::Core::Model::FNotFoundError>(
        Detail
    );
    OnError.Broadcast(ReturnGathering, ReturnError);
    SetReadyToDestroy();
}