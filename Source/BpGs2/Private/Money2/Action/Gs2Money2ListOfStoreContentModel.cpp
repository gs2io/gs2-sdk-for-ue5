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

#include "Money2/Action/Gs2Money2ListOfStoreContentModel.h"
#include "Money2/Model/Gs2Money2StoreContentModel.h"
#include "Core/BpGs2Constant.h"

UGs2Money2ListOfStoreContentModelAsyncFunction::UGs2Money2ListOfStoreContentModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2Money2ListOfStoreContentModelAsyncFunction* UGs2Money2ListOfStoreContentModelAsyncFunction::ListOfStoreContentModel(
    UObject* WorldContextObject,
    FGs2Money2Namespace Namespace
)
{
    UGs2Money2ListOfStoreContentModelAsyncFunction* Action = NewObject<UGs2Money2ListOfStoreContentModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2ListOfStoreContentModelAsyncFunction::ListOfStoreContentModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2Money2ListOfStoreContentModelAsyncFunction::Activate()
{
    TArray<FGs2Money2StoreContentModelValue> ReturnStoreContentModels;
    FGs2Error ReturnError;

    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2ListOfStoreContentModelAsyncFunction::Activate] Namespace parameter specification is missing."))
        return;
    }
    const auto It = Namespace.Value->StoreContentModels(
    );
    for (auto v : *It)
    {
        ReturnStoreContentModels.Add(EzStoreContentModelToFGs2Money2StoreContentModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnStoreContentModels, ReturnError);
}