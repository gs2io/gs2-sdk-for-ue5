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
#include "Model/CurrentExperienceMaster.h"
#include "Model/Status.h"
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

// AddExperienceByStampSheet
#include "Request/AddExperienceByStampSheetRequest.h"
#include "Result/AddExperienceByStampSheetResult.h"
#include "Task/Rest/AddExperienceByStampSheetTask.h"
#include "Task/WebSocket/AddExperienceByStampSheetTask.h"

// AddRankCapByStampSheet
#include "Request/AddRankCapByStampSheetRequest.h"
#include "Result/AddRankCapByStampSheetResult.h"
#include "Task/Rest/AddRankCapByStampSheetTask.h"
#include "Task/WebSocket/AddRankCapByStampSheetTask.h"

// SetRankCapByStampSheet
#include "Request/SetRankCapByStampSheetRequest.h"
#include "Result/SetRankCapByStampSheetResult.h"
#include "Task/Rest/SetRankCapByStampSheetTask.h"
#include "Task/WebSocket/SetRankCapByStampSheetTask.h"

// Client
#include "Gs2ExperienceRestClient.h"
#include "Gs2ExperienceWebSocketClient.h"