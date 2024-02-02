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

#include "Showcase/Action/Gs2ShowcaseRandomDisplayItemGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2ShowcaseRandomDisplayItemGetValueAsyncFunction::UGs2ShowcaseRandomDisplayItemGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ShowcaseRandomDisplayItemGetValueAsyncFunction* UGs2ShowcaseRandomDisplayItemGetValueAsyncFunction::RandomDisplayItemGetValue(
    UObject* WorldContextObject,
    FGs2ShowcaseOwnRandomDisplayItem RandomDisplayItem
)
{
    UGs2ShowcaseRandomDisplayItemGetValueAsyncFunction* Action = NewObject<UGs2ShowcaseRandomDisplayItemGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (RandomDisplayItem.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ShowcaseRandomDisplayItemGetValueAsyncFunction::RandomDisplayItemGetValue] RandomDisplayItem parameter specification is missing."))
        return Action;
    }
    Action->RandomDisplayItem = RandomDisplayItem;
    return Action;
}

void UGs2ShowcaseRandomDisplayItemGetValueAsyncFunction::Activate()
{
    auto Future = RandomDisplayItem.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzRandomDisplayItemToFGs2ShowcaseRandomDisplayItemValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2ShowcaseRandomDisplayItemValue ReturnRandomDisplayItem;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnRandomDisplayItem, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}