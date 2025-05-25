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
#include "Request/DescribeReceiptsRequest.h"
#include "Task/Rest/DescribeReceiptsTask.h"
#include "Request/GetByUserIdAndTransactionIdRequest.h"
#include "Task/Rest/GetByUserIdAndTransactionIdTask.h"
#include "Request/RecordReceiptRequest.h"
#include "Task/Rest/RecordReceiptTask.h"
#include "Request/RevertRecordReceiptRequest.h"
#include "Task/Rest/RevertRecordReceiptTask.h"
#include "Request/RecordReceiptByStampTaskRequest.h"
#include "Task/Rest/RecordReceiptByStampTaskTask.h"
#include "Request/RevertRecordReceiptByStampSheetRequest.h"
#include "Task/Rest/RevertRecordReceiptByStampSheetTask.h"

namespace Gs2::Money
{
    class GS2MONEY_API FGs2MoneyRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2MoneyRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeReceiptsTask>> DescribeReceipts(
            const Request::FDescribeReceiptsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetByUserIdAndTransactionIdTask>> GetByUserIdAndTransactionId(
            const Request::FGetByUserIdAndTransactionIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRecordReceiptTask>> RecordReceipt(
            const Request::FRecordReceiptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRevertRecordReceiptTask>> RevertRecordReceipt(
            const Request::FRevertRecordReceiptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRecordReceiptByStampTaskTask>> RecordReceiptByStampTask(
            const Request::FRecordReceiptByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRevertRecordReceiptByStampSheetTask>> RevertRecordReceiptByStampSheet(
            const Request::FRevertRecordReceiptByStampSheetRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2MoneyRestClient, ESPMode::ThreadSafe> FGs2MoneyRestClientPtr;
}