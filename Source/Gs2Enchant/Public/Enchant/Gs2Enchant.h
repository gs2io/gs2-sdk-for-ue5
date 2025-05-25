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
#include "Model/BalanceParameterModel.h"
#include "Model/BalanceParameterModelMaster.h"
#include "Model/RarityParameterModel.h"
#include "Model/RarityParameterModelMaster.h"
#include "Model/CurrentParameterMaster.h"
#include "Model/BalanceParameterStatus.h"
#include "Model/RarityParameterStatus.h"
#include "Model/BalanceParameterValueModel.h"
#include "Model/RarityParameterCountModel.h"
#include "Model/RarityParameterValueModel.h"
#include "Model/BalanceParameterValue.h"
#include "Model/RarityParameterValue.h"
#include "Model/VerifyActionResult.h"
#include "Model/ConsumeActionResult.h"
#include "Model/AcquireActionResult.h"
#include "Model/TransactionResult.h"
#include "Model/Config.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/ScriptSetting.h"
#include "Model/LogSetting.h"
#include "Model/TransactionSetting.h"

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

// GetServiceVersion
#include "Request/GetServiceVersionRequest.h"
#include "Result/GetServiceVersionResult.h"
#include "Task/Rest/GetServiceVersionTask.h"
#include "Task/WebSocket/GetServiceVersionTask.h"

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

// DescribeBalanceParameterModels
#include "Request/DescribeBalanceParameterModelsRequest.h"
#include "Result/DescribeBalanceParameterModelsResult.h"
#include "Task/Rest/DescribeBalanceParameterModelsTask.h"
#include "Task/WebSocket/DescribeBalanceParameterModelsTask.h"

// GetBalanceParameterModel
#include "Request/GetBalanceParameterModelRequest.h"
#include "Result/GetBalanceParameterModelResult.h"
#include "Task/Rest/GetBalanceParameterModelTask.h"
#include "Task/WebSocket/GetBalanceParameterModelTask.h"

// DescribeBalanceParameterModelMasters
#include "Request/DescribeBalanceParameterModelMastersRequest.h"
#include "Result/DescribeBalanceParameterModelMastersResult.h"
#include "Task/Rest/DescribeBalanceParameterModelMastersTask.h"
#include "Task/WebSocket/DescribeBalanceParameterModelMastersTask.h"

// CreateBalanceParameterModelMaster
#include "Request/CreateBalanceParameterModelMasterRequest.h"
#include "Result/CreateBalanceParameterModelMasterResult.h"
#include "Task/Rest/CreateBalanceParameterModelMasterTask.h"
#include "Task/WebSocket/CreateBalanceParameterModelMasterTask.h"

// GetBalanceParameterModelMaster
#include "Request/GetBalanceParameterModelMasterRequest.h"
#include "Result/GetBalanceParameterModelMasterResult.h"
#include "Task/Rest/GetBalanceParameterModelMasterTask.h"
#include "Task/WebSocket/GetBalanceParameterModelMasterTask.h"

// UpdateBalanceParameterModelMaster
#include "Request/UpdateBalanceParameterModelMasterRequest.h"
#include "Result/UpdateBalanceParameterModelMasterResult.h"
#include "Task/Rest/UpdateBalanceParameterModelMasterTask.h"
#include "Task/WebSocket/UpdateBalanceParameterModelMasterTask.h"

// DeleteBalanceParameterModelMaster
#include "Request/DeleteBalanceParameterModelMasterRequest.h"
#include "Result/DeleteBalanceParameterModelMasterResult.h"
#include "Task/Rest/DeleteBalanceParameterModelMasterTask.h"
#include "Task/WebSocket/DeleteBalanceParameterModelMasterTask.h"

// DescribeRarityParameterModels
#include "Request/DescribeRarityParameterModelsRequest.h"
#include "Result/DescribeRarityParameterModelsResult.h"
#include "Task/Rest/DescribeRarityParameterModelsTask.h"
#include "Task/WebSocket/DescribeRarityParameterModelsTask.h"

