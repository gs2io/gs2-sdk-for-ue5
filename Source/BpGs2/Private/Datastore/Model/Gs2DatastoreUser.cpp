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

#include "Datastore/Model/Gs2DatastoreUser.h"
#include "Datastore/Domain/EzGs2Datastore.h"
#include "Datastore/Model/Gs2DatastoreDataObject.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Datastore/Model/Gs2DatastoreDataObject.h"
#include "Core/BpGs2Constant.h"

FGs2DatastoreDataObject UGs2DatastoreUserFunctionLibrary::DataObject(
    FGs2DatastoreUser User,
    FString DataObjectName
)
{
    FGs2DatastoreDataObject Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreUserFunctionLibrary::DataObject] User parameter specification is missing."))
        return Return;
    }
    if (DataObjectName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreUserFunctionLibrary::DataObject] DataObjectName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->DataObject(
        DataObjectName
    );
    return Return;
}

FGs2DatastoreOwnDataObject UGs2DatastoreUserFunctionLibrary::OwnDataObject(
    FGs2DatastoreOwnUser User,
    FString DataObjectName
)
{
    FGs2DatastoreOwnDataObject Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreUserFunctionLibrary::OwnDataObject] User parameter specification is missing."))
        return Return;
    }
    if (DataObjectName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DatastoreUserFunctionLibrary::OwnDataObject] DataObjectName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->DataObject(
        DataObjectName
    );
    return Return;
}