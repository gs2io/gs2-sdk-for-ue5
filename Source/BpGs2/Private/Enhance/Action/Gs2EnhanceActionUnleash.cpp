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

#include "Enhance/Action/Gs2EnhanceActionUnleash.h"
#include "Core/BpGs2Constant.h"

UGs2EnhanceUnleashAsyncFunction::UGs2EnhanceUnleashAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2EnhanceUnleashAsyncFunction* UGs2EnhanceUnleashAsyncFunction::Unleash(
    UObject* WorldContextObject,
    FGs2EnhanceOwnEnhance Enhance,
    FString RateName,
    FString TargetItemSetId,
    TArray<FString> Materials,
    FString RecipeName,
    TArray<FGs2EnhanceUnleashMaterialSelection> RecipeMaterials,
    TArray<FGs2EnhanceConfig> Config
)
{
    UGs2EnhanceUnleashAsyncFunction* Action = NewObject<UGs2EnhanceUnleashAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Enhance.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceUnleashAsyncFunction::Unleash] Enhance parameter specification is missing."))
        return Action;
    }
    Action->Enhance = Enhance;
    Action->RateName = RateName;
    Action->TargetItemSetId = TargetItemSetId;
    Action->Materials = Materials;
    Action->RecipeName = RecipeName;
    Action->RecipeMaterials = RecipeMaterials;
    Action->Config = Config;
    return Action;
}

void UGs2EnhanceUnleashAsyncFunction::Activate()
{
    if (Enhance.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceUnleashAsyncFunction] Enhance parameter specification is missing."))
        return;
    }

    auto Future = Enhance.Value->Unleash(
        RateName,
        TargetItemSetId,
        Materials,
        RecipeName,
        [&]
        {
            TArray<Gs2::UE5::Enhance::Model::FEzUnleashMaterialSelectionPtr> r;
            for (auto v : RecipeMaterials)
            {
                r.Add(FGs2EnhanceUnleashMaterialSelectionToEzUnleashMaterialSelection(v));
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