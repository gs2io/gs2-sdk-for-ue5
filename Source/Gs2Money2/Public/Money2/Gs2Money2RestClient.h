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
#include "Core/Net/AbstractGs2Client.h"
#include "Request/DescribeNamespacesRequest.h"
#include "Task/Rest/DescribeNamespacesTask.h"
#include "Request/CreateNamespaceRequest.h"
#include "Task/Rest/CreateNamespaceTask.h"
#include "Request/GetNamespaceStatusRequest.h"
#include "Task/Rest/GetNamespaceStatusTask.h"
#include "Request/GetNamespaceRequest.h"
#include "Task/Rest/GetNamespaceTask.h"
#include "Request/UpdateNamespaceRequest.h"
#include "Task/Rest/UpdateNamespaceTask.h"
#include "Request/DeleteNamespaceRequest.h"
#include "Task/Rest/DeleteNamespaceTask.h"
#include "Request/GetServiceVersionRequest.h"
#include "Task/Rest/GetServiceVersionTask.h"
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Task/Rest/DumpUserDataByUserIdTask.h"
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Task/Rest/CheckDumpUserDataByUserIdTask.h"
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Task/Rest/CleanUserDataByUserIdTask.h"
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Task/Rest/CheckCleanUserDataByUserIdTask.h"
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Task/Rest/PrepareImportUserDataByUserIdTask.h"
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Task/Rest/ImportUserDataByUserIdTask.h"
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Task/Rest/CheckImportUserDataByUserIdTask.h"
#include "Request/DescribeWalletsRequest.h"
#include "Task/Rest/DescribeWalletsTask.h"
#include "Request/DescribeWalletsByUserIdRequest.h"
#include "Task/Rest/DescribeWalletsByUserIdTask.h"
#include "Request/GetWalletRequest.h"
#include "Task/Rest/GetWalletTask.h"
#include "Request/GetWalletByUserIdRequest.h"
#include "Task/Rest/GetWalletByUserIdTask.h"
#include "Request/DepositByUserIdRequest.h"
#include "Task/Rest/DepositByUserIdTask.h"
#include "Request/WithdrawRequest.h"
#include "Task/Rest/WithdrawTask.h"
#include "Request/WithdrawByUserIdRequest.h"
#include "Task/Rest/WithdrawByUserIdTask.h"
#include "Request/DepositByStampSheetRequest.h"
#include "Task/Rest/DepositByStampSheetTask.h"
#include "Request/WithdrawByStampTaskRequest.h"
#include "Task/Rest/WithdrawByStampTaskTask.h"
#include "Request/DescribeEventsByUserIdRequest.h"
#include "Task/Rest/DescribeEventsByUserIdTask.h"
#include "Request/GetEventByTransactionIdRequest.h"
#include "Task/Rest/GetEventByTransactionIdTask.h"
#include "Request/VerifyReceiptRequest.h"
#include "Task/Rest/VerifyReceiptTask.h"
#include "Request/VerifyReceiptByUserIdRequest.h"
#include "Task/Rest/VerifyReceiptByUserIdTask.h"
#include "Request/VerifyReceiptByStampTaskRequest.h"
#include "Task/Rest/VerifyReceiptByStampTaskTask.h"
#include "Request/DescribeSubscriptionStatusesRequest.h"
#include "Task/Rest/DescribeSubscriptionStatusesTask.h"
#include "Request/DescribeSubscriptionStatusesByUserIdRequest.h"
#include "Task/Rest/DescribeSubscriptionStatusesByUserIdTask.h"
#include "Request/GetSubscriptionStatusRequest.h"
#include "Task/Rest/GetSubscriptionStatusTask.h"
#include "Request/GetSubscriptionStatusByUserIdRequest.h"
#include "Task/Rest/GetSubscriptionStatusByUserIdTask.h"
#include "Request/AllocateSubscriptionStatusRequest.h"
#include "Task/Rest/AllocateSubscriptionStatusTask.h"
#include "Request/AllocateSubscriptionStatusByUserIdRequest.h"
#include "Task/Rest/AllocateSubscriptionStatusByUserIdTask.h"
#include "Request/TakeoverSubscriptionStatusRequest.h"
#include "Task/Rest/TakeoverSubscriptionStatusTask.h"
#include "Request/TakeoverSubscriptionStatusByUserIdRequest.h"
#include "Task/Rest/TakeoverSubscriptionStatusByUserIdTask.h"
#include "Request/DescribeRefundHistoriesByUserIdRequest.h"
#include "Task/Rest/DescribeRefundHistoriesByUserIdTask.h"
#include "Request/DescribeRefundHistoriesByDateRequest.h"
#include "Task/Rest/DescribeRefundHistoriesByDateTask.h"
#include "Request/GetRefundHistoryRequest.h"
#include "Task/Rest/GetRefundHistoryTask.h"
#include "Request/DescribeStoreContentModelsRequest.h"
#include "Task/Rest/DescribeStoreContentModelsTask.h"
#include "Request/GetStoreContentModelRequest.h"
#include "Task/Rest/GetStoreContentModelTask.h"
#include "Request/DescribeStoreContentModelMastersRequest.h"
#include "Task/Rest/DescribeStoreContentModelMastersTask.h"
#include "Request/CreateStoreContentModelMasterRequest.h"
#include "Task/Rest/CreateStoreContentModelMasterTask.h"
#include "Request/GetStoreContentModelMasterRequest.h"
#include "Task/Rest/GetStoreContentModelMasterTask.h"
#include "Request/UpdateStoreContentModelMasterRequest.h"
#include "Task/Rest/UpdateStoreContentModelMasterTask.h"
#include "Request/DeleteStoreContentModelMasterRequest.h"
#include "Task/Rest/DeleteStoreContentModelMasterTask.h"
#include "Request/DescribeStoreSubscriptionContentModelsRequest.h"
#include "Task/Rest/DescribeStoreSubscriptionContentModelsTask.h"
#include "Request/GetStoreSubscriptionContentModelRequest.h"
#include "Task/Rest/GetStoreSubscriptionContentModelTask.h"
#include "Request/DescribeStoreSubscriptionContentModelMastersRequest.h"
#include "Task/Rest/DescribeStoreSubscriptionContentModelMastersTask.h"
#include "Request/CreateStoreSubscriptionContentModelMasterRequest.h"
#include "Task/Rest/CreateStoreSubscriptionContentModelMasterTask.h"
#include "Request/GetStoreSubscriptionContentModelMasterRequest.h"
#include "Task/Rest/GetStoreSubscriptionContentModelMasterTask.h"
#include "Request/UpdateStoreSubscriptionContentModelMasterRequest.h"
#include "Task/Rest/UpdateStoreSubscriptionContentModelMasterTask.h"
#include "Request/DeleteStoreSubscriptionContentModelMasterRequest.h"
#include "Task/Rest/DeleteStoreSubscriptionContentModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentModelMasterRequest.h"
#include "Task/Rest/GetCurrentModelMasterTask.h"
#include "Request/PreUpdateCurrentModelMasterRequest.h"
#include "Task/Rest/PreUpdateCurrentModelMasterTask.h"
#include "Request/UpdateCurrentModelMasterRequest.h"
#include "Task/Rest/UpdateCurrentModelMasterTask.h"
#include "Request/UpdateCurrentModelMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentModelMasterFromGitHubTask.h"
#include "Request/DescribeDailyTransactionHistoriesByCurrencyRequest.h"
#include "Task/Rest/DescribeDailyTransactionHistoriesByCurrencyTask.h"
#include "Request/DescribeDailyTransactionHistoriesRequest.h"
#include "Task/Rest/DescribeDailyTransactionHistoriesTask.h"
#include "Request/GetDailyTransactionHistoryRequest.h"
#include "Task/Rest/GetDailyTransactionHistoryTask.h"
#include "Request/DescribeUnusedBalancesRequest.h"
#include "Task/Rest/DescribeUnusedBalancesTask.h"
#include "Request/GetUnusedBalanceRequest.h"
#include "Task/Rest/GetUnusedBalanceTask.h"

