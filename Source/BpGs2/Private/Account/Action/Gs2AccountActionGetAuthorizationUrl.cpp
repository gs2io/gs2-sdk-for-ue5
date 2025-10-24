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

#include "Account/Action/Gs2AccountActionGetAuthorizationUrl.h"
#include "Core/BpGs2Constant.h"

UGs2AccountGetAuthorizationUrlAsyncFunction::UGs2AccountGetAuthorizationUrlAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2AccountGetAuthorizationUrlAsyncFunction* UGs2AccountGetAuthorizationUrlAsyncFunction::GetAuthorizationUrl(
    UObject* WorldContextObject,
    FGs2AccountOwnAccount Account,
    int32 Type
)
{
    UGs2AccountGetAuthorizationUrlAsyncFunction* Action = NewObject<UGs2AccountGetAuthorizationUrlAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Account.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountGetAuthorizationUrlAsyncFunction::GetAuthorizationUrl] Account parameter specification is missing."))
        return Action;
    }
    Action->Account = Account;
    Action->Type = Type;
    return Action;
}

void UGs2AccountGetAuthorizationUrlAsyncFunction::Activate()
{
    if (Account.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountGetAuthorizationUrlAsyncFunction] Account parameter specification is missing."))
        return;
    }

    // auto Future = Account.Value->GetAuthorizationUrl(
    //     Type
    // );
    // Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    // {
    //     FGs2AccountGetAuthorizationUrl ReturnUrl;
    //     ReturnUrl.Value = Result->AuthorizationUrl();
    //     const FGs2Error ReturnError;
    //     OnError.Broadcast(ReturnUrl, ReturnError);
    //     SetReadyToDestroy();
    // });
    // Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    // {
    //     FGs2AccountGetAuthorizationUrl ReturnUrl;
    //     FGs2Error ReturnError;
    //     ReturnError.Value = Error;
    //     OnError.Broadcast(ReturnUrl, ReturnError);
    //     SetReadyToDestroy();
    // });
    // Future->StartBackgroundTask();
}