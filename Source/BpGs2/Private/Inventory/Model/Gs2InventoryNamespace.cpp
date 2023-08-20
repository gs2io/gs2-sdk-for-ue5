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

#include "BpGs2/Public/Inventory/Model/Gs2InventoryNamespace.h"
#include "BpGs2/Public/Inventory/Model/Gs2InventoryInventoryModel.h"
#include "BpGs2/Public/Inventory/Model/Gs2InventorySimpleInventoryModel.h"
#include "BpGs2/Public/Inventory/Model/Gs2InventoryBigInventoryModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Inventory/Model/Gs2InventoryInventoryModel.h"
#include "Inventory/Model/Gs2InventoryUser.h"
#include "Inventory/Model/Gs2InventorySimpleInventoryModel.h"
#include "Inventory/Model/Gs2InventoryBigInventoryModel.h"
#include "Core/BpGs2Constant.h"

FGs2InventoryInventoryModel UGs2InventoryNamespaceFunctionLibrary::InventoryModel(
    FGs2InventoryNamespace Namespace,
    FString InventoryName
)
{
    FGs2InventoryInventoryModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryNamespaceFunctionLibrary::InventoryModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (InventoryName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryNamespaceFunctionLibrary::InventoryModel] InventoryName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->InventoryModel(
        InventoryName
    );
    return Return;
}

FGs2InventoryOwnUser UGs2InventoryNamespaceFunctionLibrary::Me(
    FGs2InventoryNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2InventoryOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}

FGs2InventorySimpleInventoryModel UGs2InventoryNamespaceFunctionLibrary::SimpleInventoryModel(
    FGs2InventoryNamespace Namespace,
    FString InventoryName
)
{
    FGs2InventorySimpleInventoryModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryNamespaceFunctionLibrary::SimpleInventoryModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (InventoryName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryNamespaceFunctionLibrary::SimpleInventoryModel] InventoryName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->SimpleInventoryModel(
        InventoryName
    );
    return Return;
}

FGs2InventoryBigInventoryModel UGs2InventoryNamespaceFunctionLibrary::BigInventoryModel(
    FGs2InventoryNamespace Namespace,
    FString InventoryName
)
{
    FGs2InventoryBigInventoryModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryNamespaceFunctionLibrary::BigInventoryModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (InventoryName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryNamespaceFunctionLibrary::BigInventoryModel] InventoryName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->BigInventoryModel(
        InventoryName
    );
    return Return;
}