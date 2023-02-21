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

#include "Matchmaking/Action/Gs2MatchmakingActionUpdateGathering.h"
#include "Core/BpGs2Constant.h"

UGs2MatchmakingUpdateGatheringAsyncFunction::UGs2MatchmakingUpdateGatheringAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MatchmakingUpdateGatheringAsyncFunction* UGs2MatchmakingUpdateGatheringAsyncFunction::UpdateGathering(
    UObject* WorldContextObject,
    FGs2MatchmakingOwnGathering Gathering,
    TArray<FGs2MatchmakingAttributeRange> AttributeRanges
)
{
    UGs2MatchmakingUpdateGatheringAsyncFunction* Action = NewObject<UGs2MatchmakingUpdateGatheringAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Gathering.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingUpdateGatheringAsyncFunction::UpdateGathering] Gathering parameter specification is missing."))
        return Action;
    }
    Action->Gathering = Gathering;
    Action->AttributeRanges = AttributeRanges;
    return Action;
}

void UGs2MatchmakingUpdateGatheringAsyncFunction::Activate()
{
    if (Gathering.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingUpdateGatheringAsyncFunction] Gathering parameter specification is missing."))
        return;
    }

    auto Future = Gathering.Value->UpdateGathering(
        [&]
        {
            TArray<Gs2::UE5::Matchmaking::Model::FEzAttributeRangePtr> r;
            for (auto v : AttributeRanges)
            {
                r.Add(FGs2MatchmakingAttributeRangeToEzAttributeRange(v));
            }
            return r;
        }()
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