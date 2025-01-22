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
#include "Model/RateModel.h"
#include "Model/RateModelMaster.h"
#include "Model/UnleashRateModel.h"
#include "Model/UnleashRateModelMaster.h"
#include "Model/Progress.h"
#include "Model/CurrentRateMaster.h"
#include "Model/BonusRate.h"
#include "Model/Material.h"
#include "Model/UnleashRateEntryModel.h"
#include "Model/Config.h"
#include "Model/VerifyActionResult.h"
#include "Model/ConsumeActionResult.h"
#include "Model/AcquireActionResult.h"
#include "Model/TransactionResult.h"
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

// DescribeRateModels
#include "Request/DescribeRateModelsRequest.h"
#include "Result/DescribeRateModelsResult.h"
#include "Task/Rest/DescribeRateModelsTask.h"
#include "Task/WebSocket/DescribeRateModelsTask.h"

// GetRateModel
#include "Request/GetRateModelRequest.h"
#include "Result/GetRateModelResult.h"
#include "Task/Rest/GetRateModelTask.h"
#include "Task/WebSocket/GetRateModelTask.h"

// DescribeRateModelMasters
#include "Request/DescribeRateModelMastersRequest.h"
#include "Result/DescribeRateModelMastersResult.h"
#include "Task/Rest/DescribeRateModelMastersTask.h"
#include "Task/WebSocket/DescribeRateModelMastersTask.h"

// CreateRateModelMaster
#include "Request/CreateRateModelMasterRequest.h"
#include "Result/CreateRateModelMasterResult.h"
#include "Task/Rest/CreateRateModelMasterTask.h"
#include "Task/WebSocket/CreateRateModelMasterTask.h"

// GetRateModelMaster
#include "Request/GetRateModelMasterRequest.h"
#include "Result/GetRateModelMasterResult.h"
#include "Task/Rest/GetRateModelMasterTask.h"
#include "Task/WebSocket/GetRateModelMasterTask.h"

// UpdateRateModelMaster
#include "Request/UpdateRateModelMasterRequest.h"
#include "Result/UpdateRateModelMasterResult.h"
#include "Task/Rest/UpdateRateModelMasterTask.h"
#include "Task/WebSocket/UpdateRateModelMasterTask.h"

// DeleteRateModelMaster
#include "Request/DeleteRateModelMasterRequest.h"
#include "Result/DeleteRateModelMasterResult.h"
#include "Task/Rest/DeleteRateModelMasterTask.h"
#include "Task/WebSocket/DeleteRateModelMasterTask.h"

// DescribeUnleashRateModels
#include "Request/DescribeUnleashRateModelsRequest.h"
#include "Result/DescribeUnleashRateModelsResult.h"
#include "Task/Rest/DescribeUnleashRateModelsTask.h"
#include "Task/WebSocket/DescribeUnleashRateModelsTask.h"

// GetUnleashRateModel
#include "Request/GetUnleashRateModelRequest.h"
#include "Result/GetUnleashRateModelResult.h"
#include "Task/Rest/GetUnleashRateModelTask.h"
#include "Task/WebSocket/GetUnleashRateModelTask.h"

// DescribeUnleashRateModelMasters
#include "Request/DescribeUnleashRateModelMastersRequest.h"
#include "Result/DescribeUnleashRateModelMastersResult.h"
#include "Task/Rest/DescribeUnleashRateModelMastersTask.h"
#include "Task/WebSocket/DescribeUnleashRateModelMastersTask.h"

// CreateUnleashRateModelMaster
#include "Request/CreateUnleashRateModelMasterRequest.h"
#include "Result/CreateUnleashRateModelMasterResult.h"
#include "Task/Rest/CreateUnleashRateModelMasterTask.h"
#include "Task/WebSocket/CreateUnleashRateModelMasterTask.h"

// GetUnleashRateModelMaster
#include "Request/GetUnleashRateModelMasterRequest.h"
#include "Result/GetUnleashRateModelMasterResult.h"
#include "Task/Rest/GetUnleashRateModelMasterTask.h"
#include "Task/WebSocket/GetUnleashRateModelMasterTask.h"

// UpdateUnleashRateModelMaster
#include "Request/UpdateUnleashRateModelMasterRequest.h"
#include "Result/UpdateUnleashRateModelMasterResult.h"
#include "Task/Rest/UpdateUnleashRateModelMasterTask.h"
#include "Task/WebSocket/UpdateUnleashRateModelMasterTask.h"

// DeleteUnleashRateModelMaster
#include "Request/DeleteUnleashRateModelMasterRequest.h"
#include "Result/DeleteUnleashRateModelMasterResult.h"
#include "Task/Rest/DeleteUnleashRateModelMasterTask.h"
#include "Task/WebSocket/DeleteUnleashRateModelMasterTask.h"

// DirectEnhance
#include "Request/DirectEnhanceRequest.h"
#include "Result/DirectEnhanceResult.h"
#include "Task/Rest/DirectEnhanceTask.h"
#include "Task/WebSocket/DirectEnhanceTask.h"

