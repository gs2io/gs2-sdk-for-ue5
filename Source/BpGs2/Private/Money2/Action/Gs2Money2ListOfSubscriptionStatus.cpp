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

#include "Money2/Action/Gs2Money2ListOfSubscriptionStatus.h"
#include "Money2/Model/Gs2Money2SubscriptionStatus.h"
#include "Core/BpGs2Constant.h"

UGs2Money2ListOfSubscriptionStatusAsyncFunction::UGs2Money2ListOfSubscriptionStatusAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2Money2ListOfSubscriptionStatusAsyncFunction* UGs2Money2ListOfSubscriptionStatusAsyncFunction::ListOfSubscriptionStatus(
    UObject* WorldContextObject,
    FGs2Money2OwnUser User
)
{
    UGs2Money2ListOfSubscriptionStatusAsyncFunction* Action = NewObject<UGs2Money2ListOfSubscriptionStatusAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2ListOfSubscriptionStatusAsyncFunction::ListOfSubscriptionStatus] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2Money2ListOfSubscriptionStatusAsyncFunction::Activate()
{
    TArray<FGs2Money2SubscriptionStatusValue> ReturnSubscriptionStatuses;
    FGs2Error ReturnError;

    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2ListOfSubscriptionStatusAsyncFunction::Activate] User parameter specification is missing."))
        return;
    }
    const auto It = User.Value->SubscriptionStatuses(
    );
    for (auto v : *It)
    {
        ReturnSubscriptionStatuses.Add(EzSubscriptionStatusToFGs2Money2SubscriptionStatusValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnSubscriptionStatuses, ReturnError);
}