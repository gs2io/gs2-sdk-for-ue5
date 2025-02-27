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
#include "Model/DistributorModelMaster.h"
#include "Model/DistributorModel.h"
#include "Model/CurrentDistributorMaster.h"
#include "Model/StampSheetResult.h"
#include "Model/BatchRequestPayload.h"
#include "Model/BatchResultPayload.h"
#include "Model/AcquireAction.h"
#include "Model/ConsumeAction.h"
#include "Model/VerifyAction.h"
#include "Model/TransactionResult.h"
#include "Model/AcquireActionResult.h"
#include "Model/ConsumeActionResult.h"
#include "Model/VerifyActionResult.h"
#include "Model/Config.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/DistributeResource.h"
#include "Model/LogSetting.h"
#include "Model/NotificationSetting.h"

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

// DescribeDistributorModelMasters
#include "Request/DescribeDistributorModelMastersRequest.h"
#include "Result/DescribeDistributorModelMastersResult.h"
#include "Task/Rest/DescribeDistributorModelMastersTask.h"
#include "Task/WebSocket/DescribeDistributorModelMastersTask.h"

// CreateDistributorModelMaster
#include "Request/CreateDistributorModelMasterRequest.h"
#include "Result/CreateDistributorModelMasterResult.h"
#include "Task/Rest/CreateDistributorModelMasterTask.h"
#include "Task/WebSocket/CreateDistributorModelMasterTask.h"

// GetDistributorModelMaster
#include "Request/GetDistributorModelMasterRequest.h"
#include "Result/GetDistributorModelMasterResult.h"
#include "Task/Rest/GetDistributorModelMasterTask.h"
#include "Task/WebSocket/GetDistributorModelMasterTask.h"

// UpdateDistributorModelMaster
#include "Request/UpdateDistributorModelMasterRequest.h"
#include "Result/UpdateDistributorModelMasterResult.h"
#include "Task/Rest/UpdateDistributorModelMasterTask.h"
#include "Task/WebSocket/UpdateDistributorModelMasterTask.h"

// DeleteDistributorModelMaster
#include "Request/DeleteDistributorModelMasterRequest.h"
#include "Result/DeleteDistributorModelMasterResult.h"
#include "Task/Rest/DeleteDistributorModelMasterTask.h"
#include "Task/WebSocket/DeleteDistributorModelMasterTask.h"

// DescribeDistributorModels
#include "Request/DescribeDistributorModelsRequest.h"
#include "Result/DescribeDistributorModelsResult.h"
#include "Task/Rest/DescribeDistributorModelsTask.h"
#include "Task/WebSocket/DescribeDistributorModelsTask.h"

// GetDistributorModel
#include "Request/GetDistributorModelRequest.h"
#include "Result/GetDistributorModelResult.h"
#include "Task/Rest/GetDistributorModelTask.h"
#include "Task/WebSocket/GetDistributorModelTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentDistributorMaster
#include "Request/GetCurrentDistributorMasterRequest.h"
#include "Result/GetCurrentDistributorMasterResult.h"
#include "Task/Rest/GetCurrentDistributorMasterTask.h"
#include "Task/WebSocket/GetCurrentDistributorMasterTask.h"

// UpdateCurrentDistributorMaster
#include "Request/UpdateCurrentDistributorMasterRequest.h"
#include "Result/UpdateCurrentDistributorMasterResult.h"
#include "Task/Rest/UpdateCurrentDistributorMasterTask.h"
#include "Task/WebSocket/UpdateCurrentDistributorMasterTask.h"

// UpdateCurrentDistributorMasterFromGitHub
#include "Request/UpdateCurrentDistributorMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentDistributorMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentDistributorMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentDistributorMasterFromGitHubTask.h"

// Distribute
#include "Request/DistributeRequest.h"
#include "Result/DistributeResult.h"
#include "Task/Rest/DistributeTask.h"
#include "Task/WebSocket/DistributeTask.h"

// DistributeWithoutOverflowProcess
#include "Request/DistributeWithoutOverflowProcessRequest.h"
#include "Result/DistributeWithoutOverflowProcessResult.h"
#include "Task/Rest/DistributeWithoutOverflowProcessTask.h"
#include "Task/WebSocket/DistributeWithoutOverflowProcessTask.h"

