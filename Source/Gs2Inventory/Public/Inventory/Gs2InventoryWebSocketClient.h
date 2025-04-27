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
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/DumpUserDataByUserIdTask.h"
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckDumpUserDataByUserIdTask.h"
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CleanUserDataByUserIdTask.h"
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckCleanUserDataByUserIdTask.h"
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/PrepareImportUserDataByUserIdTask.h"
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/ImportUserDataByUserIdTask.h"
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckImportUserDataByUserIdTask.h"
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
#include "Request/DescribeBigInventoryModelMastersRequest.h"
#include "Task/WebSocket/DescribeBigInventoryModelMastersTask.h"
#include "Request/CreateBigInventoryModelMasterRequest.h"
#include "Task/WebSocket/CreateBigInventoryModelMasterTask.h"
#include "Request/GetBigInventoryModelMasterRequest.h"
#include "Task/WebSocket/GetBigInventoryModelMasterTask.h"
#include "Request/UpdateBigInventoryModelMasterRequest.h"
#include "Task/WebSocket/UpdateBigInventoryModelMasterTask.h"
#include "Request/DeleteBigInventoryModelMasterRequest.h"
#include "Task/WebSocket/DeleteBigInventoryModelMasterTask.h"
#include "Request/DescribeBigInventoryModelsRequest.h"
#include "Task/WebSocket/DescribeBigInventoryModelsTask.h"
#include "Request/GetBigInventoryModelRequest.h"
#include "Task/WebSocket/GetBigInventoryModelTask.h"
#include "Request/DescribeBigItemModelMastersRequest.h"
#include "Task/WebSocket/DescribeBigItemModelMastersTask.h"
#include "Request/CreateBigItemModelMasterRequest.h"
#include "Task/WebSocket/CreateBigItemModelMasterTask.h"
#include "Request/GetBigItemModelMasterRequest.h"
#include "Task/WebSocket/GetBigItemModelMasterTask.h"
#include "Request/UpdateBigItemModelMasterRequest.h"
#include "Task/WebSocket/UpdateBigItemModelMasterTask.h"
#include "Request/DeleteBigItemModelMasterRequest.h"
#include "Task/WebSocket/DeleteBigItemModelMasterTask.h"
#include "Request/DescribeBigItemModelsRequest.h"
#include "Task/WebSocket/DescribeBigItemModelsTask.h"
#include "Request/GetBigItemModelRequest.h"
#include "Task/WebSocket/GetBigItemModelTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentItemModelMasterRequest.h"
#include "Task/WebSocket/GetCurrentItemModelMasterTask.h"
#include "Request/PreUpdateCurrentItemModelMasterRequest.h"
#include "Task/WebSocket/PreUpdateCurrentItemModelMasterTask.h"
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
#include "Request/VerifyInventoryCurrentMaxCapacityRequest.h"
#include "Task/WebSocket/VerifyInventoryCurrentMaxCapacityTask.h"
#include "Request/VerifyInventoryCurrentMaxCapacityByUserIdRequest.h"
#include "Task/WebSocket/VerifyInventoryCurrentMaxCapacityByUserIdTask.h"
#include "Request/VerifyInventoryCurrentMaxCapacityByStampTaskRequest.h"
#include "Task/WebSocket/VerifyInventoryCurrentMaxCapacityByStampTaskTask.h"
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
#include "Request/AcquireItemSetWithGradeByUserIdRequest.h"
#include "Task/WebSocket/AcquireItemSetWithGradeByUserIdTask.h"
#include "Request/ConsumeItemSetRequest.h"
#include "Task/WebSocket/ConsumeItemSetTask.h"
#include "Request/ConsumeItemSetByUserIdRequest.h"
#include "Task/WebSocket/ConsumeItemSetByUserIdTask.h"
#include "Request/DeleteItemSetByUserIdRequest.h"
#include "Task/WebSocket/DeleteItemSetByUserIdTask.h"
#include "Request/VerifyItemSetRequest.h"
#include "Task/WebSocket/VerifyItemSetTask.h"
#include "Request/VerifyItemSetByUserIdRequest.h"
#include "Task/WebSocket/VerifyItemSetByUserIdTask.h"
#include "Request/AcquireItemSetByStampSheetRequest.h"
#include "Task/WebSocket/AcquireItemSetByStampSheetTask.h"
#include "Request/AcquireItemSetWithGradeByStampSheetRequest.h"
#include "Task/WebSocket/AcquireItemSetWithGradeByStampSheetTask.h"
#include "Request/ConsumeItemSetByStampTaskRequest.h"
#include "Task/WebSocket/ConsumeItemSetByStampTaskTask.h"
#include "Request/VerifyItemSetByStampTaskRequest.h"
#include "Task/WebSocket/VerifyItemSetByStampTaskTask.h"
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
#include "Request/SetSimpleItemsByUserIdRequest.h"
#include "Task/WebSocket/SetSimpleItemsByUserIdTask.h"
#include "Request/DeleteSimpleItemsByUserIdRequest.h"
#include "Task/WebSocket/DeleteSimpleItemsByUserIdTask.h"
#include "Request/VerifySimpleItemRequest.h"
#include "Task/WebSocket/VerifySimpleItemTask.h"
#include "Request/VerifySimpleItemByUserIdRequest.h"
#include "Task/WebSocket/VerifySimpleItemByUserIdTask.h"
#include "Request/AcquireSimpleItemsByStampSheetRequest.h"
#include "Task/WebSocket/AcquireSimpleItemsByStampSheetTask.h"
#include "Request/ConsumeSimpleItemsByStampTaskRequest.h"
#include "Task/WebSocket/ConsumeSimpleItemsByStampTaskTask.h"
#include "Request/SetSimpleItemsByStampSheetRequest.h"
#include "Task/WebSocket/SetSimpleItemsByStampSheetTask.h"
#include "Request/VerifySimpleItemByStampTaskRequest.h"
#include "Task/WebSocket/VerifySimpleItemByStampTaskTask.h"
#include "Request/DescribeBigItemsRequest.h"
#include "Task/WebSocket/DescribeBigItemsTask.h"
#include "Request/DescribeBigItemsByUserIdRequest.h"
#include "Task/WebSocket/DescribeBigItemsByUserIdTask.h"
#include "Request/GetBigItemRequest.h"
#include "Task/WebSocket/GetBigItemTask.h"
#include "Request/GetBigItemByUserIdRequest.h"
#include "Task/WebSocket/GetBigItemByUserIdTask.h"
#include "Request/AcquireBigItemByUserIdRequest.h"
#include "Task/WebSocket/AcquireBigItemByUserIdTask.h"
#include "Request/ConsumeBigItemRequest.h"
#include "Task/WebSocket/ConsumeBigItemTask.h"
#include "Request/ConsumeBigItemByUserIdRequest.h"
#include "Task/WebSocket/ConsumeBigItemByUserIdTask.h"
#include "Request/SetBigItemByUserIdRequest.h"
#include "Task/WebSocket/SetBigItemByUserIdTask.h"
#include "Request/DeleteBigItemByUserIdRequest.h"
#include "Task/WebSocket/DeleteBigItemByUserIdTask.h"
#include "Request/VerifyBigItemRequest.h"
#include "Task/WebSocket/VerifyBigItemTask.h"
#include "Request/VerifyBigItemByUserIdRequest.h"
#include "Task/WebSocket/VerifyBigItemByUserIdTask.h"
#include "Request/AcquireBigItemByStampSheetRequest.h"
#include "Task/WebSocket/AcquireBigItemByStampSheetTask.h"
#include "Request/ConsumeBigItemByStampTaskRequest.h"
#include "Task/WebSocket/ConsumeBigItemByStampTaskTask.h"
#include "Request/SetBigItemByStampSheetRequest.h"
#include "Task/WebSocket/SetBigItemByStampSheetTask.h"
#include "Request/VerifyBigItemByStampTaskRequest.h"
#include "Task/WebSocket/VerifyBigItemByStampTaskTask.h"

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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>> DumpUserDataByUserId(
            const Request::FDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>> CheckDumpUserDataByUserId(
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>> CleanUserDataByUserId(
            const Request::FCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>> CheckCleanUserDataByUserId(
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>> PrepareImportUserDataByUserId(
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>> ImportUserDataByUserId(
            const Request::FImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>> CheckImportUserDataByUserId(
            const Request::FCheckImportUserDataByUserIdRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBigInventoryModelMastersTask>> DescribeBigInventoryModelMasters(
            const Request::FDescribeBigInventoryModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateBigInventoryModelMasterTask>> CreateBigInventoryModelMaster(
            const Request::FCreateBigInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBigInventoryModelMasterTask>> GetBigInventoryModelMaster(
            const Request::FGetBigInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateBigInventoryModelMasterTask>> UpdateBigInventoryModelMaster(
            const Request::FUpdateBigInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteBigInventoryModelMasterTask>> DeleteBigInventoryModelMaster(
            const Request::FDeleteBigInventoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBigInventoryModelsTask>> DescribeBigInventoryModels(
            const Request::FDescribeBigInventoryModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBigInventoryModelTask>> GetBigInventoryModel(
            const Request::FGetBigInventoryModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBigItemModelMastersTask>> DescribeBigItemModelMasters(
            const Request::FDescribeBigItemModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateBigItemModelMasterTask>> CreateBigItemModelMaster(
            const Request::FCreateBigItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBigItemModelMasterTask>> GetBigItemModelMaster(
            const Request::FGetBigItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateBigItemModelMasterTask>> UpdateBigItemModelMaster(
            const Request::FUpdateBigItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteBigItemModelMasterTask>> DeleteBigItemModelMaster(
            const Request::FDeleteBigItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBigItemModelsTask>> DescribeBigItemModels(
            const Request::FDescribeBigItemModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBigItemModelTask>> GetBigItemModel(
            const Request::FGetBigItemModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentItemModelMasterTask>> GetCurrentItemModelMaster(
            const Request::FGetCurrentItemModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPreUpdateCurrentItemModelMasterTask>> PreUpdateCurrentItemModelMaster(
            const Request::FPreUpdateCurrentItemModelMasterRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyInventoryCurrentMaxCapacityTask>> VerifyInventoryCurrentMaxCapacity(
            const Request::FVerifyInventoryCurrentMaxCapacityRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyInventoryCurrentMaxCapacityByUserIdTask>> VerifyInventoryCurrentMaxCapacityByUserId(
            const Request::FVerifyInventoryCurrentMaxCapacityByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyInventoryCurrentMaxCapacityByStampTaskTask>> VerifyInventoryCurrentMaxCapacityByStampTask(
            const Request::FVerifyInventoryCurrentMaxCapacityByStampTaskRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireItemSetWithGradeByUserIdTask>> AcquireItemSetWithGradeByUserId(
            const Request::FAcquireItemSetWithGradeByUserIdRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyItemSetTask>> VerifyItemSet(
            const Request::FVerifyItemSetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyItemSetByUserIdTask>> VerifyItemSetByUserId(
            const Request::FVerifyItemSetByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireItemSetByStampSheetTask>> AcquireItemSetByStampSheet(
            const Request::FAcquireItemSetByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireItemSetWithGradeByStampSheetTask>> AcquireItemSetWithGradeByStampSheet(
            const Request::FAcquireItemSetWithGradeByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeItemSetByStampTaskTask>> ConsumeItemSetByStampTask(
            const Request::FConsumeItemSetByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyItemSetByStampTaskTask>> VerifyItemSetByStampTask(
            const Request::FVerifyItemSetByStampTaskRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetSimpleItemsByUserIdTask>> SetSimpleItemsByUserId(
            const Request::FSetSimpleItemsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSimpleItemsByUserIdTask>> DeleteSimpleItemsByUserId(
            const Request::FDeleteSimpleItemsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifySimpleItemTask>> VerifySimpleItem(
            const Request::FVerifySimpleItemRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifySimpleItemByUserIdTask>> VerifySimpleItemByUserId(
            const Request::FVerifySimpleItemByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireSimpleItemsByStampSheetTask>> AcquireSimpleItemsByStampSheet(
            const Request::FAcquireSimpleItemsByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeSimpleItemsByStampTaskTask>> ConsumeSimpleItemsByStampTask(
            const Request::FConsumeSimpleItemsByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetSimpleItemsByStampSheetTask>> SetSimpleItemsByStampSheet(
            const Request::FSetSimpleItemsByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifySimpleItemByStampTaskTask>> VerifySimpleItemByStampTask(
            const Request::FVerifySimpleItemByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBigItemsTask>> DescribeBigItems(
            const Request::FDescribeBigItemsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBigItemsByUserIdTask>> DescribeBigItemsByUserId(
            const Request::FDescribeBigItemsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBigItemTask>> GetBigItem(
            const Request::FGetBigItemRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBigItemByUserIdTask>> GetBigItemByUserId(
            const Request::FGetBigItemByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireBigItemByUserIdTask>> AcquireBigItemByUserId(
            const Request::FAcquireBigItemByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeBigItemTask>> ConsumeBigItem(
            const Request::FConsumeBigItemRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeBigItemByUserIdTask>> ConsumeBigItemByUserId(
            const Request::FConsumeBigItemByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetBigItemByUserIdTask>> SetBigItemByUserId(
            const Request::FSetBigItemByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteBigItemByUserIdTask>> DeleteBigItemByUserId(
            const Request::FDeleteBigItemByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyBigItemTask>> VerifyBigItem(
            const Request::FVerifyBigItemRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyBigItemByUserIdTask>> VerifyBigItemByUserId(
            const Request::FVerifyBigItemByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireBigItemByStampSheetTask>> AcquireBigItemByStampSheet(
            const Request::FAcquireBigItemByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeBigItemByStampTaskTask>> ConsumeBigItemByStampTask(
            const Request::FConsumeBigItemByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetBigItemByStampSheetTask>> SetBigItemByStampSheet(
            const Request::FSetBigItemByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyBigItemByStampTaskTask>> VerifyBigItemByStampTask(
            const Request::FVerifyBigItemByStampTaskRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2InventoryWebSocketClient, ESPMode::ThreadSafe> FGs2InventoryWebSocketClientPtr;
}