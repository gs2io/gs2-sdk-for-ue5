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
#include "Model/SalesItemMaster.h"
#include "Model/SalesItemGroupMaster.h"
#include "Model/ShowcaseMaster.h"
#include "Model/CurrentShowcaseMaster.h"
#include "Model/SalesItem.h"
#include "Model/SalesItemGroup.h"
#include "Model/Showcase.h"
#include "Model/DisplayItem.h"
#include "Model/DisplayItemMaster.h"
#include "Model/RandomShowcaseMaster.h"
#include "Model/RandomShowcase.h"
#include "Model/PurchaseCount.h"
#include "Model/RandomDisplayItem.h"
#include "Model/RandomDisplayItemModel.h"
#include "Model/ConsumeAction.h"
#include "Model/AcquireAction.h"
#include "Model/Config.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/LogSetting.h"
#include "Model/TransactionSetting.h"
#include "Model/ScriptSetting.h"

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

// DescribeSalesItemMasters
#include "Request/DescribeSalesItemMastersRequest.h"
#include "Result/DescribeSalesItemMastersResult.h"
#include "Task/Rest/DescribeSalesItemMastersTask.h"
#include "Task/WebSocket/DescribeSalesItemMastersTask.h"

// CreateSalesItemMaster
#include "Request/CreateSalesItemMasterRequest.h"
#include "Result/CreateSalesItemMasterResult.h"
#include "Task/Rest/CreateSalesItemMasterTask.h"
#include "Task/WebSocket/CreateSalesItemMasterTask.h"

// GetSalesItemMaster
#include "Request/GetSalesItemMasterRequest.h"
#include "Result/GetSalesItemMasterResult.h"
#include "Task/Rest/GetSalesItemMasterTask.h"
#include "Task/WebSocket/GetSalesItemMasterTask.h"

// UpdateSalesItemMaster
#include "Request/UpdateSalesItemMasterRequest.h"
#include "Result/UpdateSalesItemMasterResult.h"
#include "Task/Rest/UpdateSalesItemMasterTask.h"
#include "Task/WebSocket/UpdateSalesItemMasterTask.h"

// DeleteSalesItemMaster
#include "Request/DeleteSalesItemMasterRequest.h"
#include "Result/DeleteSalesItemMasterResult.h"
#include "Task/Rest/DeleteSalesItemMasterTask.h"
#include "Task/WebSocket/DeleteSalesItemMasterTask.h"

// DescribeSalesItemGroupMasters
#include "Request/DescribeSalesItemGroupMastersRequest.h"
#include "Result/DescribeSalesItemGroupMastersResult.h"
#include "Task/Rest/DescribeSalesItemGroupMastersTask.h"
#include "Task/WebSocket/DescribeSalesItemGroupMastersTask.h"

// CreateSalesItemGroupMaster
#include "Request/CreateSalesItemGroupMasterRequest.h"
#include "Result/CreateSalesItemGroupMasterResult.h"
#include "Task/Rest/CreateSalesItemGroupMasterTask.h"
#include "Task/WebSocket/CreateSalesItemGroupMasterTask.h"

// GetSalesItemGroupMaster
#include "Request/GetSalesItemGroupMasterRequest.h"
#include "Result/GetSalesItemGroupMasterResult.h"
#include "Task/Rest/GetSalesItemGroupMasterTask.h"
#include "Task/WebSocket/GetSalesItemGroupMasterTask.h"

// UpdateSalesItemGroupMaster
#include "Request/UpdateSalesItemGroupMasterRequest.h"
#include "Result/UpdateSalesItemGroupMasterResult.h"
#include "Task/Rest/UpdateSalesItemGroupMasterTask.h"
#include "Task/WebSocket/UpdateSalesItemGroupMasterTask.h"

// DeleteSalesItemGroupMaster
#include "Request/DeleteSalesItemGroupMasterRequest.h"
#include "Result/DeleteSalesItemGroupMasterResult.h"
#include "Task/Rest/DeleteSalesItemGroupMasterTask.h"
#include "Task/WebSocket/DeleteSalesItemGroupMasterTask.h"

// DescribeShowcaseMasters
#include "Request/DescribeShowcaseMastersRequest.h"
#include "Result/DescribeShowcaseMastersResult.h"
#include "Task/Rest/DescribeShowcaseMastersTask.h"
#include "Task/WebSocket/DescribeShowcaseMastersTask.h"

// CreateShowcaseMaster
#include "Request/CreateShowcaseMasterRequest.h"
#include "Result/CreateShowcaseMasterResult.h"
#include "Task/Rest/CreateShowcaseMasterTask.h"
#include "Task/WebSocket/CreateShowcaseMasterTask.h"

