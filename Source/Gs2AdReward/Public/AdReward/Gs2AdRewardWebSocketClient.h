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
#include "Request/GetPointRequest.h"
#include "Task/WebSocket/GetPointTask.h"
#include "Request/GetPointByUserIdRequest.h"
#include "Task/WebSocket/GetPointByUserIdTask.h"
#include "Request/AcquirePointByUserIdRequest.h"
#include "Task/WebSocket/AcquirePointByUserIdTask.h"
#include "Request/ConsumePointRequest.h"
#include "Task/WebSocket/ConsumePointTask.h"
#include "Request/ConsumePointByUserIdRequest.h"
#include "Task/WebSocket/ConsumePointByUserIdTask.h"
#include "Request/DeletePointByUserIdRequest.h"
#include "Task/WebSocket/DeletePointByUserIdTask.h"
#include "Request/ConsumePointByStampTaskRequest.h"
#include "Task/WebSocket/ConsumePointByStampTaskTask.h"
#include "Request/AcquirePointByStampSheetRequest.h"
#include "Task/WebSocket/AcquirePointByStampSheetTask.h"

namespace Gs2::AdReward
{
    class GS2ADREWARD_API FGs2AdRewardWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2AdRewardWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetPointTask>> GetPoint(
            const Request::FGetPointRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetPointByUserIdTask>> GetPointByUserId(
            const Request::FGetPointByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquirePointByUserIdTask>> AcquirePointByUserId(
            const Request::FAcquirePointByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FConsumePointTask>> ConsumePoint(
            const Request::FConsumePointRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FConsumePointByUserIdTask>> ConsumePointByUserId(
            const Request::FConsumePointByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeletePointByUserIdTask>> DeletePointByUserId(
            const Request::FDeletePointByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FConsumePointByStampTaskTask>> ConsumePointByStampTask(
            const Request::FConsumePointByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquirePointByStampSheetTask>> AcquirePointByStampSheet(
            const Request::FAcquirePointByStampSheetRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2AdRewardWebSocketClient, ESPMode::ThreadSafe> FGs2AdRewardWebSocketClientPtr;
}