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

#pragma once

#include "CoreMinimal.h"
#include "Core/Net/AbstractWebSocketGs2Client.h"
#include "Request/DescribeNamespacesRequest.h"
#include "Task/WebSocket/DescribeNamespacesTask.h"
#include "Request/CreateNamespaceRequest.h"
#include "Task/WebSocket/CreateNamespaceTask.h"
#include "Request/GetNamespaceStatusRequest.h"
#include "Task/WebSocket/GetNamespaceStatusTask.h"
#include "Request/GetNamespaceRequest.h"
#include "Task/WebSocket/GetNamespaceTask.h"
#include "Request/UpdateNamespaceRequest.h"
#include "Task/WebSocket/UpdateNamespaceTask.h"
#include "Request/DeleteNamespaceRequest.h"
#include "Task/WebSocket/DeleteNamespaceTask.h"
#include "Request/DescribeInventoryModelMastersRequest.h"
#include "Task/WebSocket/DescribeInventoryModelMastersTask.h"
#include "Request/CreateInventoryModelMasterRequest.h"
#include "Task/WebSocket/CreateInventoryModelMasterTask.h"
#include "Request/GetInventoryModelMasterRequest.h"
#include "Task/WebSocket/GetInventoryModelMasterTask.h"
#include "Request/UpdateInventoryModelMasterRequest.h"
#include "Task/WebSocket/UpdateInventoryModelMasterTask.h"
#include "Request/DeleteInventoryModelMasterRequest.h"
#include "Task/WebSocket/DeleteInventoryModelMasterTask.h"
#include "Request/DescribeInventoryModelsRequest.h"
#include "Task/WebSocket/DescribeInventoryModelsTask.h"
#include "Request/GetInventoryModelRequest.h"
#include "Task/WebSocket/GetInventoryModelTask.h"
#include "Request/DescribeItemModelMastersRequest.h"
#include "Task/WebSocket/DescribeItemModelMastersTask.h"
#include "Request/CreateItemModelMasterRequest.h"
#include "Task/WebSocket/CreateItemModelMasterTask.h"
#include "Request/GetItemModelMasterRequest.h"
#include "Task/WebSocket/GetItemModelMasterTask.h"
#include "Request/UpdateItemModelMasterRequest.h"
#include "Task/WebSocket/UpdateItemModelMasterTask.h"
#include "Request/DeleteItemModelMasterRequest.h"
#include "Task/WebSocket/DeleteItemModelMasterTask.h"
#include "Request/DescribeItemModelsRequest.h"
#include "Task/WebSocket/DescribeItemModelsTask.h"
#include "Request/GetItemModelRequest.h"
#include "Task/WebSocket/GetItemModelTask.h"
#include "Request/DescribeSimpleInventoryModelMastersRequest.h"
#include "Task/WebSocket/DescribeSimpleInventoryModelMastersTask.h"
#include "Request/CreateSimpleInventoryModelMasterRequest.h"
#include "Task/WebSocket/CreateSimpleInventoryModelMasterTask.h"
#include "Request/GetSimpleInventoryModelMasterRequest.h"
#include "Task/WebSocket/GetSimpleInventoryModelMasterTask.h"
#include "Request/UpdateSimpleInventoryModelMasterRequest.h"
#include "Task/WebSocket/UpdateSimpleInventoryModelMasterTask.h"
#include "Request/DeleteSimpleInventoryModelMasterRequest.h"
#include "Task/WebSocket/DeleteSimpleInventoryModelMasterTask.h"
#include "Request/DescribeSimpleInventoryModelsRequest.h"
#include "Task/WebSocket/DescribeSimpleInventoryModelsTask.h"
#include "Request/GetSimpleInventoryModelRequest.h"
#include "Task/WebSocket/GetSimpleInventoryModelTask.h"
#include "Request/DescribeSimpleItemModelMastersRequest.h"
#include "Task/WebSocket/DescribeSimpleItemModelMastersTask.h"
#include "Request/CreateSimpleItemModelMasterRequest.h"
#include "Task/WebSocket/CreateSimpleItemModelMasterTask.h"
#include "Request/GetSimpleItemModelMasterRequest.h"
#include "Task/WebSocket/GetSimpleItemModelMasterTask.h"
#include "Request/UpdateSimpleItemModelMasterRequest.h"
#include "Task/WebSocket/UpdateSimpleItemModelMasterTask.h"
#include "Request/DeleteSimpleItemModelMasterRequest.h"
#include "Task/WebSocket/DeleteSimpleItemModelMasterTask.h"
#include "Request/DescribeSimpleItemModelsRequest.h"
#include "Task/WebSocket/DescribeSimpleItemModelsTask.h"
#include "Request/GetSimpleItemModelRequest.h"
#include "Task/WebSocket/GetSimpleItemModelTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentItemModelMasterRequest.h"
#include "Task/WebSocket/GetCurrentItemModelMasterTask.h"
#include "Request/UpdateCurrentItemModelMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentItemModelMasterTask.h"
#include "Request/UpdateCurrentItemModelMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentItemModelMasterFromGitHubTask.h"
#include "Request/DescribeInventoriesRequest.h"
#include "Task/WebSocket/DescribeInventoriesTask.h"
#include "Request/DescribeInventoriesByUserIdRequest.h"
#include "Task/WebSocket/DescribeInventoriesByUserIdTask.h"
#include "Request/GetInventoryRequest.h"
#include "Task/WebSocket/GetInventoryTask.h"
#include "Request/GetInventoryByUserIdRequest.h"
#include "Task/WebSocket/GetInventoryByUserIdTask.h"
#include "Request/AddCapacityByUserIdRequest.h"
#include "Task/WebSocket/AddCapacityByUserIdTask.h"
#include "Request/SetCapacityByUserIdRequest.h"
#include "Task/WebSocket/SetCapacityByUserIdTask.h"
#include "Request/DeleteInventoryByUserIdRequest.h"
#include "Task/WebSocket/DeleteInventoryByUserIdTask.h"
#include "Request/AddCapacityByStampSheetRequest.h"
#include "Task/WebSocket/AddCapacityByStampSheetTask.h"
#include "Request/SetCapacityByStampSheetRequest.h"
#include "Task/WebSocket/SetCapacityByStampSheetTask.h"
#include "Request/DescribeItemSetsRequest.h"
#include "Task/WebSocket/DescribeItemSetsTask.h"
#include "Request/DescribeItemSetsByUserIdRequest.h"
#include "Task/WebSocket/DescribeItemSetsByUserIdTask.h"
#include "Request/GetItemSetRequest.h"
#include "Task/WebSocket/GetItemSetTask.h"
#include "Request/GetItemSetByUserIdRequest.h"
#include "Task/WebSocket/GetItemSetByUserIdTask.h"
#include "Request/GetItemWithSignatureRequest.h"
#include "Task/WebSocket/GetItemWithSignatureTask.h"
#include "Request/GetItemWithSignatureByUserIdRequest.h"
#include "Task/WebSocket/GetItemWithSignatureByUserIdTask.h"
#include "Request/AcquireItemSetByUserIdRequest.h"
#include "Task/WebSocket/AcquireItemSetByUserIdTask.h"
#include "Request/ConsumeItemSetRequest.h"
#include "Task/WebSocket/ConsumeItemSetTask.h"
#include "Request/ConsumeItemSetByUserIdRequest.h"
#include "Task/WebSocket/ConsumeItemSetByUserIdTask.h"
#include "Request/DeleteItemSetByUserIdRequest.h"
#include "Task/WebSocket/DeleteItemSetByUserIdTask.h"
#include "Request/AcquireItemSetByStampSheetRequest.h"
#include "Task/WebSocket/AcquireItemSetByStampSheetTask.h"
#include "Request/ConsumeItemSetByStampTaskRequest.h"
#include "Task/WebSocket/ConsumeItemSetByStampTaskTask.h"
#include "Request/DescribeReferenceOfRequest.h"
#include "Task/WebSocket/DescribeReferenceOfTask.h"
#include "Request/DescribeReferenceOfByUserIdRequest.h"
#include "Task/WebSocket/DescribeReferenceOfByUserIdTask.h"
#include "Request/GetReferenceOfRequest.h"
#include "Task/WebSocket/GetReferenceOfTask.h"
#include "Request/GetReferenceOfByUserIdRequest.h"
#include "Task/WebSocket/GetReferenceOfByUserIdTask.h"
#include "Request/VerifyReferenceOfRequest.h"
#include "Task/WebSocket/VerifyReferenceOfTask.h"
#include "Request/VerifyReferenceOfByUserIdRequest.h"
#include "Task/WebSocket/VerifyReferenceOfByUserIdTask.h"
#include "Request/AddReferenceOfRequest.h"
#include "Task/WebSocket/AddReferenceOfTask.h"
#include "Request/AddReferenceOfByUserIdRequest.h"
#include "Task/WebSocket/AddReferenceOfByUserIdTask.h"
#include "Request/DeleteReferenceOfRequest.h"
#include "Task/WebSocket/DeleteReferenceOfTask.h"
#include "Request/DeleteReferenceOfByUserIdRequest.h"
#include "Task/WebSocket/DeleteReferenceOfByUserIdTask.h"
#include "Request/AddReferenceOfItemSetByStampSheetRequest.h"
#include "Task/WebSocket/AddReferenceOfItemSetByStampSheetTask.h"
#include "Request/DeleteReferenceOfItemSetByStampSheetRequest.h"
#include "Task/WebSocket/DeleteReferenceOfItemSetByStampSheetTask.h"
#include "Request/VerifyReferenceOfByStampTaskRequest.h"
#include "Task/WebSocket/VerifyReferenceOfByStampTaskTask.h"
#include "Request/DescribeSimpleItemsRequest.h"
#include "Task/WebSocket/DescribeSimpleItemsTask.h"
#include "Request/DescribeSimpleItemsByUserIdRequest.h"
#include "Task/WebSocket/DescribeSimpleItemsByUserIdTask.h"
#include "Request/GetSimpleItemRequest.h"
#include "Task/WebSocket/GetSimpleItemTask.h"
#include "Request/GetSimpleItemByUserIdRequest.h"
#include "Task/WebSocket/GetSimpleItemByUserIdTask.h"
#include "Request/GetSimpleItemWithSignatureRequest.h"
#include "Task/WebSocket/GetSimpleItemWithSignatureTask.h"
#include "Request/GetSimpleItemWithSignatureByUserIdRequest.h"
#include "Task/WebSocket/GetSimpleItemWithSignatureByUserIdTask.h"
#include "Request/AcquireSimpleItemsByUserIdRequest.h"
#include "Task/WebSocket/AcquireSimpleItemsByUserIdTask.h"
#include "Request/ConsumeSimpleItemsRequest.h"
#include "Task/WebSocket/ConsumeSimpleItemsTask.h"
#include "Request/ConsumeSimpleItemsByUserIdRequest.h"
#include "Task/WebSocket/ConsumeSimpleItemsByUserIdTask.h"
#include "Request/DeleteSimpleItemsByUserIdRequest.h"
#include "Task/WebSocket/DeleteSimpleItemsByUserIdTask.h"
#include "Request/AcquireSimpleItemsByStampSheetRequest.h"
#include "Task/WebSocket/AcquireSimpleItemsByStampSheetTask.h"
#include "Request/ConsumeSimpleItemsByStampTaskRequest.h"
#include "Task/WebSocket/ConsumeSimpleItemsByStampTaskTask.h"

