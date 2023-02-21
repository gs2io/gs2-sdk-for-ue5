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

#include "Lottery/Action/Gs2LotteryLotteryModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2LotteryLotteryModelGetValueAsyncFunction::UGs2LotteryLotteryModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2LotteryLotteryModelGetValueAsyncFunction* UGs2LotteryLotteryModelGetValueAsyncFunction::LotteryModelGetValue(
    UObject* WorldContextObject,
    FGs2LotteryLotteryModel LotteryModel
)
{
    UGs2LotteryLotteryModelGetValueAsyncFunction* Action = NewObject<UGs2LotteryLotteryModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (LotteryModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LotteryLotteryModelGetValueAsyncFunction::LotteryModelGetValue] LotteryModel parameter specification is missing."))
        return Action;
    }
    Action->LotteryModel = LotteryModel;
    return Action;
}

void UGs2LotteryLotteryModelGetValueAsyncFunction::Activate()
{
    auto Future = LotteryModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzLotteryModelToFGs2LotteryLotteryModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2LotteryLotteryModelValue ReturnLotteryModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnLotteryModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}