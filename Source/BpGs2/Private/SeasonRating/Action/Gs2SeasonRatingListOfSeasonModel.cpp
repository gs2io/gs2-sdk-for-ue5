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

#include "SeasonRating/Action/Gs2SeasonRatingListOfSeasonModel.h"
#include "SeasonRating/Model/Gs2SeasonRatingSeasonModel.h"
#include "Core/BpGs2Constant.h"

UGs2SeasonRatingListOfSeasonModelAsyncFunction::UGs2SeasonRatingListOfSeasonModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2SeasonRatingListOfSeasonModelAsyncFunction* UGs2SeasonRatingListOfSeasonModelAsyncFunction::ListOfSeasonModel(
    UObject* WorldContextObject,
    FGs2SeasonRatingNamespace Namespace
)
{
    UGs2SeasonRatingListOfSeasonModelAsyncFunction* Action = NewObject<UGs2SeasonRatingListOfSeasonModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SeasonRatingListOfSeasonModelAsyncFunction::ListOfSeasonModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2SeasonRatingListOfSeasonModelAsyncFunction::Activate()
{
    TArray<FGs2SeasonRatingSeasonModelValue> ReturnSeasonModels;
    FGs2Error ReturnError;

    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SeasonRatingListOfSeasonModelAsyncFunction::Activate] Namespace parameter specification is missing."))
        return;
    }
    const auto It = Namespace.Value->SeasonModels(
    );
    for (auto v : *It)
    {
        ReturnSeasonModels.Add(EzSeasonModelToFGs2SeasonRatingSeasonModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnSeasonModels, ReturnError);
}