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

#include "Datastore/Action/Gs2DatastoreActionRestoreDataObject.h"
#include "Core/BpGs2Constant.h"

UGs2DatastoreRestoreDataObjectAsyncFunction::UGs2DatastoreRestoreDataObjectAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2DatastoreRestoreDataObjectAsyncFunction* UGs2DatastoreRestoreDataObjectAsyncFunction::RestoreDataObject(
    UObject* WorldContextObject,
    FGs2DatastoreNamespace Namespace,
    FString DataObjectId
)
{
    UGs2DatastoreRestoreDataObjectAsyncFunction* Action = NewObject<UGs2DatastoreRestoreDataObjectAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreRestoreDataObjectAsyncFunction::RestoreDataObject] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    Action->DataObjectId = DataObjectId;
    return Action;
}

void UGs2DatastoreRestoreDataObjectAsyncFunction::Activate()
{
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreRestoreDataObjectAsyncFunction] Namespace parameter specification is missing."))
        return;
    }

    auto Future = Namespace.Value->RestoreDataObject(
        DataObjectId
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2DatastoreDataObject ReturnDataObject;
        ReturnDataObject.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnDataObject, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2DatastoreDataObject ReturnDataObject;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnDataObject, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}