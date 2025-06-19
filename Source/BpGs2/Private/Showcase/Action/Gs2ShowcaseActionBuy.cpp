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

#include "Showcase/Action/Gs2ShowcaseActionBuy.h"
#include "Core/BpGs2Constant.h"

UGs2ShowcaseBuyAsyncFunction::UGs2ShowcaseBuyAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ShowcaseBuyAsyncFunction* UGs2ShowcaseBuyAsyncFunction::Buy(
    UObject* WorldContextObject,
    FGs2ShowcaseOwnDisplayItem DisplayItem,
    int32 Quantity,
    TArray<FGs2ShowcaseConfig> Config
)
{
    UGs2ShowcaseBuyAsyncFunction* Action = NewObject<UGs2ShowcaseBuyAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (DisplayItem.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ShowcaseBuyAsyncFunction::Buy] DisplayItem parameter specification is missing."))
        return Action;
    }
    Action->DisplayItem = DisplayItem;
    Action->Quantity = Quantity;
    Action->Config = Config;
    return Action;
}

void UGs2ShowcaseBuyAsyncFunction::Activate()
{
    if (DisplayItem.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ShowcaseBuyAsyncFunction] DisplayItem parameter specification is missing."))
        return;
    }

    auto Future = DisplayItem.Value->Buy(
        Quantity,
        [&]
        {
            TArray<Gs2::UE5::Showcase::Model::FEzConfigPtr> r;
            for (auto v : Config)
            {
                r.Add(FGs2ShowcaseConfigToEzConfig(v));
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