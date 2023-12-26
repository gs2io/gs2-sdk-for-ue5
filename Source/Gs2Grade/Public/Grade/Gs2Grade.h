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
#include "Model/GradeModelMaster.h"
#include "Model/GradeModel.h"
#include "Model/Status.h"
#include "Model/DefaultGradeModel.h"
#include "Model/GradeEntryModel.h"
#include "Model/AcquireActionRate.h"
#include "Model/CurrentGradeMaster.h"
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

// DescribeGradeModelMasters
#include "Request/DescribeGradeModelMastersRequest.h"
#include "Result/DescribeGradeModelMastersResult.h"
#include "Task/Rest/DescribeGradeModelMastersTask.h"
#include "Task/WebSocket/DescribeGradeModelMastersTask.h"

// CreateGradeModelMaster
#include "Request/CreateGradeModelMasterRequest.h"
#include "Result/CreateGradeModelMasterResult.h"
#include "Task/Rest/CreateGradeModelMasterTask.h"
#include "Task/WebSocket/CreateGradeModelMasterTask.h"

// GetGradeModelMaster
#include "Request/GetGradeModelMasterRequest.h"
#include "Result/GetGradeModelMasterResult.h"
#include "Task/Rest/GetGradeModelMasterTask.h"
#include "Task/WebSocket/GetGradeModelMasterTask.h"

// UpdateGradeModelMaster
#include "Request/UpdateGradeModelMasterRequest.h"
#include "Result/UpdateGradeModelMasterResult.h"
#include "Task/Rest/UpdateGradeModelMasterTask.h"
#include "Task/WebSocket/UpdateGradeModelMasterTask.h"

// DeleteGradeModelMaster
#include "Request/DeleteGradeModelMasterRequest.h"
#include "Result/DeleteGradeModelMasterResult.h"
#include "Task/Rest/DeleteGradeModelMasterTask.h"
#include "Task/WebSocket/DeleteGradeModelMasterTask.h"

// DescribeGradeModels
#include "Request/DescribeGradeModelsRequest.h"
#include "Result/DescribeGradeModelsResult.h"
#include "Task/Rest/DescribeGradeModelsTask.h"
#include "Task/WebSocket/DescribeGradeModelsTask.h"

// GetGradeModel
#include "Request/GetGradeModelRequest.h"
#include "Result/GetGradeModelResult.h"
#include "Task/Rest/GetGradeModelTask.h"
#include "Task/WebSocket/GetGradeModelTask.h"

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

// AddGradeByUserId
#include "Request/AddGradeByUserIdRequest.h"
#include "Result/AddGradeByUserIdResult.h"
#include "Task/Rest/AddGradeByUserIdTask.h"
#include "Task/WebSocket/AddGradeByUserIdTask.h"

// SubGradeByUserId
#include "Request/SubGradeByUserIdRequest.h"
#include "Result/SubGradeByUserIdResult.h"
#include "Task/Rest/SubGradeByUserIdTask.h"
#include "Task/WebSocket/SubGradeByUserIdTask.h"

// SetGradeByUserId
#include "Request/SetGradeByUserIdRequest.h"
#include "Result/SetGradeByUserIdResult.h"
#include "Task/Rest/SetGradeByUserIdTask.h"
#include "Task/WebSocket/SetGradeByUserIdTask.h"

// ApplyRankCap
#include "Request/ApplyRankCapRequest.h"
#include "Result/ApplyRankCapResult.h"
#include "Task/Rest/ApplyRankCapTask.h"
#include "Task/WebSocket/ApplyRankCapTask.h"

// ApplyRankCapByUserId
#include "Request/ApplyRankCapByUserIdRequest.h"
#include "Result/ApplyRankCapByUserIdResult.h"
#include "Task/Rest/ApplyRankCapByUserIdTask.h"
#include "Task/WebSocket/ApplyRankCapByUserIdTask.h"

