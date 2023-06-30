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

#include "MegaField/Action/Gs2MegaFieldListOfAreaModel.h"
#include "MegaField/Model/Gs2MegaFieldAreaModel.h"
#include "Core/BpGs2Constant.h"

UGs2MegaFieldListOfAreaModelAsyncFunction::UGs2MegaFieldListOfAreaModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MegaFieldListOfAreaModelAsyncFunction* UGs2MegaFieldListOfAreaModelAsyncFunction::ListOfAreaModel(
    UObject* WorldContextObject,
    FGs2MegaFieldNamespace Namespace
)
{
    UGs2MegaFieldListOfAreaModelAsyncFunction* Action = NewObject<UGs2MegaFieldListOfAreaModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldListOfAreaModelAsyncFunction::ListOfAreaModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2MegaFieldListOfAreaModelAsyncFunction::Activate()
{
    TArray<FGs2MegaFieldAreaModelValue> ReturnAreaModels;
    FGs2Error ReturnError;

    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldListOfAreaModelAsyncFunction::Activate] Namespace parameter specification is missing."))
        return;
    }
    const auto It = Namespace.Value->AreaModels(
    );
    for (auto v : *It)
    {
        ReturnAreaModels.Add(EzAreaModelToFGs2MegaFieldAreaModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnAreaModels, ReturnError);
}