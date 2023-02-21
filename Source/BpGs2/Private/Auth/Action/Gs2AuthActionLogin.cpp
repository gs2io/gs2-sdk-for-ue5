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

#include "Auth/Action/Gs2AuthActionLogin.h"
#include "Core/BpGs2Constant.h"

UGs2AuthLoginAsyncFunction::UGs2AuthLoginAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2AuthLoginAsyncFunction* UGs2AuthLoginAsyncFunction::Login(
    UObject* WorldContextObject,
    FGs2AuthAccessToken AccessToken,
    FString KeyId,
    FString Body,
    FString Signature
)
{
    UGs2AuthLoginAsyncFunction* Action = NewObject<UGs2AuthLoginAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AuthLoginAsyncFunction::Login] AccessToken parameter specification is missing."))
        return Action;
    }
    Action->AccessToken = AccessToken;
    Action->KeyId = KeyId;
    Action->Body = Body;
    Action->Signature = Signature;
    return Action;
}

void UGs2AuthLoginAsyncFunction::Activate()
{
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AuthLoginAsyncFunction] AccessToken parameter specification is missing."))
        return;
    }

    auto Future = AccessToken.Value->Login(
        KeyId,
        Body,
        Signature
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2AuthAccessToken ReturnAccessToken;
        ReturnAccessToken.Value = Result;
        const FGs2Error ReturnError;
        OnError.Broadcast(ReturnAccessToken, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2AuthAccessToken ReturnAccessToken;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnAccessToken, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}