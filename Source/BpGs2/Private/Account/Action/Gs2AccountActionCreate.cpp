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

#include "Account/Action/Gs2AccountActionCreate.h"
#include "Core/BpGs2Constant.h"

UGs2AccountCreateAsyncFunction::UGs2AccountCreateAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2AccountCreateAsyncFunction* UGs2AccountCreateAsyncFunction::Create(
    UObject* WorldContextObject,
    FGs2AccountNamespace Namespace
)
{
    UGs2AccountCreateAsyncFunction* Action = NewObject<UGs2AccountCreateAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountCreateAsyncFunction::Create] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2AccountCreateAsyncFunction::Activate()
{
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountCreateAsyncFunction] Namespace parameter specification is missing."))
        return;
    }

    auto Future = Namespace.Value->Create(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2AccountAccount ReturnAccount;
        ReturnAccount.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnAccount, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2AccountAccount ReturnAccount;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnAccount, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}