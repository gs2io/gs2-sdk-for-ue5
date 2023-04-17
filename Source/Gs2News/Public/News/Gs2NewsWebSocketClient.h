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
#include "Request/DescribeProgressesRequest.h"
#include "Task/WebSocket/DescribeProgressesTask.h"
#include "Request/GetProgressRequest.h"
#include "Task/WebSocket/GetProgressTask.h"
#include "Request/DescribeOutputsRequest.h"
#include "Task/WebSocket/DescribeOutputsTask.h"
#include "Request/GetOutputRequest.h"
#include "Task/WebSocket/GetOutputTask.h"
#include "Request/PrepareUpdateCurrentNewsMasterRequest.h"
#include "Task/WebSocket/PrepareUpdateCurrentNewsMasterTask.h"
#include "Request/UpdateCurrentNewsMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentNewsMasterTask.h"
#include "Request/PrepareUpdateCurrentNewsMasterFromGitHubRequest.h"
#include "Task/WebSocket/PrepareUpdateCurrentNewsMasterFromGitHubTask.h"
#include "Request/DescribeNewsRequest.h"
#include "Task/WebSocket/DescribeNewsTask.h"
#include "Request/DescribeNewsByUserIdRequest.h"
#include "Task/WebSocket/DescribeNewsByUserIdTask.h"
#include "Request/WantGrantRequest.h"
#include "Task/WebSocket/WantGrantTask.h"
#include "Request/WantGrantByUserIdRequest.h"
#include "Task/WebSocket/WantGrantByUserIdTask.h"

namespace Gs2::News
{
    class GS2NEWS_API FGs2NewsWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2NewsWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeProgressesTask>> DescribeProgresses(
            const Request::FDescribeProgressesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetProgressTask>> GetProgress(
            const Request::FGetProgressRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeOutputsTask>> DescribeOutputs(
            const Request::FDescribeOutputsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetOutputTask>> GetOutput(
            const Request::FGetOutputRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareUpdateCurrentNewsMasterTask>> PrepareUpdateCurrentNewsMaster(
            const Request::FPrepareUpdateCurrentNewsMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentNewsMasterTask>> UpdateCurrentNewsMaster(
            const Request::FUpdateCurrentNewsMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareUpdateCurrentNewsMasterFromGitHubTask>> PrepareUpdateCurrentNewsMasterFromGitHub(
            const Request::FPrepareUpdateCurrentNewsMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNewsTask>> DescribeNews(
            const Request::FDescribeNewsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNewsByUserIdTask>> DescribeNewsByUserId(
            const Request::FDescribeNewsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FWantGrantTask>> WantGrant(
            const Request::FWantGrantRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FWantGrantByUserIdTask>> WantGrantByUserId(
            const Request::FWantGrantByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2NewsWebSocketClient, ESPMode::ThreadSafe> FGs2NewsWebSocketClientPtr;
}