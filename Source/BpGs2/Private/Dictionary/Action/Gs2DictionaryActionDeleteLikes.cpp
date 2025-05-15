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

#include "Dictionary/Action/Gs2DictionaryActionDeleteLikes.h"
#include "Core/BpGs2Constant.h"

UGs2DictionaryDeleteLikesAsyncFunction::UGs2DictionaryDeleteLikesAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2DictionaryDeleteLikesAsyncFunction* UGs2DictionaryDeleteLikesAsyncFunction::DeleteLikes(
    UObject* WorldContextObject,
    FGs2DictionaryOwnUser User,
    TArray<FString> EntryModelNames
)
{
    UGs2DictionaryDeleteLikesAsyncFunction* Action = NewObject<UGs2DictionaryDeleteLikesAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryDeleteLikesAsyncFunction::DeleteLikes] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->EntryModelNames = EntryModelNames;
    return Action;
}

void UGs2DictionaryDeleteLikesAsyncFunction::Activate()
{
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryDeleteLikesAsyncFunction] User parameter specification is missing."))
        return;
    }

    auto Future = User.Value->DeleteLikes(
        EntryModelNames
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        TArray<FGs2DictionaryOwnLike> ReturnLike;
        for (int i=0; i<Result->Num(); i++)
        {
            FGs2DictionaryOwnLike r;
            r.Value = (*Result)[i];
            ReturnLike.Add(r);
        }
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnLike, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        TArray<FGs2DictionaryOwnLike> ReturnLike;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnSuccess.Broadcast(ReturnLike, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}