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
#include "Request/DescribeEventsByUserIdRequest.h"
#include "Task/WebSocket/DescribeEventsByUserIdTask.h"
#include "Request/GetEventByTransactionIdRequest.h"
#include "Task/WebSocket/GetEventByTransactionIdTask.h"
#include "Request/VerifyReceiptRequest.h"
#include "Task/WebSocket/VerifyReceiptTask.h"
#include "Request/VerifyReceiptByUserIdRequest.h"
#include "Task/WebSocket/VerifyReceiptByUserIdTask.h"
#include "Request/VerifyReceiptByStampTaskRequest.h"
#include "Task/WebSocket/VerifyReceiptByStampTaskTask.h"
#include "Request/DescribeSubscriptionStatusesRequest.h"
#include "Task/WebSocket/DescribeSubscriptionStatusesTask.h"
#include "Request/DescribeSubscriptionStatusesByUserIdRequest.h"
#include "Task/WebSocket/DescribeSubscriptionStatusesByUserIdTask.h"
#include "Request/GetSubscriptionStatusRequest.h"
#include "Task/WebSocket/GetSubscriptionStatusTask.h"
#include "Request/GetSubscriptionStatusByUserIdRequest.h"
#include "Task/WebSocket/GetSubscriptionStatusByUserIdTask.h"
#include "Request/AllocateSubscriptionStatusRequest.h"
#include "Task/WebSocket/AllocateSubscriptionStatusTask.h"
#include "Request/AllocateSubscriptionStatusByUserIdRequest.h"
#include "Task/WebSocket/AllocateSubscriptionStatusByUserIdTask.h"
#include "Request/TakeoverSubscriptionStatusRequest.h"
#include "Task/WebSocket/TakeoverSubscriptionStatusTask.h"
#include "Request/TakeoverSubscriptionStatusByUserIdRequest.h"
#include "Task/WebSocket/TakeoverSubscriptionStatusByUserIdTask.h"
#include "Request/DescribeRefundHistoriesByUserIdRequest.h"
#include "Task/WebSocket/DescribeRefundHistoriesByUserIdTask.h"
#include "Request/DescribeRefundHistoriesByDateRequest.h"
#include "Task/WebSocket/DescribeRefundHistoriesByDateTask.h"
#include "Request/GetRefundHistoryRequest.h"
#include "Task/WebSocket/GetRefundHistoryTask.h"
#include "Request/DescribeStoreContentModelsRequest.h"
#include "Task/WebSocket/DescribeStoreContentModelsTask.h"
#include "Request/GetStoreContentModelRequest.h"
#include "Task/WebSocket/GetStoreContentModelTask.h"
#include "Request/DescribeStoreContentModelMastersRequest.h"
#include "Task/WebSocket/DescribeStoreContentModelMastersTask.h"
#include "Request/CreateStoreContentModelMasterRequest.h"
#include "Task/WebSocket/CreateStoreContentModelMasterTask.h"
#include "Request/GetStoreContentModelMasterRequest.h"
#include "Task/WebSocket/GetStoreContentModelMasterTask.h"
#include "Request/UpdateStoreContentModelMasterRequest.h"
#include "Task/WebSocket/UpdateStoreContentModelMasterTask.h"
#include "Request/DeleteStoreContentModelMasterRequest.h"
#include "Task/WebSocket/DeleteStoreContentModelMasterTask.h"
#include "Request/DescribeStoreSubscriptionContentModelsRequest.h"
#include "Task/WebSocket/DescribeStoreSubscriptionContentModelsTask.h"
#include "Request/GetStoreSubscriptionContentModelRequest.h"
#include "Task/WebSocket/GetStoreSubscriptionContentModelTask.h"
#include "Request/DescribeStoreSubscriptionContentModelMastersRequest.h"
#include "Task/WebSocket/DescribeStoreSubscriptionContentModelMastersTask.h"
#include "Request/CreateStoreSubscriptionContentModelMasterRequest.h"
#include "Task/WebSocket/CreateStoreSubscriptionContentModelMasterTask.h"
#include "Request/GetStoreSubscriptionContentModelMasterRequest.h"
#include "Task/WebSocket/GetStoreSubscriptionContentModelMasterTask.h"
#include "Request/UpdateStoreSubscriptionContentModelMasterRequest.h"
#include "Task/WebSocket/UpdateStoreSubscriptionContentModelMasterTask.h"
#include "Request/DeleteStoreSubscriptionContentModelMasterRequest.h"
#include "Task/WebSocket/DeleteStoreSubscriptionContentModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentModelMasterRequest.h"
#include "Task/WebSocket/GetCurrentModelMasterTask.h"
#include "Request/PreUpdateCurrentModelMasterRequest.h"
#include "Task/WebSocket/PreUpdateCurrentModelMasterTask.h"
#include "Request/UpdateCurrentModelMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentModelMasterTask.h"
#include "Request/UpdateCurrentModelMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentModelMasterFromGitHubTask.h"
#include "Request/DescribeDailyTransactionHistoriesByCurrencyRequest.h"
#include "Task/WebSocket/DescribeDailyTransactionHistoriesByCurrencyTask.h"
#include "Request/DescribeDailyTransactionHistoriesRequest.h"
#include "Task/WebSocket/DescribeDailyTransactionHistoriesTask.h"
#include "Request/GetDailyTransactionHistoryRequest.h"
#include "Task/WebSocket/GetDailyTransactionHistoryTask.h"
#include "Request/DescribeUnusedBalancesRequest.h"
#include "Task/WebSocket/DescribeUnusedBalancesTask.h"
#include "Request/GetUnusedBalanceRequest.h"
#include "Task/WebSocket/GetUnusedBalanceTask.h"

