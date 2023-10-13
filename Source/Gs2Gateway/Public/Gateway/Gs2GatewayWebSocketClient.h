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
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/DumpUserDataByUserIdTask.h"
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckDumpUserDataByUserIdTask.h"
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CleanUserDataByUserIdTask.h"
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckCleanUserDataByUserIdTask.h"
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/PrepareImportUserDataByUserIdTask.h"
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/ImportUserDataByUserIdTask.h"
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckImportUserDataByUserIdTask.h"
#include "Request/DescribeWebSocketSessionsRequest.h"
#include "Task/WebSocket/DescribeWebSocketSessionsTask.h"
#include "Request/DescribeWebSocketSessionsByUserIdRequest.h"
#include "Task/WebSocket/DescribeWebSocketSessionsByUserIdTask.h"
#include "Request/SetUserIdRequest.h"
#include "Task/WebSocket/SetUserIdTask.h"
#include "Request/SetUserIdByUserIdRequest.h"
#include "Task/WebSocket/SetUserIdByUserIdTask.h"
#include "Request/SendNotificationRequest.h"
#include "Task/WebSocket/SendNotificationTask.h"
#include "Request/DisconnectByUserIdRequest.h"
#include "Task/WebSocket/DisconnectByUserIdTask.h"
#include "Request/DisconnectAllRequest.h"
#include "Task/WebSocket/DisconnectAllTask.h"
#include "Request/SetFirebaseTokenRequest.h"
#include "Task/WebSocket/SetFirebaseTokenTask.h"
#include "Request/SetFirebaseTokenByUserIdRequest.h"
#include "Task/WebSocket/SetFirebaseTokenByUserIdTask.h"
#include "Request/GetFirebaseTokenRequest.h"
#include "Task/WebSocket/GetFirebaseTokenTask.h"
#include "Request/GetFirebaseTokenByUserIdRequest.h"
#include "Task/WebSocket/GetFirebaseTokenByUserIdTask.h"
#include "Request/DeleteFirebaseTokenRequest.h"
#include "Task/WebSocket/DeleteFirebaseTokenTask.h"
#include "Request/DeleteFirebaseTokenByUserIdRequest.h"
#include "Task/WebSocket/DeleteFirebaseTokenByUserIdTask.h"
#include "Request/SendMobileNotificationByUserIdRequest.h"
#include "Task/WebSocket/SendMobileNotificationByUserIdTask.h"

namespace Gs2::Gateway
{
    class GS2GATEWAY_API FGs2GatewayWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2GatewayWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>> DumpUserDataByUserId(
            const Request::FDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>> CheckDumpUserDataByUserId(
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>> CleanUserDataByUserId(
            const Request::FCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>> CheckCleanUserDataByUserId(
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>> PrepareImportUserDataByUserId(
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>> ImportUserDataByUserId(
            const Request::FImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>> CheckImportUserDataByUserId(
            const Request::FCheckImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeWebSocketSessionsTask>> DescribeWebSocketSessions(
            const Request::FDescribeWebSocketSessionsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeWebSocketSessionsByUserIdTask>> DescribeWebSocketSessionsByUserId(
            const Request::FDescribeWebSocketSessionsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetUserIdTask>> SetUserId(
            const Request::FSetUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetUserIdByUserIdTask>> SetUserIdByUserId(
            const Request::FSetUserIdByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSendNotificationTask>> SendNotification(
            const Request::FSendNotificationRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDisconnectByUserIdTask>> DisconnectByUserId(
            const Request::FDisconnectByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDisconnectAllTask>> DisconnectAll(
            const Request::FDisconnectAllRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetFirebaseTokenTask>> SetFirebaseToken(
            const Request::FSetFirebaseTokenRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetFirebaseTokenByUserIdTask>> SetFirebaseTokenByUserId(
            const Request::FSetFirebaseTokenByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetFirebaseTokenTask>> GetFirebaseToken(
            const Request::FGetFirebaseTokenRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetFirebaseTokenByUserIdTask>> GetFirebaseTokenByUserId(
            const Request::FGetFirebaseTokenByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteFirebaseTokenTask>> DeleteFirebaseToken(
            const Request::FDeleteFirebaseTokenRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteFirebaseTokenByUserIdTask>> DeleteFirebaseTokenByUserId(
            const Request::FDeleteFirebaseTokenByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSendMobileNotificationByUserIdTask>> SendMobileNotificationByUserId(
            const Request::FSendMobileNotificationByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2GatewayWebSocketClient, ESPMode::ThreadSafe> FGs2GatewayWebSocketClientPtr;
}