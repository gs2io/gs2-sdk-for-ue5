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
#include "Model/ExperienceModelMaster.h"
#include "Model/ExperienceModel.h"
#include "Model/ThresholdMaster.h"
#include "Model/Threshold.h"
#include "Model/AcquireActionRate.h"
#include "Model/CurrentExperienceMaster.h"
#include "Model/Status.h"
#include "Model/VerifyActionResult.h"
#include "Model/ConsumeActionResult.h"
#include "Model/AcquireActionResult.h"
#include "Model/TransactionResult.h"
#include "Model/AcquireAction.h"
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

// DescribeExperienceModelMasters
#include "Request/DescribeExperienceModelMastersRequest.h"
#include "Result/DescribeExperienceModelMastersResult.h"
#include "Task/Rest/DescribeExperienceModelMastersTask.h"
#include "Task/WebSocket/DescribeExperienceModelMastersTask.h"

// CreateExperienceModelMaster
#include "Request/CreateExperienceModelMasterRequest.h"
#include "Result/CreateExperienceModelMasterResult.h"
#include "Task/Rest/CreateExperienceModelMasterTask.h"
#include "Task/WebSocket/CreateExperienceModelMasterTask.h"

// GetExperienceModelMaster
#include "Request/GetExperienceModelMasterRequest.h"
#include "Result/GetExperienceModelMasterResult.h"
#include "Task/Rest/GetExperienceModelMasterTask.h"
#include "Task/WebSocket/GetExperienceModelMasterTask.h"

// UpdateExperienceModelMaster
#include "Request/UpdateExperienceModelMasterRequest.h"
#include "Result/UpdateExperienceModelMasterResult.h"
#include "Task/Rest/UpdateExperienceModelMasterTask.h"
#include "Task/WebSocket/UpdateExperienceModelMasterTask.h"

// DeleteExperienceModelMaster
#include "Request/DeleteExperienceModelMasterRequest.h"
#include "Result/DeleteExperienceModelMasterResult.h"
#include "Task/Rest/DeleteExperienceModelMasterTask.h"
#include "Task/WebSocket/DeleteExperienceModelMasterTask.h"

// DescribeExperienceModels
#include "Request/DescribeExperienceModelsRequest.h"
#include "Result/DescribeExperienceModelsResult.h"
#include "Task/Rest/DescribeExperienceModelsTask.h"
#include "Task/WebSocket/DescribeExperienceModelsTask.h"

// GetExperienceModel
#include "Request/GetExperienceModelRequest.h"
#include "Result/GetExperienceModelResult.h"
#include "Task/Rest/GetExperienceModelTask.h"
#include "Task/WebSocket/GetExperienceModelTask.h"

// DescribeThresholdMasters
#include "Request/DescribeThresholdMastersRequest.h"
#include "Result/DescribeThresholdMastersResult.h"
#include "Task/Rest/DescribeThresholdMastersTask.h"
#include "Task/WebSocket/DescribeThresholdMastersTask.h"

// CreateThresholdMaster
#include "Request/CreateThresholdMasterRequest.h"
#include "Result/CreateThresholdMasterResult.h"
#include "Task/Rest/CreateThresholdMasterTask.h"
#include "Task/WebSocket/CreateThresholdMasterTask.h"

// GetThresholdMaster
#include "Request/GetThresholdMasterRequest.h"
#include "Result/GetThresholdMasterResult.h"
#include "Task/Rest/GetThresholdMasterTask.h"
#include "Task/WebSocket/GetThresholdMasterTask.h"

// UpdateThresholdMaster
#include "Request/UpdateThresholdMasterRequest.h"
#include "Result/UpdateThresholdMasterResult.h"
#include "Task/Rest/UpdateThresholdMasterTask.h"
#include "Task/WebSocket/UpdateThresholdMasterTask.h"

// DeleteThresholdMaster
#include "Request/DeleteThresholdMasterRequest.h"
#include "Result/DeleteThresholdMasterResult.h"
#include "Task/Rest/DeleteThresholdMasterTask.h"
#include "Task/WebSocket/DeleteThresholdMasterTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentExperienceMaster
#include "Request/GetCurrentExperienceMasterRequest.h"
#include "Result/GetCurrentExperienceMasterResult.h"
#include "Task/Rest/GetCurrentExperienceMasterTask.h"
#include "Task/WebSocket/GetCurrentExperienceMasterTask.h"

// PreUpdateCurrentExperienceMaster
#include "Request/PreUpdateCurrentExperienceMasterRequest.h"
#include "Result/PreUpdateCurrentExperienceMasterResult.h"
#include "Task/Rest/PreUpdateCurrentExperienceMasterTask.h"
#include "Task/WebSocket/PreUpdateCurrentExperienceMasterTask.h"

