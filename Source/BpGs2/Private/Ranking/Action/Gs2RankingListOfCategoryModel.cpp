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

#include "Ranking/Action/Gs2RankingListOfCategoryModel.h"
#include "Ranking/Model/Gs2RankingCategoryModel.h"
#include "Core/BpGs2Constant.h"

UGs2RankingListOfCategoryModelAsyncFunction::UGs2RankingListOfCategoryModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2RankingListOfCategoryModelAsyncFunction* UGs2RankingListOfCategoryModelAsyncFunction::ListOfCategoryModel(
    UObject* WorldContextObject,
    FGs2RankingNamespace Namespace
)
{
    UGs2RankingListOfCategoryModelAsyncFunction* Action = NewObject<UGs2RankingListOfCategoryModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingListOfCategoryModelAsyncFunction::ListOfCategoryModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2RankingListOfCategoryModelAsyncFunction::Activate()
{
    TArray<FGs2RankingCategoryModelValue> ReturnCategoryModels;
    FGs2Error ReturnError;
    const auto It = Namespace.Value->CategoryModels(
    );
    for (auto v : *It)
    {
        ReturnCategoryModels.Add(EzCategoryModelToFGs2RankingCategoryModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnCategoryModels, ReturnError);
}