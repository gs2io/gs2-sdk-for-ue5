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

#include "Dictionary/Action/Gs2DictionaryLikeGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2DictionaryLikeGetValueAsyncFunction::UGs2DictionaryLikeGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2DictionaryLikeGetValueAsyncFunction* UGs2DictionaryLikeGetValueAsyncFunction::LikeGetValue(
    UObject* WorldContextObject,
    FGs2DictionaryOwnLike Like
)
{
    UGs2DictionaryLikeGetValueAsyncFunction* Action = NewObject<UGs2DictionaryLikeGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Like.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryLikeGetValueAsyncFunction::LikeGetValue] Like parameter specification is missing."))
        return Action;
    }
    Action->Like = Like;
    return Action;
}

void UGs2DictionaryLikeGetValueAsyncFunction::Activate()
{
    auto Future = Like.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzLikeToFGs2DictionaryLikeValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2DictionaryLikeValue ReturnLike;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnLike, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}