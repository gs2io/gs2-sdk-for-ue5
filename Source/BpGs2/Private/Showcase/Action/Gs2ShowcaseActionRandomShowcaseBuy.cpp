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

#include "Showcase/Action/Gs2ShowcaseActionRandomShowcaseBuy.h"
#include "Core/BpGs2Constant.h"

UGs2ShowcaseRandomShowcaseBuyAsyncFunction::UGs2ShowcaseRandomShowcaseBuyAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ShowcaseRandomShowcaseBuyAsyncFunction* UGs2ShowcaseRandomShowcaseBuyAsyncFunction::RandomShowcaseBuy(
    UObject* WorldContextObject,
    FGs2ShowcaseOwnRandomDisplayItem RandomDisplayItem,
    int32 Quantity,
    TArray<FGs2ShowcaseConfig> Config
)
{
    UGs2ShowcaseRandomShowcaseBuyAsyncFunction* Action = NewObject<UGs2ShowcaseRandomShowcaseBuyAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (RandomDisplayItem.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ShowcaseRandomShowcaseBuyAsyncFunction::RandomShowcaseBuy] RandomDisplayItem parameter specification is missing."))
        return Action;
    }
    Action->RandomDisplayItem = RandomDisplayItem;
    Action->Quantity = Quantity;
    Action->Config = Config;
    return Action;
}

void UGs2ShowcaseRandomShowcaseBuyAsyncFunction::Activate()
{
    if (RandomDisplayItem.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ShowcaseRandomShowcaseBuyAsyncFunction] RandomDisplayItem parameter specification is missing."))
        return;
    }

    auto Future = RandomDisplayItem.Value->RandomShowcaseBuy(
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
        FGs2ShowcaseOwnRandomDisplayItem ReturnRandomDisplayItem;
        ReturnRandomDisplayItem.Value = Result;
        const FGs2Error ReturnError;
        OnError.Broadcast(ReturnRandomDisplayItem, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2ShowcaseOwnRandomDisplayItem ReturnRandomDisplayItem;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnRandomDisplayItem, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}