namespace Gs2::Money2
{
    class GS2MONEY2_API FGs2Money2RestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2Money2RestClient(
            const Core::Net::Rest::FGs2RestSessionPtr Session
        ): FAbstractGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> DescribeNamespaces(
            const Request::FDescribeNamespacesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> CreateNamespace(
            const Request::FCreateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> GetNamespaceStatus(
            const Request::FGetNamespaceStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> GetNamespace(
            const Request::FGetNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> UpdateNamespace(
            const Request::FUpdateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> DeleteNamespace(
            const Request::FDeleteNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetServiceVersionTask>> GetServiceVersion(
            const Request::FGetServiceVersionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDumpUserDataByUserIdTask>> DumpUserDataByUserId(
            const Request::FDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckDumpUserDataByUserIdTask>> CheckDumpUserDataByUserId(
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCleanUserDataByUserIdTask>> CleanUserDataByUserId(
            const Request::FCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckCleanUserDataByUserIdTask>> CheckCleanUserDataByUserId(
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareImportUserDataByUserIdTask>> PrepareImportUserDataByUserId(
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FImportUserDataByUserIdTask>> ImportUserDataByUserId(
            const Request::FImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckImportUserDataByUserIdTask>> CheckImportUserDataByUserId(
            const Request::FCheckImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeWalletsTask>> DescribeWallets(
            const Request::FDescribeWalletsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeWalletsByUserIdTask>> DescribeWalletsByUserId(
            const Request::FDescribeWalletsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetWalletTask>> GetWallet(
            const Request::FGetWalletRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetWalletByUserIdTask>> GetWalletByUserId(
            const Request::FGetWalletByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDepositByUserIdTask>> DepositByUserId(
            const Request::FDepositByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FWithdrawTask>> Withdraw(
            const Request::FWithdrawRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FWithdrawByUserIdTask>> WithdrawByUserId(
            const Request::FWithdrawByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDepositByStampSheetTask>> DepositByStampSheet(
            const Request::FDepositByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FWithdrawByStampTaskTask>> WithdrawByStampTask(
            const Request::FWithdrawByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeEventsByUserIdTask>> DescribeEventsByUserId(
            const Request::FDescribeEventsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetEventByTransactionIdTask>> GetEventByTransactionId(
            const Request::FGetEventByTransactionIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyReceiptTask>> VerifyReceipt(
            const Request::FVerifyReceiptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyReceiptByUserIdTask>> VerifyReceiptByUserId(
            const Request::FVerifyReceiptByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyReceiptByStampTaskTask>> VerifyReceiptByStampTask(
            const Request::FVerifyReceiptByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscriptionStatusesTask>> DescribeSubscriptionStatuses(
            const Request::FDescribeSubscriptionStatusesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscriptionStatusesByUserIdTask>> DescribeSubscriptionStatusesByUserId(
            const Request::FDescribeSubscriptionStatusesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSubscriptionStatusTask>> GetSubscriptionStatus(
            const Request::FGetSubscriptionStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSubscriptionStatusByUserIdTask>> GetSubscriptionStatusByUserId(
            const Request::FGetSubscriptionStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAllocateSubscriptionStatusTask>> AllocateSubscriptionStatus(
            const Request::FAllocateSubscriptionStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAllocateSubscriptionStatusByUserIdTask>> AllocateSubscriptionStatusByUserId(
            const Request::FAllocateSubscriptionStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FTakeoverSubscriptionStatusTask>> TakeoverSubscriptionStatus(
            const Request::FTakeoverSubscriptionStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FTakeoverSubscriptionStatusByUserIdTask>> TakeoverSubscriptionStatusByUserId(
            const Request::FTakeoverSubscriptionStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRefundHistoriesByUserIdTask>> DescribeRefundHistoriesByUserId(
            const Request::FDescribeRefundHistoriesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRefundHistoriesByDateTask>> DescribeRefundHistoriesByDate(
            const Request::FDescribeRefundHistoriesByDateRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRefundHistoryTask>> GetRefundHistory(
            const Request::FGetRefundHistoryRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeStoreContentModelsTask>> DescribeStoreContentModels(
            const Request::FDescribeStoreContentModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStoreContentModelTask>> GetStoreContentModel(
            const Request::FGetStoreContentModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeStoreContentModelMastersTask>> DescribeStoreContentModelMasters(
            const Request::FDescribeStoreContentModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateStoreContentModelMasterTask>> CreateStoreContentModelMaster(
            const Request::FCreateStoreContentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStoreContentModelMasterTask>> GetStoreContentModelMaster(
            const Request::FGetStoreContentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateStoreContentModelMasterTask>> UpdateStoreContentModelMaster(
            const Request::FUpdateStoreContentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteStoreContentModelMasterTask>> DeleteStoreContentModelMaster(
            const Request::FDeleteStoreContentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeStoreSubscriptionContentModelsTask>> DescribeStoreSubscriptionContentModels(
            const Request::FDescribeStoreSubscriptionContentModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStoreSubscriptionContentModelTask>> GetStoreSubscriptionContentModel(
            const Request::FGetStoreSubscriptionContentModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeStoreSubscriptionContentModelMastersTask>> DescribeStoreSubscriptionContentModelMasters(
            const Request::FDescribeStoreSubscriptionContentModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateStoreSubscriptionContentModelMasterTask>> CreateStoreSubscriptionContentModelMaster(
            const Request::FCreateStoreSubscriptionContentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStoreSubscriptionContentModelMasterTask>> GetStoreSubscriptionContentModelMaster(
            const Request::FGetStoreSubscriptionContentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateStoreSubscriptionContentModelMasterTask>> UpdateStoreSubscriptionContentModelMaster(
            const Request::FUpdateStoreSubscriptionContentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteStoreSubscriptionContentModelMasterTask>> DeleteStoreSubscriptionContentModelMaster(
            const Request::FDeleteStoreSubscriptionContentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentModelMasterTask>> GetCurrentModelMaster(
            const Request::FGetCurrentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPreUpdateCurrentModelMasterTask>> PreUpdateCurrentModelMaster(
            const Request::FPreUpdateCurrentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentModelMasterTask>> UpdateCurrentModelMaster(
            const Request::FUpdateCurrentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentModelMasterFromGitHubTask>> UpdateCurrentModelMasterFromGitHub(
            const Request::FUpdateCurrentModelMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeDailyTransactionHistoriesByCurrencyTask>> DescribeDailyTransactionHistoriesByCurrency(
            const Request::FDescribeDailyTransactionHistoriesByCurrencyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeDailyTransactionHistoriesTask>> DescribeDailyTransactionHistories(
            const Request::FDescribeDailyTransactionHistoriesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetDailyTransactionHistoryTask>> GetDailyTransactionHistory(
            const Request::FGetDailyTransactionHistoryRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeUnusedBalancesTask>> DescribeUnusedBalances(
            const Request::FDescribeUnusedBalancesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetUnusedBalanceTask>> GetUnusedBalance(
            const Request::FGetUnusedBalanceRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2Money2RestClient, ESPMode::ThreadSafe> FGs2Money2RestClientPtr;
}