// RunVerifyTask
#include "Request/RunVerifyTaskRequest.h"
#include "Result/RunVerifyTaskResult.h"
#include "Task/Rest/RunVerifyTaskTask.h"
#include "Task/WebSocket/RunVerifyTaskTask.h"

// RunStampTask
#include "Request/RunStampTaskRequest.h"
#include "Result/RunStampTaskResult.h"
#include "Task/Rest/RunStampTaskTask.h"
#include "Task/WebSocket/RunStampTaskTask.h"

// RunStampSheet
#include "Request/RunStampSheetRequest.h"
#include "Result/RunStampSheetResult.h"
#include "Task/Rest/RunStampSheetTask.h"
#include "Task/WebSocket/RunStampSheetTask.h"

// RunStampSheetExpress
#include "Request/RunStampSheetExpressRequest.h"
#include "Result/RunStampSheetExpressResult.h"
#include "Task/Rest/RunStampSheetExpressTask.h"
#include "Task/WebSocket/RunStampSheetExpressTask.h"

// RunVerifyTaskWithoutNamespace
#include "Request/RunVerifyTaskWithoutNamespaceRequest.h"
#include "Result/RunVerifyTaskWithoutNamespaceResult.h"
#include "Task/Rest/RunVerifyTaskWithoutNamespaceTask.h"
#include "Task/WebSocket/RunVerifyTaskWithoutNamespaceTask.h"

// RunStampTaskWithoutNamespace
#include "Request/RunStampTaskWithoutNamespaceRequest.h"
#include "Result/RunStampTaskWithoutNamespaceResult.h"
#include "Task/Rest/RunStampTaskWithoutNamespaceTask.h"
#include "Task/WebSocket/RunStampTaskWithoutNamespaceTask.h"

// RunStampSheetWithoutNamespace
#include "Request/RunStampSheetWithoutNamespaceRequest.h"
#include "Result/RunStampSheetWithoutNamespaceResult.h"
#include "Task/Rest/RunStampSheetWithoutNamespaceTask.h"
#include "Task/WebSocket/RunStampSheetWithoutNamespaceTask.h"

// RunStampSheetExpressWithoutNamespace
#include "Request/RunStampSheetExpressWithoutNamespaceRequest.h"
#include "Result/RunStampSheetExpressWithoutNamespaceResult.h"
#include "Task/Rest/RunStampSheetExpressWithoutNamespaceTask.h"
#include "Task/WebSocket/RunStampSheetExpressWithoutNamespaceTask.h"

// SetTransactionDefaultConfig
#include "Request/SetTransactionDefaultConfigRequest.h"
#include "Result/SetTransactionDefaultConfigResult.h"
#include "Task/Rest/SetTransactionDefaultConfigTask.h"
#include "Task/WebSocket/SetTransactionDefaultConfigTask.h"

// SetTransactionDefaultConfigByUserId
#include "Request/SetTransactionDefaultConfigByUserIdRequest.h"
#include "Result/SetTransactionDefaultConfigByUserIdResult.h"
#include "Task/Rest/SetTransactionDefaultConfigByUserIdTask.h"
#include "Task/WebSocket/SetTransactionDefaultConfigByUserIdTask.h"

// FreezeMasterData
#include "Request/FreezeMasterDataRequest.h"
#include "Result/FreezeMasterDataResult.h"
#include "Task/Rest/FreezeMasterDataTask.h"
#include "Task/WebSocket/FreezeMasterDataTask.h"

// FreezeMasterDataByUserId
#include "Request/FreezeMasterDataByUserIdRequest.h"
#include "Result/FreezeMasterDataByUserIdResult.h"
#include "Task/Rest/FreezeMasterDataByUserIdTask.h"
#include "Task/WebSocket/FreezeMasterDataByUserIdTask.h"

// SignFreezeMasterDataTimestamp
#include "Request/SignFreezeMasterDataTimestampRequest.h"
#include "Result/SignFreezeMasterDataTimestampResult.h"
#include "Task/Rest/SignFreezeMasterDataTimestampTask.h"
#include "Task/WebSocket/SignFreezeMasterDataTimestampTask.h"

