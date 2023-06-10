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
#include "Model/CategoryModelMaster.h"
#include "Model/CategoryModel.h"
#include "Model/Status.h"
#include "Model/CurrentCategoryMaster.h"
#include "Model/Config.h"
#include "Model/AcquireAction.h"
#include "Model/AcquireActionList.h"
#include "Model/TransactionSetting.h"
#include "Model/ScriptSetting.h"
#include "Model/LogSetting.h"
#include "Model/GitHubCheckoutSetting.h"

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

// DescribeCategoryModelMasters
#include "Request/DescribeCategoryModelMastersRequest.h"
#include "Result/DescribeCategoryModelMastersResult.h"
#include "Task/Rest/DescribeCategoryModelMastersTask.h"
#include "Task/WebSocket/DescribeCategoryModelMastersTask.h"

// CreateCategoryModelMaster
#include "Request/CreateCategoryModelMasterRequest.h"
#include "Result/CreateCategoryModelMasterResult.h"
#include "Task/Rest/CreateCategoryModelMasterTask.h"
#include "Task/WebSocket/CreateCategoryModelMasterTask.h"

// GetCategoryModelMaster
#include "Request/GetCategoryModelMasterRequest.h"
#include "Result/GetCategoryModelMasterResult.h"
#include "Task/Rest/GetCategoryModelMasterTask.h"
#include "Task/WebSocket/GetCategoryModelMasterTask.h"

// UpdateCategoryModelMaster
#include "Request/UpdateCategoryModelMasterRequest.h"
#include "Result/UpdateCategoryModelMasterResult.h"
#include "Task/Rest/UpdateCategoryModelMasterTask.h"
#include "Task/WebSocket/UpdateCategoryModelMasterTask.h"

// DeleteCategoryModelMaster
#include "Request/DeleteCategoryModelMasterRequest.h"
#include "Result/DeleteCategoryModelMasterResult.h"
#include "Task/Rest/DeleteCategoryModelMasterTask.h"
#include "Task/WebSocket/DeleteCategoryModelMasterTask.h"

// DescribeCategoryModels
#include "Request/DescribeCategoryModelsRequest.h"
#include "Result/DescribeCategoryModelsResult.h"
#include "Task/Rest/DescribeCategoryModelsTask.h"
#include "Task/WebSocket/DescribeCategoryModelsTask.h"

// GetCategoryModel
#include "Request/GetCategoryModelRequest.h"
#include "Result/GetCategoryModelResult.h"
#include "Task/Rest/GetCategoryModelTask.h"
#include "Task/WebSocket/GetCategoryModelTask.h"

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

// Prediction
#include "Request/PredictionRequest.h"
#include "Result/PredictionResult.h"
#include "Task/Rest/PredictionTask.h"
#include "Task/WebSocket/PredictionTask.h"

// PredictionByUserId
#include "Request/PredictionByUserIdRequest.h"
#include "Result/PredictionByUserIdResult.h"
#include "Task/Rest/PredictionByUserIdTask.h"
#include "Task/WebSocket/PredictionByUserIdTask.h"

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

// IncreaseMaximumIdleMinutesByUserId
#include "Request/IncreaseMaximumIdleMinutesByUserIdRequest.h"
#include "Result/IncreaseMaximumIdleMinutesByUserIdResult.h"
#include "Task/Rest/IncreaseMaximumIdleMinutesByUserIdTask.h"
#include "Task/WebSocket/IncreaseMaximumIdleMinutesByUserIdTask.h"

// IncreaseMaximumIdleMinutesByStampSheet
#include "Request/IncreaseMaximumIdleMinutesByStampSheetRequest.h"
#include "Result/IncreaseMaximumIdleMinutesByStampSheetResult.h"
#include "Task/Rest/IncreaseMaximumIdleMinutesByStampSheetTask.h"
#include "Task/WebSocket/IncreaseMaximumIdleMinutesByStampSheetTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentCategoryMaster
#include "Request/GetCurrentCategoryMasterRequest.h"
#include "Result/GetCurrentCategoryMasterResult.h"
#include "Task/Rest/GetCurrentCategoryMasterTask.h"
#include "Task/WebSocket/GetCurrentCategoryMasterTask.h"

// UpdateCurrentCategoryMaster
#include "Request/UpdateCurrentCategoryMasterRequest.h"
#include "Result/UpdateCurrentCategoryMasterResult.h"
#include "Task/Rest/UpdateCurrentCategoryMasterTask.h"
#include "Task/WebSocket/UpdateCurrentCategoryMasterTask.h"

// UpdateCurrentCategoryMasterFromGitHub
#include "Request/UpdateCurrentCategoryMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentCategoryMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentCategoryMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentCategoryMasterFromGitHubTask.h"

// Client
#include "Gs2IdleRestClient.h"
#include "Gs2IdleWebSocketClient.h"