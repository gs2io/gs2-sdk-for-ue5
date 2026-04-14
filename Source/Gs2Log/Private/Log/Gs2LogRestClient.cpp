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

#include "Log/Gs2LogRestClient.h"

namespace Gs2::Log
{

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> FGs2LogRestClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> FGs2LogRestClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> FGs2LogRestClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> FGs2LogRestClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> FGs2LogRestClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> FGs2LogRestClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetServiceVersionTask>> FGs2LogRestClient::GetServiceVersion(
        const Request::FGetServiceVersionRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetServiceVersionTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FQueryAccessLogTask>> FGs2LogRestClient::QueryAccessLog(
        const Request::FQueryAccessLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FQueryAccessLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCountAccessLogTask>> FGs2LogRestClient::CountAccessLog(
        const Request::FCountAccessLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCountAccessLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FQueryIssueStampSheetLogTask>> FGs2LogRestClient::QueryIssueStampSheetLog(
        const Request::FQueryIssueStampSheetLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FQueryIssueStampSheetLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCountIssueStampSheetLogTask>> FGs2LogRestClient::CountIssueStampSheetLog(
        const Request::FCountIssueStampSheetLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCountIssueStampSheetLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FQueryExecuteStampSheetLogTask>> FGs2LogRestClient::QueryExecuteStampSheetLog(
        const Request::FQueryExecuteStampSheetLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FQueryExecuteStampSheetLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCountExecuteStampSheetLogTask>> FGs2LogRestClient::CountExecuteStampSheetLog(
        const Request::FCountExecuteStampSheetLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCountExecuteStampSheetLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FQueryExecuteStampTaskLogTask>> FGs2LogRestClient::QueryExecuteStampTaskLog(
        const Request::FQueryExecuteStampTaskLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FQueryExecuteStampTaskLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCountExecuteStampTaskLogTask>> FGs2LogRestClient::CountExecuteStampTaskLog(
        const Request::FCountExecuteStampTaskLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCountExecuteStampTaskLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FQueryInGameLogTask>> FGs2LogRestClient::QueryInGameLog(
        const Request::FQueryInGameLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FQueryInGameLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSendInGameLogTask>> FGs2LogRestClient::SendInGameLog(
        const Request::FSendInGameLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSendInGameLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSendInGameLogByUserIdTask>> FGs2LogRestClient::SendInGameLogByUserId(
        const Request::FSendInGameLogByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSendInGameLogByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FQueryAccessLogWithTelemetryTask>> FGs2LogRestClient::QueryAccessLogWithTelemetry(
        const Request::FQueryAccessLogWithTelemetryRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FQueryAccessLogWithTelemetryTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeInsightsTask>> FGs2LogRestClient::DescribeInsights(
        const Request::FDescribeInsightsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeInsightsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateInsightTask>> FGs2LogRestClient::CreateInsight(
        const Request::FCreateInsightRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateInsightTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetInsightTask>> FGs2LogRestClient::GetInsight(
        const Request::FGetInsightRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetInsightTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteInsightTask>> FGs2LogRestClient::DeleteInsight(
        const Request::FDeleteInsightRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteInsightTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeFacetModelsTask>> FGs2LogRestClient::DescribeFacetModels(
        const Request::FDescribeFacetModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeFacetModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateFacetModelTask>> FGs2LogRestClient::CreateFacetModel(
        const Request::FCreateFacetModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateFacetModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetFacetModelTask>> FGs2LogRestClient::GetFacetModel(
        const Request::FGetFacetModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetFacetModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateFacetModelTask>> FGs2LogRestClient::UpdateFacetModel(
        const Request::FUpdateFacetModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateFacetModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteFacetModelTask>> FGs2LogRestClient::DeleteFacetModel(
        const Request::FDeleteFacetModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteFacetModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeDashboardsTask>> FGs2LogRestClient::DescribeDashboards(
        const Request::FDescribeDashboardsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeDashboardsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateDashboardTask>> FGs2LogRestClient::CreateDashboard(
        const Request::FCreateDashboardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateDashboardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetDashboardTask>> FGs2LogRestClient::GetDashboard(
        const Request::FGetDashboardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetDashboardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateDashboardTask>> FGs2LogRestClient::UpdateDashboard(
        const Request::FUpdateDashboardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateDashboardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDuplicateDashboardTask>> FGs2LogRestClient::DuplicateDashboard(
        const Request::FDuplicateDashboardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDuplicateDashboardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteDashboardTask>> FGs2LogRestClient::DeleteDashboard(
        const Request::FDeleteDashboardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteDashboardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FQueryLogTask>> FGs2LogRestClient::QueryLog(
        const Request::FQueryLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FQueryLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetLogTask>> FGs2LogRestClient::GetLog(
        const Request::FGetLogRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetLogTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FQueryFacetsTask>> FGs2LogRestClient::QueryFacets(
        const Request::FQueryFacetsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FQueryFacetsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FQueryTimeseriesTask>> FGs2LogRestClient::QueryTimeseries(
        const Request::FQueryTimeseriesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FQueryTimeseriesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetTraceTask>> FGs2LogRestClient::GetTrace(
        const Request::FGetTraceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetTraceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FQueryMetricsTimeseriesTask>> FGs2LogRestClient::QueryMetricsTimeseries(
        const Request::FQueryMetricsTimeseriesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FQueryMetricsTimeseriesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeMetricsTask>> FGs2LogRestClient::DescribeMetrics(
        const Request::FDescribeMetricsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeMetricsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeLabelValuesTask>> FGs2LogRestClient::DescribeLabelValues(
        const Request::FDescribeLabelValuesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeLabelValuesTask>>(
            Session,
            Request
        );
    }
}