// GetRarityParameterModel
#include "Request/GetRarityParameterModelRequest.h"
#include "Result/GetRarityParameterModelResult.h"
#include "Task/Rest/GetRarityParameterModelTask.h"
#include "Task/WebSocket/GetRarityParameterModelTask.h"

// DescribeRarityParameterModelMasters
#include "Request/DescribeRarityParameterModelMastersRequest.h"
#include "Result/DescribeRarityParameterModelMastersResult.h"
#include "Task/Rest/DescribeRarityParameterModelMastersTask.h"
#include "Task/WebSocket/DescribeRarityParameterModelMastersTask.h"

// CreateRarityParameterModelMaster
#include "Request/CreateRarityParameterModelMasterRequest.h"
#include "Result/CreateRarityParameterModelMasterResult.h"
#include "Task/Rest/CreateRarityParameterModelMasterTask.h"
#include "Task/WebSocket/CreateRarityParameterModelMasterTask.h"

// GetRarityParameterModelMaster
#include "Request/GetRarityParameterModelMasterRequest.h"
#include "Result/GetRarityParameterModelMasterResult.h"
#include "Task/Rest/GetRarityParameterModelMasterTask.h"
#include "Task/WebSocket/GetRarityParameterModelMasterTask.h"

// UpdateRarityParameterModelMaster
#include "Request/UpdateRarityParameterModelMasterRequest.h"
#include "Result/UpdateRarityParameterModelMasterResult.h"
#include "Task/Rest/UpdateRarityParameterModelMasterTask.h"
#include "Task/WebSocket/UpdateRarityParameterModelMasterTask.h"

// DeleteRarityParameterModelMaster
#include "Request/DeleteRarityParameterModelMasterRequest.h"
#include "Result/DeleteRarityParameterModelMasterResult.h"
#include "Task/Rest/DeleteRarityParameterModelMasterTask.h"
#include "Task/WebSocket/DeleteRarityParameterModelMasterTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentParameterMaster
#include "Request/GetCurrentParameterMasterRequest.h"
#include "Result/GetCurrentParameterMasterResult.h"
#include "Task/Rest/GetCurrentParameterMasterTask.h"
#include "Task/WebSocket/GetCurrentParameterMasterTask.h"

// PreUpdateCurrentParameterMaster
#include "Request/PreUpdateCurrentParameterMasterRequest.h"
#include "Result/PreUpdateCurrentParameterMasterResult.h"
#include "Task/Rest/PreUpdateCurrentParameterMasterTask.h"
#include "Task/WebSocket/PreUpdateCurrentParameterMasterTask.h"

// UpdateCurrentParameterMaster
#include "Request/UpdateCurrentParameterMasterRequest.h"
#include "Result/UpdateCurrentParameterMasterResult.h"
#include "Task/Rest/UpdateCurrentParameterMasterTask.h"
#include "Task/WebSocket/UpdateCurrentParameterMasterTask.h"

// UpdateCurrentParameterMasterFromGitHub
#include "Request/UpdateCurrentParameterMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentParameterMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentParameterMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentParameterMasterFromGitHubTask.h"

// DescribeBalanceParameterStatuses
#include "Request/DescribeBalanceParameterStatusesRequest.h"
#include "Result/DescribeBalanceParameterStatusesResult.h"
#include "Task/Rest/DescribeBalanceParameterStatusesTask.h"
#include "Task/WebSocket/DescribeBalanceParameterStatusesTask.h"

// DescribeBalanceParameterStatusesByUserId
#include "Request/DescribeBalanceParameterStatusesByUserIdRequest.h"
#include "Result/DescribeBalanceParameterStatusesByUserIdResult.h"
#include "Task/Rest/DescribeBalanceParameterStatusesByUserIdTask.h"
#include "Task/WebSocket/DescribeBalanceParameterStatusesByUserIdTask.h"

