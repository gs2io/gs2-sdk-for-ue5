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

#include "Showcase/Action/Gs2ShowcaseActionGetRandomShowcaseDisplayItem.h"
#include "Core/BpGs2Constant.h"

UGs2ShowcaseGetRandomShowcaseDisplayItemAsyncFunction::UGs2ShowcaseGetRandomShowcaseDisplayItemAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ShowcaseGetRandomShowcaseDisplayItemAsyncFunction* UGs2ShowcaseGetRandomShowcaseDisplayItemAsyncFunction::GetRandomShowcaseDisplayItem(
    UObject* WorldContextObject,
    FGs2ShowcaseOwnRandomShowcase RandomShowcase,
    FString DisplayItemName
)
{
    UGs2ShowcaseGetRandomShowcaseDisplayItemAsyncFunction* Action = NewObject<UGs2ShowcaseGetRandomShowcaseDisplayItemAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (RandomShowcase.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ShowcaseGetRandomShowcaseDisplayItemAsyncFunction::GetRandomShowcaseDisplayItem] RandomShowcase parameter specification is missing."))
        return Action;
    }
    Action->RandomShowcase = RandomShowcase;
    Action->DisplayItemName = DisplayItemName;
    return Action;
}

void UGs2ShowcaseGetRandomShowcaseDisplayItemAsyncFunction::Activate()
{
    if (RandomShowcase.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ShowcaseGetRandomShowcaseDisplayItemAsyncFunction] RandomShowcase parameter specification is missing."))
        return;
    }

    auto Future = RandomShowcase.Value->GetRandomShowcaseDisplayItem(
        DisplayItemName
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2ShowcaseOwnRandomDisplayItem ReturnRandomDisplayItem;
        ReturnRandomDisplayItem.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnRandomDisplayItem, ReturnError);
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