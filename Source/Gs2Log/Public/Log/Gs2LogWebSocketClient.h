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
#include "Request/QueryAccessLogRequest.h"
#include "Task/WebSocket/QueryAccessLogTask.h"
#include "Request/CountAccessLogRequest.h"
#include "Task/WebSocket/CountAccessLogTask.h"
#include "Request/QueryIssueStampSheetLogRequest.h"
#include "Task/WebSocket/QueryIssueStampSheetLogTask.h"
#include "Request/CountIssueStampSheetLogRequest.h"
#include "Task/WebSocket/CountIssueStampSheetLogTask.h"
#include "Request/QueryExecuteStampSheetLogRequest.h"
#include "Task/WebSocket/QueryExecuteStampSheetLogTask.h"
#include "Request/CountExecuteStampSheetLogRequest.h"
#include "Task/WebSocket/CountExecuteStampSheetLogTask.h"
#include "Request/QueryExecuteStampTaskLogRequest.h"
#include "Task/WebSocket/QueryExecuteStampTaskLogTask.h"
#include "Request/CountExecuteStampTaskLogRequest.h"
#include "Task/WebSocket/CountExecuteStampTaskLogTask.h"
#include "Request/QueryInGameLogRequest.h"
#include "Task/WebSocket/QueryInGameLogTask.h"
#include "Request/SendInGameLogRequest.h"
#include "Task/WebSocket/SendInGameLogTask.h"
#include "Request/SendInGameLogByUserIdRequest.h"
#include "Task/WebSocket/SendInGameLogByUserIdTask.h"
#include "Request/QueryAccessLogWithTelemetryRequest.h"
#include "Task/WebSocket/QueryAccessLogWithTelemetryTask.h"
#include "Request/DescribeInsightsRequest.h"
#include "Task/WebSocket/DescribeInsightsTask.h"
#include "Request/CreateInsightRequest.h"
#include "Task/WebSocket/CreateInsightTask.h"
#include "Request/GetInsightRequest.h"
#include "Task/WebSocket/GetInsightTask.h"
#include "Request/DeleteInsightRequest.h"
#include "Task/WebSocket/DeleteInsightTask.h"

namespace Gs2::Log
{
    class GS2LOG_API FGs2LogWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2LogWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FQueryAccessLogTask>> QueryAccessLog(
            const Request::FQueryAccessLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCountAccessLogTask>> CountAccessLog(
            const Request::FCountAccessLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FQueryIssueStampSheetLogTask>> QueryIssueStampSheetLog(
            const Request::FQueryIssueStampSheetLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCountIssueStampSheetLogTask>> CountIssueStampSheetLog(
            const Request::FCountIssueStampSheetLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FQueryExecuteStampSheetLogTask>> QueryExecuteStampSheetLog(
            const Request::FQueryExecuteStampSheetLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCountExecuteStampSheetLogTask>> CountExecuteStampSheetLog(
            const Request::FCountExecuteStampSheetLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FQueryExecuteStampTaskLogTask>> QueryExecuteStampTaskLog(
            const Request::FQueryExecuteStampTaskLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCountExecuteStampTaskLogTask>> CountExecuteStampTaskLog(
            const Request::FCountExecuteStampTaskLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FQueryInGameLogTask>> QueryInGameLog(
            const Request::FQueryInGameLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSendInGameLogTask>> SendInGameLog(
            const Request::FSendInGameLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSendInGameLogByUserIdTask>> SendInGameLogByUserId(
            const Request::FSendInGameLogByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FQueryAccessLogWithTelemetryTask>> QueryAccessLogWithTelemetry(
            const Request::FQueryAccessLogWithTelemetryRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeInsightsTask>> DescribeInsights(
            const Request::FDescribeInsightsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateInsightTask>> CreateInsight(
            const Request::FCreateInsightRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetInsightTask>> GetInsight(
            const Request::FGetInsightRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteInsightTask>> DeleteInsight(
            const Request::FDeleteInsightRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2LogWebSocketClient, ESPMode::ThreadSafe> FGs2LogWebSocketClientPtr;
}