// GetBalanceParameterStatus
#include "Request/GetBalanceParameterStatusRequest.h"
#include "Result/GetBalanceParameterStatusResult.h"
#include "Task/Rest/GetBalanceParameterStatusTask.h"
#include "Task/WebSocket/GetBalanceParameterStatusTask.h"

// GetBalanceParameterStatusByUserId
#include "Request/GetBalanceParameterStatusByUserIdRequest.h"
#include "Result/GetBalanceParameterStatusByUserIdResult.h"
#include "Task/Rest/GetBalanceParameterStatusByUserIdTask.h"
#include "Task/WebSocket/GetBalanceParameterStatusByUserIdTask.h"

// DeleteBalanceParameterStatusByUserId
#include "Request/DeleteBalanceParameterStatusByUserIdRequest.h"
#include "Result/DeleteBalanceParameterStatusByUserIdResult.h"
#include "Task/Rest/DeleteBalanceParameterStatusByUserIdTask.h"
#include "Task/WebSocket/DeleteBalanceParameterStatusByUserIdTask.h"

// ReDrawBalanceParameterStatusByUserId
#include "Request/ReDrawBalanceParameterStatusByUserIdRequest.h"
#include "Result/ReDrawBalanceParameterStatusByUserIdResult.h"
#include "Task/Rest/ReDrawBalanceParameterStatusByUserIdTask.h"
#include "Task/WebSocket/ReDrawBalanceParameterStatusByUserIdTask.h"

// ReDrawBalanceParameterStatusByStampSheet
#include "Request/ReDrawBalanceParameterStatusByStampSheetRequest.h"
#include "Result/ReDrawBalanceParameterStatusByStampSheetResult.h"
#include "Task/Rest/ReDrawBalanceParameterStatusByStampSheetTask.h"
#include "Task/WebSocket/ReDrawBalanceParameterStatusByStampSheetTask.h"

// SetBalanceParameterStatusByUserId
#include "Request/SetBalanceParameterStatusByUserIdRequest.h"
#include "Result/SetBalanceParameterStatusByUserIdResult.h"
#include "Task/Rest/SetBalanceParameterStatusByUserIdTask.h"
#include "Task/WebSocket/SetBalanceParameterStatusByUserIdTask.h"

// SetBalanceParameterStatusByStampSheet
#include "Request/SetBalanceParameterStatusByStampSheetRequest.h"
#include "Result/SetBalanceParameterStatusByStampSheetResult.h"
#include "Task/Rest/SetBalanceParameterStatusByStampSheetTask.h"
#include "Task/WebSocket/SetBalanceParameterStatusByStampSheetTask.h"

// DescribeRarityParameterStatuses
#include "Request/DescribeRarityParameterStatusesRequest.h"
#include "Result/DescribeRarityParameterStatusesResult.h"
#include "Task/Rest/DescribeRarityParameterStatusesTask.h"
#include "Task/WebSocket/DescribeRarityParameterStatusesTask.h"

// DescribeRarityParameterStatusesByUserId
#include "Request/DescribeRarityParameterStatusesByUserIdRequest.h"
#include "Result/DescribeRarityParameterStatusesByUserIdResult.h"
#include "Task/Rest/DescribeRarityParameterStatusesByUserIdTask.h"
#include "Task/WebSocket/DescribeRarityParameterStatusesByUserIdTask.h"

// GetRarityParameterStatus
#include "Request/GetRarityParameterStatusRequest.h"
#include "Result/GetRarityParameterStatusResult.h"
#include "Task/Rest/GetRarityParameterStatusTask.h"
#include "Task/WebSocket/GetRarityParameterStatusTask.h"

// GetRarityParameterStatusByUserId
#include "Request/GetRarityParameterStatusByUserIdRequest.h"
#include "Result/GetRarityParameterStatusByUserIdResult.h"
#include "Task/Rest/GetRarityParameterStatusByUserIdTask.h"
#include "Task/WebSocket/GetRarityParameterStatusByUserIdTask.h"

