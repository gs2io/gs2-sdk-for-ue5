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

#include "Datastore/Action/Gs2DatastoreActionReUpload.h"
#include "Core/BpGs2Constant.h"

UGs2DatastoreReUploadAsyncFunction::UGs2DatastoreReUploadAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2DatastoreReUploadAsyncFunction* UGs2DatastoreReUploadAsyncFunction::ReUpload(
    UObject* WorldContextObject,
    FGs2DatastoreOwnDataObject DataObject,
    TArray<uint8> Binary,
    FString ContentType
)
{
    UGs2DatastoreReUploadAsyncFunction* Action = NewObject<UGs2DatastoreReUploadAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (DataObject.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreReUploadAsyncFunction::ReUpload] DataObject parameter specification is missing."))
        return Action;
    }
    Action->DataObject = DataObject;
    Action->Binary = Binary;
    Action->ContentType = ContentType;
    return Action;
}

void UGs2DatastoreReUploadAsyncFunction::Activate()
{
    if (DataObject.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreReUploadAsyncFunction] DataObject parameter specification is missing."))
        return;
    }

    auto Future = DataObject.Value->ReUpload(
        Binary,
        ContentType
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