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
#include "Model/Receipt.h"
#include "Model/WalletDetail.h"
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

// DescribeReceipts
#include "Request/DescribeReceiptsRequest.h"
#include "Result/DescribeReceiptsResult.h"
#include "Task/Rest/DescribeReceiptsTask.h"
#include "Task/WebSocket/DescribeReceiptsTask.h"

// GetByUserIdAndTransactionId
#include "Request/GetByUserIdAndTransactionIdRequest.h"
#include "Result/GetByUserIdAndTransactionIdResult.h"
#include "Task/Rest/GetByUserIdAndTransactionIdTask.h"
#include "Task/WebSocket/GetByUserIdAndTransactionIdTask.h"

// RecordReceipt
#include "Request/RecordReceiptRequest.h"
#include "Result/RecordReceiptResult.h"
#include "Task/Rest/RecordReceiptTask.h"
#include "Task/WebSocket/RecordReceiptTask.h"

// RevertRecordReceipt
#include "Request/RevertRecordReceiptRequest.h"
#include "Result/RevertRecordReceiptResult.h"
#include "Task/Rest/RevertRecordReceiptTask.h"
#include "Task/WebSocket/RevertRecordReceiptTask.h"

// RecordReceiptByStampTask
#include "Request/RecordReceiptByStampTaskRequest.h"
#include "Result/RecordReceiptByStampTaskResult.h"
#include "Task/Rest/RecordReceiptByStampTaskTask.h"
#include "Task/WebSocket/RecordReceiptByStampTaskTask.h"

// RevertRecordReceiptByStampSheet
#include "Request/RevertRecordReceiptByStampSheetRequest.h"
#include "Result/RevertRecordReceiptByStampSheetResult.h"
#include "Task/Rest/RevertRecordReceiptByStampSheetTask.h"
#include "Task/WebSocket/RevertRecordReceiptByStampSheetTask.h"

// Client
#include "Gs2MoneyRestClient.h"
#include "Gs2MoneyWebSocketClient.h"