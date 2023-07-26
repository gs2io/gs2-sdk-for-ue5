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
#include "Request/DescribeStateMachineMastersRequest.h"
#include "Task/WebSocket/DescribeStateMachineMastersTask.h"
#include "Request/UpdateStateMachineMasterRequest.h"
#include "Task/WebSocket/UpdateStateMachineMasterTask.h"
#include "Request/GetStateMachineMasterRequest.h"
#include "Task/WebSocket/GetStateMachineMasterTask.h"
#include "Request/DeleteStateMachineMasterRequest.h"
#include "Task/WebSocket/DeleteStateMachineMasterTask.h"
#include "Request/DescribeStatusesRequest.h"
#include "Task/WebSocket/DescribeStatusesTask.h"
#include "Request/DescribeStatusesByUserIdRequest.h"
#include "Task/WebSocket/DescribeStatusesByUserIdTask.h"
#include "Request/GetStatusRequest.h"
#include "Task/WebSocket/GetStatusTask.h"
#include "Request/GetStatusByUserIdRequest.h"
#include "Task/WebSocket/GetStatusByUserIdTask.h"
#include "Request/StartStateMachineByUserIdRequest.h"
#include "Task/WebSocket/StartStateMachineByUserIdTask.h"
#include "Request/StartStateMachineByStampSheetRequest.h"
#include "Task/WebSocket/StartStateMachineByStampSheetTask.h"
#include "Request/EmitRequest.h"
#include "Task/WebSocket/EmitTask.h"
#include "Request/EmitByUserIdRequest.h"
#include "Task/WebSocket/EmitByUserIdTask.h"
#include "Request/DeleteStatusByUserIdRequest.h"
#include "Task/WebSocket/DeleteStatusByUserIdTask.h"
#include "Request/ExitStateMachineRequest.h"
#include "Task/WebSocket/ExitStateMachineTask.h"
#include "Request/ExitStateMachineByUserIdRequest.h"
#include "Task/WebSocket/ExitStateMachineByUserIdTask.h"

namespace Gs2::StateMachine
{
    class GS2STATEMACHINE_API FGs2StateMachineWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2StateMachineWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStateMachineMastersTask>> DescribeStateMachineMasters(
            const Request::FDescribeStateMachineMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateStateMachineMasterTask>> UpdateStateMachineMaster(
            const Request::FUpdateStateMachineMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStateMachineMasterTask>> GetStateMachineMaster(
            const Request::FGetStateMachineMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteStateMachineMasterTask>> DeleteStateMachineMaster(
            const Request::FDeleteStateMachineMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStatusesTask>> DescribeStatuses(
            const Request::FDescribeStatusesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStatusesByUserIdTask>> DescribeStatusesByUserId(
            const Request::FDescribeStatusesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStatusTask>> GetStatus(
            const Request::FGetStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStatusByUserIdTask>> GetStatusByUserId(
            const Request::FGetStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FStartStateMachineByUserIdTask>> StartStateMachineByUserId(
            const Request::FStartStateMachineByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FStartStateMachineByStampSheetTask>> StartStateMachineByStampSheet(
            const Request::FStartStateMachineByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FEmitTask>> Emit(
            const Request::FEmitRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FEmitByUserIdTask>> EmitByUserId(
            const Request::FEmitByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteStatusByUserIdTask>> DeleteStatusByUserId(
            const Request::FDeleteStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExitStateMachineTask>> ExitStateMachine(
            const Request::FExitStateMachineRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExitStateMachineByUserIdTask>> ExitStateMachineByUserId(
            const Request::FExitStateMachineByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2StateMachineWebSocketClient, ESPMode::ThreadSafe> FGs2StateMachineWebSocketClientPtr;
}