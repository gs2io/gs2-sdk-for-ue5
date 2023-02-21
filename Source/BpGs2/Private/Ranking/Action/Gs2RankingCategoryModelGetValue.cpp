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

#include "Ranking/Action/Gs2RankingCategoryModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2RankingCategoryModelGetValueAsyncFunction::UGs2RankingCategoryModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2RankingCategoryModelGetValueAsyncFunction* UGs2RankingCategoryModelGetValueAsyncFunction::CategoryModelGetValue(
    UObject* WorldContextObject,
    FGs2RankingCategoryModel CategoryModel
)
{
    UGs2RankingCategoryModelGetValueAsyncFunction* Action = NewObject<UGs2RankingCategoryModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (CategoryModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingCategoryModelGetValueAsyncFunction::CategoryModelGetValue] CategoryModel parameter specification is missing."))
        return Action;
    }
    Action->CategoryModel = CategoryModel;
    return Action;
}

void UGs2RankingCategoryModelGetValueAsyncFunction::Activate()
{
    auto Future = CategoryModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzCategoryModelToFGs2RankingCategoryModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2RankingCategoryModelValue ReturnCategoryModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnCategoryModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}