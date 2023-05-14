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

#include "MegaField/Action/Gs2MegaFieldListOfLayerModel.h"
#include "MegaField/Model/Gs2MegaFieldLayerModel.h"
#include "Core/BpGs2Constant.h"

UGs2MegaFieldListOfLayerModelAsyncFunction::UGs2MegaFieldListOfLayerModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MegaFieldListOfLayerModelAsyncFunction* UGs2MegaFieldListOfLayerModelAsyncFunction::ListOfLayerModel(
    UObject* WorldContextObject,
    FGs2MegaFieldAreaModel AreaModel
)
{
    UGs2MegaFieldListOfLayerModelAsyncFunction* Action = NewObject<UGs2MegaFieldListOfLayerModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (AreaModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldListOfLayerModelAsyncFunction::ListOfLayerModel] AreaModel parameter specification is missing."))
        return Action;
    }
    Action->AreaModel = AreaModel;
    return Action;
}

void UGs2MegaFieldListOfLayerModelAsyncFunction::Activate()
{
    TArray<FGs2MegaFieldLayerModelValue> ReturnLayerModels;
    FGs2Error ReturnError;
    const auto It = AreaModel.Value->LayerModels(
    );
    for (auto v : *It)
    {
        ReturnLayerModels.Add(EzLayerModelToFGs2MegaFieldLayerModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnLayerModels, ReturnError);
}