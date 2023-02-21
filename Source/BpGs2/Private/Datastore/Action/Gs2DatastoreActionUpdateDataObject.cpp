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

#include "Datastore/Action/Gs2DatastoreActionUpdateDataObject.h"
#include "Core/BpGs2Constant.h"

UGs2DatastoreUpdateDataObjectAsyncFunction::UGs2DatastoreUpdateDataObjectAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2DatastoreUpdateDataObjectAsyncFunction* UGs2DatastoreUpdateDataObjectAsyncFunction::UpdateDataObject(
    UObject* WorldContextObject,
    FGs2DatastoreOwnDataObject DataObject,
    FString Scope,
    TArray<FString> AllowUserIds
)
{
    UGs2DatastoreUpdateDataObjectAsyncFunction* Action = NewObject<UGs2DatastoreUpdateDataObjectAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (DataObject.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreUpdateDataObjectAsyncFunction::UpdateDataObject] DataObject parameter specification is missing."))
        return Action;
    }
    Action->DataObject = DataObject;
    Action->Scope = Scope;
    Action->AllowUserIds = AllowUserIds;
    return Action;
}

void UGs2DatastoreUpdateDataObjectAsyncFunction::Activate()
{
    if (DataObject.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreUpdateDataObjectAsyncFunction] DataObject parameter specification is missing."))
        return;
    }

    auto Future = DataObject.Value->UpdateDataObject(
        Scope,
        AllowUserIds
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2DatastoreOwnDataObject ReturnDataObject;
        ReturnDataObject.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnDataObject, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2DatastoreOwnDataObject ReturnDataObject;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnDataObject, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}