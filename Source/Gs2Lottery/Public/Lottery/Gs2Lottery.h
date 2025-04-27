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
#include "Model/LotteryModelMaster.h"
#include "Model/PrizeTableMaster.h"
#include "Model/LotteryModel.h"
#include "Model/PrizeTable.h"
#include "Model/Probability.h"
#include "Model/CurrentLotteryMaster.h"
#include "Model/Prize.h"
#include "Model/PrizeLimit.h"
#include "Model/DrawnPrize.h"
#include "Model/BoxItem.h"
#include "Model/BoxItems.h"
#include "Model/AcquireAction.h"
#include "Model/Config.h"
#include "Model/VerifyActionResult.h"
#include "Model/ConsumeActionResult.h"
#include "Model/AcquireActionResult.h"
#include "Model/TransactionResult.h"
#include "Model/GitHubCheckoutSetting.h"
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

// DescribeLotteryModelMasters
#include "Request/DescribeLotteryModelMastersRequest.h"
#include "Result/DescribeLotteryModelMastersResult.h"
#include "Task/Rest/DescribeLotteryModelMastersTask.h"
#include "Task/WebSocket/DescribeLotteryModelMastersTask.h"

// CreateLotteryModelMaster
#include "Request/CreateLotteryModelMasterRequest.h"
#include "Result/CreateLotteryModelMasterResult.h"
#include "Task/Rest/CreateLotteryModelMasterTask.h"
#include "Task/WebSocket/CreateLotteryModelMasterTask.h"

// GetLotteryModelMaster
#include "Request/GetLotteryModelMasterRequest.h"
#include "Result/GetLotteryModelMasterResult.h"
#include "Task/Rest/GetLotteryModelMasterTask.h"
#include "Task/WebSocket/GetLotteryModelMasterTask.h"

// UpdateLotteryModelMaster
#include "Request/UpdateLotteryModelMasterRequest.h"
#include "Result/UpdateLotteryModelMasterResult.h"
#include "Task/Rest/UpdateLotteryModelMasterTask.h"
#include "Task/WebSocket/UpdateLotteryModelMasterTask.h"

// DeleteLotteryModelMaster
#include "Request/DeleteLotteryModelMasterRequest.h"
#include "Result/DeleteLotteryModelMasterResult.h"
#include "Task/Rest/DeleteLotteryModelMasterTask.h"
#include "Task/WebSocket/DeleteLotteryModelMasterTask.h"

// DescribePrizeTableMasters
#include "Request/DescribePrizeTableMastersRequest.h"
#include "Result/DescribePrizeTableMastersResult.h"
#include "Task/Rest/DescribePrizeTableMastersTask.h"
#include "Task/WebSocket/DescribePrizeTableMastersTask.h"

// CreatePrizeTableMaster
#include "Request/CreatePrizeTableMasterRequest.h"
#include "Result/CreatePrizeTableMasterResult.h"
#include "Task/Rest/CreatePrizeTableMasterTask.h"
#include "Task/WebSocket/CreatePrizeTableMasterTask.h"

// GetPrizeTableMaster
#include "Request/GetPrizeTableMasterRequest.h"
#include "Result/GetPrizeTableMasterResult.h"
#include "Task/Rest/GetPrizeTableMasterTask.h"
#include "Task/WebSocket/GetPrizeTableMasterTask.h"

// UpdatePrizeTableMaster
#include "Request/UpdatePrizeTableMasterRequest.h"
#include "Result/UpdatePrizeTableMasterResult.h"
#include "Task/Rest/UpdatePrizeTableMasterTask.h"
#include "Task/WebSocket/UpdatePrizeTableMasterTask.h"

// DeletePrizeTableMaster
#include "Request/DeletePrizeTableMasterRequest.h"
#include "Result/DeletePrizeTableMasterResult.h"
#include "Task/Rest/DeletePrizeTableMasterTask.h"
#include "Task/WebSocket/DeletePrizeTableMasterTask.h"

// DescribeLotteryModels
#include "Request/DescribeLotteryModelsRequest.h"
#include "Result/DescribeLotteryModelsResult.h"
#include "Task/Rest/DescribeLotteryModelsTask.h"
#include "Task/WebSocket/DescribeLotteryModelsTask.h"

// GetLotteryModel
#include "Request/GetLotteryModelRequest.h"
#include "Result/GetLotteryModelResult.h"
#include "Task/Rest/GetLotteryModelTask.h"
#include "Task/WebSocket/GetLotteryModelTask.h"

// DescribePrizeTables
#include "Request/DescribePrizeTablesRequest.h"
#include "Result/DescribePrizeTablesResult.h"
#include "Task/Rest/DescribePrizeTablesTask.h"
#include "Task/WebSocket/DescribePrizeTablesTask.h"

// GetPrizeTable
#include "Request/GetPrizeTableRequest.h"
#include "Result/GetPrizeTableResult.h"
#include "Task/Rest/GetPrizeTableTask.h"
#include "Task/WebSocket/GetPrizeTableTask.h"

// DrawByUserId
#include "Request/DrawByUserIdRequest.h"
#include "Result/DrawByUserIdResult.h"
#include "Task/Rest/DrawByUserIdTask.h"
#include "Task/WebSocket/DrawByUserIdTask.h"

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

