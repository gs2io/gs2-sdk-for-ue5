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

// Model
#include "Model/Namespace.h"
#include "Model/InventoryModelMaster.h"
#include "Model/InventoryModel.h"
#include "Model/ItemModelMaster.h"
#include "Model/ItemModel.h"
#include "Model/CurrentItemModelMaster.h"
#include "Model/Inventory.h"
#include "Model/ItemSet.h"
#include "Model/ReferenceOf.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/ScriptSetting.h"
#include "Model/LogSetting.h"

// DescribeNamespaces
#include "Request/DescribeNamespacesRequest.h"
#include "Result/DescribeNamespacesResult.h"
#include "Task/Rest/DescribeNamespacesTask.h"
#include "Task/WebSocket/DescribeNamespacesTask.h"

// CreateNamespace
#include "Request/CreateNamespaceRequest.h"
#include "Result/CreateNamespaceResult.h"
#include "Task/Rest/CreateNamespaceTask.h"
#include "Task/WebSocket/CreateNamespaceTask.h"

// GetNamespaceStatus
#include "Request/GetNamespaceStatusRequest.h"
#include "Result/GetNamespaceStatusResult.h"
#include "Task/Rest/GetNamespaceStatusTask.h"
#include "Task/WebSocket/GetNamespaceStatusTask.h"

// GetNamespace
#include "Request/GetNamespaceRequest.h"
#include "Result/GetNamespaceResult.h"
#include "Task/Rest/GetNamespaceTask.h"
#include "Task/WebSocket/GetNamespaceTask.h"

// UpdateNamespace
#include "Request/UpdateNamespaceRequest.h"
#include "Result/UpdateNamespaceResult.h"
#include "Task/Rest/UpdateNamespaceTask.h"
#include "Task/WebSocket/UpdateNamespaceTask.h"

// DeleteNamespace
#include "Request/DeleteNamespaceRequest.h"
#include "Result/DeleteNamespaceResult.h"
#include "Task/Rest/DeleteNamespaceTask.h"
#include "Task/WebSocket/DeleteNamespaceTask.h"

// DescribeInventoryModelMasters
#include "Request/DescribeInventoryModelMastersRequest.h"
#include "Result/DescribeInventoryModelMastersResult.h"
#include "Task/Rest/DescribeInventoryModelMastersTask.h"
#include "Task/WebSocket/DescribeInventoryModelMastersTask.h"

// CreateInventoryModelMaster
#include "Request/CreateInventoryModelMasterRequest.h"
#include "Result/CreateInventoryModelMasterResult.h"
#include "Task/Rest/CreateInventoryModelMasterTask.h"
#include "Task/WebSocket/CreateInventoryModelMasterTask.h"

// GetInventoryModelMaster
#include "Request/GetInventoryModelMasterRequest.h"
#include "Result/GetInventoryModelMasterResult.h"
#include "Task/Rest/GetInventoryModelMasterTask.h"
#include "Task/WebSocket/GetInventoryModelMasterTask.h"

// UpdateInventoryModelMaster
#include "Request/UpdateInventoryModelMasterRequest.h"
#include "Result/UpdateInventoryModelMasterResult.h"
#include "Task/Rest/UpdateInventoryModelMasterTask.h"
#include "Task/WebSocket/UpdateInventoryModelMasterTask.h"

// DeleteInventoryModelMaster
#include "Request/DeleteInventoryModelMasterRequest.h"
#include "Result/DeleteInventoryModelMasterResult.h"
#include "Task/Rest/DeleteInventoryModelMasterTask.h"
#include "Task/WebSocket/DeleteInventoryModelMasterTask.h"

// DescribeInventoryModels
#include "Request/DescribeInventoryModelsRequest.h"
#include "Result/DescribeInventoryModelsResult.h"
#include "Task/Rest/DescribeInventoryModelsTask.h"
#include "Task/WebSocket/DescribeInventoryModelsTask.h"

// GetInventoryModel
#include "Request/GetInventoryModelRequest.h"
#include "Result/GetInventoryModelResult.h"
#include "Task/Rest/GetInventoryModelTask.h"
#include "Task/WebSocket/GetInventoryModelTask.h"

// DescribeItemModelMasters
#include "Request/DescribeItemModelMastersRequest.h"
#include "Result/DescribeItemModelMastersResult.h"
#include "Task/Rest/DescribeItemModelMastersTask.h"
#include "Task/WebSocket/DescribeItemModelMastersTask.h"

