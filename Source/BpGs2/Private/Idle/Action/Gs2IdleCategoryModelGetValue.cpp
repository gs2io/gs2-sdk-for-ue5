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

#include "Idle/Action/Gs2IdleCategoryModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2IdleCategoryModelGetValueAsyncFunction::UGs2IdleCategoryModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2IdleCategoryModelGetValueAsyncFunction* UGs2IdleCategoryModelGetValueAsyncFunction::CategoryModelGetValue(
    UObject* WorldContextObject,
    FGs2IdleCategoryModel CategoryModel
)
{
    UGs2IdleCategoryModelGetValueAsyncFunction* Action = NewObject<UGs2IdleCategoryModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (CategoryModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2IdleCategoryModelGetValueAsyncFunction::CategoryModelGetValue] CategoryModel parameter specification is missing."))
        return Action;
    }
    Action->CategoryModel = CategoryModel;
    return Action;
}

void UGs2IdleCategoryModelGetValueAsyncFunction::Activate()
{
    auto Future = CategoryModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzCategoryModelToFGs2IdleCategoryModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2IdleCategoryModelValue ReturnCategoryModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnCategoryModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}