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
#include "Model/BonusModelMaster.h"
#include "Model/CurrentBonusMaster.h"
#include "Model/BonusModel.h"
#include "Model/Reward.h"
#include "Model/ReceiveStatus.h"
#include "Model/ConsumeAction.h"
#include "Model/AcquireAction.h"
#include "Model/VerifyAction.h"
#include "Model/Config.h"
#include "Model/VerifyActionResult.h"
#include "Model/ConsumeActionResult.h"
#include "Model/AcquireActionResult.h"
#include "Model/TransactionResult.h"
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

// DescribeBonusModelMasters
#include "Request/DescribeBonusModelMastersRequest.h"
#include "Result/DescribeBonusModelMastersResult.h"
#include "Task/Rest/DescribeBonusModelMastersTask.h"
#include "Task/WebSocket/DescribeBonusModelMastersTask.h"

// CreateBonusModelMaster
#include "Request/CreateBonusModelMasterRequest.h"
#include "Result/CreateBonusModelMasterResult.h"
#include "Task/Rest/CreateBonusModelMasterTask.h"
#include "Task/WebSocket/CreateBonusModelMasterTask.h"

// GetBonusModelMaster
#include "Request/GetBonusModelMasterRequest.h"
#include "Result/GetBonusModelMasterResult.h"
#include "Task/Rest/GetBonusModelMasterTask.h"
#include "Task/WebSocket/GetBonusModelMasterTask.h"

// UpdateBonusModelMaster
#include "Request/UpdateBonusModelMasterRequest.h"
#include "Result/UpdateBonusModelMasterResult.h"
#include "Task/Rest/UpdateBonusModelMasterTask.h"
#include "Task/WebSocket/UpdateBonusModelMasterTask.h"

// DeleteBonusModelMaster
#include "Request/DeleteBonusModelMasterRequest.h"
#include "Result/DeleteBonusModelMasterResult.h"
#include "Task/Rest/DeleteBonusModelMasterTask.h"
#include "Task/WebSocket/DeleteBonusModelMasterTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentBonusMaster
#include "Request/GetCurrentBonusMasterRequest.h"
#include "Result/GetCurrentBonusMasterResult.h"
#include "Task/Rest/GetCurrentBonusMasterTask.h"
#include "Task/WebSocket/GetCurrentBonusMasterTask.h"

// UpdateCurrentBonusMaster
#include "Request/UpdateCurrentBonusMasterRequest.h"
#include "Result/UpdateCurrentBonusMasterResult.h"
#include "Task/Rest/UpdateCurrentBonusMasterTask.h"
#include "Task/WebSocket/UpdateCurrentBonusMasterTask.h"

// UpdateCurrentBonusMasterFromGitHub
#include "Request/UpdateCurrentBonusMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentBonusMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentBonusMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentBonusMasterFromGitHubTask.h"

// DescribeBonusModels
#include "Request/DescribeBonusModelsRequest.h"
#include "Result/DescribeBonusModelsResult.h"
#include "Task/Rest/DescribeBonusModelsTask.h"
#include "Task/WebSocket/DescribeBonusModelsTask.h"

// GetBonusModel
#include "Request/GetBonusModelRequest.h"
#include "Result/GetBonusModelResult.h"
#include "Task/Rest/GetBonusModelTask.h"
#include "Task/WebSocket/GetBonusModelTask.h"

// Receive
#include "Request/ReceiveRequest.h"
#include "Result/ReceiveResult.h"
#include "Task/Rest/ReceiveTask.h"
#include "Task/WebSocket/ReceiveTask.h"

// ReceiveByUserId
#include "Request/ReceiveByUserIdRequest.h"
#include "Result/ReceiveByUserIdResult.h"
#include "Task/Rest/ReceiveByUserIdTask.h"
#include "Task/WebSocket/ReceiveByUserIdTask.h"

// MissedReceive
#include "Request/MissedReceiveRequest.h"
#include "Result/MissedReceiveResult.h"
#include "Task/Rest/MissedReceiveTask.h"
#include "Task/WebSocket/MissedReceiveTask.h"

