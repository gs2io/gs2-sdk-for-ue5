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
#include "Model/SimpleInventoryModelMaster.h"
#include "Model/SimpleInventoryModel.h"
#include "Model/SimpleItemModelMaster.h"
#include "Model/SimpleItemModel.h"
#include "Model/BigInventoryModelMaster.h"
#include "Model/BigInventoryModel.h"
#include "Model/BigItemModelMaster.h"
#include "Model/BigItemModel.h"
#include "Model/CurrentItemModelMaster.h"
#include "Model/Inventory.h"
#include "Model/ItemSet.h"
#include "Model/ReferenceOf.h"
#include "Model/SimpleInventory.h"
#include "Model/SimpleItem.h"
#include "Model/BigInventory.h"
#include "Model/BigItem.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/ScriptSetting.h"
#include "Model/LogSetting.h"
#include "Model/AcquireCount.h"
#include "Model/ConsumeCount.h"
#include "Model/HeldCount.h"

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

// DumpUserDataByUserId
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Result/DumpUserDataByUserIdResult.h"
#include "Task/Rest/DumpUserDataByUserIdTask.h"
#include "Task/WebSocket/DumpUserDataByUserIdTask.h"

// CheckDumpUserDataByUserId
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Result/CheckDumpUserDataByUserIdResult.h"
#include "Task/Rest/CheckDumpUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckDumpUserDataByUserIdTask.h"

// CleanUserDataByUserId
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Result/CleanUserDataByUserIdResult.h"
#include "Task/Rest/CleanUserDataByUserIdTask.h"
#include "Task/WebSocket/CleanUserDataByUserIdTask.h"

// CheckCleanUserDataByUserId
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Result/CheckCleanUserDataByUserIdResult.h"
#include "Task/Rest/CheckCleanUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckCleanUserDataByUserIdTask.h"

// PrepareImportUserDataByUserId
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Result/PrepareImportUserDataByUserIdResult.h"
#include "Task/Rest/PrepareImportUserDataByUserIdTask.h"
#include "Task/WebSocket/PrepareImportUserDataByUserIdTask.h"

// ImportUserDataByUserId
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Result/ImportUserDataByUserIdResult.h"
#include "Task/Rest/ImportUserDataByUserIdTask.h"
#include "Task/WebSocket/ImportUserDataByUserIdTask.h"

// CheckImportUserDataByUserId
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Result/CheckImportUserDataByUserIdResult.h"
#include "Task/Rest/CheckImportUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckImportUserDataByUserIdTask.h"

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

// DescribeSimpleInventoryModelMasters
#include "Request/DescribeSimpleInventoryModelMastersRequest.h"
#include "Result/DescribeSimpleInventoryModelMastersResult.h"
#include "Task/Rest/DescribeSimpleInventoryModelMastersTask.h"
#include "Task/WebSocket/DescribeSimpleInventoryModelMastersTask.h"

// CreateSimpleInventoryModelMaster
#include "Request/CreateSimpleInventoryModelMasterRequest.h"
#include "Result/CreateSimpleInventoryModelMasterResult.h"
#include "Task/Rest/CreateSimpleInventoryModelMasterTask.h"
#include "Task/WebSocket/CreateSimpleInventoryModelMasterTask.h"

// GetSimpleInventoryModelMaster
#include "Request/GetSimpleInventoryModelMasterRequest.h"
#include "Result/GetSimpleInventoryModelMasterResult.h"
#include "Task/Rest/GetSimpleInventoryModelMasterTask.h"
#include "Task/WebSocket/GetSimpleInventoryModelMasterTask.h"

// UpdateSimpleInventoryModelMaster
#include "Request/UpdateSimpleInventoryModelMasterRequest.h"
#include "Result/UpdateSimpleInventoryModelMasterResult.h"
#include "Task/Rest/UpdateSimpleInventoryModelMasterTask.h"
#include "Task/WebSocket/UpdateSimpleInventoryModelMasterTask.h"

// DeleteSimpleInventoryModelMaster
#include "Request/DeleteSimpleInventoryModelMasterRequest.h"
#include "Result/DeleteSimpleInventoryModelMasterResult.h"
#include "Task/Rest/DeleteSimpleInventoryModelMasterTask.h"
#include "Task/WebSocket/DeleteSimpleInventoryModelMasterTask.h"

