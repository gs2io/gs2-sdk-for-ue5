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

#include "Grade/Action/Gs2GradeListOfGradeModel.h"
#include "Grade/Model/Gs2GradeGradeModel.h"
#include "Core/BpGs2Constant.h"

UGs2GradeListOfGradeModelAsyncFunction::UGs2GradeListOfGradeModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2GradeListOfGradeModelAsyncFunction* UGs2GradeListOfGradeModelAsyncFunction::ListOfGradeModel(
    UObject* WorldContextObject,
    FGs2GradeNamespace Namespace
)
{
    UGs2GradeListOfGradeModelAsyncFunction* Action = NewObject<UGs2GradeListOfGradeModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2GradeListOfGradeModelAsyncFunction::ListOfGradeModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2GradeListOfGradeModelAsyncFunction::Activate()
{
    TArray<FGs2GradeGradeModelValue> ReturnGradeModels;
    FGs2Error ReturnError;

    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2GradeListOfGradeModelAsyncFunction::Activate] Namespace parameter specification is missing."))
        return;
    }
    const auto It = Namespace.Value->GradeModels(
    );
    for (auto v : *It)
    {
        ReturnGradeModels.Add(EzGradeModelToFGs2GradeGradeModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnGradeModels, ReturnError);
}