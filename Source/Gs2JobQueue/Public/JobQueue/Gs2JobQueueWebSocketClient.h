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
#include "Request/DescribeJobsByUserIdRequest.h"
#include "Task/WebSocket/DescribeJobsByUserIdTask.h"
#include "Request/GetJobByUserIdRequest.h"
#include "Task/WebSocket/GetJobByUserIdTask.h"
#include "Request/PushByUserIdRequest.h"
#include "Task/WebSocket/PushByUserIdTask.h"
#include "Request/RunRequest.h"
#include "Task/WebSocket/RunTask.h"
#include "Request/RunByUserIdRequest.h"
#include "Task/WebSocket/RunByUserIdTask.h"
#include "Request/DeleteJobByUserIdRequest.h"
#include "Task/WebSocket/DeleteJobByUserIdTask.h"
#include "Request/PushByStampSheetRequest.h"
#include "Task/WebSocket/PushByStampSheetTask.h"
#include "Request/GetJobResultRequest.h"
#include "Task/WebSocket/GetJobResultTask.h"
#include "Request/GetJobResultByUserIdRequest.h"
#include "Task/WebSocket/GetJobResultByUserIdTask.h"
#include "Request/DescribeDeadLetterJobsByUserIdRequest.h"
#include "Task/WebSocket/DescribeDeadLetterJobsByUserIdTask.h"
#include "Request/GetDeadLetterJobByUserIdRequest.h"
#include "Task/WebSocket/GetDeadLetterJobByUserIdTask.h"
#include "Request/DeleteDeadLetterJobByUserIdRequest.h"
#include "Task/WebSocket/DeleteDeadLetterJobByUserIdTask.h"

namespace Gs2::JobQueue
{
    class GS2JOBQUEUE_API FGs2JobQueueWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2JobQueueWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeJobsByUserIdTask>> DescribeJobsByUserId(
            const Request::FDescribeJobsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetJobByUserIdTask>> GetJobByUserId(
            const Request::FGetJobByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPushByUserIdTask>> PushByUserId(
            const Request::FPushByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRunTask>> Run(
            const Request::FRunRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRunByUserIdTask>> RunByUserId(
            const Request::FRunByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteJobByUserIdTask>> DeleteJobByUserId(
            const Request::FDeleteJobByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPushByStampSheetTask>> PushByStampSheet(
            const Request::FPushByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetJobResultTask>> GetJobResult(
            const Request::FGetJobResultRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetJobResultByUserIdTask>> GetJobResultByUserId(
            const Request::FGetJobResultByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeDeadLetterJobsByUserIdTask>> DescribeDeadLetterJobsByUserId(
            const Request::FDescribeDeadLetterJobsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetDeadLetterJobByUserIdTask>> GetDeadLetterJobByUserId(
            const Request::FGetDeadLetterJobByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteDeadLetterJobByUserIdTask>> DeleteDeadLetterJobByUserId(
            const Request::FDeleteDeadLetterJobByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2JobQueueWebSocketClient, ESPMode::ThreadSafe> FGs2JobQueueWebSocketClientPtr;
}