// DeleteStatusByUserId
#include "Request/DeleteStatusByUserIdRequest.h"
#include "Result/DeleteStatusByUserIdResult.h"
#include "Task/Rest/DeleteStatusByUserIdTask.h"
#include "Task/WebSocket/DeleteStatusByUserIdTask.h"

// VerifyGrade
#include "Request/VerifyGradeRequest.h"
#include "Result/VerifyGradeResult.h"
#include "Task/Rest/VerifyGradeTask.h"
#include "Task/WebSocket/VerifyGradeTask.h"

// VerifyGradeByUserId
#include "Request/VerifyGradeByUserIdRequest.h"
#include "Result/VerifyGradeByUserIdResult.h"
#include "Task/Rest/VerifyGradeByUserIdTask.h"
#include "Task/WebSocket/VerifyGradeByUserIdTask.h"

// VerifyGradeUpMaterial
#include "Request/VerifyGradeUpMaterialRequest.h"
#include "Result/VerifyGradeUpMaterialResult.h"
#include "Task/Rest/VerifyGradeUpMaterialTask.h"
#include "Task/WebSocket/VerifyGradeUpMaterialTask.h"

// VerifyGradeUpMaterialByUserId
#include "Request/VerifyGradeUpMaterialByUserIdRequest.h"
#include "Result/VerifyGradeUpMaterialByUserIdResult.h"
#include "Task/Rest/VerifyGradeUpMaterialByUserIdTask.h"
#include "Task/WebSocket/VerifyGradeUpMaterialByUserIdTask.h"

// AddGradeByStampSheet
#include "Request/AddGradeByStampSheetRequest.h"
#include "Result/AddGradeByStampSheetResult.h"
#include "Task/Rest/AddGradeByStampSheetTask.h"
#include "Task/WebSocket/AddGradeByStampSheetTask.h"

// ApplyRankCapByStampSheet
#include "Request/ApplyRankCapByStampSheetRequest.h"
#include "Result/ApplyRankCapByStampSheetResult.h"
#include "Task/Rest/ApplyRankCapByStampSheetTask.h"
#include "Task/WebSocket/ApplyRankCapByStampSheetTask.h"

// SubGradeByStampTask
#include "Request/SubGradeByStampTaskRequest.h"
#include "Result/SubGradeByStampTaskResult.h"
#include "Task/Rest/SubGradeByStampTaskTask.h"
#include "Task/WebSocket/SubGradeByStampTaskTask.h"

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

// VerifyGradeByStampTask
#include "Request/VerifyGradeByStampTaskRequest.h"
#include "Result/VerifyGradeByStampTaskResult.h"
#include "Task/Rest/VerifyGradeByStampTaskTask.h"
#include "Task/WebSocket/VerifyGradeByStampTaskTask.h"

// VerifyGradeUpMaterialByStampTask
#include "Request/VerifyGradeUpMaterialByStampTaskRequest.h"
#include "Result/VerifyGradeUpMaterialByStampTaskResult.h"
#include "Task/Rest/VerifyGradeUpMaterialByStampTaskTask.h"
#include "Task/WebSocket/VerifyGradeUpMaterialByStampTaskTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentGradeMaster
#include "Request/GetCurrentGradeMasterRequest.h"
#include "Result/GetCurrentGradeMasterResult.h"
#include "Task/Rest/GetCurrentGradeMasterTask.h"
#include "Task/WebSocket/GetCurrentGradeMasterTask.h"

// UpdateCurrentGradeMaster
#include "Request/UpdateCurrentGradeMasterRequest.h"
#include "Result/UpdateCurrentGradeMasterResult.h"
#include "Task/Rest/UpdateCurrentGradeMasterTask.h"
#include "Task/WebSocket/UpdateCurrentGradeMasterTask.h"

// UpdateCurrentGradeMasterFromGitHub
#include "Request/UpdateCurrentGradeMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentGradeMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentGradeMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentGradeMasterFromGitHubTask.h"

// Client
#include "Gs2GradeRestClient.h"
#include "Gs2GradeWebSocketClient.h"