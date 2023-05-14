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

#include "Datastore/Action/Gs2DatastoreListOfDataObject.h"
#include "Datastore/Model/Gs2DatastoreDataObject.h"
#include "Core/BpGs2Constant.h"

UGs2DatastoreListOfDataObjectAsyncFunction::UGs2DatastoreListOfDataObjectAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2DatastoreListOfDataObjectAsyncFunction* UGs2DatastoreListOfDataObjectAsyncFunction::ListOfDataObject(
    UObject* WorldContextObject,
    FGs2DatastoreOwnUser User,
    FString Status
)
{
    UGs2DatastoreListOfDataObjectAsyncFunction* Action = NewObject<UGs2DatastoreListOfDataObjectAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreListOfDataObjectAsyncFunction::ListOfDataObject] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->Status = Status;
    return Action;
}

void UGs2DatastoreListOfDataObjectAsyncFunction::Activate()
{
    TArray<FGs2DatastoreDataObjectValue> ReturnDataObjects;
    FGs2Error ReturnError;
    const auto It = User.Value->DataObjects(
        Status
    );
    for (auto v : *It)
    {
        ReturnDataObjects.Add(EzDataObjectToFGs2DatastoreDataObjectValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnDataObjects, ReturnError);
}