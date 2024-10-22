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

#include "Datastore/Model/Gs2DatastoreDataObject.h"
#include "Datastore/Domain/EzGs2Datastore.h"
#include "Datastore/Model/Gs2DatastoreDataObjectHistory.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Datastore/Model/Gs2DatastoreDataObjectHistory.h"
#include "Core/BpGs2Constant.h"

FGs2DatastoreOwnDataObjectHistory UGs2DatastoreDataObjectFunctionLibrary::OwnDataObjectHistory(
    FGs2DatastoreOwnDataObject DataObject,
    FString Generation
)
{
    FGs2DatastoreOwnDataObjectHistory Return;
    if (DataObject.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreDataObjectFunctionLibrary::OwnDataObjectHistory] DataObject parameter specification is missing."))
        return Return;
    }
    if (Generation == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreDataObjectFunctionLibrary::OwnDataObjectHistory] Generation parameter specification is missing."))
        return Return;
    }
    Return.Value = DataObject.Value->DataObjectHistory(
        Generation
    );
    return Return;
}