// GetShowcaseMaster
#include "Request/GetShowcaseMasterRequest.h"
#include "Result/GetShowcaseMasterResult.h"
#include "Task/Rest/GetShowcaseMasterTask.h"
#include "Task/WebSocket/GetShowcaseMasterTask.h"

// UpdateShowcaseMaster
#include "Request/UpdateShowcaseMasterRequest.h"
#include "Result/UpdateShowcaseMasterResult.h"
#include "Task/Rest/UpdateShowcaseMasterTask.h"
#include "Task/WebSocket/UpdateShowcaseMasterTask.h"

// DeleteShowcaseMaster
#include "Request/DeleteShowcaseMasterRequest.h"
#include "Result/DeleteShowcaseMasterResult.h"
#include "Task/Rest/DeleteShowcaseMasterTask.h"
#include "Task/WebSocket/DeleteShowcaseMasterTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentShowcaseMaster
#include "Request/GetCurrentShowcaseMasterRequest.h"
#include "Result/GetCurrentShowcaseMasterResult.h"
#include "Task/Rest/GetCurrentShowcaseMasterTask.h"
#include "Task/WebSocket/GetCurrentShowcaseMasterTask.h"

// UpdateCurrentShowcaseMaster
#include "Request/UpdateCurrentShowcaseMasterRequest.h"
#include "Result/UpdateCurrentShowcaseMasterResult.h"
#include "Task/Rest/UpdateCurrentShowcaseMasterTask.h"
#include "Task/WebSocket/UpdateCurrentShowcaseMasterTask.h"

// UpdateCurrentShowcaseMasterFromGitHub
#include "Request/UpdateCurrentShowcaseMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentShowcaseMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentShowcaseMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentShowcaseMasterFromGitHubTask.h"

// DescribeShowcases
#include "Request/DescribeShowcasesRequest.h"
#include "Result/DescribeShowcasesResult.h"
#include "Task/Rest/DescribeShowcasesTask.h"
#include "Task/WebSocket/DescribeShowcasesTask.h"

// DescribeShowcasesByUserId
#include "Request/DescribeShowcasesByUserIdRequest.h"
#include "Result/DescribeShowcasesByUserIdResult.h"
#include "Task/Rest/DescribeShowcasesByUserIdTask.h"
#include "Task/WebSocket/DescribeShowcasesByUserIdTask.h"

// GetShowcase
#include "Request/GetShowcaseRequest.h"
#include "Result/GetShowcaseResult.h"
#include "Task/Rest/GetShowcaseTask.h"
#include "Task/WebSocket/GetShowcaseTask.h"

// GetShowcaseByUserId
#include "Request/GetShowcaseByUserIdRequest.h"
#include "Result/GetShowcaseByUserIdResult.h"
#include "Task/Rest/GetShowcaseByUserIdTask.h"
#include "Task/WebSocket/GetShowcaseByUserIdTask.h"

// Buy
#include "Request/BuyRequest.h"
#include "Result/BuyResult.h"
#include "Task/Rest/BuyTask.h"
#include "Task/WebSocket/BuyTask.h"

// BuyByUserId
#include "Request/BuyByUserIdRequest.h"
#include "Result/BuyByUserIdResult.h"
#include "Task/Rest/BuyByUserIdTask.h"
#include "Task/WebSocket/BuyByUserIdTask.h"

// DescribeRandomShowcaseMasters
#include "Request/DescribeRandomShowcaseMastersRequest.h"
#include "Result/DescribeRandomShowcaseMastersResult.h"
#include "Task/Rest/DescribeRandomShowcaseMastersTask.h"
#include "Task/WebSocket/DescribeRandomShowcaseMastersTask.h"

// CreateRandomShowcaseMaster
#include "Request/CreateRandomShowcaseMasterRequest.h"
#include "Result/CreateRandomShowcaseMasterResult.h"
#include "Task/Rest/CreateRandomShowcaseMasterTask.h"
#include "Task/WebSocket/CreateRandomShowcaseMasterTask.h"

// GetRandomShowcaseMaster
#include "Request/GetRandomShowcaseMasterRequest.h"
#include "Result/GetRandomShowcaseMasterResult.h"
#include "Task/Rest/GetRandomShowcaseMasterTask.h"
#include "Task/WebSocket/GetRandomShowcaseMasterTask.h"

// UpdateRandomShowcaseMaster
#include "Request/UpdateRandomShowcaseMasterRequest.h"
#include "Result/UpdateRandomShowcaseMasterResult.h"
#include "Task/Rest/UpdateRandomShowcaseMasterTask.h"
#include "Task/WebSocket/UpdateRandomShowcaseMasterTask.h"

