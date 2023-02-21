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

#include "Datastore/Action/Gs2DatastoreActionDownloadOwnData.h"
#include "Core/BpGs2Constant.h"

UGs2DatastoreDownloadOwnDataAsyncFunction::UGs2DatastoreDownloadOwnDataAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2DatastoreDownloadOwnDataAsyncFunction* UGs2DatastoreDownloadOwnDataAsyncFunction::DownloadOwnData(
    UObject* WorldContextObject,
    FGs2DatastoreOwnDataObject DataObject
)
{
    UGs2DatastoreDownloadOwnDataAsyncFunction* Action = NewObject<UGs2DatastoreDownloadOwnDataAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (DataObject.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreDownloadOwnDataAsyncFunction::DownloadOwnData] DataObject parameter specification is missing."))
        return Action;
    }
    Action->DataObject = DataObject;
    return Action;
}

void UGs2DatastoreDownloadOwnDataAsyncFunction::Activate()
{
    if (DataObject.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreDownloadOwnDataAsyncFunction] DataObject parameter specification is missing."))
        return;
    }

    auto Future = DataObject.Value->Download(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
  
        TArray<uint8> ReturnBinary = *Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnBinary, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
  
        TArray<uint8> ReturnBinary;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnBinary, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}