// DescribeSimpleInventoryModels
#include "Request/DescribeSimpleInventoryModelsRequest.h"
#include "Result/DescribeSimpleInventoryModelsResult.h"
#include "Task/Rest/DescribeSimpleInventoryModelsTask.h"
#include "Task/WebSocket/DescribeSimpleInventoryModelsTask.h"

// GetSimpleInventoryModel
#include "Request/GetSimpleInventoryModelRequest.h"
#include "Result/GetSimpleInventoryModelResult.h"
#include "Task/Rest/GetSimpleInventoryModelTask.h"
#include "Task/WebSocket/GetSimpleInventoryModelTask.h"

// DescribeSimpleItemModelMasters
#include "Request/DescribeSimpleItemModelMastersRequest.h"
#include "Result/DescribeSimpleItemModelMastersResult.h"
#include "Task/Rest/DescribeSimpleItemModelMastersTask.h"
#include "Task/WebSocket/DescribeSimpleItemModelMastersTask.h"

// CreateSimpleItemModelMaster
#include "Request/CreateSimpleItemModelMasterRequest.h"
#include "Result/CreateSimpleItemModelMasterResult.h"
#include "Task/Rest/CreateSimpleItemModelMasterTask.h"
#include "Task/WebSocket/CreateSimpleItemModelMasterTask.h"

// GetSimpleItemModelMaster
#include "Request/GetSimpleItemModelMasterRequest.h"
#include "Result/GetSimpleItemModelMasterResult.h"
#include "Task/Rest/GetSimpleItemModelMasterTask.h"
#include "Task/WebSocket/GetSimpleItemModelMasterTask.h"

// UpdateSimpleItemModelMaster
#include "Request/UpdateSimpleItemModelMasterRequest.h"
#include "Result/UpdateSimpleItemModelMasterResult.h"
#include "Task/Rest/UpdateSimpleItemModelMasterTask.h"
#include "Task/WebSocket/UpdateSimpleItemModelMasterTask.h"

// DeleteSimpleItemModelMaster
#include "Request/DeleteSimpleItemModelMasterRequest.h"
#include "Result/DeleteSimpleItemModelMasterResult.h"
#include "Task/Rest/DeleteSimpleItemModelMasterTask.h"
#include "Task/WebSocket/DeleteSimpleItemModelMasterTask.h"

// DescribeSimpleItemModels
#include "Request/DescribeSimpleItemModelsRequest.h"
#include "Result/DescribeSimpleItemModelsResult.h"
#include "Task/Rest/DescribeSimpleItemModelsTask.h"
#include "Task/WebSocket/DescribeSimpleItemModelsTask.h"

// GetSimpleItemModel
#include "Request/GetSimpleItemModelRequest.h"
#include "Result/GetSimpleItemModelResult.h"
#include "Task/Rest/GetSimpleItemModelTask.h"
#include "Task/WebSocket/GetSimpleItemModelTask.h"

// DescribeBigInventoryModelMasters
#include "Request/DescribeBigInventoryModelMastersRequest.h"
#include "Result/DescribeBigInventoryModelMastersResult.h"
#include "Task/Rest/DescribeBigInventoryModelMastersTask.h"
#include "Task/WebSocket/DescribeBigInventoryModelMastersTask.h"

// CreateBigInventoryModelMaster
#include "Request/CreateBigInventoryModelMasterRequest.h"
#include "Result/CreateBigInventoryModelMasterResult.h"
#include "Task/Rest/CreateBigInventoryModelMasterTask.h"
#include "Task/WebSocket/CreateBigInventoryModelMasterTask.h"

// GetBigInventoryModelMaster
#include "Request/GetBigInventoryModelMasterRequest.h"
#include "Result/GetBigInventoryModelMasterResult.h"
#include "Task/Rest/GetBigInventoryModelMasterTask.h"
#include "Task/WebSocket/GetBigInventoryModelMasterTask.h"

// UpdateBigInventoryModelMaster
#include "Request/UpdateBigInventoryModelMasterRequest.h"
#include "Result/UpdateBigInventoryModelMasterResult.h"
#include "Task/Rest/UpdateBigInventoryModelMasterTask.h"
#include "Task/WebSocket/UpdateBigInventoryModelMasterTask.h"

