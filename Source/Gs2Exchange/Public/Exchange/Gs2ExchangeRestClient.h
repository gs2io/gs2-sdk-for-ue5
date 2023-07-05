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
#include "Request/DescribeRateModelsRequest.h"
#include "Task/Rest/DescribeRateModelsTask.h"
#include "Request/GetRateModelRequest.h"
#include "Task/Rest/GetRateModelTask.h"
#include "Request/DescribeRateModelMastersRequest.h"
#include "Task/Rest/DescribeRateModelMastersTask.h"
#include "Request/CreateRateModelMasterRequest.h"
#include "Task/Rest/CreateRateModelMasterTask.h"
#include "Request/GetRateModelMasterRequest.h"
#include "Task/Rest/GetRateModelMasterTask.h"
#include "Request/UpdateRateModelMasterRequest.h"
#include "Task/Rest/UpdateRateModelMasterTask.h"
#include "Request/DeleteRateModelMasterRequest.h"
#include "Task/Rest/DeleteRateModelMasterTask.h"
#include "Request/DescribeIncrementalRateModelsRequest.h"
#include "Task/Rest/DescribeIncrementalRateModelsTask.h"
#include "Request/GetIncrementalRateModelRequest.h"
#include "Task/Rest/GetIncrementalRateModelTask.h"
#include "Request/DescribeIncrementalRateModelMastersRequest.h"
#include "Task/Rest/DescribeIncrementalRateModelMastersTask.h"
#include "Request/CreateIncrementalRateModelMasterRequest.h"
#include "Task/Rest/CreateIncrementalRateModelMasterTask.h"
#include "Request/GetIncrementalRateModelMasterRequest.h"
#include "Task/Rest/GetIncrementalRateModelMasterTask.h"
#include "Request/UpdateIncrementalRateModelMasterRequest.h"
#include "Task/Rest/UpdateIncrementalRateModelMasterTask.h"
#include "Request/DeleteIncrementalRateModelMasterRequest.h"
#include "Task/Rest/DeleteIncrementalRateModelMasterTask.h"
#include "Request/ExchangeRequest.h"
#include "Task/Rest/ExchangeTask.h"
#include "Request/ExchangeByUserIdRequest.h"
#include "Task/Rest/ExchangeByUserIdTask.h"
#include "Request/ExchangeByStampSheetRequest.h"
#include "Task/Rest/ExchangeByStampSheetTask.h"
#include "Request/IncrementalExchangeRequest.h"
#include "Task/Rest/IncrementalExchangeTask.h"
#include "Request/IncrementalExchangeByUserIdRequest.h"
#include "Task/Rest/IncrementalExchangeByUserIdTask.h"
#include "Request/IncrementalExchangeByStampSheetRequest.h"
#include "Task/Rest/IncrementalExchangeByStampSheetTask.h"
#include "Request/UnlockIncrementalExchangeByUserIdRequest.h"
#include "Task/Rest/UnlockIncrementalExchangeByUserIdTask.h"
#include "Request/UnlockIncrementalExchangeByStampSheetRequest.h"
#include "Task/Rest/UnlockIncrementalExchangeByStampSheetTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentRateMasterRequest.h"
#include "Task/Rest/GetCurrentRateMasterTask.h"
#include "Request/UpdateCurrentRateMasterRequest.h"
#include "Task/Rest/UpdateCurrentRateMasterTask.h"
#include "Request/UpdateCurrentRateMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentRateMasterFromGitHubTask.h"
#include "Request/CreateAwaitByUserIdRequest.h"
#include "Task/Rest/CreateAwaitByUserIdTask.h"
#include "Request/DescribeAwaitsRequest.h"
#include "Task/Rest/DescribeAwaitsTask.h"
#include "Request/DescribeAwaitsByUserIdRequest.h"
#include "Task/Rest/DescribeAwaitsByUserIdTask.h"
#include "Request/GetAwaitRequest.h"
#include "Task/Rest/GetAwaitTask.h"
#include "Request/GetAwaitByUserIdRequest.h"
#include "Task/Rest/GetAwaitByUserIdTask.h"
#include "Request/AcquireRequest.h"
#include "Task/Rest/AcquireTask.h"
#include "Request/AcquireByUserIdRequest.h"
#include "Task/Rest/AcquireByUserIdTask.h"
#include "Request/AcquireForceByUserIdRequest.h"
#include "Task/Rest/AcquireForceByUserIdTask.h"
#include "Request/SkipRequest.h"
#include "Task/Rest/SkipTask.h"
#include "Request/SkipByUserIdRequest.h"
#include "Task/Rest/SkipByUserIdTask.h"
#include "Request/DeleteAwaitRequest.h"
#include "Task/Rest/DeleteAwaitTask.h"
#include "Request/DeleteAwaitByUserIdRequest.h"
#include "Task/Rest/DeleteAwaitByUserIdTask.h"
#include "Request/CreateAwaitByStampSheetRequest.h"
#include "Task/Rest/CreateAwaitByStampSheetTask.h"
#include "Request/DeleteAwaitByStampTaskRequest.h"
#include "Task/Rest/DeleteAwaitByStampTaskTask.h"

