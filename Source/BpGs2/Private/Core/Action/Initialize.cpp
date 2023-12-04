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

#include "Core/Action/Initialize.h"

UInitializeAsyncFunction::UInitializeAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer), ClientId(""), ClientSecret(""), Region(ApNorthEast1)
{
}

UInitializeAsyncFunction* UInitializeAsyncFunction::Gs2Initialize(
    UObject* WorldContextObject,
    FString ClientId,
    FString ClientSecret,
    EGs2Region Region
)
{
    UInitializeAsyncFunction* Action = NewObject<UInitializeAsyncFunction>();
    Action->ClientId = ClientId;
    Action->ClientSecret = ClientSecret;
    Action->Region = Region;
    Action->RegisterWithGameInstance(WorldContextObject);
    return Action;
}

void UInitializeAsyncFunction::Activate()
{
    auto Future = Gs2::UE5::Core::FGs2Client::Create(
        MakeShared<Gs2::Core::Model::FBasicGs2Credential>(
            ClientId,
            ClientSecret
        ),
        EGs2RegionToERegion(Region)
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        FGs2Client ReturnClient;
        const FGs2Error ReturnError;
        ReturnClient.Value = Result;
        OnSuccess.Broadcast(ReturnClient, ReturnError);
    	SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2Client ReturnClient;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnClient, ReturnError);
    	SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}