// UpdateCurrentExperienceMaster
#include "Request/UpdateCurrentExperienceMasterRequest.h"
#include "Result/UpdateCurrentExperienceMasterResult.h"
#include "Task/Rest/UpdateCurrentExperienceMasterTask.h"
#include "Task/WebSocket/UpdateCurrentExperienceMasterTask.h"

// UpdateCurrentExperienceMasterFromGitHub
#include "Request/UpdateCurrentExperienceMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentExperienceMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentExperienceMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentExperienceMasterFromGitHubTask.h"

// DescribeStatuses
#include "Request/DescribeStatusesRequest.h"
#include "Result/DescribeStatusesResult.h"
#include "Task/Rest/DescribeStatusesTask.h"
#include "Task/WebSocket/DescribeStatusesTask.h"

// DescribeStatusesByUserId
#include "Request/DescribeStatusesByUserIdRequest.h"
#include "Result/DescribeStatusesByUserIdResult.h"
#include "Task/Rest/DescribeStatusesByUserIdTask.h"
#include "Task/WebSocket/DescribeStatusesByUserIdTask.h"

// GetStatus
#include "Request/GetStatusRequest.h"
#include "Result/GetStatusResult.h"
#include "Task/Rest/GetStatusTask.h"
#include "Task/WebSocket/GetStatusTask.h"

// GetStatusByUserId
#include "Request/GetStatusByUserIdRequest.h"
#include "Result/GetStatusByUserIdResult.h"
#include "Task/Rest/GetStatusByUserIdTask.h"
#include "Task/WebSocket/GetStatusByUserIdTask.h"

// GetStatusWithSignature
#include "Request/GetStatusWithSignatureRequest.h"
#include "Result/GetStatusWithSignatureResult.h"
#include "Task/Rest/GetStatusWithSignatureTask.h"
#include "Task/WebSocket/GetStatusWithSignatureTask.h"

// GetStatusWithSignatureByUserId
#include "Request/GetStatusWithSignatureByUserIdRequest.h"
#include "Result/GetStatusWithSignatureByUserIdResult.h"
#include "Task/Rest/GetStatusWithSignatureByUserIdTask.h"
#include "Task/WebSocket/GetStatusWithSignatureByUserIdTask.h"

// AddExperienceByUserId
#include "Request/AddExperienceByUserIdRequest.h"
#include "Result/AddExperienceByUserIdResult.h"
#include "Task/Rest/AddExperienceByUserIdTask.h"
#include "Task/WebSocket/AddExperienceByUserIdTask.h"

// SubExperience
#include "Request/SubExperienceRequest.h"
#include "Result/SubExperienceResult.h"
#include "Task/Rest/SubExperienceTask.h"
#include "Task/WebSocket/SubExperienceTask.h"

// SubExperienceByUserId
#include "Request/SubExperienceByUserIdRequest.h"
#include "Result/SubExperienceByUserIdResult.h"
#include "Task/Rest/SubExperienceByUserIdTask.h"
#include "Task/WebSocket/SubExperienceByUserIdTask.h"

// SetExperienceByUserId
#include "Request/SetExperienceByUserIdRequest.h"
#include "Result/SetExperienceByUserIdResult.h"
#include "Task/Rest/SetExperienceByUserIdTask.h"
#include "Task/WebSocket/SetExperienceByUserIdTask.h"

// AddRankCapByUserId
#include "Request/AddRankCapByUserIdRequest.h"
#include "Result/AddRankCapByUserIdResult.h"
#include "Task/Rest/AddRankCapByUserIdTask.h"
#include "Task/WebSocket/AddRankCapByUserIdTask.h"

// SubRankCap
#include "Request/SubRankCapRequest.h"
#include "Result/SubRankCapResult.h"
#include "Task/Rest/SubRankCapTask.h"
#include "Task/WebSocket/SubRankCapTask.h"

// SubRankCapByUserId
#include "Request/SubRankCapByUserIdRequest.h"
#include "Result/SubRankCapByUserIdResult.h"
#include "Task/Rest/SubRankCapByUserIdTask.h"
#include "Task/WebSocket/SubRankCapByUserIdTask.h"

// SetRankCapByUserId
#include "Request/SetRankCapByUserIdRequest.h"
#include "Result/SetRankCapByUserIdResult.h"
#include "Task/Rest/SetRankCapByUserIdTask.h"
#include "Task/WebSocket/SetRankCapByUserIdTask.h"

