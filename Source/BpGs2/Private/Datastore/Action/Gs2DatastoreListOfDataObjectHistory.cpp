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

#include "Datastore/Action/Gs2DatastoreListOfDataObjectHistory.h"
#include "Datastore/Model/Gs2DatastoreDataObjectHistory.h"
#include "Core/BpGs2Constant.h"

UGs2DatastoreListOfDataObjectHistoryAsyncFunction::UGs2DatastoreListOfDataObjectHistoryAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2DatastoreListOfDataObjectHistoryAsyncFunction* UGs2DatastoreListOfDataObjectHistoryAsyncFunction::ListOfDataObjectHistory(
    UObject* WorldContextObject,
    FGs2DatastoreOwnDataObject DataObject
)
{
    UGs2DatastoreListOfDataObjectHistoryAsyncFunction* Action = NewObject<UGs2DatastoreListOfDataObjectHistoryAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (DataObject.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreListOfDataObjectHistoryAsyncFunction::ListOfDataObjectHistory] DataObject parameter specification is missing."))
        return Action;
    }
    Action->DataObject = DataObject;
    return Action;
}

void UGs2DatastoreListOfDataObjectHistoryAsyncFunction::Activate()
{
    TArray<FGs2DatastoreDataObjectHistoryValue> ReturnDataObjectHistories;
    FGs2Error ReturnError;

    if (DataObject.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreListOfDataObjectHistoryAsyncFunction::Activate] DataObject parameter specification is missing."))
        return;
    }
    const auto It = DataObject.Value->DataObjectHistories(
    );
    for (auto v : *It)
    {
        ReturnDataObjectHistories.Add(EzDataObjectHistoryToFGs2DatastoreDataObjectHistoryValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnDataObjectHistories, ReturnError);
}