// DeleteBigInventoryModelMaster
#include "Request/DeleteBigInventoryModelMasterRequest.h"
#include "Result/DeleteBigInventoryModelMasterResult.h"
#include "Task/Rest/DeleteBigInventoryModelMasterTask.h"
#include "Task/WebSocket/DeleteBigInventoryModelMasterTask.h"

// DescribeBigInventoryModels
#include "Request/DescribeBigInventoryModelsRequest.h"
#include "Result/DescribeBigInventoryModelsResult.h"
#include "Task/Rest/DescribeBigInventoryModelsTask.h"
#include "Task/WebSocket/DescribeBigInventoryModelsTask.h"

// GetBigInventoryModel
#include "Request/GetBigInventoryModelRequest.h"
#include "Result/GetBigInventoryModelResult.h"
#include "Task/Rest/GetBigInventoryModelTask.h"
#include "Task/WebSocket/GetBigInventoryModelTask.h"

// DescribeBigItemModelMasters
#include "Request/DescribeBigItemModelMastersRequest.h"
#include "Result/DescribeBigItemModelMastersResult.h"
#include "Task/Rest/DescribeBigItemModelMastersTask.h"
#include "Task/WebSocket/DescribeBigItemModelMastersTask.h"

// CreateBigItemModelMaster
#include "Request/CreateBigItemModelMasterRequest.h"
#include "Result/CreateBigItemModelMasterResult.h"
#include "Task/Rest/CreateBigItemModelMasterTask.h"
#include "Task/WebSocket/CreateBigItemModelMasterTask.h"

// GetBigItemModelMaster
#include "Request/GetBigItemModelMasterRequest.h"
#include "Result/GetBigItemModelMasterResult.h"
#include "Task/Rest/GetBigItemModelMasterTask.h"
#include "Task/WebSocket/GetBigItemModelMasterTask.h"

// UpdateBigItemModelMaster
#include "Request/UpdateBigItemModelMasterRequest.h"
#include "Result/UpdateBigItemModelMasterResult.h"
#include "Task/Rest/UpdateBigItemModelMasterTask.h"
#include "Task/WebSocket/UpdateBigItemModelMasterTask.h"

// DeleteBigItemModelMaster
#include "Request/DeleteBigItemModelMasterRequest.h"
#include "Result/DeleteBigItemModelMasterResult.h"
#include "Task/Rest/DeleteBigItemModelMasterTask.h"
#include "Task/WebSocket/DeleteBigItemModelMasterTask.h"

// DescribeBigItemModels
#include "Request/DescribeBigItemModelsRequest.h"
#include "Result/DescribeBigItemModelsResult.h"
#include "Task/Rest/DescribeBigItemModelsTask.h"
#include "Task/WebSocket/DescribeBigItemModelsTask.h"

// GetBigItemModel
#include "Request/GetBigItemModelRequest.h"
#include "Result/GetBigItemModelResult.h"
#include "Task/Rest/GetBigItemModelTask.h"
#include "Task/WebSocket/GetBigItemModelTask.h"

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

// PreUpdateCurrentItemModelMaster
#include "Request/PreUpdateCurrentItemModelMasterRequest.h"
#include "Result/PreUpdateCurrentItemModelMasterResult.h"
#include "Task/Rest/PreUpdateCurrentItemModelMasterTask.h"
#include "Task/WebSocket/PreUpdateCurrentItemModelMasterTask.h"

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

// VerifyInventoryCurrentMaxCapacity
#include "Request/VerifyInventoryCurrentMaxCapacityRequest.h"
#include "Result/VerifyInventoryCurrentMaxCapacityResult.h"
#include "Task/Rest/VerifyInventoryCurrentMaxCapacityTask.h"
#include "Task/WebSocket/VerifyInventoryCurrentMaxCapacityTask.h"

// VerifyInventoryCurrentMaxCapacityByUserId
#include "Request/VerifyInventoryCurrentMaxCapacityByUserIdRequest.h"
#include "Result/VerifyInventoryCurrentMaxCapacityByUserIdResult.h"
#include "Task/Rest/VerifyInventoryCurrentMaxCapacityByUserIdTask.h"
#include "Task/WebSocket/VerifyInventoryCurrentMaxCapacityByUserIdTask.h"

