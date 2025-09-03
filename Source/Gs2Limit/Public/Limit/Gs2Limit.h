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
#include "Model/Counter.h"
#include "Model/LimitModelMaster.h"
#include "Model/CurrentLimitMaster.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/LogSetting.h"
#include "Model/TransactionSetting.h"
#include "Model/LimitModel.h"

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

// DescribeCounters
#include "Request/DescribeCountersRequest.h"
#include "Result/DescribeCountersResult.h"
#include "Task/Rest/DescribeCountersTask.h"
#include "Task/WebSocket/DescribeCountersTask.h"

// DescribeCountersByUserId
#include "Request/DescribeCountersByUserIdRequest.h"
#include "Result/DescribeCountersByUserIdResult.h"
#include "Task/Rest/DescribeCountersByUserIdTask.h"
#include "Task/WebSocket/DescribeCountersByUserIdTask.h"

// GetCounter
#include "Request/GetCounterRequest.h"
#include "Result/GetCounterResult.h"
#include "Task/Rest/GetCounterTask.h"
#include "Task/WebSocket/GetCounterTask.h"

// GetCounterByUserId
#include "Request/GetCounterByUserIdRequest.h"
#include "Result/GetCounterByUserIdResult.h"
#include "Task/Rest/GetCounterByUserIdTask.h"
#include "Task/WebSocket/GetCounterByUserIdTask.h"

// CountUp
#include "Request/CountUpRequest.h"
#include "Result/CountUpResult.h"
#include "Task/Rest/CountUpTask.h"
#include "Task/WebSocket/CountUpTask.h"

// CountUpByUserId
#include "Request/CountUpByUserIdRequest.h"
#include "Result/CountUpByUserIdResult.h"
#include "Task/Rest/CountUpByUserIdTask.h"
#include "Task/WebSocket/CountUpByUserIdTask.h"

// CountDownByUserId
#include "Request/CountDownByUserIdRequest.h"
#include "Result/CountDownByUserIdResult.h"
#include "Task/Rest/CountDownByUserIdTask.h"
#include "Task/WebSocket/CountDownByUserIdTask.h"

// DeleteCounterByUserId
#include "Request/DeleteCounterByUserIdRequest.h"
#include "Result/DeleteCounterByUserIdResult.h"
#include "Task/Rest/DeleteCounterByUserIdTask.h"
#include "Task/WebSocket/DeleteCounterByUserIdTask.h"

// VerifyCounter
#include "Request/VerifyCounterRequest.h"
#include "Result/VerifyCounterResult.h"
#include "Task/Rest/VerifyCounterTask.h"
#include "Task/WebSocket/VerifyCounterTask.h"

// VerifyCounterByUserId
#include "Request/VerifyCounterByUserIdRequest.h"
#include "Result/VerifyCounterByUserIdResult.h"
#include "Task/Rest/VerifyCounterByUserIdTask.h"
#include "Task/WebSocket/VerifyCounterByUserIdTask.h"

// CountUpByStampTask
#include "Request/CountUpByStampTaskRequest.h"
#include "Result/CountUpByStampTaskResult.h"
#include "Task/Rest/CountUpByStampTaskTask.h"
#include "Task/WebSocket/CountUpByStampTaskTask.h"

// CountDownByStampSheet
#include "Request/CountDownByStampSheetRequest.h"
#include "Result/CountDownByStampSheetResult.h"
#include "Task/Rest/CountDownByStampSheetTask.h"
#include "Task/WebSocket/CountDownByStampSheetTask.h"

// DeleteByStampSheet
#include "Request/DeleteByStampSheetRequest.h"
#include "Result/DeleteByStampSheetResult.h"
#include "Task/Rest/DeleteByStampSheetTask.h"
#include "Task/WebSocket/DeleteByStampSheetTask.h"

// VerifyCounterByStampTask
#include "Request/VerifyCounterByStampTaskRequest.h"
#include "Result/VerifyCounterByStampTaskResult.h"
#include "Task/Rest/VerifyCounterByStampTaskTask.h"
#include "Task/WebSocket/VerifyCounterByStampTaskTask.h"

// DescribeLimitModelMasters
#include "Request/DescribeLimitModelMastersRequest.h"
#include "Result/DescribeLimitModelMastersResult.h"
#include "Task/Rest/DescribeLimitModelMastersTask.h"
#include "Task/WebSocket/DescribeLimitModelMastersTask.h"

// CreateLimitModelMaster
#include "Request/CreateLimitModelMasterRequest.h"
#include "Result/CreateLimitModelMasterResult.h"
#include "Task/Rest/CreateLimitModelMasterTask.h"
#include "Task/WebSocket/CreateLimitModelMasterTask.h"

// GetLimitModelMaster
#include "Request/GetLimitModelMasterRequest.h"
#include "Result/GetLimitModelMasterResult.h"
#include "Task/Rest/GetLimitModelMasterTask.h"
#include "Task/WebSocket/GetLimitModelMasterTask.h"

// UpdateLimitModelMaster
#include "Request/UpdateLimitModelMasterRequest.h"
#include "Result/UpdateLimitModelMasterResult.h"
#include "Task/Rest/UpdateLimitModelMasterTask.h"
#include "Task/WebSocket/UpdateLimitModelMasterTask.h"

// DeleteLimitModelMaster
#include "Request/DeleteLimitModelMasterRequest.h"
#include "Result/DeleteLimitModelMasterResult.h"
#include "Task/Rest/DeleteLimitModelMasterTask.h"
#include "Task/WebSocket/DeleteLimitModelMasterTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentLimitMaster
#include "Request/GetCurrentLimitMasterRequest.h"
#include "Result/GetCurrentLimitMasterResult.h"
#include "Task/Rest/GetCurrentLimitMasterTask.h"
#include "Task/WebSocket/GetCurrentLimitMasterTask.h"

// PreUpdateCurrentLimitMaster
#include "Request/PreUpdateCurrentLimitMasterRequest.h"
#include "Result/PreUpdateCurrentLimitMasterResult.h"
#include "Task/Rest/PreUpdateCurrentLimitMasterTask.h"
#include "Task/WebSocket/PreUpdateCurrentLimitMasterTask.h"

// UpdateCurrentLimitMaster
#include "Request/UpdateCurrentLimitMasterRequest.h"
#include "Result/UpdateCurrentLimitMasterResult.h"
#include "Task/Rest/UpdateCurrentLimitMasterTask.h"
#include "Task/WebSocket/UpdateCurrentLimitMasterTask.h"

// UpdateCurrentLimitMasterFromGitHub
#include "Request/UpdateCurrentLimitMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentLimitMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentLimitMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentLimitMasterFromGitHubTask.h"

// DescribeLimitModels
#include "Request/DescribeLimitModelsRequest.h"
#include "Result/DescribeLimitModelsResult.h"
#include "Task/Rest/DescribeLimitModelsTask.h"
#include "Task/WebSocket/DescribeLimitModelsTask.h"

// GetLimitModel
#include "Request/GetLimitModelRequest.h"
#include "Result/GetLimitModelResult.h"
#include "Task/Rest/GetLimitModelTask.h"
#include "Task/WebSocket/GetLimitModelTask.h"

// Client
#include "Gs2LimitRestClient.h"
#include "Gs2LimitWebSocketClient.h"