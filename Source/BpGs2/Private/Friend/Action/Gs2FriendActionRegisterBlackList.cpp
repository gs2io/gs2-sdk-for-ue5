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

#include "Friend/Action/Gs2FriendActionRegisterBlackList.h"
#include "Core/BpGs2Constant.h"

UGs2FriendRegisterBlackListAsyncFunction::UGs2FriendRegisterBlackListAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FriendRegisterBlackListAsyncFunction* UGs2FriendRegisterBlackListAsyncFunction::RegisterBlackList(
    UObject* WorldContextObject,
    FGs2FriendOwnBlackList BlackList,
    FString TargetUserId
)
{
    UGs2FriendRegisterBlackListAsyncFunction* Action = NewObject<UGs2FriendRegisterBlackListAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (BlackList.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendRegisterBlackListAsyncFunction::RegisterBlackList] BlackList parameter specification is missing."))
        return Action;
    }
    Action->BlackList = BlackList;
    Action->TargetUserId = TargetUserId;
    return Action;
}

void UGs2FriendRegisterBlackListAsyncFunction::Activate()
{
    if (BlackList.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendRegisterBlackListAsyncFunction] BlackList parameter specification is missing."))
        return;
    }

    auto Future = BlackList.Value->RegisterBlackList(
        TargetUserId
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2FriendOwnBlackList ReturnBlackList;
        ReturnBlackList.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnBlackList, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2FriendOwnBlackList ReturnBlackList;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnBlackList, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}