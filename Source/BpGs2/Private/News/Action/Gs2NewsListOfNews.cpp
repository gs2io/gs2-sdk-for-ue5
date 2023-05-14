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

#include "News/Action/Gs2NewsListOfNews.h"
#include "News/Model/Gs2NewsNews.h"
#include "Core/BpGs2Constant.h"

UGs2NewsListOfNewsAsyncFunction::UGs2NewsListOfNewsAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2NewsListOfNewsAsyncFunction* UGs2NewsListOfNewsAsyncFunction::ListOfNews(
    UObject* WorldContextObject,
    FGs2NewsOwnUser User
)
{
    UGs2NewsListOfNewsAsyncFunction* Action = NewObject<UGs2NewsListOfNewsAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2NewsListOfNewsAsyncFunction::ListOfNews] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2NewsListOfNewsAsyncFunction::Activate()
{
    TArray<FGs2NewsNewsValue> ReturnNewses;
    FGs2Error ReturnError;
    const auto It = User.Value->Newses(
    );
    for (auto v : *It)
    {
        ReturnNewses.Add(EzNewsToFGs2NewsNewsValue(v.Current()));
    }
    OnSuccess.Broadcast(ReturnNewses, ReturnError);
}