// VerifyInventoryCurrentMaxCapacityByStampTask
#include "Request/VerifyInventoryCurrentMaxCapacityByStampTaskRequest.h"
#include "Result/VerifyInventoryCurrentMaxCapacityByStampTaskResult.h"
#include "Task/Rest/VerifyInventoryCurrentMaxCapacityByStampTaskTask.h"
#include "Task/WebSocket/VerifyInventoryCurrentMaxCapacityByStampTaskTask.h"

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

// AcquireItemSetWithGradeByUserId
#include "Request/AcquireItemSetWithGradeByUserIdRequest.h"
#include "Result/AcquireItemSetWithGradeByUserIdResult.h"
#include "Task/Rest/AcquireItemSetWithGradeByUserIdTask.h"
#include "Task/WebSocket/AcquireItemSetWithGradeByUserIdTask.h"

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

// VerifyItemSet
#include "Request/VerifyItemSetRequest.h"
#include "Result/VerifyItemSetResult.h"
#include "Task/Rest/VerifyItemSetTask.h"
#include "Task/WebSocket/VerifyItemSetTask.h"

// VerifyItemSetByUserId
#include "Request/VerifyItemSetByUserIdRequest.h"
#include "Result/VerifyItemSetByUserIdResult.h"
#include "Task/Rest/VerifyItemSetByUserIdTask.h"
#include "Task/WebSocket/VerifyItemSetByUserIdTask.h"

// AcquireItemSetByStampSheet
#include "Request/AcquireItemSetByStampSheetRequest.h"
#include "Result/AcquireItemSetByStampSheetResult.h"
#include "Task/Rest/AcquireItemSetByStampSheetTask.h"
#include "Task/WebSocket/AcquireItemSetByStampSheetTask.h"

// AcquireItemSetWithGradeByStampSheet
#include "Request/AcquireItemSetWithGradeByStampSheetRequest.h"
#include "Result/AcquireItemSetWithGradeByStampSheetResult.h"
#include "Task/Rest/AcquireItemSetWithGradeByStampSheetTask.h"
#include "Task/WebSocket/AcquireItemSetWithGradeByStampSheetTask.h"

// ConsumeItemSetByStampTask
#include "Request/ConsumeItemSetByStampTaskRequest.h"
#include "Result/ConsumeItemSetByStampTaskResult.h"
#include "Task/Rest/ConsumeItemSetByStampTaskTask.h"
#include "Task/WebSocket/ConsumeItemSetByStampTaskTask.h"

// VerifyItemSetByStampTask
#include "Request/VerifyItemSetByStampTaskRequest.h"
#include "Result/VerifyItemSetByStampTaskResult.h"
#include "Task/Rest/VerifyItemSetByStampTaskTask.h"
#include "Task/WebSocket/VerifyItemSetByStampTaskTask.h"

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

// DescribeSimpleItems
#include "Request/DescribeSimpleItemsRequest.h"
#include "Result/DescribeSimpleItemsResult.h"
#include "Task/Rest/DescribeSimpleItemsTask.h"
#include "Task/WebSocket/DescribeSimpleItemsTask.h"

// DescribeSimpleItemsByUserId
#include "Request/DescribeSimpleItemsByUserIdRequest.h"
#include "Result/DescribeSimpleItemsByUserIdResult.h"
#include "Task/Rest/DescribeSimpleItemsByUserIdTask.h"
#include "Task/WebSocket/DescribeSimpleItemsByUserIdTask.h"

// GetSimpleItem
#include "Request/GetSimpleItemRequest.h"
#include "Result/GetSimpleItemResult.h"
#include "Task/Rest/GetSimpleItemTask.h"
#include "Task/WebSocket/GetSimpleItemTask.h"

// GetSimpleItemByUserId
#include "Request/GetSimpleItemByUserIdRequest.h"
#include "Result/GetSimpleItemByUserIdResult.h"
#include "Task/Rest/GetSimpleItemByUserIdTask.h"
#include "Task/WebSocket/GetSimpleItemByUserIdTask.h"

// GetSimpleItemWithSignature
#include "Request/GetSimpleItemWithSignatureRequest.h"
#include "Result/GetSimpleItemWithSignatureResult.h"
#include "Task/Rest/GetSimpleItemWithSignatureTask.h"
#include "Task/WebSocket/GetSimpleItemWithSignatureTask.h"

