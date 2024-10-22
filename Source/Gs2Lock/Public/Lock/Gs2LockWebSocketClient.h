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
#include "Request/LockRequest.h"
#include "Task/WebSocket/LockTask.h"
#include "Request/LockByUserIdRequest.h"
#include "Task/WebSocket/LockByUserIdTask.h"
#include "Request/UnlockRequest.h"
#include "Task/WebSocket/UnlockTask.h"
#include "Request/UnlockByUserIdRequest.h"
#include "Task/WebSocket/UnlockByUserIdTask.h"
#include "Request/GetMutexRequest.h"
#include "Task/WebSocket/GetMutexTask.h"
#include "Request/GetMutexByUserIdRequest.h"
#include "Task/WebSocket/GetMutexByUserIdTask.h"
#include "Request/DeleteMutexByUserIdRequest.h"
#include "Task/WebSocket/DeleteMutexByUserIdTask.h"

namespace Gs2::Lock
{
    class GS2LOCK_API FGs2LockWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2LockWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FLockTask>> Lock(
            const Request::FLockRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FLockByUserIdTask>> LockByUserId(
            const Request::FLockByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUnlockTask>> Unlock(
            const Request::FUnlockRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUnlockByUserIdTask>> UnlockByUserId(
            const Request::FUnlockByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetMutexTask>> GetMutex(
            const Request::FGetMutexRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetMutexByUserIdTask>> GetMutexByUserId(
            const Request::FGetMutexByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMutexByUserIdTask>> DeleteMutexByUserId(
            const Request::FDeleteMutexByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2LockWebSocketClient, ESPMode::ThreadSafe> FGs2LockWebSocketClientPtr;
}