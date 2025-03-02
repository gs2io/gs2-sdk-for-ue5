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
#include "Model/Wallet.h"
#include "Model/Event.h"
#include "Model/SubscribeTransaction.h"
#include "Model/SubscriptionStatus.h"
#include "Model/StoreContentModel.h"
#include "Model/StoreContentModelMaster.h"
#include "Model/StoreSubscriptionContentModel.h"
#include "Model/StoreSubscriptionContentModelMaster.h"
#include "Model/CurrentModelMaster.h"
#include "Model/Receipt.h"
#include "Model/PlatformSetting.h"
#include "Model/AppleAppStoreSetting.h"
#include "Model/GooglePlaySetting.h"
#include "Model/FakeSetting.h"
#include "Model/WalletSummary.h"
#include "Model/DepositTransaction.h"
#include "Model/VerifyReceiptEvent.h"
#include "Model/DepositEvent.h"
#include "Model/WithdrawEvent.h"
#include "Model/RefundEvent.h"
#include "Model/AppleAppStoreVerifyReceiptEvent.h"
#include "Model/GooglePlayVerifyReceiptEvent.h"
#include "Model/AppleAppStoreContent.h"
#include "Model/GooglePlayContent.h"
#include "Model/AppleAppStoreSubscriptionContent.h"
#include "Model/GooglePlaySubscriptionContent.h"
#include "Model/GooglePlayRealtimeNotificationMessage.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/ScriptSetting.h"
#include "Model/LogSetting.h"
#include "Model/DailyTransactionHistory.h"
#include "Model/UnusedBalance.h"

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

// DescribeWallets
#include "Request/DescribeWalletsRequest.h"
#include "Result/DescribeWalletsResult.h"
#include "Task/Rest/DescribeWalletsTask.h"
#include "Task/WebSocket/DescribeWalletsTask.h"

// DescribeWalletsByUserId
#include "Request/DescribeWalletsByUserIdRequest.h"
#include "Result/DescribeWalletsByUserIdResult.h"
#include "Task/Rest/DescribeWalletsByUserIdTask.h"
#include "Task/WebSocket/DescribeWalletsByUserIdTask.h"

// GetWallet
#include "Request/GetWalletRequest.h"
#include "Result/GetWalletResult.h"
#include "Task/Rest/GetWalletTask.h"
#include "Task/WebSocket/GetWalletTask.h"

// GetWalletByUserId
#include "Request/GetWalletByUserIdRequest.h"
#include "Result/GetWalletByUserIdResult.h"
#include "Task/Rest/GetWalletByUserIdTask.h"
#include "Task/WebSocket/GetWalletByUserIdTask.h"

// DepositByUserId
#include "Request/DepositByUserIdRequest.h"
#include "Result/DepositByUserIdResult.h"
#include "Task/Rest/DepositByUserIdTask.h"
#include "Task/WebSocket/DepositByUserIdTask.h"

// Withdraw
#include "Request/WithdrawRequest.h"
#include "Result/WithdrawResult.h"
#include "Task/Rest/WithdrawTask.h"
#include "Task/WebSocket/WithdrawTask.h"

// WithdrawByUserId
#include "Request/WithdrawByUserIdRequest.h"
#include "Result/WithdrawByUserIdResult.h"
#include "Task/Rest/WithdrawByUserIdTask.h"
#include "Task/WebSocket/WithdrawByUserIdTask.h"

// DepositByStampSheet
#include "Request/DepositByStampSheetRequest.h"
#include "Result/DepositByStampSheetResult.h"
#include "Task/Rest/DepositByStampSheetTask.h"
#include "Task/WebSocket/DepositByStampSheetTask.h"

// WithdrawByStampTask
#include "Request/WithdrawByStampTaskRequest.h"
#include "Result/WithdrawByStampTaskResult.h"
#include "Task/Rest/WithdrawByStampTaskTask.h"
#include "Task/WebSocket/WithdrawByStampTaskTask.h"

// DescribeEventsByUserId
#include "Request/DescribeEventsByUserIdRequest.h"
#include "Result/DescribeEventsByUserIdResult.h"
#include "Task/Rest/DescribeEventsByUserIdTask.h"
#include "Task/WebSocket/DescribeEventsByUserIdTask.h"

// GetEventByTransactionId
#include "Request/GetEventByTransactionIdRequest.h"
#include "Result/GetEventByTransactionIdResult.h"
#include "Task/Rest/GetEventByTransactionIdTask.h"
#include "Task/WebSocket/GetEventByTransactionIdTask.h"

// VerifyReceipt
#include "Request/VerifyReceiptRequest.h"
#include "Result/VerifyReceiptResult.h"
#include "Task/Rest/VerifyReceiptTask.h"
#include "Task/WebSocket/VerifyReceiptTask.h"

