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
#include "Request/DescribeRateModelsRequest.h"
#include "Task/WebSocket/DescribeRateModelsTask.h"
#include "Request/GetRateModelRequest.h"
#include "Task/WebSocket/GetRateModelTask.h"
#include "Request/DescribeRateModelMastersRequest.h"
#include "Task/WebSocket/DescribeRateModelMastersTask.h"
#include "Request/CreateRateModelMasterRequest.h"
#include "Task/WebSocket/CreateRateModelMasterTask.h"
#include "Request/GetRateModelMasterRequest.h"
#include "Task/WebSocket/GetRateModelMasterTask.h"
#include "Request/UpdateRateModelMasterRequest.h"
#include "Task/WebSocket/UpdateRateModelMasterTask.h"
#include "Request/DeleteRateModelMasterRequest.h"
#include "Task/WebSocket/DeleteRateModelMasterTask.h"
#include "Request/ExchangeRequest.h"
#include "Task/WebSocket/ExchangeTask.h"
#include "Request/ExchangeByUserIdRequest.h"
#include "Task/WebSocket/ExchangeByUserIdTask.h"
#include "Request/ExchangeByStampSheetRequest.h"
#include "Task/WebSocket/ExchangeByStampSheetTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentRateMasterRequest.h"
#include "Task/WebSocket/GetCurrentRateMasterTask.h"
#include "Request/UpdateCurrentRateMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentRateMasterTask.h"
#include "Request/UpdateCurrentRateMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentRateMasterFromGitHubTask.h"
#include "Request/CreateAwaitByUserIdRequest.h"
#include "Task/WebSocket/CreateAwaitByUserIdTask.h"
#include "Request/DescribeAwaitsRequest.h"
#include "Task/WebSocket/DescribeAwaitsTask.h"
#include "Request/DescribeAwaitsByUserIdRequest.h"
#include "Task/WebSocket/DescribeAwaitsByUserIdTask.h"
#include "Request/GetAwaitRequest.h"
#include "Task/WebSocket/GetAwaitTask.h"
#include "Request/GetAwaitByUserIdRequest.h"
#include "Task/WebSocket/GetAwaitByUserIdTask.h"
#include "Request/AcquireRequest.h"
#include "Task/WebSocket/AcquireTask.h"
#include "Request/AcquireByUserIdRequest.h"
#include "Task/WebSocket/AcquireByUserIdTask.h"
#include "Request/AcquireForceByUserIdRequest.h"
#include "Task/WebSocket/AcquireForceByUserIdTask.h"
#include "Request/SkipRequest.h"
#include "Task/WebSocket/SkipTask.h"
#include "Request/SkipByUserIdRequest.h"
#include "Task/WebSocket/SkipByUserIdTask.h"
#include "Request/DeleteAwaitRequest.h"
#include "Task/WebSocket/DeleteAwaitTask.h"
#include "Request/DeleteAwaitByUserIdRequest.h"
#include "Task/WebSocket/DeleteAwaitByUserIdTask.h"
#include "Request/CreateAwaitByStampSheetRequest.h"
#include "Task/WebSocket/CreateAwaitByStampSheetTask.h"
#include "Request/DeleteAwaitByStampTaskRequest.h"
#include "Task/WebSocket/DeleteAwaitByStampTaskTask.h"

namespace Gs2::Exchange
{
    class GS2EXCHANGE_API FGs2ExchangeWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2ExchangeWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRateModelsTask>> DescribeRateModels(
            const Request::FDescribeRateModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRateModelTask>> GetRateModel(
            const Request::FGetRateModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRateModelMastersTask>> DescribeRateModelMasters(
            const Request::FDescribeRateModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateRateModelMasterTask>> CreateRateModelMaster(
            const Request::FCreateRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRateModelMasterTask>> GetRateModelMaster(
            const Request::FGetRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateRateModelMasterTask>> UpdateRateModelMaster(
            const Request::FUpdateRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRateModelMasterTask>> DeleteRateModelMaster(
            const Request::FDeleteRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExchangeTask>> Exchange(
            const Request::FExchangeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExchangeByUserIdTask>> ExchangeByUserId(
            const Request::FExchangeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExchangeByStampSheetTask>> ExchangeByStampSheet(
            const Request::FExchangeByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentRateMasterTask>> GetCurrentRateMaster(
            const Request::FGetCurrentRateMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentRateMasterTask>> UpdateCurrentRateMaster(
            const Request::FUpdateCurrentRateMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentRateMasterFromGitHubTask>> UpdateCurrentRateMasterFromGitHub(
            const Request::FUpdateCurrentRateMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateAwaitByUserIdTask>> CreateAwaitByUserId(
            const Request::FCreateAwaitByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeAwaitsTask>> DescribeAwaits(
            const Request::FDescribeAwaitsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeAwaitsByUserIdTask>> DescribeAwaitsByUserId(
            const Request::FDescribeAwaitsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetAwaitTask>> GetAwait(
            const Request::FGetAwaitRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetAwaitByUserIdTask>> GetAwaitByUserId(
            const Request::FGetAwaitByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireTask>> Acquire(
            const Request::FAcquireRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireByUserIdTask>> AcquireByUserId(
            const Request::FAcquireByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireForceByUserIdTask>> AcquireForceByUserId(
            const Request::FAcquireForceByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSkipTask>> Skip(
            const Request::FSkipRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSkipByUserIdTask>> SkipByUserId(
            const Request::FSkipByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteAwaitTask>> DeleteAwait(
            const Request::FDeleteAwaitRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteAwaitByUserIdTask>> DeleteAwaitByUserId(
            const Request::FDeleteAwaitByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateAwaitByStampSheetTask>> CreateAwaitByStampSheet(
            const Request::FCreateAwaitByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteAwaitByStampTaskTask>> DeleteAwaitByStampTask(
            const Request::FDeleteAwaitByStampTaskRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2ExchangeWebSocketClient, ESPMode::ThreadSafe> FGs2ExchangeWebSocketClientPtr;
}