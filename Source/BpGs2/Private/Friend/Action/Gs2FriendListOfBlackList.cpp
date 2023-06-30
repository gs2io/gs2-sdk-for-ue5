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

#include "Friend/Action/Gs2FriendListOfBlackList.h"
#include "Friend/Model/Gs2FriendBlackList.h"
#include "Core/BpGs2Constant.h"

UGs2FriendListOfBlackListAsyncFunction::UGs2FriendListOfBlackListAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FriendListOfBlackListAsyncFunction* UGs2FriendListOfBlackListAsyncFunction::ListOfBlackList(
    UObject* WorldContextObject,
    FGs2FriendOwnUser User
)
{
    UGs2FriendListOfBlackListAsyncFunction* Action = NewObject<UGs2FriendListOfBlackListAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendListOfBlackListAsyncFunction::ListOfBlackList] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2FriendListOfBlackListAsyncFunction::Activate()
{
    TArray<FString> ReturnBlackList;
    FGs2Error ReturnError;

    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendListOfBlackListAsyncFunction::Activate] User parameter specification is missing."))
        return;
    }
    const auto It = User.Value->BlackLists(
    );
    for (auto v : *It)
    {
        ReturnBlackList.Add(v->Current()->Value);
    }
    OnSuccess.Broadcast(ReturnBlackList, ReturnError);
}