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

#include "Version/Action/Gs2VersionListOfVersionModel.h"
#include "Version/Model/Gs2VersionVersionModel.h"
#include "Core/BpGs2Constant.h"

UGs2VersionListOfVersionModelAsyncFunction::UGs2VersionListOfVersionModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2VersionListOfVersionModelAsyncFunction* UGs2VersionListOfVersionModelAsyncFunction::ListOfVersionModel(
    UObject* WorldContextObject,
    FGs2VersionNamespace Namespace
)
{
    UGs2VersionListOfVersionModelAsyncFunction* Action = NewObject<UGs2VersionListOfVersionModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2VersionListOfVersionModelAsyncFunction::ListOfVersionModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2VersionListOfVersionModelAsyncFunction::Activate()
{
    TArray<FGs2VersionVersionModelValue> ReturnVersionModels;
    FGs2Error ReturnError;
    const auto It = Namespace.Value->VersionModels(
    );
    for (auto v : *It)
    {
        ReturnVersionModels.Add(EzVersionModelToFGs2VersionVersionModelValue(v));
    }
    OnSuccess.Broadcast(ReturnVersionModels, ReturnError);
}