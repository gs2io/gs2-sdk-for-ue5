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
#include "Model/IncrementalRateModel.h"
#include "Model/IncrementalRateModelMaster.h"
#include "Model/CurrentRateMaster.h"
#include "Model/Await.h"
#include "Model/LogCost.h"
#include "Model/LogRate.h"
#include "Model/AcquireAction.h"
#include "Model/ConsumeAction.h"
#include "Model/VerifyAction.h"
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

// DescribeIncrementalRateModels
#include "Request/DescribeIncrementalRateModelsRequest.h"
#include "Result/DescribeIncrementalRateModelsResult.h"
#include "Task/Rest/DescribeIncrementalRateModelsTask.h"
#include "Task/WebSocket/DescribeIncrementalRateModelsTask.h"

// GetIncrementalRateModel
#include "Request/GetIncrementalRateModelRequest.h"
#include "Result/GetIncrementalRateModelResult.h"
#include "Task/Rest/GetIncrementalRateModelTask.h"
#include "Task/WebSocket/GetIncrementalRateModelTask.h"

// DescribeIncrementalRateModelMasters
#include "Request/DescribeIncrementalRateModelMastersRequest.h"
#include "Result/DescribeIncrementalRateModelMastersResult.h"
#include "Task/Rest/DescribeIncrementalRateModelMastersTask.h"
#include "Task/WebSocket/DescribeIncrementalRateModelMastersTask.h"

// CreateIncrementalRateModelMaster
#include "Request/CreateIncrementalRateModelMasterRequest.h"
#include "Result/CreateIncrementalRateModelMasterResult.h"
#include "Task/Rest/CreateIncrementalRateModelMasterTask.h"
#include "Task/WebSocket/CreateIncrementalRateModelMasterTask.h"

// GetIncrementalRateModelMaster
#include "Request/GetIncrementalRateModelMasterRequest.h"
#include "Result/GetIncrementalRateModelMasterResult.h"
#include "Task/Rest/GetIncrementalRateModelMasterTask.h"
#include "Task/WebSocket/GetIncrementalRateModelMasterTask.h"

// UpdateIncrementalRateModelMaster
#include "Request/UpdateIncrementalRateModelMasterRequest.h"
#include "Result/UpdateIncrementalRateModelMasterResult.h"
#include "Task/Rest/UpdateIncrementalRateModelMasterTask.h"
#include "Task/WebSocket/UpdateIncrementalRateModelMasterTask.h"

// DeleteIncrementalRateModelMaster
#include "Request/DeleteIncrementalRateModelMasterRequest.h"
#include "Result/DeleteIncrementalRateModelMasterResult.h"
#include "Task/Rest/DeleteIncrementalRateModelMasterTask.h"
#include "Task/WebSocket/DeleteIncrementalRateModelMasterTask.h"

// Exchange
#include "Request/ExchangeRequest.h"
#include "Result/ExchangeResult.h"
#include "Task/Rest/ExchangeTask.h"
#include "Task/WebSocket/ExchangeTask.h"

// ExchangeByUserId
#include "Request/ExchangeByUserIdRequest.h"
#include "Result/ExchangeByUserIdResult.h"
#include "Task/Rest/ExchangeByUserIdTask.h"
#include "Task/WebSocket/ExchangeByUserIdTask.h"

// ExchangeByStampSheet
#include "Request/ExchangeByStampSheetRequest.h"
#include "Result/ExchangeByStampSheetResult.h"
#include "Task/Rest/ExchangeByStampSheetTask.h"
#include "Task/WebSocket/ExchangeByStampSheetTask.h"

// IncrementalExchange
#include "Request/IncrementalExchangeRequest.h"
#include "Result/IncrementalExchangeResult.h"
#include "Task/Rest/IncrementalExchangeTask.h"
#include "Task/WebSocket/IncrementalExchangeTask.h"

// IncrementalExchangeByUserId
#include "Request/IncrementalExchangeByUserIdRequest.h"
#include "Result/IncrementalExchangeByUserIdResult.h"
#include "Task/Rest/IncrementalExchangeByUserIdTask.h"
#include "Task/WebSocket/IncrementalExchangeByUserIdTask.h"

// IncrementalExchangeByStampSheet
#include "Request/IncrementalExchangeByStampSheetRequest.h"
#include "Result/IncrementalExchangeByStampSheetResult.h"
#include "Task/Rest/IncrementalExchangeByStampSheetTask.h"
#include "Task/WebSocket/IncrementalExchangeByStampSheetTask.h"

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

