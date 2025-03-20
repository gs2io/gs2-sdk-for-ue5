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

#include "Dictionary/Action/Gs2DictionaryListOfLike.h"
#include "Dictionary/Model/Gs2DictionaryLike.h"
#include "Core/BpGs2Constant.h"

UGs2DictionaryListOfLikeAsyncFunction::UGs2DictionaryListOfLikeAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2DictionaryListOfLikeAsyncFunction* UGs2DictionaryListOfLikeAsyncFunction::ListOfLike(
    UObject* WorldContextObject,
    FGs2DictionaryOwnUser User
)
{
    UGs2DictionaryListOfLikeAsyncFunction* Action = NewObject<UGs2DictionaryListOfLikeAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryListOfLikeAsyncFunction::ListOfLike] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2DictionaryListOfLikeAsyncFunction::Activate()
{
    TArray<FGs2DictionaryLikeValue> ReturnLikes;
    FGs2Error ReturnError;

    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryListOfLikeAsyncFunction::Activate] User parameter specification is missing."))
        return;
    }
    const auto It = User.Value->Likes(
    );
    for (auto v : *It)
    {
        ReturnLikes.Add(EzLikeToFGs2DictionaryLikeValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnLikes, ReturnError);
}