// DeleteRandomShowcaseMaster
#include "Request/DeleteRandomShowcaseMasterRequest.h"
#include "Result/DeleteRandomShowcaseMasterResult.h"
#include "Task/Rest/DeleteRandomShowcaseMasterTask.h"
#include "Task/WebSocket/DeleteRandomShowcaseMasterTask.h"

// IncrementPurchaseCountByUserId
#include "Request/IncrementPurchaseCountByUserIdRequest.h"
#include "Result/IncrementPurchaseCountByUserIdResult.h"
#include "Task/Rest/IncrementPurchaseCountByUserIdTask.h"
#include "Task/WebSocket/IncrementPurchaseCountByUserIdTask.h"

// DecrementPurchaseCountByUserId
#include "Request/DecrementPurchaseCountByUserIdRequest.h"
#include "Result/DecrementPurchaseCountByUserIdResult.h"
#include "Task/Rest/DecrementPurchaseCountByUserIdTask.h"
#include "Task/WebSocket/DecrementPurchaseCountByUserIdTask.h"

// IncrementPurchaseCountByStampTask
#include "Request/IncrementPurchaseCountByStampTaskRequest.h"
#include "Result/IncrementPurchaseCountByStampTaskResult.h"
#include "Task/Rest/IncrementPurchaseCountByStampTaskTask.h"
#include "Task/WebSocket/IncrementPurchaseCountByStampTaskTask.h"

// DecrementPurchaseCountByStampSheet
#include "Request/DecrementPurchaseCountByStampSheetRequest.h"
#include "Result/DecrementPurchaseCountByStampSheetResult.h"
#include "Task/Rest/DecrementPurchaseCountByStampSheetTask.h"
#include "Task/WebSocket/DecrementPurchaseCountByStampSheetTask.h"

// ForceReDrawByUserId
#include "Request/ForceReDrawByUserIdRequest.h"
#include "Result/ForceReDrawByUserIdResult.h"
#include "Task/Rest/ForceReDrawByUserIdTask.h"
#include "Task/WebSocket/ForceReDrawByUserIdTask.h"

// ForceReDrawByUserIdByStampSheet
#include "Request/ForceReDrawByUserIdByStampSheetRequest.h"
#include "Result/ForceReDrawByUserIdByStampSheetResult.h"
#include "Task/Rest/ForceReDrawByUserIdByStampSheetTask.h"
#include "Task/WebSocket/ForceReDrawByUserIdByStampSheetTask.h"

// DescribeRandomDisplayItems
#include "Request/DescribeRandomDisplayItemsRequest.h"
#include "Result/DescribeRandomDisplayItemsResult.h"
#include "Task/Rest/DescribeRandomDisplayItemsTask.h"
#include "Task/WebSocket/DescribeRandomDisplayItemsTask.h"

// DescribeRandomDisplayItemsByUserId
#include "Request/DescribeRandomDisplayItemsByUserIdRequest.h"
#include "Result/DescribeRandomDisplayItemsByUserIdResult.h"
#include "Task/Rest/DescribeRandomDisplayItemsByUserIdTask.h"
#include "Task/WebSocket/DescribeRandomDisplayItemsByUserIdTask.h"

// GetRandomDisplayItem
#include "Request/GetRandomDisplayItemRequest.h"
#include "Result/GetRandomDisplayItemResult.h"
#include "Task/Rest/GetRandomDisplayItemTask.h"
#include "Task/WebSocket/GetRandomDisplayItemTask.h"

// GetRandomDisplayItemByUserId
#include "Request/GetRandomDisplayItemByUserIdRequest.h"
#include "Result/GetRandomDisplayItemByUserIdResult.h"
#include "Task/Rest/GetRandomDisplayItemByUserIdTask.h"
#include "Task/WebSocket/GetRandomDisplayItemByUserIdTask.h"

// RandomShowcaseBuy
#include "Request/RandomShowcaseBuyRequest.h"
#include "Result/RandomShowcaseBuyResult.h"
#include "Task/Rest/RandomShowcaseBuyTask.h"
#include "Task/WebSocket/RandomShowcaseBuyTask.h"

// RandomShowcaseBuyByUserId
#include "Request/RandomShowcaseBuyByUserIdRequest.h"
#include "Result/RandomShowcaseBuyByUserIdResult.h"
#include "Task/Rest/RandomShowcaseBuyByUserIdTask.h"
#include "Task/WebSocket/RandomShowcaseBuyByUserIdTask.h"

// Client
#include "Gs2ShowcaseRestClient.h"
#include "Gs2ShowcaseWebSocketClient.h"