// DrawWithRandomSeedByUserId
#include "Request/DrawWithRandomSeedByUserIdRequest.h"
#include "Result/DrawWithRandomSeedByUserIdResult.h"
#include "Task/Rest/DrawWithRandomSeedByUserIdTask.h"
#include "Task/WebSocket/DrawWithRandomSeedByUserIdTask.h"

// DrawByStampSheet
#include "Request/DrawByStampSheetRequest.h"
#include "Result/DrawByStampSheetResult.h"
#include "Task/Rest/DrawByStampSheetTask.h"
#include "Task/WebSocket/DrawByStampSheetTask.h"

// DescribeProbabilities
#include "Request/DescribeProbabilitiesRequest.h"
#include "Result/DescribeProbabilitiesResult.h"
#include "Task/Rest/DescribeProbabilitiesTask.h"
#include "Task/WebSocket/DescribeProbabilitiesTask.h"

// DescribeProbabilitiesByUserId
#include "Request/DescribeProbabilitiesByUserIdRequest.h"
#include "Result/DescribeProbabilitiesByUserIdResult.h"
#include "Task/Rest/DescribeProbabilitiesByUserIdTask.h"
#include "Task/WebSocket/DescribeProbabilitiesByUserIdTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentLotteryMaster
#include "Request/GetCurrentLotteryMasterRequest.h"
#include "Result/GetCurrentLotteryMasterResult.h"
#include "Task/Rest/GetCurrentLotteryMasterTask.h"
#include "Task/WebSocket/GetCurrentLotteryMasterTask.h"

// PreUpdateCurrentLotteryMaster
#include "Request/PreUpdateCurrentLotteryMasterRequest.h"
#include "Result/PreUpdateCurrentLotteryMasterResult.h"
#include "Task/Rest/PreUpdateCurrentLotteryMasterTask.h"
#include "Task/WebSocket/PreUpdateCurrentLotteryMasterTask.h"

// UpdateCurrentLotteryMaster
#include "Request/UpdateCurrentLotteryMasterRequest.h"
#include "Result/UpdateCurrentLotteryMasterResult.h"
#include "Task/Rest/UpdateCurrentLotteryMasterTask.h"
#include "Task/WebSocket/UpdateCurrentLotteryMasterTask.h"

// UpdateCurrentLotteryMasterFromGitHub
#include "Request/UpdateCurrentLotteryMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentLotteryMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentLotteryMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentLotteryMasterFromGitHubTask.h"

// DescribePrizeLimits
#include "Request/DescribePrizeLimitsRequest.h"
#include "Result/DescribePrizeLimitsResult.h"
#include "Task/Rest/DescribePrizeLimitsTask.h"
#include "Task/WebSocket/DescribePrizeLimitsTask.h"

// GetPrizeLimit
#include "Request/GetPrizeLimitRequest.h"
#include "Result/GetPrizeLimitResult.h"
#include "Task/Rest/GetPrizeLimitTask.h"
#include "Task/WebSocket/GetPrizeLimitTask.h"

// ResetPrizeLimit
#include "Request/ResetPrizeLimitRequest.h"
#include "Result/ResetPrizeLimitResult.h"
#include "Task/Rest/ResetPrizeLimitTask.h"
#include "Task/WebSocket/ResetPrizeLimitTask.h"

// DescribeBoxes
#include "Request/DescribeBoxesRequest.h"
#include "Result/DescribeBoxesResult.h"
#include "Task/Rest/DescribeBoxesTask.h"
#include "Task/WebSocket/DescribeBoxesTask.h"

// DescribeBoxesByUserId
#include "Request/DescribeBoxesByUserIdRequest.h"
#include "Result/DescribeBoxesByUserIdResult.h"
#include "Task/Rest/DescribeBoxesByUserIdTask.h"
#include "Task/WebSocket/DescribeBoxesByUserIdTask.h"

// GetBox
#include "Request/GetBoxRequest.h"
#include "Result/GetBoxResult.h"
#include "Task/Rest/GetBoxTask.h"
#include "Task/WebSocket/GetBoxTask.h"

// GetBoxByUserId
#include "Request/GetBoxByUserIdRequest.h"
#include "Result/GetBoxByUserIdResult.h"
#include "Task/Rest/GetBoxByUserIdTask.h"
#include "Task/WebSocket/GetBoxByUserIdTask.h"

// ResetBox
#include "Request/ResetBoxRequest.h"
#include "Result/ResetBoxResult.h"
#include "Task/Rest/ResetBoxTask.h"
#include "Task/WebSocket/ResetBoxTask.h"

// ResetBoxByUserId
#include "Request/ResetBoxByUserIdRequest.h"
#include "Result/ResetBoxByUserIdResult.h"
#include "Task/Rest/ResetBoxByUserIdTask.h"
#include "Task/WebSocket/ResetBoxByUserIdTask.h"

// ResetByStampSheet
#include "Request/ResetByStampSheetRequest.h"
#include "Result/ResetByStampSheetResult.h"
#include "Task/Rest/ResetByStampSheetTask.h"
#include "Task/WebSocket/ResetByStampSheetTask.h"

// Client
#include "Gs2LotteryRestClient.h"
#include "Gs2LotteryWebSocketClient.h"