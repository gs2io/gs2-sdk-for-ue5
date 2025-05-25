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

// Model
#include "Model/Namespace.h"
#include "Model/AccessLog.h"
#include "Model/AccessLogCount.h"
#include "Model/IssueStampSheetLog.h"
#include "Model/IssueStampSheetLogCount.h"
#include "Model/ExecuteStampSheetLog.h"
#include "Model/ExecuteStampSheetLogCount.h"
#include "Model/ExecuteStampTaskLog.h"
#include "Model/ExecuteStampTaskLogCount.h"
#include "Model/InGameLog.h"
#include "Model/AccessLogWithTelemetry.h"
#include "Model/Insight.h"
#include "Model/InGameLogTag.h"

// DescribeNamespaces
#include "Request/DescribeNamespacesRequest.h"
#include "Result/DescribeNamespacesResult.h"
#include "Task/Rest/DescribeNamespacesTask.h"
#include "Task/WebSocket/DescribeNamespacesTask.h"

// CreateNamespace
#include "Request/CreateNamespaceRequest.h"
#include "Result/CreateNamespaceResult.h"
#include "Task/Rest/CreateNamespaceTask.h"
#include "Task/WebSocket/CreateNamespaceTask.h"

// GetNamespaceStatus
#include "Request/GetNamespaceStatusRequest.h"
#include "Result/GetNamespaceStatusResult.h"
#include "Task/Rest/GetNamespaceStatusTask.h"
#include "Task/WebSocket/GetNamespaceStatusTask.h"

// GetNamespace
#include "Request/GetNamespaceRequest.h"
#include "Result/GetNamespaceResult.h"
#include "Task/Rest/GetNamespaceTask.h"
#include "Task/WebSocket/GetNamespaceTask.h"

// UpdateNamespace
#include "Request/UpdateNamespaceRequest.h"
#include "Result/UpdateNamespaceResult.h"
#include "Task/Rest/UpdateNamespaceTask.h"
#include "Task/WebSocket/UpdateNamespaceTask.h"

// DeleteNamespace
#include "Request/DeleteNamespaceRequest.h"
#include "Result/DeleteNamespaceResult.h"
#include "Task/Rest/DeleteNamespaceTask.h"
#include "Task/WebSocket/DeleteNamespaceTask.h"

// GetServiceVersion
#include "Request/GetServiceVersionRequest.h"
#include "Result/GetServiceVersionResult.h"
#include "Task/Rest/GetServiceVersionTask.h"
#include "Task/WebSocket/GetServiceVersionTask.h"

// QueryAccessLog
#include "Request/QueryAccessLogRequest.h"
#include "Result/QueryAccessLogResult.h"
#include "Task/Rest/QueryAccessLogTask.h"
#include "Task/WebSocket/QueryAccessLogTask.h"

// CountAccessLog
#include "Request/CountAccessLogRequest.h"
#include "Result/CountAccessLogResult.h"
#include "Task/Rest/CountAccessLogTask.h"
#include "Task/WebSocket/CountAccessLogTask.h"

// QueryIssueStampSheetLog
#include "Request/QueryIssueStampSheetLogRequest.h"
#include "Result/QueryIssueStampSheetLogResult.h"
#include "Task/Rest/QueryIssueStampSheetLogTask.h"
#include "Task/WebSocket/QueryIssueStampSheetLogTask.h"

// CountIssueStampSheetLog
#include "Request/CountIssueStampSheetLogRequest.h"
#include "Result/CountIssueStampSheetLogResult.h"
#include "Task/Rest/CountIssueStampSheetLogTask.h"
#include "Task/WebSocket/CountIssueStampSheetLogTask.h"

// QueryExecuteStampSheetLog
#include "Request/QueryExecuteStampSheetLogRequest.h"
#include "Result/QueryExecuteStampSheetLogResult.h"
#include "Task/Rest/QueryExecuteStampSheetLogTask.h"
#include "Task/WebSocket/QueryExecuteStampSheetLogTask.h"

// CountExecuteStampSheetLog
#include "Request/CountExecuteStampSheetLogRequest.h"
#include "Result/CountExecuteStampSheetLogResult.h"
#include "Task/Rest/CountExecuteStampSheetLogTask.h"
#include "Task/WebSocket/CountExecuteStampSheetLogTask.h"

// QueryExecuteStampTaskLog
#include "Request/QueryExecuteStampTaskLogRequest.h"
#include "Result/QueryExecuteStampTaskLogResult.h"
#include "Task/Rest/QueryExecuteStampTaskLogTask.h"
#include "Task/WebSocket/QueryExecuteStampTaskLogTask.h"

// CountExecuteStampTaskLog
#include "Request/CountExecuteStampTaskLogRequest.h"
#include "Result/CountExecuteStampTaskLogResult.h"
#include "Task/Rest/CountExecuteStampTaskLogTask.h"
#include "Task/WebSocket/CountExecuteStampTaskLogTask.h"

// QueryInGameLog
#include "Request/QueryInGameLogRequest.h"
#include "Result/QueryInGameLogResult.h"
#include "Task/Rest/QueryInGameLogTask.h"
#include "Task/WebSocket/QueryInGameLogTask.h"

// SendInGameLog
#include "Request/SendInGameLogRequest.h"
#include "Result/SendInGameLogResult.h"
#include "Task/Rest/SendInGameLogTask.h"
#include "Task/WebSocket/SendInGameLogTask.h"

// SendInGameLogByUserId
#include "Request/SendInGameLogByUserIdRequest.h"
#include "Result/SendInGameLogByUserIdResult.h"
#include "Task/Rest/SendInGameLogByUserIdTask.h"
#include "Task/WebSocket/SendInGameLogByUserIdTask.h"

// QueryAccessLogWithTelemetry
#include "Request/QueryAccessLogWithTelemetryRequest.h"
#include "Result/QueryAccessLogWithTelemetryResult.h"
#include "Task/Rest/QueryAccessLogWithTelemetryTask.h"
#include "Task/WebSocket/QueryAccessLogWithTelemetryTask.h"

// DescribeInsights
#include "Request/DescribeInsightsRequest.h"
#include "Result/DescribeInsightsResult.h"
#include "Task/Rest/DescribeInsightsTask.h"
#include "Task/WebSocket/DescribeInsightsTask.h"

// CreateInsight
#include "Request/CreateInsightRequest.h"
#include "Result/CreateInsightResult.h"
#include "Task/Rest/CreateInsightTask.h"
#include "Task/WebSocket/CreateInsightTask.h"

// GetInsight
#include "Request/GetInsightRequest.h"
#include "Result/GetInsightResult.h"
#include "Task/Rest/GetInsightTask.h"
#include "Task/WebSocket/GetInsightTask.h"

// DeleteInsight
#include "Request/DeleteInsightRequest.h"
#include "Result/DeleteInsightResult.h"
#include "Task/Rest/DeleteInsightTask.h"
#include "Task/WebSocket/DeleteInsightTask.h"

// Client
#include "Gs2LogRestClient.h"
#include "Gs2LogWebSocketClient.h"