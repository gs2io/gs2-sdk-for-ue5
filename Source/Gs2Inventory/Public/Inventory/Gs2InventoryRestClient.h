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
#include "Core/Net/AbstractGs2Client.h"
#include "Request/DescribeNamespacesRequest.h"
#include "Task/Rest/DescribeNamespacesTask.h"
#include "Request/CreateNamespaceRequest.h"
#include "Task/Rest/CreateNamespaceTask.h"
#include "Request/GetNamespaceStatusRequest.h"
#include "Task/Rest/GetNamespaceStatusTask.h"
#include "Request/GetNamespaceRequest.h"
#include "Task/Rest/GetNamespaceTask.h"
#include "Request/UpdateNamespaceRequest.h"
#include "Task/Rest/UpdateNamespaceTask.h"
#include "Request/DeleteNamespaceRequest.h"
#include "Task/Rest/DeleteNamespaceTask.h"
#include "Request/DescribeInventoryModelMastersRequest.h"
#include "Task/Rest/DescribeInventoryModelMastersTask.h"
#include "Request/CreateInventoryModelMasterRequest.h"
#include "Task/Rest/CreateInventoryModelMasterTask.h"
#include "Request/GetInventoryModelMasterRequest.h"
#include "Task/Rest/GetInventoryModelMasterTask.h"
#include "Request/UpdateInventoryModelMasterRequest.h"
#include "Task/Rest/UpdateInventoryModelMasterTask.h"
#include "Request/DeleteInventoryModelMasterRequest.h"
#include "Task/Rest/DeleteInventoryModelMasterTask.h"
#include "Request/DescribeInventoryModelsRequest.h"
#include "Task/Rest/DescribeInventoryModelsTask.h"
#include "Request/GetInventoryModelRequest.h"
#include "Task/Rest/GetInventoryModelTask.h"
#include "Request/DescribeItemModelMastersRequest.h"
#include "Task/Rest/DescribeItemModelMastersTask.h"
#include "Request/CreateItemModelMasterRequest.h"
#include "Task/Rest/CreateItemModelMasterTask.h"
#include "Request/GetItemModelMasterRequest.h"
#include "Task/Rest/GetItemModelMasterTask.h"
#include "Request/UpdateItemModelMasterRequest.h"
#include "Task/Rest/UpdateItemModelMasterTask.h"
#include "Request/DeleteItemModelMasterRequest.h"
#include "Task/Rest/DeleteItemModelMasterTask.h"
#include "Request/DescribeItemModelsRequest.h"
#include "Task/Rest/DescribeItemModelsTask.h"
#include "Request/GetItemModelRequest.h"
#include "Task/Rest/GetItemModelTask.h"
#include "Request/DescribeSimpleInventoryModelMastersRequest.h"
#include "Task/Rest/DescribeSimpleInventoryModelMastersTask.h"
#include "Request/CreateSimpleInventoryModelMasterRequest.h"
#include "Task/Rest/CreateSimpleInventoryModelMasterTask.h"
#include "Request/GetSimpleInventoryModelMasterRequest.h"
#include "Task/Rest/GetSimpleInventoryModelMasterTask.h"
#include "Request/UpdateSimpleInventoryModelMasterRequest.h"
#include "Task/Rest/UpdateSimpleInventoryModelMasterTask.h"
#include "Request/DeleteSimpleInventoryModelMasterRequest.h"
#include "Task/Rest/DeleteSimpleInventoryModelMasterTask.h"
#include "Request/DescribeSimpleInventoryModelsRequest.h"
#include "Task/Rest/DescribeSimpleInventoryModelsTask.h"
#include "Request/GetSimpleInventoryModelRequest.h"
#include "Task/Rest/GetSimpleInventoryModelTask.h"
#include "Request/DescribeSimpleItemModelMastersRequest.h"
#include "Task/Rest/DescribeSimpleItemModelMastersTask.h"
#include "Request/CreateSimpleItemModelMasterRequest.h"
#include "Task/Rest/CreateSimpleItemModelMasterTask.h"
#include "Request/GetSimpleItemModelMasterRequest.h"
#include "Task/Rest/GetSimpleItemModelMasterTask.h"
#include "Request/UpdateSimpleItemModelMasterRequest.h"
#include "Task/Rest/UpdateSimpleItemModelMasterTask.h"
#include "Request/DeleteSimpleItemModelMasterRequest.h"
#include "Task/Rest/DeleteSimpleItemModelMasterTask.h"
#include "Request/DescribeSimpleItemModelsRequest.h"
#include "Task/Rest/DescribeSimpleItemModelsTask.h"
#include "Request/GetSimpleItemModelRequest.h"
#include "Task/Rest/GetSimpleItemModelTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentItemModelMasterRequest.h"
#include "Task/Rest/GetCurrentItemModelMasterTask.h"
#include "Request/UpdateCurrentItemModelMasterRequest.h"
#include "Task/Rest/UpdateCurrentItemModelMasterTask.h"
#include "Request/UpdateCurrentItemModelMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentItemModelMasterFromGitHubTask.h"
#include "Request/DescribeInventoriesRequest.h"
#include "Task/Rest/DescribeInventoriesTask.h"
#include "Request/DescribeInventoriesByUserIdRequest.h"
#include "Task/Rest/DescribeInventoriesByUserIdTask.h"
#include "Request/GetInventoryRequest.h"
#include "Task/Rest/GetInventoryTask.h"
#include "Request/GetInventoryByUserIdRequest.h"
#include "Task/Rest/GetInventoryByUserIdTask.h"
#include "Request/AddCapacityByUserIdRequest.h"
#include "Task/Rest/AddCapacityByUserIdTask.h"
#include "Request/SetCapacityByUserIdRequest.h"
#include "Task/Rest/SetCapacityByUserIdTask.h"
#include "Request/DeleteInventoryByUserIdRequest.h"
#include "Task/Rest/DeleteInventoryByUserIdTask.h"
#include "Request/AddCapacityByStampSheetRequest.h"
#include "Task/Rest/AddCapacityByStampSheetTask.h"
#include "Request/SetCapacityByStampSheetRequest.h"
#include "Task/Rest/SetCapacityByStampSheetTask.h"
#include "Request/DescribeItemSetsRequest.h"
#include "Task/Rest/DescribeItemSetsTask.h"
#include "Request/DescribeItemSetsByUserIdRequest.h"
#include "Task/Rest/DescribeItemSetsByUserIdTask.h"
#include "Request/GetItemSetRequest.h"
#include "Task/Rest/GetItemSetTask.h"
#include "Request/GetItemSetByUserIdRequest.h"
#include "Task/Rest/GetItemSetByUserIdTask.h"
#include "Request/GetItemWithSignatureRequest.h"
#include "Task/Rest/GetItemWithSignatureTask.h"
#include "Request/GetItemWithSignatureByUserIdRequest.h"
#include "Task/Rest/GetItemWithSignatureByUserIdTask.h"
#include "Request/AcquireItemSetByUserIdRequest.h"
#include "Task/Rest/AcquireItemSetByUserIdTask.h"
#include "Request/ConsumeItemSetRequest.h"
#include "Task/Rest/ConsumeItemSetTask.h"
#include "Request/ConsumeItemSetByUserIdRequest.h"
#include "Task/Rest/ConsumeItemSetByUserIdTask.h"
#include "Request/DeleteItemSetByUserIdRequest.h"
#include "Task/Rest/DeleteItemSetByUserIdTask.h"
#include "Request/AcquireItemSetByStampSheetRequest.h"
#include "Task/Rest/AcquireItemSetByStampSheetTask.h"
#include "Request/ConsumeItemSetByStampTaskRequest.h"
#include "Task/Rest/ConsumeItemSetByStampTaskTask.h"
#include "Request/DescribeReferenceOfRequest.h"
#include "Task/Rest/DescribeReferenceOfTask.h"
#include "Request/DescribeReferenceOfByUserIdRequest.h"
#include "Task/Rest/DescribeReferenceOfByUserIdTask.h"
#include "Request/GetReferenceOfRequest.h"
#include "Task/Rest/GetReferenceOfTask.h"
#include "Request/GetReferenceOfByUserIdRequest.h"
#include "Task/Rest/GetReferenceOfByUserIdTask.h"
#include "Request/VerifyReferenceOfRequest.h"
#include "Task/Rest/VerifyReferenceOfTask.h"
#include "Request/VerifyReferenceOfByUserIdRequest.h"
#include "Task/Rest/VerifyReferenceOfByUserIdTask.h"
#include "Request/AddReferenceOfRequest.h"
#include "Task/Rest/AddReferenceOfTask.h"
#include "Request/AddReferenceOfByUserIdRequest.h"
#include "Task/Rest/AddReferenceOfByUserIdTask.h"
#include "Request/DeleteReferenceOfRequest.h"
#include "Task/Rest/DeleteReferenceOfTask.h"
#include "Request/DeleteReferenceOfByUserIdRequest.h"
#include "Task/Rest/DeleteReferenceOfByUserIdTask.h"
#include "Request/AddReferenceOfItemSetByStampSheetRequest.h"
#include "Task/Rest/AddReferenceOfItemSetByStampSheetTask.h"
#include "Request/DeleteReferenceOfItemSetByStampSheetRequest.h"
#include "Task/Rest/DeleteReferenceOfItemSetByStampSheetTask.h"
#include "Request/VerifyReferenceOfByStampTaskRequest.h"
#include "Task/Rest/VerifyReferenceOfByStampTaskTask.h"
#include "Request/DescribeSimpleItemsRequest.h"
#include "Task/Rest/DescribeSimpleItemsTask.h"
#include "Request/DescribeSimpleItemsByUserIdRequest.h"
#include "Task/Rest/DescribeSimpleItemsByUserIdTask.h"
#include "Request/GetSimpleItemRequest.h"
#include "Task/Rest/GetSimpleItemTask.h"
#include "Request/GetSimpleItemByUserIdRequest.h"
#include "Task/Rest/GetSimpleItemByUserIdTask.h"
#include "Request/GetSimpleItemWithSignatureRequest.h"
#include "Task/Rest/GetSimpleItemWithSignatureTask.h"
#include "Request/GetSimpleItemWithSignatureByUserIdRequest.h"
#include "Task/Rest/GetSimpleItemWithSignatureByUserIdTask.h"
#include "Request/AcquireSimpleItemsByUserIdRequest.h"
#include "Task/Rest/AcquireSimpleItemsByUserIdTask.h"
#include "Request/ConsumeSimpleItemsRequest.h"
#include "Task/Rest/ConsumeSimpleItemsTask.h"
#include "Request/ConsumeSimpleItemsByUserIdRequest.h"
#include "Task/Rest/ConsumeSimpleItemsByUserIdTask.h"
#include "Request/DeleteSimpleItemsByUserIdRequest.h"
#include "Task/Rest/DeleteSimpleItemsByUserIdTask.h"
#include "Request/AcquireSimpleItemsByStampSheetRequest.h"
#include "Task/Rest/AcquireSimpleItemsByStampSheetTask.h"
#include "Request/ConsumeSimpleItemsByStampTaskRequest.h"
#include "Task/Rest/ConsumeSimpleItemsByStampTaskTask.h"