// GetSimpleItemWithSignatureByUserId
#include "Request/GetSimpleItemWithSignatureByUserIdRequest.h"
#include "Result/GetSimpleItemWithSignatureByUserIdResult.h"
#include "Task/Rest/GetSimpleItemWithSignatureByUserIdTask.h"
#include "Task/WebSocket/GetSimpleItemWithSignatureByUserIdTask.h"

// AcquireSimpleItemsByUserId
#include "Request/AcquireSimpleItemsByUserIdRequest.h"
#include "Result/AcquireSimpleItemsByUserIdResult.h"
#include "Task/Rest/AcquireSimpleItemsByUserIdTask.h"
#include "Task/WebSocket/AcquireSimpleItemsByUserIdTask.h"

// ConsumeSimpleItems
#include "Request/ConsumeSimpleItemsRequest.h"
#include "Result/ConsumeSimpleItemsResult.h"
#include "Task/Rest/ConsumeSimpleItemsTask.h"
#include "Task/WebSocket/ConsumeSimpleItemsTask.h"

// ConsumeSimpleItemsByUserId
#include "Request/ConsumeSimpleItemsByUserIdRequest.h"
#include "Result/ConsumeSimpleItemsByUserIdResult.h"
#include "Task/Rest/ConsumeSimpleItemsByUserIdTask.h"
#include "Task/WebSocket/ConsumeSimpleItemsByUserIdTask.h"

// SetSimpleItemsByUserId
#include "Request/SetSimpleItemsByUserIdRequest.h"
#include "Result/SetSimpleItemsByUserIdResult.h"
#include "Task/Rest/SetSimpleItemsByUserIdTask.h"
#include "Task/WebSocket/SetSimpleItemsByUserIdTask.h"

// DeleteSimpleItemsByUserId
#include "Request/DeleteSimpleItemsByUserIdRequest.h"
#include "Result/DeleteSimpleItemsByUserIdResult.h"
#include "Task/Rest/DeleteSimpleItemsByUserIdTask.h"
#include "Task/WebSocket/DeleteSimpleItemsByUserIdTask.h"

// VerifySimpleItem
#include "Request/VerifySimpleItemRequest.h"
#include "Result/VerifySimpleItemResult.h"
#include "Task/Rest/VerifySimpleItemTask.h"
#include "Task/WebSocket/VerifySimpleItemTask.h"

// VerifySimpleItemByUserId
#include "Request/VerifySimpleItemByUserIdRequest.h"
#include "Result/VerifySimpleItemByUserIdResult.h"
#include "Task/Rest/VerifySimpleItemByUserIdTask.h"
#include "Task/WebSocket/VerifySimpleItemByUserIdTask.h"

// AcquireSimpleItemsByStampSheet
#include "Request/AcquireSimpleItemsByStampSheetRequest.h"
#include "Result/AcquireSimpleItemsByStampSheetResult.h"
#include "Task/Rest/AcquireSimpleItemsByStampSheetTask.h"
#include "Task/WebSocket/AcquireSimpleItemsByStampSheetTask.h"

// ConsumeSimpleItemsByStampTask
#include "Request/ConsumeSimpleItemsByStampTaskRequest.h"
#include "Result/ConsumeSimpleItemsByStampTaskResult.h"
#include "Task/Rest/ConsumeSimpleItemsByStampTaskTask.h"
#include "Task/WebSocket/ConsumeSimpleItemsByStampTaskTask.h"

// SetSimpleItemsByStampSheet
#include "Request/SetSimpleItemsByStampSheetRequest.h"
#include "Result/SetSimpleItemsByStampSheetResult.h"
#include "Task/Rest/SetSimpleItemsByStampSheetTask.h"
#include "Task/WebSocket/SetSimpleItemsByStampSheetTask.h"

// VerifySimpleItemByStampTask
#include "Request/VerifySimpleItemByStampTaskRequest.h"
#include "Result/VerifySimpleItemByStampTaskResult.h"
#include "Task/Rest/VerifySimpleItemByStampTaskTask.h"
#include "Task/WebSocket/VerifySimpleItemByStampTaskTask.h"

// DescribeBigItems
#include "Request/DescribeBigItemsRequest.h"
#include "Result/DescribeBigItemsResult.h"
#include "Task/Rest/DescribeBigItemsTask.h"
#include "Task/WebSocket/DescribeBigItemsTask.h"