// FreezeMasterDataBySignedTimestamp
#include "Request/FreezeMasterDataBySignedTimestampRequest.h"
#include "Result/FreezeMasterDataBySignedTimestampResult.h"
#include "Task/Rest/FreezeMasterDataBySignedTimestampTask.h"
#include "Task/WebSocket/FreezeMasterDataBySignedTimestampTask.h"

// FreezeMasterDataByTimestamp
#include "Request/FreezeMasterDataByTimestampRequest.h"
#include "Result/FreezeMasterDataByTimestampResult.h"
#include "Task/Rest/FreezeMasterDataByTimestampTask.h"
#include "Task/WebSocket/FreezeMasterDataByTimestampTask.h"

// BatchExecuteApi
#include "Request/BatchExecuteApiRequest.h"
#include "Result/BatchExecuteApiResult.h"
#include "Task/Rest/BatchExecuteApiTask.h"
#include "Task/WebSocket/BatchExecuteApiTask.h"

// IfExpressionByUserId
#include "Request/IfExpressionByUserIdRequest.h"
#include "Result/IfExpressionByUserIdResult.h"
#include "Task/Rest/IfExpressionByUserIdTask.h"
#include "Task/WebSocket/IfExpressionByUserIdTask.h"

// AndExpressionByUserId
#include "Request/AndExpressionByUserIdRequest.h"
#include "Result/AndExpressionByUserIdResult.h"
#include "Task/Rest/AndExpressionByUserIdTask.h"
#include "Task/WebSocket/AndExpressionByUserIdTask.h"

// OrExpressionByUserId
#include "Request/OrExpressionByUserIdRequest.h"
#include "Result/OrExpressionByUserIdResult.h"
#include "Task/Rest/OrExpressionByUserIdTask.h"
#include "Task/WebSocket/OrExpressionByUserIdTask.h"

// IfExpressionByStampTask
#include "Request/IfExpressionByStampTaskRequest.h"
#include "Result/IfExpressionByStampTaskResult.h"
#include "Task/Rest/IfExpressionByStampTaskTask.h"
#include "Task/WebSocket/IfExpressionByStampTaskTask.h"

// AndExpressionByStampTask
#include "Request/AndExpressionByStampTaskRequest.h"
#include "Result/AndExpressionByStampTaskResult.h"
#include "Task/Rest/AndExpressionByStampTaskTask.h"
#include "Task/WebSocket/AndExpressionByStampTaskTask.h"

// OrExpressionByStampTask
#include "Request/OrExpressionByStampTaskRequest.h"
#include "Result/OrExpressionByStampTaskResult.h"
#include "Task/Rest/OrExpressionByStampTaskTask.h"
#include "Task/WebSocket/OrExpressionByStampTaskTask.h"

// GetStampSheetResult
#include "Request/GetStampSheetResultRequest.h"
#include "Result/GetStampSheetResultResult.h"
#include "Task/Rest/GetStampSheetResultTask.h"
#include "Task/WebSocket/GetStampSheetResultTask.h"

// GetStampSheetResultByUserId
#include "Request/GetStampSheetResultByUserIdRequest.h"
#include "Result/GetStampSheetResultByUserIdResult.h"
#include "Task/Rest/GetStampSheetResultByUserIdTask.h"
#include "Task/WebSocket/GetStampSheetResultByUserIdTask.h"

// RunTransaction
#include "Request/RunTransactionRequest.h"
#include "Result/RunTransactionResult.h"
#include "Task/Rest/RunTransactionTask.h"
#include "Task/WebSocket/RunTransactionTask.h"

// GetTransactionResult
#include "Request/GetTransactionResultRequest.h"
#include "Result/GetTransactionResultResult.h"
#include "Task/Rest/GetTransactionResultTask.h"
#include "Task/WebSocket/GetTransactionResultTask.h"

// GetTransactionResultByUserId
#include "Request/GetTransactionResultByUserIdRequest.h"
#include "Result/GetTransactionResultByUserIdResult.h"
#include "Task/Rest/GetTransactionResultByUserIdTask.h"
#include "Task/WebSocket/GetTransactionResultByUserIdTask.h"

// Client
#include "Gs2DistributorRestClient.h"
#include "Gs2DistributorWebSocketClient.h"