namespace Gs2::Inventory
{
    class GS2INVENTORY_API FGs2InventoryRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2InventoryRestClient(
            const Core::Net::Rest::FGs2RestSessionPtr Session
        ): FAbstractGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> DescribeNamespaces(
            const Request::FDescribeNamespacesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> CreateNamespace(
            const Request::FCreateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> GetNamespaceStatus(
            const Request::FGetNamespaceStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> GetNamespace(
            const Request::FGetNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> UpdateNamespace(
            const Request::FUpdateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> DeleteNamespace(
            const Request::FDeleteNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeInventoryModelMastersTask>> DescribeInventoryModelMasters(
            const Request::FDescribeInventoryModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateInventoryModelMasterTask>> CreateInventoryModelMaster(
            const Request::FCreateInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetInventoryModelMasterTask>> GetInventoryModelMaster(
            const Request::FGetInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateInventoryModelMasterTask>> UpdateInventoryModelMaster(
            const Request::FUpdateInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteInventoryModelMasterTask>> DeleteInventoryModelMaster(
            const Request::FDeleteInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeInventoryModelsTask>> DescribeInventoryModels(
            const Request::FDescribeInventoryModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetInventoryModelTask>> GetInventoryModel(
            const Request::FGetInventoryModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeItemModelMastersTask>> DescribeItemModelMasters(
            const Request::FDescribeItemModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateItemModelMasterTask>> CreateItemModelMaster(
            const Request::FCreateItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetItemModelMasterTask>> GetItemModelMaster(
            const Request::FGetItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateItemModelMasterTask>> UpdateItemModelMaster(
            const Request::FUpdateItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteItemModelMasterTask>> DeleteItemModelMaster(
            const Request::FDeleteItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeItemModelsTask>> DescribeItemModels(
            const Request::FDescribeItemModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetItemModelTask>> GetItemModel(
            const Request::FGetItemModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSimpleInventoryModelMastersTask>> DescribeSimpleInventoryModelMasters(
            const Request::FDescribeSimpleInventoryModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateSimpleInventoryModelMasterTask>> CreateSimpleInventoryModelMaster(
            const Request::FCreateSimpleInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSimpleInventoryModelMasterTask>> GetSimpleInventoryModelMaster(
            const Request::FGetSimpleInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateSimpleInventoryModelMasterTask>> UpdateSimpleInventoryModelMaster(
            const Request::FUpdateSimpleInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteSimpleInventoryModelMasterTask>> DeleteSimpleInventoryModelMaster(
            const Request::FDeleteSimpleInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSimpleInventoryModelsTask>> DescribeSimpleInventoryModels(
            const Request::FDescribeSimpleInventoryModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSimpleInventoryModelTask>> GetSimpleInventoryModel(
            const Request::FGetSimpleInventoryModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSimpleItemModelMastersTask>> DescribeSimpleItemModelMasters(
            const Request::FDescribeSimpleItemModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateSimpleItemModelMasterTask>> CreateSimpleItemModelMaster(
            const Request::FCreateSimpleItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSimpleItemModelMasterTask>> GetSimpleItemModelMaster(
            const Request::FGetSimpleItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateSimpleItemModelMasterTask>> UpdateSimpleItemModelMaster(
            const Request::FUpdateSimpleItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteSimpleItemModelMasterTask>> DeleteSimpleItemModelMaster(
            const Request::FDeleteSimpleItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSimpleItemModelsTask>> DescribeSimpleItemModels(
            const Request::FDescribeSimpleItemModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSimpleItemModelTask>> GetSimpleItemModel(
            const Request::FGetSimpleItemModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentItemModelMasterTask>> GetCurrentItemModelMaster(
            const Request::FGetCurrentItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentItemModelMasterTask>> UpdateCurrentItemModelMaster(
            const Request::FUpdateCurrentItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentItemModelMasterFromGitHubTask>> UpdateCurrentItemModelMasterFromGitHub(
            const Request::FUpdateCurrentItemModelMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeInventoriesTask>> DescribeInventories(
            const Request::FDescribeInventoriesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeInventoriesByUserIdTask>> DescribeInventoriesByUserId(
            const Request::FDescribeInventoriesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetInventoryTask>> GetInventory(
            const Request::FGetInventoryRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetInventoryByUserIdTask>> GetInventoryByUserId(
            const Request::FGetInventoryByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddCapacityByUserIdTask>> AddCapacityByUserId(
            const Request::FAddCapacityByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetCapacityByUserIdTask>> SetCapacityByUserId(
            const Request::FSetCapacityByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteInventoryByUserIdTask>> DeleteInventoryByUserId(
            const Request::FDeleteInventoryByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddCapacityByStampSheetTask>> AddCapacityByStampSheet(
            const Request::FAddCapacityByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetCapacityByStampSheetTask>> SetCapacityByStampSheet(
            const Request::FSetCapacityByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeItemSetsTask>> DescribeItemSets(
            const Request::FDescribeItemSetsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeItemSetsByUserIdTask>> DescribeItemSetsByUserId(
            const Request::FDescribeItemSetsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetItemSetTask>> GetItemSet(
            const Request::FGetItemSetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetItemSetByUserIdTask>> GetItemSetByUserId(
            const Request::FGetItemSetByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetItemWithSignatureTask>> GetItemWithSignature(
            const Request::FGetItemWithSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetItemWithSignatureByUserIdTask>> GetItemWithSignatureByUserId(
            const Request::FGetItemWithSignatureByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAcquireItemSetByUserIdTask>> AcquireItemSetByUserId(
            const Request::FAcquireItemSetByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FConsumeItemSetTask>> ConsumeItemSet(
            const Request::FConsumeItemSetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FConsumeItemSetByUserIdTask>> ConsumeItemSetByUserId(
            const Request::FConsumeItemSetByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteItemSetByUserIdTask>> DeleteItemSetByUserId(
            const Request::FDeleteItemSetByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAcquireItemSetByStampSheetTask>> AcquireItemSetByStampSheet(
            const Request::FAcquireItemSetByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FConsumeItemSetByStampTaskTask>> ConsumeItemSetByStampTask(
            const Request::FConsumeItemSetByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeReferenceOfTask>> DescribeReferenceOf(
            const Request::FDescribeReferenceOfRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeReferenceOfByUserIdTask>> DescribeReferenceOfByUserId(
            const Request::FDescribeReferenceOfByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetReferenceOfTask>> GetReferenceOf(
            const Request::FGetReferenceOfRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetReferenceOfByUserIdTask>> GetReferenceOfByUserId(
            const Request::FGetReferenceOfByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyReferenceOfTask>> VerifyReferenceOf(
            const Request::FVerifyReferenceOfRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyReferenceOfByUserIdTask>> VerifyReferenceOfByUserId(
            const Request::FVerifyReferenceOfByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddReferenceOfTask>> AddReferenceOf(
            const Request::FAddReferenceOfRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddReferenceOfByUserIdTask>> AddReferenceOfByUserId(
            const Request::FAddReferenceOfByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteReferenceOfTask>> DeleteReferenceOf(
            const Request::FDeleteReferenceOfRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteReferenceOfByUserIdTask>> DeleteReferenceOfByUserId(
            const Request::FDeleteReferenceOfByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddReferenceOfItemSetByStampSheetTask>> AddReferenceOfItemSetByStampSheet(
            const Request::FAddReferenceOfItemSetByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteReferenceOfItemSetByStampSheetTask>> DeleteReferenceOfItemSetByStampSheet(
            const Request::FDeleteReferenceOfItemSetByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyReferenceOfByStampTaskTask>> VerifyReferenceOfByStampTask(
            const Request::FVerifyReferenceOfByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSimpleItemsTask>> DescribeSimpleItems(
            const Request::FDescribeSimpleItemsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSimpleItemsByUserIdTask>> DescribeSimpleItemsByUserId(
            const Request::FDescribeSimpleItemsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSimpleItemTask>> GetSimpleItem(
            const Request::FGetSimpleItemRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSimpleItemByUserIdTask>> GetSimpleItemByUserId(
            const Request::FGetSimpleItemByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSimpleItemWithSignatureTask>> GetSimpleItemWithSignature(
            const Request::FGetSimpleItemWithSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSimpleItemWithSignatureByUserIdTask>> GetSimpleItemWithSignatureByUserId(
            const Request::FGetSimpleItemWithSignatureByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAcquireSimpleItemsByUserIdTask>> AcquireSimpleItemsByUserId(
            const Request::FAcquireSimpleItemsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FConsumeSimpleItemsTask>> ConsumeSimpleItems(
            const Request::FConsumeSimpleItemsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FConsumeSimpleItemsByUserIdTask>> ConsumeSimpleItemsByUserId(
            const Request::FConsumeSimpleItemsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteSimpleItemsByUserIdTask>> DeleteSimpleItemsByUserId(
            const Request::FDeleteSimpleItemsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAcquireSimpleItemsByStampSheetTask>> AcquireSimpleItemsByStampSheet(
            const Request::FAcquireSimpleItemsByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FConsumeSimpleItemsByStampTaskTask>> ConsumeSimpleItemsByStampTask(
            const Request::FConsumeSimpleItemsByStampTaskRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2InventoryRestClient, ESPMode::ThreadSafe> FGs2InventoryRestClientPtr;
}