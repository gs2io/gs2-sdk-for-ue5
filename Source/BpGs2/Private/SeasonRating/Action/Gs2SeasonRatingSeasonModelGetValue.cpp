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

#include "SeasonRating/Action/Gs2SeasonRatingSeasonModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2SeasonRatingSeasonModelGetValueAsyncFunction::UGs2SeasonRatingSeasonModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2SeasonRatingSeasonModelGetValueAsyncFunction* UGs2SeasonRatingSeasonModelGetValueAsyncFunction::SeasonModelGetValue(
    UObject* WorldContextObject,
    FGs2SeasonRatingSeasonModel SeasonModel
)
{
    UGs2SeasonRatingSeasonModelGetValueAsyncFunction* Action = NewObject<UGs2SeasonRatingSeasonModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (SeasonModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SeasonRatingSeasonModelGetValueAsyncFunction::SeasonModelGetValue] SeasonModel parameter specification is missing."))
        return Action;
    }
    Action->SeasonModel = SeasonModel;
    return Action;
}

void UGs2SeasonRatingSeasonModelGetValueAsyncFunction::Activate()
{
    auto Future = SeasonModel.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzSeasonModelToFGs2SeasonRatingSeasonModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2SeasonRatingSeasonModelValue ReturnSeasonModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnSeasonModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}