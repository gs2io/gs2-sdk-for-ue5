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
 *
 * deny overwrite
 */

#include "Enhance/Action/Gs2EnhanceActionEnhance.h"
#include "Core/BpGs2Constant.h"

UGs2EnhanceEnhanceAsyncFunction::UGs2EnhanceEnhanceAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2EnhanceEnhanceAsyncFunction* UGs2EnhanceEnhanceAsyncFunction::Enhance(
    UObject* WorldContextObject,
    FGs2EnhanceOwnEnhance Enhance,
    FString RateName,
    FString TargetItemSetId,
    TArray<FGs2EnhanceMaterial> Materials,
    TArray<FGs2EnhanceConfig> Config
)
{
    UGs2EnhanceEnhanceAsyncFunction* Action = NewObject<UGs2EnhanceEnhanceAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Enhance.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceEnhanceAsyncFunction::Enhance] Enhance parameter specification is missing."))
        return Action;
    }
    Action->EnhanceValue = Enhance;
    Action->RateName = RateName;
    Action->TargetItemSetId = TargetItemSetId;
    Action->Materials = Materials;
    Action->Config = Config;
    return Action;
}

void UGs2EnhanceEnhanceAsyncFunction::Activate()
{
    if (EnhanceValue.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceEnhanceAsyncFunction] Enhance parameter specification is missing."))
        return;
    }

    auto Future = EnhanceValue.Value->Enhance(
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
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        FGs2EnhanceOwnEnhance ReturnEnhance;
        ReturnEnhance.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnEnhance, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2EnhanceOwnEnhance ReturnEnhance;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnEnhance, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}