namespace Gs2::Money2
{
    class GS2MONEY2_API FGs2Money2WebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2Money2WebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeEventsByUserIdTask>> DescribeEventsByUserId(
            const Request::FDescribeEventsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetEventByTransactionIdTask>> GetEventByTransactionId(
            const Request::FGetEventByTransactionIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyReceiptTask>> VerifyReceipt(
            const Request::FVerifyReceiptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyReceiptByUserIdTask>> VerifyReceiptByUserId(
            const Request::FVerifyReceiptByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyReceiptByStampTaskTask>> VerifyReceiptByStampTask(
            const Request::FVerifyReceiptByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscriptionStatusesTask>> DescribeSubscriptionStatuses(
            const Request::FDescribeSubscriptionStatusesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscriptionStatusesByUserIdTask>> DescribeSubscriptionStatusesByUserId(
            const Request::FDescribeSubscriptionStatusesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscriptionStatusTask>> GetSubscriptionStatus(
            const Request::FGetSubscriptionStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscriptionStatusByUserIdTask>> GetSubscriptionStatusByUserId(
            const Request::FGetSubscriptionStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAllocateSubscriptionStatusTask>> AllocateSubscriptionStatus(
            const Request::FAllocateSubscriptionStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAllocateSubscriptionStatusByUserIdTask>> AllocateSubscriptionStatusByUserId(
            const Request::FAllocateSubscriptionStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FTakeoverSubscriptionStatusTask>> TakeoverSubscriptionStatus(
            const Request::FTakeoverSubscriptionStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FTakeoverSubscriptionStatusByUserIdTask>> TakeoverSubscriptionStatusByUserId(
            const Request::FTakeoverSubscriptionStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRefundHistoriesByUserIdTask>> DescribeRefundHistoriesByUserId(
            const Request::FDescribeRefundHistoriesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRefundHistoriesByDateTask>> DescribeRefundHistoriesByDate(
            const Request::FDescribeRefundHistoriesByDateRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRefundHistoryTask>> GetRefundHistory(
            const Request::FGetRefundHistoryRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStoreContentModelsTask>> DescribeStoreContentModels(
            const Request::FDescribeStoreContentModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStoreContentModelTask>> GetStoreContentModel(
            const Request::FGetStoreContentModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStoreContentModelMastersTask>> DescribeStoreContentModelMasters(
            const Request::FDescribeStoreContentModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateStoreContentModelMasterTask>> CreateStoreContentModelMaster(
            const Request::FCreateStoreContentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStoreContentModelMasterTask>> GetStoreContentModelMaster(
            const Request::FGetStoreContentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateStoreContentModelMasterTask>> UpdateStoreContentModelMaster(
            const Request::FUpdateStoreContentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteStoreContentModelMasterTask>> DeleteStoreContentModelMaster(
            const Request::FDeleteStoreContentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStoreSubscriptionContentModelsTask>> DescribeStoreSubscriptionContentModels(
            const Request::FDescribeStoreSubscriptionContentModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStoreSubscriptionContentModelTask>> GetStoreSubscriptionContentModel(
            const Request::FGetStoreSubscriptionContentModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStoreSubscriptionContentModelMastersTask>> DescribeStoreSubscriptionContentModelMasters(
            const Request::FDescribeStoreSubscriptionContentModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateStoreSubscriptionContentModelMasterTask>> CreateStoreSubscriptionContentModelMaster(
            const Request::FCreateStoreSubscriptionContentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStoreSubscriptionContentModelMasterTask>> GetStoreSubscriptionContentModelMaster(
            const Request::FGetStoreSubscriptionContentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateStoreSubscriptionContentModelMasterTask>> UpdateStoreSubscriptionContentModelMaster(
            const Request::FUpdateStoreSubscriptionContentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteStoreSubscriptionContentModelMasterTask>> DeleteStoreSubscriptionContentModelMaster(
            const Request::FDeleteStoreSubscriptionContentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentModelMasterTask>> GetCurrentModelMaster(
            const Request::FGetCurrentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPreUpdateCurrentModelMasterTask>> PreUpdateCurrentModelMaster(
            const Request::FPreUpdateCurrentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentModelMasterTask>> UpdateCurrentModelMaster(
            const Request::FUpdateCurrentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentModelMasterFromGitHubTask>> UpdateCurrentModelMasterFromGitHub(
            const Request::FUpdateCurrentModelMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeDailyTransactionHistoriesByCurrencyTask>> DescribeDailyTransactionHistoriesByCurrency(
            const Request::FDescribeDailyTransactionHistoriesByCurrencyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeDailyTransactionHistoriesTask>> DescribeDailyTransactionHistories(
            const Request::FDescribeDailyTransactionHistoriesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetDailyTransactionHistoryTask>> GetDailyTransactionHistory(
            const Request::FGetDailyTransactionHistoryRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeUnusedBalancesTask>> DescribeUnusedBalances(
            const Request::FDescribeUnusedBalancesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetUnusedBalanceTask>> GetUnusedBalance(
            const Request::FGetUnusedBalanceRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2Money2WebSocketClient, ESPMode::ThreadSafe> FGs2Money2WebSocketClientPtr;
}