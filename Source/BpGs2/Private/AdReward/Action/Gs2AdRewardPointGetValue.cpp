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

#include "AdReward/Action/Gs2AdRewardPointGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2AdRewardPointGetValueAsyncFunction::UGs2AdRewardPointGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2AdRewardPointGetValueAsyncFunction* UGs2AdRewardPointGetValueAsyncFunction::PointGetValue(
    UObject* WorldContextObject,
    FGs2AdRewardOwnPoint Point
)
{
    UGs2AdRewardPointGetValueAsyncFunction* Action = NewObject<UGs2AdRewardPointGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Point.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AdRewardPointGetValueAsyncFunction::PointGetValue] Point parameter specification is missing."))
        return Action;
    }
    Action->Point = Point;
    return Action;
}

void UGs2AdRewardPointGetValueAsyncFunction::Activate()
{
    auto Future = Point.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzPointToFGs2AdRewardPointValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2AdRewardPointValue ReturnPoint;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnPoint, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}