// CreateItemModelMaster
#include "Request/CreateItemModelMasterRequest.h"
#include "Result/CreateItemModelMasterResult.h"
#include "Task/Rest/CreateItemModelMasterTask.h"
#include "Task/WebSocket/CreateItemModelMasterTask.h"

// GetItemModelMaster
#include "Request/GetItemModelMasterRequest.h"
#include "Result/GetItemModelMasterResult.h"
#include "Task/Rest/GetItemModelMasterTask.h"
#include "Task/WebSocket/GetItemModelMasterTask.h"

// UpdateItemModelMaster
#include "Request/UpdateItemModelMasterRequest.h"
#include "Result/UpdateItemModelMasterResult.h"
#include "Task/Rest/UpdateItemModelMasterTask.h"
#include "Task/WebSocket/UpdateItemModelMasterTask.h"

// DeleteItemModelMaster
#include "Request/DeleteItemModelMasterRequest.h"
#include "Result/DeleteItemModelMasterResult.h"
#include "Task/Rest/DeleteItemModelMasterTask.h"
#include "Task/WebSocket/DeleteItemModelMasterTask.h"

// DescribeItemModels
#include "Request/DescribeItemModelsRequest.h"
#include "Result/DescribeItemModelsResult.h"
#include "Task/Rest/DescribeItemModelsTask.h"
#include "Task/WebSocket/DescribeItemModelsTask.h"

// GetItemModel
#include "Request/GetItemModelRequest.h"
#include "Result/GetItemModelResult.h"
#include "Task/Rest/GetItemModelTask.h"
#include "Task/WebSocket/GetItemModelTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentItemModelMaster
#include "Request/GetCurrentItemModelMasterRequest.h"
#include "Result/GetCurrentItemModelMasterResult.h"
#include "Task/Rest/GetCurrentItemModelMasterTask.h"
#include "Task/WebSocket/GetCurrentItemModelMasterTask.h"

// UpdateCurrentItemModelMaster
#include "Request/UpdateCurrentItemModelMasterRequest.h"
#include "Result/UpdateCurrentItemModelMasterResult.h"
#include "Task/Rest/UpdateCurrentItemModelMasterTask.h"
#include "Task/WebSocket/UpdateCurrentItemModelMasterTask.h"

// UpdateCurrentItemModelMasterFromGitHub
#include "Request/UpdateCurrentItemModelMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentItemModelMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentItemModelMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentItemModelMasterFromGitHubTask.h"

// DescribeInventories
#include "Request/DescribeInventoriesRequest.h"
#include "Result/DescribeInventoriesResult.h"
#include "Task/Rest/DescribeInventoriesTask.h"
#include "Task/WebSocket/DescribeInventoriesTask.h"

// DescribeInventoriesByUserId
#include "Request/DescribeInventoriesByUserIdRequest.h"
#include "Result/DescribeInventoriesByUserIdResult.h"
#include "Task/Rest/DescribeInventoriesByUserIdTask.h"
#include "Task/WebSocket/DescribeInventoriesByUserIdTask.h"

// GetInventory
#include "Request/GetInventoryRequest.h"
#include "Result/GetInventoryResult.h"
#include "Task/Rest/GetInventoryTask.h"
#include "Task/WebSocket/GetInventoryTask.h"

// GetInventoryByUserId
#include "Request/GetInventoryByUserIdRequest.h"
#include "Result/GetInventoryByUserIdResult.h"
#include "Task/Rest/GetInventoryByUserIdTask.h"
#include "Task/WebSocket/GetInventoryByUserIdTask.h"

// AddCapacityByUserId
#include "Request/AddCapacityByUserIdRequest.h"
#include "Result/AddCapacityByUserIdResult.h"
#include "Task/Rest/AddCapacityByUserIdTask.h"
#include "Task/WebSocket/AddCapacityByUserIdTask.h"

// SetCapacityByUserId
#include "Request/SetCapacityByUserIdRequest.h"
#include "Result/SetCapacityByUserIdResult.h"
#include "Task/Rest/SetCapacityByUserIdTask.h"
#include "Task/WebSocket/SetCapacityByUserIdTask.h"