// PreUpdateCurrentRateMaster
#include "Request/PreUpdateCurrentRateMasterRequest.h"
#include "Result/PreUpdateCurrentRateMasterResult.h"
#include "Task/Rest/PreUpdateCurrentRateMasterTask.h"
#include "Task/WebSocket/PreUpdateCurrentRateMasterTask.h"

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

// CreateAwaitByUserId
#include "Request/CreateAwaitByUserIdRequest.h"
#include "Result/CreateAwaitByUserIdResult.h"
#include "Task/Rest/CreateAwaitByUserIdTask.h"
#include "Task/WebSocket/CreateAwaitByUserIdTask.h"

// DescribeAwaits
#include "Request/DescribeAwaitsRequest.h"
#include "Result/DescribeAwaitsResult.h"
#include "Task/Rest/DescribeAwaitsTask.h"
#include "Task/WebSocket/DescribeAwaitsTask.h"

// DescribeAwaitsByUserId
#include "Request/DescribeAwaitsByUserIdRequest.h"
#include "Result/DescribeAwaitsByUserIdResult.h"
#include "Task/Rest/DescribeAwaitsByUserIdTask.h"
#include "Task/WebSocket/DescribeAwaitsByUserIdTask.h"

// GetAwait
#include "Request/GetAwaitRequest.h"
#include "Result/GetAwaitResult.h"
#include "Task/Rest/GetAwaitTask.h"
#include "Task/WebSocket/GetAwaitTask.h"

// GetAwaitByUserId
#include "Request/GetAwaitByUserIdRequest.h"
#include "Result/GetAwaitByUserIdResult.h"
#include "Task/Rest/GetAwaitByUserIdTask.h"
#include "Task/WebSocket/GetAwaitByUserIdTask.h"

// Acquire
#include "Request/AcquireRequest.h"
#include "Result/AcquireResult.h"
#include "Task/Rest/AcquireTask.h"
#include "Task/WebSocket/AcquireTask.h"

// AcquireByUserId
#include "Request/AcquireByUserIdRequest.h"
#include "Result/AcquireByUserIdResult.h"
#include "Task/Rest/AcquireByUserIdTask.h"
#include "Task/WebSocket/AcquireByUserIdTask.h"

// AcquireForceByUserId
#include "Request/AcquireForceByUserIdRequest.h"
#include "Result/AcquireForceByUserIdResult.h"
#include "Task/Rest/AcquireForceByUserIdTask.h"
#include "Task/WebSocket/AcquireForceByUserIdTask.h"

// SkipByUserId
#include "Request/SkipByUserIdRequest.h"
#include "Result/SkipByUserIdResult.h"
#include "Task/Rest/SkipByUserIdTask.h"
#include "Task/WebSocket/SkipByUserIdTask.h"

// DeleteAwait
#include "Request/DeleteAwaitRequest.h"
#include "Result/DeleteAwaitResult.h"
#include "Task/Rest/DeleteAwaitTask.h"
#include "Task/WebSocket/DeleteAwaitTask.h"

// DeleteAwaitByUserId
#include "Request/DeleteAwaitByUserIdRequest.h"
#include "Result/DeleteAwaitByUserIdResult.h"
#include "Task/Rest/DeleteAwaitByUserIdTask.h"
#include "Task/WebSocket/DeleteAwaitByUserIdTask.h"

// CreateAwaitByStampSheet
#include "Request/CreateAwaitByStampSheetRequest.h"
#include "Result/CreateAwaitByStampSheetResult.h"
#include "Task/Rest/CreateAwaitByStampSheetTask.h"
#include "Task/WebSocket/CreateAwaitByStampSheetTask.h"

// AcquireForceByStampSheet
#include "Request/AcquireForceByStampSheetRequest.h"
#include "Result/AcquireForceByStampSheetResult.h"
#include "Task/Rest/AcquireForceByStampSheetTask.h"
#include "Task/WebSocket/AcquireForceByStampSheetTask.h"

// SkipByStampSheet
#include "Request/SkipByStampSheetRequest.h"
#include "Result/SkipByStampSheetResult.h"
#include "Task/Rest/SkipByStampSheetTask.h"
#include "Task/WebSocket/SkipByStampSheetTask.h"

// DeleteAwaitByStampTask
#include "Request/DeleteAwaitByStampTaskRequest.h"
#include "Result/DeleteAwaitByStampTaskResult.h"
#include "Task/Rest/DeleteAwaitByStampTaskTask.h"
#include "Task/WebSocket/DeleteAwaitByStampTaskTask.h"

// Client
#include "Gs2ExchangeRestClient.h"
#include "Gs2ExchangeWebSocketClient.h"