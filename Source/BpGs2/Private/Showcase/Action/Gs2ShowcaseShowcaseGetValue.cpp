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

#include "Showcase/Action/Gs2ShowcaseShowcaseGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2ShowcaseShowcaseGetValueAsyncFunction::UGs2ShowcaseShowcaseGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ShowcaseShowcaseGetValueAsyncFunction* UGs2ShowcaseShowcaseGetValueAsyncFunction::ShowcaseGetValue(
    UObject* WorldContextObject,
    FGs2ShowcaseOwnShowcase Showcase
)
{
    UGs2ShowcaseShowcaseGetValueAsyncFunction* Action = NewObject<UGs2ShowcaseShowcaseGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Showcase.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ShowcaseShowcaseGetValueAsyncFunction::ShowcaseGetValue] Showcase parameter specification is missing."))
        return Action;
    }
    Action->Showcase = Showcase;
    return Action;
}

void UGs2ShowcaseShowcaseGetValueAsyncFunction::Activate()
{
    auto Future = Showcase.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzShowcaseToFGs2ShowcaseShowcaseValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2ShowcaseShowcaseValue ReturnShowcase;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnShowcase, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}