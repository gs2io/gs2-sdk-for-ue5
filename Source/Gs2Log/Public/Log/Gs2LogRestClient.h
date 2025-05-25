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
#include "Request/GetServiceVersionRequest.h"
#include "Task/Rest/GetServiceVersionTask.h"
#include "Request/QueryAccessLogRequest.h"
#include "Task/Rest/QueryAccessLogTask.h"
#include "Request/CountAccessLogRequest.h"
#include "Task/Rest/CountAccessLogTask.h"
#include "Request/QueryIssueStampSheetLogRequest.h"
#include "Task/Rest/QueryIssueStampSheetLogTask.h"
#include "Request/CountIssueStampSheetLogRequest.h"
#include "Task/Rest/CountIssueStampSheetLogTask.h"
#include "Request/QueryExecuteStampSheetLogRequest.h"
#include "Task/Rest/QueryExecuteStampSheetLogTask.h"
#include "Request/CountExecuteStampSheetLogRequest.h"
#include "Task/Rest/CountExecuteStampSheetLogTask.h"
#include "Request/QueryExecuteStampTaskLogRequest.h"
#include "Task/Rest/QueryExecuteStampTaskLogTask.h"
#include "Request/CountExecuteStampTaskLogRequest.h"
#include "Task/Rest/CountExecuteStampTaskLogTask.h"
#include "Request/QueryInGameLogRequest.h"
#include "Task/Rest/QueryInGameLogTask.h"
#include "Request/SendInGameLogRequest.h"
#include "Task/Rest/SendInGameLogTask.h"
#include "Request/SendInGameLogByUserIdRequest.h"
#include "Task/Rest/SendInGameLogByUserIdTask.h"
#include "Request/QueryAccessLogWithTelemetryRequest.h"
#include "Task/Rest/QueryAccessLogWithTelemetryTask.h"
#include "Request/DescribeInsightsRequest.h"
#include "Task/Rest/DescribeInsightsTask.h"
#include "Request/CreateInsightRequest.h"
#include "Task/Rest/CreateInsightTask.h"
#include "Request/GetInsightRequest.h"
#include "Task/Rest/GetInsightTask.h"
#include "Request/DeleteInsightRequest.h"
#include "Task/Rest/DeleteInsightTask.h"

namespace Gs2::Log
{
    class GS2LOG_API FGs2LogRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2LogRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FGetServiceVersionTask>> GetServiceVersion(
            const Request::FGetServiceVersionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FQueryAccessLogTask>> QueryAccessLog(
            const Request::FQueryAccessLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCountAccessLogTask>> CountAccessLog(
            const Request::FCountAccessLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FQueryIssueStampSheetLogTask>> QueryIssueStampSheetLog(
            const Request::FQueryIssueStampSheetLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCountIssueStampSheetLogTask>> CountIssueStampSheetLog(
            const Request::FCountIssueStampSheetLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FQueryExecuteStampSheetLogTask>> QueryExecuteStampSheetLog(
            const Request::FQueryExecuteStampSheetLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCountExecuteStampSheetLogTask>> CountExecuteStampSheetLog(
            const Request::FCountExecuteStampSheetLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FQueryExecuteStampTaskLogTask>> QueryExecuteStampTaskLog(
            const Request::FQueryExecuteStampTaskLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCountExecuteStampTaskLogTask>> CountExecuteStampTaskLog(
            const Request::FCountExecuteStampTaskLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FQueryInGameLogTask>> QueryInGameLog(
            const Request::FQueryInGameLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSendInGameLogTask>> SendInGameLog(
            const Request::FSendInGameLogRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSendInGameLogByUserIdTask>> SendInGameLogByUserId(
            const Request::FSendInGameLogByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FQueryAccessLogWithTelemetryTask>> QueryAccessLogWithTelemetry(
            const Request::FQueryAccessLogWithTelemetryRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeInsightsTask>> DescribeInsights(
            const Request::FDescribeInsightsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateInsightTask>> CreateInsight(
            const Request::FCreateInsightRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetInsightTask>> GetInsight(
            const Request::FGetInsightRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteInsightTask>> DeleteInsight(
            const Request::FDeleteInsightRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2LogRestClient, ESPMode::ThreadSafe> FGs2LogRestClientPtr;
}