// DeleteInventoryByUserId
#include "Request/DeleteInventoryByUserIdRequest.h"
#include "Result/DeleteInventoryByUserIdResult.h"
#include "Task/Rest/DeleteInventoryByUserIdTask.h"
#include "Task/WebSocket/DeleteInventoryByUserIdTask.h"

// AddCapacityByStampSheet
#include "Request/AddCapacityByStampSheetRequest.h"
#include "Result/AddCapacityByStampSheetResult.h"
#include "Task/Rest/AddCapacityByStampSheetTask.h"
#include "Task/WebSocket/AddCapacityByStampSheetTask.h"

// SetCapacityByStampSheet
#include "Request/SetCapacityByStampSheetRequest.h"
#include "Result/SetCapacityByStampSheetResult.h"
#include "Task/Rest/SetCapacityByStampSheetTask.h"
#include "Task/WebSocket/SetCapacityByStampSheetTask.h"

// DescribeItemSets
#include "Request/DescribeItemSetsRequest.h"
#include "Result/DescribeItemSetsResult.h"
#include "Task/Rest/DescribeItemSetsTask.h"
#include "Task/WebSocket/DescribeItemSetsTask.h"

// DescribeItemSetsByUserId
#include "Request/DescribeItemSetsByUserIdRequest.h"
#include "Result/DescribeItemSetsByUserIdResult.h"
#include "Task/Rest/DescribeItemSetsByUserIdTask.h"
#include "Task/WebSocket/DescribeItemSetsByUserIdTask.h"

// GetItemSet
#include "Request/GetItemSetRequest.h"
#include "Result/GetItemSetResult.h"
#include "Task/Rest/GetItemSetTask.h"
#include "Task/WebSocket/GetItemSetTask.h"

// GetItemSetByUserId
#include "Request/GetItemSetByUserIdRequest.h"
#include "Result/GetItemSetByUserIdResult.h"
#include "Task/Rest/GetItemSetByUserIdTask.h"
#include "Task/WebSocket/GetItemSetByUserIdTask.h"

// GetItemWithSignature
#include "Request/GetItemWithSignatureRequest.h"
#include "Result/GetItemWithSignatureResult.h"
#include "Task/Rest/GetItemWithSignatureTask.h"
#include "Task/WebSocket/GetItemWithSignatureTask.h"

// GetItemWithSignatureByUserId
#include "Request/GetItemWithSignatureByUserIdRequest.h"
#include "Result/GetItemWithSignatureByUserIdResult.h"
#include "Task/Rest/GetItemWithSignatureByUserIdTask.h"
#include "Task/WebSocket/GetItemWithSignatureByUserIdTask.h"

// AcquireItemSetByUserId
#include "Request/AcquireItemSetByUserIdRequest.h"
#include "Result/AcquireItemSetByUserIdResult.h"
#include "Task/Rest/AcquireItemSetByUserIdTask.h"
#include "Task/WebSocket/AcquireItemSetByUserIdTask.h"

// ConsumeItemSet
#include "Request/ConsumeItemSetRequest.h"
#include "Result/ConsumeItemSetResult.h"
#include "Task/Rest/ConsumeItemSetTask.h"
#include "Task/WebSocket/ConsumeItemSetTask.h"

// ConsumeItemSetByUserId
#include "Request/ConsumeItemSetByUserIdRequest.h"
#include "Result/ConsumeItemSetByUserIdResult.h"
#include "Task/Rest/ConsumeItemSetByUserIdTask.h"
#include "Task/WebSocket/ConsumeItemSetByUserIdTask.h"

// DeleteItemSetByUserId
#include "Request/DeleteItemSetByUserIdRequest.h"
#include "Result/DeleteItemSetByUserIdResult.h"
#include "Task/Rest/DeleteItemSetByUserIdTask.h"
#include "Task/WebSocket/DeleteItemSetByUserIdTask.h"

// AcquireItemSetByStampSheet
#include "Request/AcquireItemSetByStampSheetRequest.h"
#include "Result/AcquireItemSetByStampSheetResult.h"
#include "Task/Rest/AcquireItemSetByStampSheetTask.h"
#include "Task/WebSocket/AcquireItemSetByStampSheetTask.h"

// ConsumeItemSetByStampTask
#include "Request/ConsumeItemSetByStampTaskRequest.h"
#include "Result/ConsumeItemSetByStampTaskResult.h"
#include "Task/Rest/ConsumeItemSetByStampTaskTask.h"
#include "Task/WebSocket/ConsumeItemSetByStampTaskTask.h"