// MissedReceiveByUserId
#include "Request/MissedReceiveByUserIdRequest.h"
#include "Result/MissedReceiveByUserIdResult.h"
#include "Task/Rest/MissedReceiveByUserIdTask.h"
#include "Task/WebSocket/MissedReceiveByUserIdTask.h"

// DescribeReceiveStatuses
#include "Request/DescribeReceiveStatusesRequest.h"
#include "Result/DescribeReceiveStatusesResult.h"
#include "Task/Rest/DescribeReceiveStatusesTask.h"
#include "Task/WebSocket/DescribeReceiveStatusesTask.h"

// DescribeReceiveStatusesByUserId
#include "Request/DescribeReceiveStatusesByUserIdRequest.h"
#include "Result/DescribeReceiveStatusesByUserIdResult.h"
#include "Task/Rest/DescribeReceiveStatusesByUserIdTask.h"
#include "Task/WebSocket/DescribeReceiveStatusesByUserIdTask.h"

// GetReceiveStatus
#include "Request/GetReceiveStatusRequest.h"
#include "Result/GetReceiveStatusResult.h"
#include "Task/Rest/GetReceiveStatusTask.h"
#include "Task/WebSocket/GetReceiveStatusTask.h"

// GetReceiveStatusByUserId
#include "Request/GetReceiveStatusByUserIdRequest.h"
#include "Result/GetReceiveStatusByUserIdResult.h"
#include "Task/Rest/GetReceiveStatusByUserIdTask.h"
#include "Task/WebSocket/GetReceiveStatusByUserIdTask.h"

// DeleteReceiveStatusByUserId
#include "Request/DeleteReceiveStatusByUserIdRequest.h"
#include "Result/DeleteReceiveStatusByUserIdResult.h"
#include "Task/Rest/DeleteReceiveStatusByUserIdTask.h"
#include "Task/WebSocket/DeleteReceiveStatusByUserIdTask.h"

// DeleteReceiveStatusByStampSheet
#include "Request/DeleteReceiveStatusByStampSheetRequest.h"
#include "Result/DeleteReceiveStatusByStampSheetResult.h"
#include "Task/Rest/DeleteReceiveStatusByStampSheetTask.h"
#include "Task/WebSocket/DeleteReceiveStatusByStampSheetTask.h"

// MarkReceived
#include "Request/MarkReceivedRequest.h"
#include "Result/MarkReceivedResult.h"
#include "Task/Rest/MarkReceivedTask.h"
#include "Task/WebSocket/MarkReceivedTask.h"

// MarkReceivedByUserId
#include "Request/MarkReceivedByUserIdRequest.h"
#include "Result/MarkReceivedByUserIdResult.h"
#include "Task/Rest/MarkReceivedByUserIdTask.h"
#include "Task/WebSocket/MarkReceivedByUserIdTask.h"

// UnmarkReceivedByUserId
#include "Request/UnmarkReceivedByUserIdRequest.h"
#include "Result/UnmarkReceivedByUserIdResult.h"
#include "Task/Rest/UnmarkReceivedByUserIdTask.h"
#include "Task/WebSocket/UnmarkReceivedByUserIdTask.h"

// MarkReceivedByStampTask
#include "Request/MarkReceivedByStampTaskRequest.h"
#include "Result/MarkReceivedByStampTaskResult.h"
#include "Task/Rest/MarkReceivedByStampTaskTask.h"
#include "Task/WebSocket/MarkReceivedByStampTaskTask.h"

// UnmarkReceivedByStampSheet
#include "Request/UnmarkReceivedByStampSheetRequest.h"
#include "Result/UnmarkReceivedByStampSheetResult.h"
#include "Task/Rest/UnmarkReceivedByStampSheetTask.h"
#include "Task/WebSocket/UnmarkReceivedByStampSheetTask.h"

// Client
#include "Gs2LoginRewardRestClient.h"
#include "Gs2LoginRewardWebSocketClient.h"