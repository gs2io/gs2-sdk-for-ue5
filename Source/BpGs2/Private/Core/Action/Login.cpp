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

#include "Core/Action/Login.h"

ULoginAsyncFunction::ULoginAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

ULoginAsyncFunction* ULoginAsyncFunction::Gs2Login(
    UObject* WorldContextObject,
    FGs2Client Client,
    FGs2Authenticator Authenticator,
    FString UserId,
    FString Password
)
{
    ULoginAsyncFunction* Action = NewObject<ULoginAsyncFunction>();
    Action->Client = Client;
    Action->Authenticator = Authenticator;
    Action->UserId = UserId;
    Action->Password = Password;
    Action->RegisterWithGameInstance(WorldContextObject);
    return Action;
}

void ULoginAsyncFunction::Activate()
{
    if (Client.Profile == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[ULoginAsyncFunction::Activate] Client parameter specification is missing."))
        return;
    }
    if (Authenticator.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[ULoginAsyncFunction::Activate] Authenticator parameter specification is missing."))
        return;
    }
    auto Future = Client.Profile->Login(
        Authenticator.Value,
        UserId,
        Password
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        FGs2AccessToken ReturnAccessToken;
        ReturnAccessToken.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnAccessToken, ReturnError);
    	SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2AccessToken ReturnAccessToken;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnAccessToken, ReturnError);
    	SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}