// DeleteStatusByUserId
#include "Request/DeleteStatusByUserIdRequest.h"
#include "Result/DeleteStatusByUserIdResult.h"
#include "Task/Rest/DeleteStatusByUserIdTask.h"
#include "Task/WebSocket/DeleteStatusByUserIdTask.h"

// VerifyRank
#include "Request/VerifyRankRequest.h"
#include "Result/VerifyRankResult.h"
#include "Task/Rest/VerifyRankTask.h"
#include "Task/WebSocket/VerifyRankTask.h"

// VerifyRankByUserId
#include "Request/VerifyRankByUserIdRequest.h"
#include "Result/VerifyRankByUserIdResult.h"
#include "Task/Rest/VerifyRankByUserIdTask.h"
#include "Task/WebSocket/VerifyRankByUserIdTask.h"

// VerifyRankCap
#include "Request/VerifyRankCapRequest.h"
#include "Result/VerifyRankCapResult.h"
#include "Task/Rest/VerifyRankCapTask.h"
#include "Task/WebSocket/VerifyRankCapTask.h"

// VerifyRankCapByUserId
#include "Request/VerifyRankCapByUserIdRequest.h"
#include "Result/VerifyRankCapByUserIdResult.h"
#include "Task/Rest/VerifyRankCapByUserIdTask.h"
#include "Task/WebSocket/VerifyRankCapByUserIdTask.h"

// AddExperienceByStampSheet
#include "Request/AddExperienceByStampSheetRequest.h"
#include "Result/AddExperienceByStampSheetResult.h"
#include "Task/Rest/AddExperienceByStampSheetTask.h"
#include "Task/WebSocket/AddExperienceByStampSheetTask.h"

// SetExperienceByStampSheet
#include "Request/SetExperienceByStampSheetRequest.h"
#include "Result/SetExperienceByStampSheetResult.h"
#include "Task/Rest/SetExperienceByStampSheetTask.h"
#include "Task/WebSocket/SetExperienceByStampSheetTask.h"

// SubExperienceByStampTask
#include "Request/SubExperienceByStampTaskRequest.h"
#include "Result/SubExperienceByStampTaskResult.h"
#include "Task/Rest/SubExperienceByStampTaskTask.h"
#include "Task/WebSocket/SubExperienceByStampTaskTask.h"

// AddRankCapByStampSheet
#include "Request/AddRankCapByStampSheetRequest.h"
#include "Result/AddRankCapByStampSheetResult.h"
#include "Task/Rest/AddRankCapByStampSheetTask.h"
#include "Task/WebSocket/AddRankCapByStampSheetTask.h"

// SubRankCapByStampTask
#include "Request/SubRankCapByStampTaskRequest.h"
#include "Result/SubRankCapByStampTaskResult.h"
#include "Task/Rest/SubRankCapByStampTaskTask.h"
#include "Task/WebSocket/SubRankCapByStampTaskTask.h"

// SetRankCapByStampSheet
#include "Request/SetRankCapByStampSheetRequest.h"
#include "Result/SetRankCapByStampSheetResult.h"
#include "Task/Rest/SetRankCapByStampSheetTask.h"
#include "Task/WebSocket/SetRankCapByStampSheetTask.h"

// MultiplyAcquireActionsByUserId
#include "Request/MultiplyAcquireActionsByUserIdRequest.h"
#include "Result/MultiplyAcquireActionsByUserIdResult.h"
#include "Task/Rest/MultiplyAcquireActionsByUserIdTask.h"
#include "Task/WebSocket/MultiplyAcquireActionsByUserIdTask.h"

// MultiplyAcquireActionsByStampSheet
#include "Request/MultiplyAcquireActionsByStampSheetRequest.h"
#include "Result/MultiplyAcquireActionsByStampSheetResult.h"
#include "Task/Rest/MultiplyAcquireActionsByStampSheetTask.h"
#include "Task/WebSocket/MultiplyAcquireActionsByStampSheetTask.h"

// VerifyRankByStampTask
#include "Request/VerifyRankByStampTaskRequest.h"
#include "Result/VerifyRankByStampTaskResult.h"
#include "Task/Rest/VerifyRankByStampTaskTask.h"
#include "Task/WebSocket/VerifyRankByStampTaskTask.h"

// VerifyRankCapByStampTask
#include "Request/VerifyRankCapByStampTaskRequest.h"
#include "Result/VerifyRankCapByStampTaskResult.h"
#include "Task/Rest/VerifyRankCapByStampTaskTask.h"
#include "Task/WebSocket/VerifyRankCapByStampTaskTask.h"

// Client
#include "Gs2ExperienceRestClient.h"
#include "Gs2ExperienceWebSocketClient.h"