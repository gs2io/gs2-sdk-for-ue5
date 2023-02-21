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

#include "Datastore/Action/Gs2DatastoreOwnDataObjectGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2DatastoreOwnDataObjectGetValueAsyncFunction::UGs2DatastoreOwnDataObjectGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2DatastoreOwnDataObjectGetValueAsyncFunction* UGs2DatastoreOwnDataObjectGetValueAsyncFunction::OwnDataObjectGetValue(
    UObject* WorldContextObject,
    FGs2DatastoreOwnDataObject Datastore
)
{
    UGs2DatastoreOwnDataObjectGetValueAsyncFunction* Action = NewObject<UGs2DatastoreOwnDataObjectGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Datastore.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreOwnDataObjectGetValueAsyncFunction::DatastoreGetValue] Datastore parameter specification is missing."))
        return Action;
    }
    Action->Datastore = Datastore;
    return Action;
}

void UGs2DatastoreOwnDataObjectGetValueAsyncFunction::Activate()
{
    auto Future = Datastore.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzDataObjectToFGs2DatastoreDataObjectValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2DatastoreDataObjectValue ReturnValue;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}