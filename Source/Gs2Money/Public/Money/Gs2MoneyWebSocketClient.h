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

#include "CoreMinimal.h"
#include "Core/Net/AbstractWebSocketGs2Client.h"
#include "Request/DescribeNamespacesRequest.h"
#include "Task/WebSocket/DescribeNamespacesTask.h"
#include "Request/CreateNamespaceRequest.h"
#include "Task/WebSocket/CreateNamespaceTask.h"
#include "Request/GetNamespaceStatusRequest.h"
#include "Task/WebSocket/GetNamespaceStatusTask.h"
#include "Request/GetNamespaceRequest.h"
#include "Task/WebSocket/GetNamespaceTask.h"
#include "Request/UpdateNamespaceRequest.h"
#include "Task/WebSocket/UpdateNamespaceTask.h"
#include "Request/DeleteNamespaceRequest.h"
#include "Task/WebSocket/DeleteNamespaceTask.h"
#include "Request/GetServiceVersionRequest.h"
#include "Task/WebSocket/GetServiceVersionTask.h"
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/DumpUserDataByUserIdTask.h"
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckDumpUserDataByUserIdTask.h"
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CleanUserDataByUserIdTask.h"
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckCleanUserDataByUserIdTask.h"
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/PrepareImportUserDataByUserIdTask.h"
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/ImportUserDataByUserIdTask.h"
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckImportUserDataByUserIdTask.h"
#include "Request/DescribeWalletsRequest.h"
#include "Task/WebSocket/DescribeWalletsTask.h"
#include "Request/DescribeWalletsByUserIdRequest.h"
#include "Task/WebSocket/DescribeWalletsByUserIdTask.h"
#include "Request/GetWalletRequest.h"
#include "Task/WebSocket/GetWalletTask.h"
#include "Request/GetWalletByUserIdRequest.h"
#include "Task/WebSocket/GetWalletByUserIdTask.h"
#include "Request/DepositByUserIdRequest.h"
#include "Task/WebSocket/DepositByUserIdTask.h"
#include "Request/WithdrawRequest.h"
#include "Task/WebSocket/WithdrawTask.h"
#include "Request/WithdrawByUserIdRequest.h"
#include "Task/WebSocket/WithdrawByUserIdTask.h"
#include "Request/DepositByStampSheetRequest.h"
#include "Task/WebSocket/DepositByStampSheetTask.h"
#include "Request/WithdrawByStampTaskRequest.h"
#include "Task/WebSocket/WithdrawByStampTaskTask.h"
#include "Request/DescribeReceiptsRequest.h"
#include "Task/WebSocket/DescribeReceiptsTask.h"
#include "Request/GetByUserIdAndTransactionIdRequest.h"
#include "Task/WebSocket/GetByUserIdAndTransactionIdTask.h"
#include "Request/RecordReceiptRequest.h"
#include "Task/WebSocket/RecordReceiptTask.h"
#include "Request/RevertRecordReceiptRequest.h"
#include "Task/WebSocket/RevertRecordReceiptTask.h"
#include "Request/RecordReceiptByStampTaskRequest.h"
#include "Task/WebSocket/RecordReceiptByStampTaskTask.h"
#include "Request/RevertRecordReceiptByStampSheetRequest.h"
#include "Task/WebSocket/RevertRecordReceiptByStampSheetTask.h"

namespace Gs2::Money
{
    class GS2MONEY_API FGs2MoneyWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2MoneyWebSocketClient(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session
        ): FAbstractWebSocketGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> DescribeNamespaces(
            const Request::FDescribeNamespacesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> CreateNamespace(
            const Request::FCreateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> GetNamespaceStatus(
            const Request::FGetNamespaceStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> GetNamespace(
            const Request::FGetNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> UpdateNamespace(
            const Request::FUpdateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> DeleteNamespace(
            const Request::FDeleteNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetServiceVersionTask>> GetServiceVersion(
            const Request::FGetServiceVersionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>> DumpUserDataByUserId(
            const Request::FDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>> CheckDumpUserDataByUserId(
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>> CleanUserDataByUserId(
            const Request::FCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>> CheckCleanUserDataByUserId(
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>> PrepareImportUserDataByUserId(
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>> ImportUserDataByUserId(
            const Request::FImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>> CheckImportUserDataByUserId(
            const Request::FCheckImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeWalletsTask>> DescribeWallets(
            const Request::FDescribeWalletsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeWalletsByUserIdTask>> DescribeWalletsByUserId(
            const Request::FDescribeWalletsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetWalletTask>> GetWallet(
            const Request::FGetWalletRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetWalletByUserIdTask>> GetWalletByUserId(
            const Request::FGetWalletByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDepositByUserIdTask>> DepositByUserId(
            const Request::FDepositByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FWithdrawTask>> Withdraw(
            const Request::FWithdrawRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FWithdrawByUserIdTask>> WithdrawByUserId(
            const Request::FWithdrawByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDepositByStampSheetTask>> DepositByStampSheet(
            const Request::FDepositByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FWithdrawByStampTaskTask>> WithdrawByStampTask(
            const Request::FWithdrawByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeReceiptsTask>> DescribeReceipts(
            const Request::FDescribeReceiptsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetByUserIdAndTransactionIdTask>> GetByUserIdAndTransactionId(
            const Request::FGetByUserIdAndTransactionIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRecordReceiptTask>> RecordReceipt(
            const Request::FRecordReceiptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRevertRecordReceiptTask>> RevertRecordReceipt(
            const Request::FRevertRecordReceiptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRecordReceiptByStampTaskTask>> RecordReceiptByStampTask(
            const Request::FRecordReceiptByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRevertRecordReceiptByStampSheetTask>> RevertRecordReceiptByStampSheet(
            const Request::FRevertRecordReceiptByStampSheetRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2MoneyWebSocketClient, ESPMode::ThreadSafe> FGs2MoneyWebSocketClientPtr;
}