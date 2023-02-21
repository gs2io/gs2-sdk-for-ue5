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

#include "Matchmaking/Action/Gs2MatchmakingActionCreateGathering.h"
#include "Core/BpGs2Constant.h"

UGs2MatchmakingCreateGatheringAsyncFunction::UGs2MatchmakingCreateGatheringAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MatchmakingCreateGatheringAsyncFunction* UGs2MatchmakingCreateGatheringAsyncFunction::CreateGathering(
    UObject* WorldContextObject,
    FGs2MatchmakingOwnUser User,
    FGs2MatchmakingPlayer Player,
    TArray<FGs2MatchmakingAttributeRange> AttributeRanges,
    TArray<FGs2MatchmakingCapacityOfRole> CapacityOfRoles,
    TArray<FString> AllowUserIds,
    int64 ExpiresAt,
    FGs2MatchmakingTimeSpan ExpiresAtTimeSpan
)
{
    UGs2MatchmakingCreateGatheringAsyncFunction* Action = NewObject<UGs2MatchmakingCreateGatheringAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingCreateGatheringAsyncFunction::CreateGathering] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->Player = Player;
    Action->AttributeRanges = AttributeRanges;
    Action->CapacityOfRoles = CapacityOfRoles;
    Action->AllowUserIds = AllowUserIds;
    Action->ExpiresAt = ExpiresAt;
    Action->ExpiresAtTimeSpan = ExpiresAtTimeSpan;
    return Action;
}

void UGs2MatchmakingCreateGatheringAsyncFunction::Activate()
{
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingCreateGatheringAsyncFunction] User parameter specification is missing."))
        return;
    }

    auto Future = User.Value->CreateGathering(
        FGs2MatchmakingPlayerToEzPlayer(Player),
        [&]
        {
            TArray<Gs2::UE5::Matchmaking::Model::FEzAttributeRangePtr> r;
            for (auto v : AttributeRanges)
            {
                r.Add(FGs2MatchmakingAttributeRangeToEzAttributeRange(v));
            }
            return r;
        }(),
        [&]
        {
            TArray<Gs2::UE5::Matchmaking::Model::FEzCapacityOfRolePtr> r;
            for (auto v : CapacityOfRoles)
            {
                r.Add(FGs2MatchmakingCapacityOfRoleToEzCapacityOfRole(v));
            }
            return r;
        }(),
        AllowUserIds,
        ExpiresAt,
        FGs2MatchmakingTimeSpanToEzTimeSpan(ExpiresAtTimeSpan)
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2MatchmakingOwnGathering ReturnGathering;
        ReturnGathering.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnGathering, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2MatchmakingOwnGathering ReturnGathering;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnGathering, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}