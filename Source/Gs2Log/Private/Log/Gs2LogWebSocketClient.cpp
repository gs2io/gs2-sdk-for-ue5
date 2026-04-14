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

#include "Log/Gs2LogWebSocketClient.h"

namespace Gs2::Log
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> FGs2LogWebSocketClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> FGs2LogWebSocketClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> FGs2LogWebSocketClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> FGs2LogWebSocketClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> FGs2LogWebSocketClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> FGs2LogWebSocketClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetServiceVersionTask>> FGs2LogWebSocketClient::GetServiceVersion(
        const Request::FGetServiceVersionRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetServiceVersionTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FQueryAccessLogTask>> FGs2LogWebSocketClient::QueryAccessLog(
        const Request::FQueryAccessLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FQueryAccessLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCountAccessLogTask>> FGs2LogWebSocketClient::CountAccessLog(
        const Request::FCountAccessLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCountAccessLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FQueryIssueStampSheetLogTask>> FGs2LogWebSocketClient::QueryIssueStampSheetLog(
        const Request::FQueryIssueStampSheetLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FQueryIssueStampSheetLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCountIssueStampSheetLogTask>> FGs2LogWebSocketClient::CountIssueStampSheetLog(
        const Request::FCountIssueStampSheetLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCountIssueStampSheetLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FQueryExecuteStampSheetLogTask>> FGs2LogWebSocketClient::QueryExecuteStampSheetLog(
        const Request::FQueryExecuteStampSheetLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FQueryExecuteStampSheetLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCountExecuteStampSheetLogTask>> FGs2LogWebSocketClient::CountExecuteStampSheetLog(
        const Request::FCountExecuteStampSheetLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCountExecuteStampSheetLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FQueryExecuteStampTaskLogTask>> FGs2LogWebSocketClient::QueryExecuteStampTaskLog(
        const Request::FQueryExecuteStampTaskLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FQueryExecuteStampTaskLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCountExecuteStampTaskLogTask>> FGs2LogWebSocketClient::CountExecuteStampTaskLog(
        const Request::FCountExecuteStampTaskLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCountExecuteStampTaskLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FQueryInGameLogTask>> FGs2LogWebSocketClient::QueryInGameLog(
        const Request::FQueryInGameLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FQueryInGameLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSendInGameLogTask>> FGs2LogWebSocketClient::SendInGameLog(
        const Request::FSendInGameLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSendInGameLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSendInGameLogByUserIdTask>> FGs2LogWebSocketClient::SendInGameLogByUserId(
        const Request::FSendInGameLogByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSendInGameLogByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FQueryAccessLogWithTelemetryTask>> FGs2LogWebSocketClient::QueryAccessLogWithTelemetry(
        const Request::FQueryAccessLogWithTelemetryRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FQueryAccessLogWithTelemetryTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeInsightsTask>> FGs2LogWebSocketClient::DescribeInsights(
        const Request::FDescribeInsightsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeInsightsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateInsightTask>> FGs2LogWebSocketClient::CreateInsight(
        const Request::FCreateInsightRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateInsightTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetInsightTask>> FGs2LogWebSocketClient::GetInsight(
        const Request::FGetInsightRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetInsightTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteInsightTask>> FGs2LogWebSocketClient::DeleteInsight(
        const Request::FDeleteInsightRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteInsightTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeFacetModelsTask>> FGs2LogWebSocketClient::DescribeFacetModels(
        const Request::FDescribeFacetModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeFacetModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateFacetModelTask>> FGs2LogWebSocketClient::CreateFacetModel(
        const Request::FCreateFacetModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateFacetModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetFacetModelTask>> FGs2LogWebSocketClient::GetFacetModel(
        const Request::FGetFacetModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetFacetModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateFacetModelTask>> FGs2LogWebSocketClient::UpdateFacetModel(
        const Request::FUpdateFacetModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateFacetModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteFacetModelTask>> FGs2LogWebSocketClient::DeleteFacetModel(
        const Request::FDeleteFacetModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteFacetModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeDashboardsTask>> FGs2LogWebSocketClient::DescribeDashboards(
        const Request::FDescribeDashboardsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeDashboardsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateDashboardTask>> FGs2LogWebSocketClient::CreateDashboard(
        const Request::FCreateDashboardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateDashboardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetDashboardTask>> FGs2LogWebSocketClient::GetDashboard(
        const Request::FGetDashboardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetDashboardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateDashboardTask>> FGs2LogWebSocketClient::UpdateDashboard(
        const Request::FUpdateDashboardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateDashboardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDuplicateDashboardTask>> FGs2LogWebSocketClient::DuplicateDashboard(
        const Request::FDuplicateDashboardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDuplicateDashboardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteDashboardTask>> FGs2LogWebSocketClient::DeleteDashboard(
        const Request::FDeleteDashboardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteDashboardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FQueryLogTask>> FGs2LogWebSocketClient::QueryLog(
        const Request::FQueryLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FQueryLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetLogTask>> FGs2LogWebSocketClient::GetLog(
        const Request::FGetLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FQueryFacetsTask>> FGs2LogWebSocketClient::QueryFacets(
        const Request::FQueryFacetsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FQueryFacetsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FQueryTimeseriesTask>> FGs2LogWebSocketClient::QueryTimeseries(
        const Request::FQueryTimeseriesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FQueryTimeseriesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetTraceTask>> FGs2LogWebSocketClient::GetTrace(
        const Request::FGetTraceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetTraceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FQueryMetricsTimeseriesTask>> FGs2LogWebSocketClient::QueryMetricsTimeseries(
        const Request::FQueryMetricsTimeseriesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FQueryMetricsTimeseriesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMetricsTask>> FGs2LogWebSocketClient::DescribeMetrics(
        const Request::FDescribeMetricsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeMetricsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeLabelValuesTask>> FGs2LogWebSocketClient::DescribeLabelValues(
        const Request::FDescribeLabelValuesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeLabelValuesTask>>(
            Session,
            Request
        );
    }
}