// VerifyReceiptByUserId
#include "Request/VerifyReceiptByUserIdRequest.h"
#include "Result/VerifyReceiptByUserIdResult.h"
#include "Task/Rest/VerifyReceiptByUserIdTask.h"
#include "Task/WebSocket/VerifyReceiptByUserIdTask.h"

// VerifyReceiptByStampTask
#include "Request/VerifyReceiptByStampTaskRequest.h"
#include "Result/VerifyReceiptByStampTaskResult.h"
#include "Task/Rest/VerifyReceiptByStampTaskTask.h"
#include "Task/WebSocket/VerifyReceiptByStampTaskTask.h"

// DescribeSubscriptionStatuses
#include "Request/DescribeSubscriptionStatusesRequest.h"
#include "Result/DescribeSubscriptionStatusesResult.h"
#include "Task/Rest/DescribeSubscriptionStatusesTask.h"
#include "Task/WebSocket/DescribeSubscriptionStatusesTask.h"

// DescribeSubscriptionStatusesByUserId
#include "Request/DescribeSubscriptionStatusesByUserIdRequest.h"
#include "Result/DescribeSubscriptionStatusesByUserIdResult.h"
#include "Task/Rest/DescribeSubscriptionStatusesByUserIdTask.h"
#include "Task/WebSocket/DescribeSubscriptionStatusesByUserIdTask.h"

// GetSubscriptionStatus
#include "Request/GetSubscriptionStatusRequest.h"
#include "Result/GetSubscriptionStatusResult.h"
#include "Task/Rest/GetSubscriptionStatusTask.h"
#include "Task/WebSocket/GetSubscriptionStatusTask.h"

// GetSubscriptionStatusByUserId
#include "Request/GetSubscriptionStatusByUserIdRequest.h"
#include "Result/GetSubscriptionStatusByUserIdResult.h"
#include "Task/Rest/GetSubscriptionStatusByUserIdTask.h"
#include "Task/WebSocket/GetSubscriptionStatusByUserIdTask.h"

// DescribeStoreContentModels
#include "Request/DescribeStoreContentModelsRequest.h"
#include "Result/DescribeStoreContentModelsResult.h"
#include "Task/Rest/DescribeStoreContentModelsTask.h"
#include "Task/WebSocket/DescribeStoreContentModelsTask.h"

// GetStoreContentModel
#include "Request/GetStoreContentModelRequest.h"
#include "Result/GetStoreContentModelResult.h"
#include "Task/Rest/GetStoreContentModelTask.h"
#include "Task/WebSocket/GetStoreContentModelTask.h"

// DescribeStoreContentModelMasters
#include "Request/DescribeStoreContentModelMastersRequest.h"
#include "Result/DescribeStoreContentModelMastersResult.h"
#include "Task/Rest/DescribeStoreContentModelMastersTask.h"
#include "Task/WebSocket/DescribeStoreContentModelMastersTask.h"

// CreateStoreContentModelMaster
#include "Request/CreateStoreContentModelMasterRequest.h"
#include "Result/CreateStoreContentModelMasterResult.h"
#include "Task/Rest/CreateStoreContentModelMasterTask.h"
#include "Task/WebSocket/CreateStoreContentModelMasterTask.h"

// GetStoreContentModelMaster
#include "Request/GetStoreContentModelMasterRequest.h"
#include "Result/GetStoreContentModelMasterResult.h"
#include "Task/Rest/GetStoreContentModelMasterTask.h"
#include "Task/WebSocket/GetStoreContentModelMasterTask.h"

// UpdateStoreContentModelMaster
#include "Request/UpdateStoreContentModelMasterRequest.h"
#include "Result/UpdateStoreContentModelMasterResult.h"
#include "Task/Rest/UpdateStoreContentModelMasterTask.h"
#include "Task/WebSocket/UpdateStoreContentModelMasterTask.h"

// DeleteStoreContentModelMaster
#include "Request/DeleteStoreContentModelMasterRequest.h"
#include "Result/DeleteStoreContentModelMasterResult.h"
#include "Task/Rest/DeleteStoreContentModelMasterTask.h"
#include "Task/WebSocket/DeleteStoreContentModelMasterTask.h"

// DescribeStoreSubscriptionContentModels
#include "Request/DescribeStoreSubscriptionContentModelsRequest.h"
#include "Result/DescribeStoreSubscriptionContentModelsResult.h"
#include "Task/Rest/DescribeStoreSubscriptionContentModelsTask.h"
#include "Task/WebSocket/DescribeStoreSubscriptionContentModelsTask.h"

