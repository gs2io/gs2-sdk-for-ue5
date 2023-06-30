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

#include "Experience/Action/Gs2ExperienceListOfExperienceModel.h"
#include "Experience/Model/Gs2ExperienceExperienceModel.h"
#include "Core/BpGs2Constant.h"

UGs2ExperienceListOfExperienceModelAsyncFunction::UGs2ExperienceListOfExperienceModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ExperienceListOfExperienceModelAsyncFunction* UGs2ExperienceListOfExperienceModelAsyncFunction::ListOfExperienceModel(
    UObject* WorldContextObject,
    FGs2ExperienceNamespace Namespace
)
{
    UGs2ExperienceListOfExperienceModelAsyncFunction* Action = NewObject<UGs2ExperienceListOfExperienceModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExperienceListOfExperienceModelAsyncFunction::ListOfExperienceModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2ExperienceListOfExperienceModelAsyncFunction::Activate()
{
    TArray<FGs2ExperienceExperienceModelValue> ReturnExperienceModels;
    FGs2Error ReturnError;

    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExperienceListOfExperienceModelAsyncFunction::Activate] Namespace parameter specification is missing."))
        return;
    }
    const auto It = Namespace.Value->ExperienceModels(
    );
    for (auto v : *It)
    {
        ReturnExperienceModels.Add(EzExperienceModelToFGs2ExperienceExperienceModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnExperienceModels, ReturnError);
}