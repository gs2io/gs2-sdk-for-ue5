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

#include "Enhance/Action/Gs2EnhanceActionStart.h"
#include "Core/BpGs2Constant.h"

UGs2EnhanceStartAsyncFunction::UGs2EnhanceStartAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2EnhanceStartAsyncFunction* UGs2EnhanceStartAsyncFunction::Start(
    UObject* WorldContextObject,
    FGs2EnhanceOwnProgress Progress,
    FString RateName,
    FString TargetItemSetId,
    TArray<FGs2EnhanceMaterial> Materials,
    bool Force,
    TArray<FGs2EnhanceConfig> Config
)
{
    UGs2EnhanceStartAsyncFunction* Action = NewObject<UGs2EnhanceStartAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Progress.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceStartAsyncFunction::Start] Progress parameter specification is missing."))
        return Action;
    }
    Action->Progress = Progress;
    Action->RateName = RateName;
    Action->TargetItemSetId = TargetItemSetId;
    Action->Materials = Materials;
    Action->Force = Force;
    Action->Config = Config;
    return Action;
}

void UGs2EnhanceStartAsyncFunction::Activate()
{
    if (Progress.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceStartAsyncFunction] Progress parameter specification is missing."))
        return;
    }

    auto Future = Progress.Value->Start(
        RateName,
        TargetItemSetId,
        [&]
        {
            TArray<Gs2::UE5::Enhance::Model::FEzMaterialPtr> r;
            for (auto v : Materials)
            {
                r.Add(FGs2EnhanceMaterialToEzMaterial(v));
            }
            return r;
        }(),
        Force,
        [&]
        {
            TArray<Gs2::UE5::Enhance::Model::FEzConfigPtr> r;
            for (auto v : Config)
            {
                r.Add(FGs2EnhanceConfigToEzConfig(v));
            }
            return r;
        }()
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2CoreOwnTransaction ReturnTransaction;
        const FGs2Error ReturnError;
        OnError.Broadcast(ReturnTransaction, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2CoreOwnTransaction ReturnTransaction;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnTransaction, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}