// DescribeReferenceOf
#include "Request/DescribeReferenceOfRequest.h"
#include "Result/DescribeReferenceOfResult.h"
#include "Task/Rest/DescribeReferenceOfTask.h"
#include "Task/WebSocket/DescribeReferenceOfTask.h"

// DescribeReferenceOfByUserId
#include "Request/DescribeReferenceOfByUserIdRequest.h"
#include "Result/DescribeReferenceOfByUserIdResult.h"
#include "Task/Rest/DescribeReferenceOfByUserIdTask.h"
#include "Task/WebSocket/DescribeReferenceOfByUserIdTask.h"

// GetReferenceOf
#include "Request/GetReferenceOfRequest.h"
#include "Result/GetReferenceOfResult.h"
#include "Task/Rest/GetReferenceOfTask.h"
#include "Task/WebSocket/GetReferenceOfTask.h"

// GetReferenceOfByUserId
#include "Request/GetReferenceOfByUserIdRequest.h"
#include "Result/GetReferenceOfByUserIdResult.h"
#include "Task/Rest/GetReferenceOfByUserIdTask.h"
#include "Task/WebSocket/GetReferenceOfByUserIdTask.h"

// VerifyReferenceOf
#include "Request/VerifyReferenceOfRequest.h"
#include "Result/VerifyReferenceOfResult.h"
#include "Task/Rest/VerifyReferenceOfTask.h"
#include "Task/WebSocket/VerifyReferenceOfTask.h"

// VerifyReferenceOfByUserId
#include "Request/VerifyReferenceOfByUserIdRequest.h"
#include "Result/VerifyReferenceOfByUserIdResult.h"
#include "Task/Rest/VerifyReferenceOfByUserIdTask.h"
#include "Task/WebSocket/VerifyReferenceOfByUserIdTask.h"

// AddReferenceOf
#include "Request/AddReferenceOfRequest.h"
#include "Result/AddReferenceOfResult.h"
#include "Task/Rest/AddReferenceOfTask.h"
#include "Task/WebSocket/AddReferenceOfTask.h"

// AddReferenceOfByUserId
#include "Request/AddReferenceOfByUserIdRequest.h"
#include "Result/AddReferenceOfByUserIdResult.h"
#include "Task/Rest/AddReferenceOfByUserIdTask.h"
#include "Task/WebSocket/AddReferenceOfByUserIdTask.h"

// DeleteReferenceOf
#include "Request/DeleteReferenceOfRequest.h"
#include "Result/DeleteReferenceOfResult.h"
#include "Task/Rest/DeleteReferenceOfTask.h"
#include "Task/WebSocket/DeleteReferenceOfTask.h"

// DeleteReferenceOfByUserId
#include "Request/DeleteReferenceOfByUserIdRequest.h"
#include "Result/DeleteReferenceOfByUserIdResult.h"
#include "Task/Rest/DeleteReferenceOfByUserIdTask.h"
#include "Task/WebSocket/DeleteReferenceOfByUserIdTask.h"

// AddReferenceOfItemSetByStampSheet
#include "Request/AddReferenceOfItemSetByStampSheetRequest.h"
#include "Result/AddReferenceOfItemSetByStampSheetResult.h"
#include "Task/Rest/AddReferenceOfItemSetByStampSheetTask.h"
#include "Task/WebSocket/AddReferenceOfItemSetByStampSheetTask.h"

// DeleteReferenceOfItemSetByStampSheet
#include "Request/DeleteReferenceOfItemSetByStampSheetRequest.h"
#include "Result/DeleteReferenceOfItemSetByStampSheetResult.h"
#include "Task/Rest/DeleteReferenceOfItemSetByStampSheetTask.h"
#include "Task/WebSocket/DeleteReferenceOfItemSetByStampSheetTask.h"

// VerifyReferenceOfByStampTask
#include "Request/VerifyReferenceOfByStampTaskRequest.h"
#include "Result/VerifyReferenceOfByStampTaskResult.h"
#include "Task/Rest/VerifyReferenceOfByStampTaskTask.h"
#include "Task/WebSocket/VerifyReferenceOfByStampTaskTask.h"

// Client
#include "Gs2InventoryRestClient.h"
#include "Gs2InventoryWebSocketClient.h"