// DescribeBigItemsByUserId
#include "Request/DescribeBigItemsByUserIdRequest.h"
#include "Result/DescribeBigItemsByUserIdResult.h"
#include "Task/Rest/DescribeBigItemsByUserIdTask.h"
#include "Task/WebSocket/DescribeBigItemsByUserIdTask.h"

// GetBigItem
#include "Request/GetBigItemRequest.h"
#include "Result/GetBigItemResult.h"
#include "Task/Rest/GetBigItemTask.h"
#include "Task/WebSocket/GetBigItemTask.h"

// GetBigItemByUserId
#include "Request/GetBigItemByUserIdRequest.h"
#include "Result/GetBigItemByUserIdResult.h"
#include "Task/Rest/GetBigItemByUserIdTask.h"
#include "Task/WebSocket/GetBigItemByUserIdTask.h"

// AcquireBigItemByUserId
#include "Request/AcquireBigItemByUserIdRequest.h"
#include "Result/AcquireBigItemByUserIdResult.h"
#include "Task/Rest/AcquireBigItemByUserIdTask.h"
#include "Task/WebSocket/AcquireBigItemByUserIdTask.h"

// ConsumeBigItem
#include "Request/ConsumeBigItemRequest.h"
#include "Result/ConsumeBigItemResult.h"
#include "Task/Rest/ConsumeBigItemTask.h"
#include "Task/WebSocket/ConsumeBigItemTask.h"

// ConsumeBigItemByUserId
#include "Request/ConsumeBigItemByUserIdRequest.h"
#include "Result/ConsumeBigItemByUserIdResult.h"
#include "Task/Rest/ConsumeBigItemByUserIdTask.h"
#include "Task/WebSocket/ConsumeBigItemByUserIdTask.h"

// SetBigItemByUserId
#include "Request/SetBigItemByUserIdRequest.h"
#include "Result/SetBigItemByUserIdResult.h"
#include "Task/Rest/SetBigItemByUserIdTask.h"
#include "Task/WebSocket/SetBigItemByUserIdTask.h"

// DeleteBigItemByUserId
#include "Request/DeleteBigItemByUserIdRequest.h"
#include "Result/DeleteBigItemByUserIdResult.h"
#include "Task/Rest/DeleteBigItemByUserIdTask.h"
#include "Task/WebSocket/DeleteBigItemByUserIdTask.h"

// VerifyBigItem
#include "Request/VerifyBigItemRequest.h"
#include "Result/VerifyBigItemResult.h"
#include "Task/Rest/VerifyBigItemTask.h"
#include "Task/WebSocket/VerifyBigItemTask.h"

// VerifyBigItemByUserId
#include "Request/VerifyBigItemByUserIdRequest.h"
#include "Result/VerifyBigItemByUserIdResult.h"
#include "Task/Rest/VerifyBigItemByUserIdTask.h"
#include "Task/WebSocket/VerifyBigItemByUserIdTask.h"

// AcquireBigItemByStampSheet
#include "Request/AcquireBigItemByStampSheetRequest.h"
#include "Result/AcquireBigItemByStampSheetResult.h"
#include "Task/Rest/AcquireBigItemByStampSheetTask.h"
#include "Task/WebSocket/AcquireBigItemByStampSheetTask.h"

// ConsumeBigItemByStampTask
#include "Request/ConsumeBigItemByStampTaskRequest.h"
#include "Result/ConsumeBigItemByStampTaskResult.h"
#include "Task/Rest/ConsumeBigItemByStampTaskTask.h"
#include "Task/WebSocket/ConsumeBigItemByStampTaskTask.h"

// SetBigItemByStampSheet
#include "Request/SetBigItemByStampSheetRequest.h"
#include "Result/SetBigItemByStampSheetResult.h"
#include "Task/Rest/SetBigItemByStampSheetTask.h"
#include "Task/WebSocket/SetBigItemByStampSheetTask.h"

// VerifyBigItemByStampTask
#include "Request/VerifyBigItemByStampTaskRequest.h"
#include "Result/VerifyBigItemByStampTaskResult.h"
#include "Task/Rest/VerifyBigItemByStampTaskTask.h"
#include "Task/WebSocket/VerifyBigItemByStampTaskTask.h"

// Client
#include "Gs2InventoryRestClient.h"
#include "Gs2InventoryWebSocketClient.h"