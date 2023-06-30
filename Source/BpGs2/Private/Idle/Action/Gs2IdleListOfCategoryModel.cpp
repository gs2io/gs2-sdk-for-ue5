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

#include "Idle/Action/Gs2IdleListOfCategoryModel.h"
#include "Idle/Model/Gs2IdleCategoryModel.h"
#include "Core/BpGs2Constant.h"

UGs2IdleListOfCategoryModelAsyncFunction::UGs2IdleListOfCategoryModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2IdleListOfCategoryModelAsyncFunction* UGs2IdleListOfCategoryModelAsyncFunction::ListOfCategoryModel(
    UObject* WorldContextObject,
    FGs2IdleNamespace Namespace
)
{
    UGs2IdleListOfCategoryModelAsyncFunction* Action = NewObject<UGs2IdleListOfCategoryModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2IdleListOfCategoryModelAsyncFunction::ListOfCategoryModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2IdleListOfCategoryModelAsyncFunction::Activate()
{
    TArray<FGs2IdleCategoryModelValue> ReturnCategoryModels;
    FGs2Error ReturnError;

    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2IdleListOfCategoryModelAsyncFunction::Activate] Namespace parameter specification is missing."))
        return;
    }
    const auto It = Namespace.Value->CategoryModels(
    );
    for (auto v : *It)
    {
        ReturnCategoryModels.Add(EzCategoryModelToFGs2IdleCategoryModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnCategoryModels, ReturnError);
}