// DirectEnhanceByUserId
#include "Request/DirectEnhanceByUserIdRequest.h"
#include "Result/DirectEnhanceByUserIdResult.h"
#include "Task/Rest/DirectEnhanceByUserIdTask.h"
#include "Task/WebSocket/DirectEnhanceByUserIdTask.h"

// DirectEnhanceByStampSheet
#include "Request/DirectEnhanceByStampSheetRequest.h"
#include "Result/DirectEnhanceByStampSheetResult.h"
#include "Task/Rest/DirectEnhanceByStampSheetTask.h"
#include "Task/WebSocket/DirectEnhanceByStampSheetTask.h"

// Unleash
#include "Request/UnleashRequest.h"
#include "Result/UnleashResult.h"
#include "Task/Rest/UnleashTask.h"
#include "Task/WebSocket/UnleashTask.h"

// UnleashByUserId
#include "Request/UnleashByUserIdRequest.h"
#include "Result/UnleashByUserIdResult.h"
#include "Task/Rest/UnleashByUserIdTask.h"
#include "Task/WebSocket/UnleashByUserIdTask.h"

// UnleashByStampSheet
#include "Request/UnleashByStampSheetRequest.h"
#include "Result/UnleashByStampSheetResult.h"
#include "Task/Rest/UnleashByStampSheetTask.h"
#include "Task/WebSocket/UnleashByStampSheetTask.h"

// CreateProgressByUserId
#include "Request/CreateProgressByUserIdRequest.h"
#include "Result/CreateProgressByUserIdResult.h"
#include "Task/Rest/CreateProgressByUserIdTask.h"
#include "Task/WebSocket/CreateProgressByUserIdTask.h"

// GetProgress
#include "Request/GetProgressRequest.h"
#include "Result/GetProgressResult.h"
#include "Task/Rest/GetProgressTask.h"
#include "Task/WebSocket/GetProgressTask.h"

// GetProgressByUserId
#include "Request/GetProgressByUserIdRequest.h"
#include "Result/GetProgressByUserIdResult.h"
#include "Task/Rest/GetProgressByUserIdTask.h"
#include "Task/WebSocket/GetProgressByUserIdTask.h"

// Start
#include "Request/StartRequest.h"
#include "Result/StartResult.h"
#include "Task/Rest/StartTask.h"
#include "Task/WebSocket/StartTask.h"

// StartByUserId
#include "Request/StartByUserIdRequest.h"
#include "Result/StartByUserIdResult.h"
#include "Task/Rest/StartByUserIdTask.h"
#include "Task/WebSocket/StartByUserIdTask.h"

// End
#include "Request/EndRequest.h"
#include "Result/EndResult.h"
#include "Task/Rest/EndTask.h"
#include "Task/WebSocket/EndTask.h"

// EndByUserId
#include "Request/EndByUserIdRequest.h"
#include "Result/EndByUserIdResult.h"
#include "Task/Rest/EndByUserIdTask.h"
#include "Task/WebSocket/EndByUserIdTask.h"

// DeleteProgress
#include "Request/DeleteProgressRequest.h"
#include "Result/DeleteProgressResult.h"
#include "Task/Rest/DeleteProgressTask.h"
#include "Task/WebSocket/DeleteProgressTask.h"

// DeleteProgressByUserId
#include "Request/DeleteProgressByUserIdRequest.h"
#include "Result/DeleteProgressByUserIdResult.h"
#include "Task/Rest/DeleteProgressByUserIdTask.h"
#include "Task/WebSocket/DeleteProgressByUserIdTask.h"

// CreateProgressByStampSheet
#include "Request/CreateProgressByStampSheetRequest.h"
#include "Result/CreateProgressByStampSheetResult.h"
#include "Task/Rest/CreateProgressByStampSheetTask.h"
#include "Task/WebSocket/CreateProgressByStampSheetTask.h"

// DeleteProgressByStampTask
#include "Request/DeleteProgressByStampTaskRequest.h"
#include "Result/DeleteProgressByStampTaskResult.h"
#include "Task/Rest/DeleteProgressByStampTaskTask.h"
#include "Task/WebSocket/DeleteProgressByStampTaskTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentRateMaster
#include "Request/GetCurrentRateMasterRequest.h"
#include "Result/GetCurrentRateMasterResult.h"
#include "Task/Rest/GetCurrentRateMasterTask.h"
#include "Task/WebSocket/GetCurrentRateMasterTask.h"

// UpdateCurrentRateMaster
#include "Request/UpdateCurrentRateMasterRequest.h"
#include "Result/UpdateCurrentRateMasterResult.h"
#include "Task/Rest/UpdateCurrentRateMasterTask.h"
#include "Task/WebSocket/UpdateCurrentRateMasterTask.h"

// UpdateCurrentRateMasterFromGitHub
#include "Request/UpdateCurrentRateMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentRateMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentRateMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentRateMasterFromGitHubTask.h"

// Client
#include "Gs2EnhanceRestClient.h"
#include "Gs2EnhanceWebSocketClient.h"