namespace Gs2::Exchange
{
    class GS2EXCHANGE_API FGs2ExchangeRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2ExchangeRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRateModelsTask>> DescribeRateModels(
            const Request::FDescribeRateModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRateModelTask>> GetRateModel(
            const Request::FGetRateModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRateModelMastersTask>> DescribeRateModelMasters(
            const Request::FDescribeRateModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateRateModelMasterTask>> CreateRateModelMaster(
            const Request::FCreateRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRateModelMasterTask>> GetRateModelMaster(
            const Request::FGetRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateRateModelMasterTask>> UpdateRateModelMaster(
            const Request::FUpdateRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteRateModelMasterTask>> DeleteRateModelMaster(
            const Request::FDeleteRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeIncrementalRateModelsTask>> DescribeIncrementalRateModels(
            const Request::FDescribeIncrementalRateModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetIncrementalRateModelTask>> GetIncrementalRateModel(
            const Request::FGetIncrementalRateModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeIncrementalRateModelMastersTask>> DescribeIncrementalRateModelMasters(
            const Request::FDescribeIncrementalRateModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateIncrementalRateModelMasterTask>> CreateIncrementalRateModelMaster(
            const Request::FCreateIncrementalRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetIncrementalRateModelMasterTask>> GetIncrementalRateModelMaster(
            const Request::FGetIncrementalRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateIncrementalRateModelMasterTask>> UpdateIncrementalRateModelMaster(
            const Request::FUpdateIncrementalRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteIncrementalRateModelMasterTask>> DeleteIncrementalRateModelMaster(
            const Request::FDeleteIncrementalRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExchangeTask>> Exchange(
            const Request::FExchangeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExchangeByUserIdTask>> ExchangeByUserId(
            const Request::FExchangeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExchangeByStampSheetTask>> ExchangeByStampSheet(
            const Request::FExchangeByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FIncrementalExchangeTask>> IncrementalExchange(
            const Request::FIncrementalExchangeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FIncrementalExchangeByUserIdTask>> IncrementalExchangeByUserId(
            const Request::FIncrementalExchangeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FIncrementalExchangeByStampSheetTask>> IncrementalExchangeByStampSheet(
            const Request::FIncrementalExchangeByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUnlockIncrementalExchangeByUserIdTask>> UnlockIncrementalExchangeByUserId(
            const Request::FUnlockIncrementalExchangeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUnlockIncrementalExchangeByStampSheetTask>> UnlockIncrementalExchangeByStampSheet(
            const Request::FUnlockIncrementalExchangeByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentRateMasterTask>> GetCurrentRateMaster(
            const Request::FGetCurrentRateMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentRateMasterTask>> UpdateCurrentRateMaster(
            const Request::FUpdateCurrentRateMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentRateMasterFromGitHubTask>> UpdateCurrentRateMasterFromGitHub(
            const Request::FUpdateCurrentRateMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateAwaitByUserIdTask>> CreateAwaitByUserId(
            const Request::FCreateAwaitByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeAwaitsTask>> DescribeAwaits(
            const Request::FDescribeAwaitsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeAwaitsByUserIdTask>> DescribeAwaitsByUserId(
            const Request::FDescribeAwaitsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetAwaitTask>> GetAwait(
            const Request::FGetAwaitRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetAwaitByUserIdTask>> GetAwaitByUserId(
            const Request::FGetAwaitByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAcquireTask>> Acquire(
            const Request::FAcquireRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAcquireByUserIdTask>> AcquireByUserId(
            const Request::FAcquireByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAcquireForceByUserIdTask>> AcquireForceByUserId(
            const Request::FAcquireForceByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSkipTask>> Skip(
            const Request::FSkipRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSkipByUserIdTask>> SkipByUserId(
            const Request::FSkipByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteAwaitTask>> DeleteAwait(
            const Request::FDeleteAwaitRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteAwaitByUserIdTask>> DeleteAwaitByUserId(
            const Request::FDeleteAwaitByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateAwaitByStampSheetTask>> CreateAwaitByStampSheet(
            const Request::FCreateAwaitByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteAwaitByStampTaskTask>> DeleteAwaitByStampTask(
            const Request::FDeleteAwaitByStampTaskRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2ExchangeRestClient, ESPMode::ThreadSafe> FGs2ExchangeRestClientPtr;
}