// DeleteRarityParameterStatusByUserId
#include "Request/DeleteRarityParameterStatusByUserIdRequest.h"
#include "Result/DeleteRarityParameterStatusByUserIdResult.h"
#include "Task/Rest/DeleteRarityParameterStatusByUserIdTask.h"
#include "Task/WebSocket/DeleteRarityParameterStatusByUserIdTask.h"

// ReDrawRarityParameterStatusByUserId
#include "Request/ReDrawRarityParameterStatusByUserIdRequest.h"
#include "Result/ReDrawRarityParameterStatusByUserIdResult.h"
#include "Task/Rest/ReDrawRarityParameterStatusByUserIdTask.h"
#include "Task/WebSocket/ReDrawRarityParameterStatusByUserIdTask.h"

// ReDrawRarityParameterStatusByStampSheet
#include "Request/ReDrawRarityParameterStatusByStampSheetRequest.h"
#include "Result/ReDrawRarityParameterStatusByStampSheetResult.h"
#include "Task/Rest/ReDrawRarityParameterStatusByStampSheetTask.h"
#include "Task/WebSocket/ReDrawRarityParameterStatusByStampSheetTask.h"

// AddRarityParameterStatusByUserId
#include "Request/AddRarityParameterStatusByUserIdRequest.h"
#include "Result/AddRarityParameterStatusByUserIdResult.h"
#include "Task/Rest/AddRarityParameterStatusByUserIdTask.h"
#include "Task/WebSocket/AddRarityParameterStatusByUserIdTask.h"

// AddRarityParameterStatusByStampSheet
#include "Request/AddRarityParameterStatusByStampSheetRequest.h"
#include "Result/AddRarityParameterStatusByStampSheetResult.h"
#include "Task/Rest/AddRarityParameterStatusByStampSheetTask.h"
#include "Task/WebSocket/AddRarityParameterStatusByStampSheetTask.h"

// VerifyRarityParameterStatus
#include "Request/VerifyRarityParameterStatusRequest.h"
#include "Result/VerifyRarityParameterStatusResult.h"
#include "Task/Rest/VerifyRarityParameterStatusTask.h"
#include "Task/WebSocket/VerifyRarityParameterStatusTask.h"

// VerifyRarityParameterStatusByUserId
#include "Request/VerifyRarityParameterStatusByUserIdRequest.h"
#include "Result/VerifyRarityParameterStatusByUserIdResult.h"
#include "Task/Rest/VerifyRarityParameterStatusByUserIdTask.h"
#include "Task/WebSocket/VerifyRarityParameterStatusByUserIdTask.h"

// VerifyRarityParameterStatusByStampTask
#include "Request/VerifyRarityParameterStatusByStampTaskRequest.h"
#include "Result/VerifyRarityParameterStatusByStampTaskResult.h"
#include "Task/Rest/VerifyRarityParameterStatusByStampTaskTask.h"
#include "Task/WebSocket/VerifyRarityParameterStatusByStampTaskTask.h"

// SetRarityParameterStatusByUserId
#include "Request/SetRarityParameterStatusByUserIdRequest.h"
#include "Result/SetRarityParameterStatusByUserIdResult.h"
#include "Task/Rest/SetRarityParameterStatusByUserIdTask.h"
#include "Task/WebSocket/SetRarityParameterStatusByUserIdTask.h"

// SetRarityParameterStatusByStampSheet
#include "Request/SetRarityParameterStatusByStampSheetRequest.h"
#include "Result/SetRarityParameterStatusByStampSheetResult.h"
#include "Task/Rest/SetRarityParameterStatusByStampSheetTask.h"
#include "Task/WebSocket/SetRarityParameterStatusByStampSheetTask.h"

// Client
#include "Gs2EnchantRestClient.h"
#include "Gs2EnchantWebSocketClient.h"