// GetStoreSubscriptionContentModel
#include "Request/GetStoreSubscriptionContentModelRequest.h"
#include "Result/GetStoreSubscriptionContentModelResult.h"
#include "Task/Rest/GetStoreSubscriptionContentModelTask.h"
#include "Task/WebSocket/GetStoreSubscriptionContentModelTask.h"

// DescribeStoreSubscriptionContentModelMasters
#include "Request/DescribeStoreSubscriptionContentModelMastersRequest.h"
#include "Result/DescribeStoreSubscriptionContentModelMastersResult.h"
#include "Task/Rest/DescribeStoreSubscriptionContentModelMastersTask.h"
#include "Task/WebSocket/DescribeStoreSubscriptionContentModelMastersTask.h"

// CreateStoreSubscriptionContentModelMaster
#include "Request/CreateStoreSubscriptionContentModelMasterRequest.h"
#include "Result/CreateStoreSubscriptionContentModelMasterResult.h"
#include "Task/Rest/CreateStoreSubscriptionContentModelMasterTask.h"
#include "Task/WebSocket/CreateStoreSubscriptionContentModelMasterTask.h"

// GetStoreSubscriptionContentModelMaster
#include "Request/GetStoreSubscriptionContentModelMasterRequest.h"
#include "Result/GetStoreSubscriptionContentModelMasterResult.h"
#include "Task/Rest/GetStoreSubscriptionContentModelMasterTask.h"
#include "Task/WebSocket/GetStoreSubscriptionContentModelMasterTask.h"

// UpdateStoreSubscriptionContentModelMaster
#include "Request/UpdateStoreSubscriptionContentModelMasterRequest.h"
#include "Result/UpdateStoreSubscriptionContentModelMasterResult.h"
#include "Task/Rest/UpdateStoreSubscriptionContentModelMasterTask.h"
#include "Task/WebSocket/UpdateStoreSubscriptionContentModelMasterTask.h"

// DeleteStoreSubscriptionContentModelMaster
#include "Request/DeleteStoreSubscriptionContentModelMasterRequest.h"
#include "Result/DeleteStoreSubscriptionContentModelMasterResult.h"
#include "Task/Rest/DeleteStoreSubscriptionContentModelMasterTask.h"
#include "Task/WebSocket/DeleteStoreSubscriptionContentModelMasterTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentModelMaster
#include "Request/GetCurrentModelMasterRequest.h"
#include "Result/GetCurrentModelMasterResult.h"
#include "Task/Rest/GetCurrentModelMasterTask.h"
#include "Task/WebSocket/GetCurrentModelMasterTask.h"

// UpdateCurrentModelMaster
#include "Request/UpdateCurrentModelMasterRequest.h"
#include "Result/UpdateCurrentModelMasterResult.h"
#include "Task/Rest/UpdateCurrentModelMasterTask.h"
#include "Task/WebSocket/UpdateCurrentModelMasterTask.h"

// UpdateCurrentModelMasterFromGitHub
#include "Request/UpdateCurrentModelMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentModelMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentModelMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentModelMasterFromGitHubTask.h"

// DescribeDailyTransactionHistoriesByCurrency
#include "Request/DescribeDailyTransactionHistoriesByCurrencyRequest.h"
#include "Result/DescribeDailyTransactionHistoriesByCurrencyResult.h"
#include "Task/Rest/DescribeDailyTransactionHistoriesByCurrencyTask.h"
#include "Task/WebSocket/DescribeDailyTransactionHistoriesByCurrencyTask.h"

// DescribeDailyTransactionHistories
#include "Request/DescribeDailyTransactionHistoriesRequest.h"
#include "Result/DescribeDailyTransactionHistoriesResult.h"
#include "Task/Rest/DescribeDailyTransactionHistoriesTask.h"
#include "Task/WebSocket/DescribeDailyTransactionHistoriesTask.h"

// GetDailyTransactionHistory
#include "Request/GetDailyTransactionHistoryRequest.h"
#include "Result/GetDailyTransactionHistoryResult.h"
#include "Task/Rest/GetDailyTransactionHistoryTask.h"
#include "Task/WebSocket/GetDailyTransactionHistoryTask.h"

// DescribeUnusedBalances
#include "Request/DescribeUnusedBalancesRequest.h"
#include "Result/DescribeUnusedBalancesResult.h"
#include "Task/Rest/DescribeUnusedBalancesTask.h"
#include "Task/WebSocket/DescribeUnusedBalancesTask.h"

// GetUnusedBalance
#include "Request/GetUnusedBalanceRequest.h"
#include "Result/GetUnusedBalanceResult.h"
#include "Task/Rest/GetUnusedBalanceTask.h"
#include "Task/WebSocket/GetUnusedBalanceTask.h"

// Client
#include "Gs2Money2RestClient.h"
#include "Gs2Money2WebSocketClient.h"