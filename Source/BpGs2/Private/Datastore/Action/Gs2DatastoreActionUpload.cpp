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

#include "Datastore/Action/Gs2DatastoreActionUpload.h"
#include "Core/BpGs2Constant.h"

UGs2DatastoreUploadAsyncFunction::UGs2DatastoreUploadAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2DatastoreUploadAsyncFunction* UGs2DatastoreUploadAsyncFunction::Upload(
    UObject* WorldContextObject,
    FGs2DatastoreOwnUser User,
    TArray<uint8> Binary,
    FString Name,
    FString Scope,
    FString ContentType,
    TArray<FString> AllowUserIds,
    bool UpdateIfExists
)
{
    UGs2DatastoreUploadAsyncFunction* Action = NewObject<UGs2DatastoreUploadAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreUploadAsyncFunction::Upload] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->Binary = Binary;
    Action->Name = Name;
    Action->Scope = Scope;
    Action->ContentType = ContentType;
    Action->AllowUserIds = AllowUserIds;
    Action->UpdateIfExists = UpdateIfExists;
    return Action;
}

void UGs2DatastoreUploadAsyncFunction::Activate()
{
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreUploadAsyncFunction] User parameter specification is missing."))
        return;
    }

    auto Future = User.Value->Upload(
        Binary,
        Name,
        Scope,
        ContentType,
        AllowUserIds,
        UpdateIfExists
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
  
        FGs2DatastoreOwnDataObject ReturnDataObject;
        ReturnDataObject.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnDataObject, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
  
        FGs2DatastoreOwnDataObject ReturnDataObject;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnDataObject, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}