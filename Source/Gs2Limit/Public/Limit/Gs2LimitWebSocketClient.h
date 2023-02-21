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
#include "Request/DescribeCountersRequest.h"
#include "Task/WebSocket/DescribeCountersTask.h"
#include "Request/DescribeCountersByUserIdRequest.h"
#include "Task/WebSocket/DescribeCountersByUserIdTask.h"
#include "Request/GetCounterRequest.h"
#include "Task/WebSocket/GetCounterTask.h"
#include "Request/GetCounterByUserIdRequest.h"
#include "Task/WebSocket/GetCounterByUserIdTask.h"
#include "Request/CountUpRequest.h"
#include "Task/WebSocket/CountUpTask.h"
#include "Request/CountUpByUserIdRequest.h"
#include "Task/WebSocket/CountUpByUserIdTask.h"
#include "Request/DeleteCounterByUserIdRequest.h"
#include "Task/WebSocket/DeleteCounterByUserIdTask.h"
#include "Request/CountUpByStampTaskRequest.h"
#include "Task/WebSocket/CountUpByStampTaskTask.h"
#include "Request/DeleteByStampSheetRequest.h"
#include "Task/WebSocket/DeleteByStampSheetTask.h"
#include "Request/DescribeLimitModelMastersRequest.h"
#include "Task/WebSocket/DescribeLimitModelMastersTask.h"
#include "Request/CreateLimitModelMasterRequest.h"
#include "Task/WebSocket/CreateLimitModelMasterTask.h"
#include "Request/GetLimitModelMasterRequest.h"
#include "Task/WebSocket/GetLimitModelMasterTask.h"
#include "Request/UpdateLimitModelMasterRequest.h"
#include "Task/WebSocket/UpdateLimitModelMasterTask.h"
#include "Request/DeleteLimitModelMasterRequest.h"
#include "Task/WebSocket/DeleteLimitModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentLimitMasterRequest.h"
#include "Task/WebSocket/GetCurrentLimitMasterTask.h"
#include "Request/UpdateCurrentLimitMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentLimitMasterTask.h"
#include "Request/UpdateCurrentLimitMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentLimitMasterFromGitHubTask.h"
#include "Request/DescribeLimitModelsRequest.h"
#include "Task/WebSocket/DescribeLimitModelsTask.h"
#include "Request/GetLimitModelRequest.h"
#include "Task/WebSocket/GetLimitModelTask.h"

namespace Gs2::Limit
{
    class GS2LIMIT_API FGs2LimitWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2LimitWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCountersTask>> DescribeCounters(
            const Request::FDescribeCountersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCountersByUserIdTask>> DescribeCountersByUserId(
            const Request::FDescribeCountersByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCounterTask>> GetCounter(
            const Request::FGetCounterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCounterByUserIdTask>> GetCounterByUserId(
            const Request::FGetCounterByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCountUpTask>> CountUp(
            const Request::FCountUpRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCountUpByUserIdTask>> CountUpByUserId(
            const Request::FCountUpByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteCounterByUserIdTask>> DeleteCounterByUserId(
            const Request::FDeleteCounterByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCountUpByStampTaskTask>> CountUpByStampTask(
            const Request::FCountUpByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteByStampSheetTask>> DeleteByStampSheet(
            const Request::FDeleteByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeLimitModelMastersTask>> DescribeLimitModelMasters(
            const Request::FDescribeLimitModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateLimitModelMasterTask>> CreateLimitModelMaster(
            const Request::FCreateLimitModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetLimitModelMasterTask>> GetLimitModelMaster(
            const Request::FGetLimitModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateLimitModelMasterTask>> UpdateLimitModelMaster(
            const Request::FUpdateLimitModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteLimitModelMasterTask>> DeleteLimitModelMaster(
            const Request::FDeleteLimitModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentLimitMasterTask>> GetCurrentLimitMaster(
            const Request::FGetCurrentLimitMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentLimitMasterTask>> UpdateCurrentLimitMaster(
            const Request::FUpdateCurrentLimitMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentLimitMasterFromGitHubTask>> UpdateCurrentLimitMasterFromGitHub(
            const Request::FUpdateCurrentLimitMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeLimitModelsTask>> DescribeLimitModels(
            const Request::FDescribeLimitModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetLimitModelTask>> GetLimitModel(
            const Request::FGetLimitModelRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2LimitWebSocketClient, ESPMode::ThreadSafe> FGs2LimitWebSocketClientPtr;
}