namespace Gs2::Inventory
{
    class GS2INVENTORY_API FGs2InventoryWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2InventoryWebSocketClient(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session
        ): FAbstractWebSocketGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> DescribeNamespaces(
            const Request::FDescribeNamespacesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> CreateNamespace(
            const Request::FCreateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> GetNamespaceStatus(
            const Request::FGetNamespaceStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> GetNamespace(
            const Request::FGetNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> UpdateNamespace(
            const Request::FUpdateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> DeleteNamespace(
            const Request::FDeleteNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeInventoryModelMastersTask>> DescribeInventoryModelMasters(
            const Request::FDescribeInventoryModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateInventoryModelMasterTask>> CreateInventoryModelMaster(
            const Request::FCreateInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetInventoryModelMasterTask>> GetInventoryModelMaster(
            const Request::FGetInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateInventoryModelMasterTask>> UpdateInventoryModelMaster(
            const Request::FUpdateInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteInventoryModelMasterTask>> DeleteInventoryModelMaster(
            const Request::FDeleteInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeInventoryModelsTask>> DescribeInventoryModels(
            const Request::FDescribeInventoryModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetInventoryModelTask>> GetInventoryModel(
            const Request::FGetInventoryModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeItemModelMastersTask>> DescribeItemModelMasters(
            const Request::FDescribeItemModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateItemModelMasterTask>> CreateItemModelMaster(
            const Request::FCreateItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetItemModelMasterTask>> GetItemModelMaster(
            const Request::FGetItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateItemModelMasterTask>> UpdateItemModelMaster(
            const Request::FUpdateItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteItemModelMasterTask>> DeleteItemModelMaster(
            const Request::FDeleteItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeItemModelsTask>> DescribeItemModels(
            const Request::FDescribeItemModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetItemModelTask>> GetItemModel(
            const Request::FGetItemModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSimpleInventoryModelMastersTask>> DescribeSimpleInventoryModelMasters(
            const Request::FDescribeSimpleInventoryModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateSimpleInventoryModelMasterTask>> CreateSimpleInventoryModelMaster(
            const Request::FCreateSimpleInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSimpleInventoryModelMasterTask>> GetSimpleInventoryModelMaster(
            const Request::FGetSimpleInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateSimpleInventoryModelMasterTask>> UpdateSimpleInventoryModelMaster(
            const Request::FUpdateSimpleInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSimpleInventoryModelMasterTask>> DeleteSimpleInventoryModelMaster(
            const Request::FDeleteSimpleInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSimpleInventoryModelsTask>> DescribeSimpleInventoryModels(
            const Request::FDescribeSimpleInventoryModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSimpleInventoryModelTask>> GetSimpleInventoryModel(
            const Request::FGetSimpleInventoryModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSimpleItemModelMastersTask>> DescribeSimpleItemModelMasters(
            const Request::FDescribeSimpleItemModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateSimpleItemModelMasterTask>> CreateSimpleItemModelMaster(
            const Request::FCreateSimpleItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSimpleItemModelMasterTask>> GetSimpleItemModelMaster(
            const Request::FGetSimpleItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateSimpleItemModelMasterTask>> UpdateSimpleItemModelMaster(
            const Request::FUpdateSimpleItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSimpleItemModelMasterTask>> DeleteSimpleItemModelMaster(
            const Request::FDeleteSimpleItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSimpleItemModelsTask>> DescribeSimpleItemModels(
            const Request::FDescribeSimpleItemModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSimpleItemModelTask>> GetSimpleItemModel(
            const Request::FGetSimpleItemModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentItemModelMasterTask>> GetCurrentItemModelMaster(
            const Request::FGetCurrentItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentItemModelMasterTask>> UpdateCurrentItemModelMaster(
            const Request::FUpdateCurrentItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentItemModelMasterFromGitHubTask>> UpdateCurrentItemModelMasterFromGitHub(
            const Request::FUpdateCurrentItemModelMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeInventoriesTask>> DescribeInventories(
            const Request::FDescribeInventoriesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeInventoriesByUserIdTask>> DescribeInventoriesByUserId(
            const Request::FDescribeInventoriesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetInventoryTask>> GetInventory(
            const Request::FGetInventoryRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetInventoryByUserIdTask>> GetInventoryByUserId(
            const Request::FGetInventoryByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddCapacityByUserIdTask>> AddCapacityByUserId(
            const Request::FAddCapacityByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetCapacityByUserIdTask>> SetCapacityByUserId(
            const Request::FSetCapacityByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteInventoryByUserIdTask>> DeleteInventoryByUserId(
            const Request::FDeleteInventoryByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddCapacityByStampSheetTask>> AddCapacityByStampSheet(
            const Request::FAddCapacityByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetCapacityByStampSheetTask>> SetCapacityByStampSheet(
            const Request::FSetCapacityByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeItemSetsTask>> DescribeItemSets(
            const Request::FDescribeItemSetsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeItemSetsByUserIdTask>> DescribeItemSetsByUserId(
            const Request::FDescribeItemSetsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetItemSetTask>> GetItemSet(
            const Request::FGetItemSetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetItemSetByUserIdTask>> GetItemSetByUserId(
            const Request::FGetItemSetByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetItemWithSignatureTask>> GetItemWithSignature(
            const Request::FGetItemWithSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetItemWithSignatureByUserIdTask>> GetItemWithSignatureByUserId(
            const Request::FGetItemWithSignatureByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireItemSetByUserIdTask>> AcquireItemSetByUserId(
            const Request::FAcquireItemSetByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeItemSetTask>> ConsumeItemSet(
            const Request::FConsumeItemSetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeItemSetByUserIdTask>> ConsumeItemSetByUserId(
            const Request::FConsumeItemSetByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteItemSetByUserIdTask>> DeleteItemSetByUserId(
            const Request::FDeleteItemSetByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireItemSetByStampSheetTask>> AcquireItemSetByStampSheet(
            const Request::FAcquireItemSetByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeItemSetByStampTaskTask>> ConsumeItemSetByStampTask(
            const Request::FConsumeItemSetByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeReferenceOfTask>> DescribeReferenceOf(
            const Request::FDescribeReferenceOfRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeReferenceOfByUserIdTask>> DescribeReferenceOfByUserId(
            const Request::FDescribeReferenceOfByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetReferenceOfTask>> GetReferenceOf(
            const Request::FGetReferenceOfRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetReferenceOfByUserIdTask>> GetReferenceOfByUserId(
            const Request::FGetReferenceOfByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyReferenceOfTask>> VerifyReferenceOf(
            const Request::FVerifyReferenceOfRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyReferenceOfByUserIdTask>> VerifyReferenceOfByUserId(
            const Request::FVerifyReferenceOfByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddReferenceOfTask>> AddReferenceOf(
            const Request::FAddReferenceOfRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddReferenceOfByUserIdTask>> AddReferenceOfByUserId(
            const Request::FAddReferenceOfByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteReferenceOfTask>> DeleteReferenceOf(
            const Request::FDeleteReferenceOfRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteReferenceOfByUserIdTask>> DeleteReferenceOfByUserId(
            const Request::FDeleteReferenceOfByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddReferenceOfItemSetByStampSheetTask>> AddReferenceOfItemSetByStampSheet(
            const Request::FAddReferenceOfItemSetByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteReferenceOfItemSetByStampSheetTask>> DeleteReferenceOfItemSetByStampSheet(
            const Request::FDeleteReferenceOfItemSetByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyReferenceOfByStampTaskTask>> VerifyReferenceOfByStampTask(
            const Request::FVerifyReferenceOfByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSimpleItemsTask>> DescribeSimpleItems(
            const Request::FDescribeSimpleItemsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSimpleItemsByUserIdTask>> DescribeSimpleItemsByUserId(
            const Request::FDescribeSimpleItemsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSimpleItemTask>> GetSimpleItem(
            const Request::FGetSimpleItemRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSimpleItemByUserIdTask>> GetSimpleItemByUserId(
            const Request::FGetSimpleItemByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSimpleItemWithSignatureTask>> GetSimpleItemWithSignature(
            const Request::FGetSimpleItemWithSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSimpleItemWithSignatureByUserIdTask>> GetSimpleItemWithSignatureByUserId(
            const Request::FGetSimpleItemWithSignatureByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireSimpleItemsByUserIdTask>> AcquireSimpleItemsByUserId(
            const Request::FAcquireSimpleItemsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeSimpleItemsTask>> ConsumeSimpleItems(
            const Request::FConsumeSimpleItemsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeSimpleItemsByUserIdTask>> ConsumeSimpleItemsByUserId(
            const Request::FConsumeSimpleItemsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSimpleItemsByUserIdTask>> DeleteSimpleItemsByUserId(
            const Request::FDeleteSimpleItemsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireSimpleItemsByStampSheetTask>> AcquireSimpleItemsByStampSheet(
            const Request::FAcquireSimpleItemsByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeSimpleItemsByStampTaskTask>> ConsumeSimpleItemsByStampTask(
            const Request::FConsumeSimpleItemsByStampTaskRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2InventoryWebSocketClient, ESPMode::ThreadSafe> FGs2InventoryWebSocketClientPtr;
}