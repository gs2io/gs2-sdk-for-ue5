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

#include "Ranking/Gs2RankingWebSocketClient.h"

namespace Gs2::Ranking
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> FGs2RankingWebSocketClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> FGs2RankingWebSocketClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> FGs2RankingWebSocketClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> FGs2RankingWebSocketClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> FGs2RankingWebSocketClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> FGs2RankingWebSocketClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>> FGs2RankingWebSocketClient::DumpUserDataByUserId(
        const Request::FDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>> FGs2RankingWebSocketClient::CheckDumpUserDataByUserId(
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>> FGs2RankingWebSocketClient::CleanUserDataByUserId(
        const Request::FCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>> FGs2RankingWebSocketClient::CheckCleanUserDataByUserId(
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCategoryModelsTask>> FGs2RankingWebSocketClient::DescribeCategoryModels(
        const Request::FDescribeCategoryModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeCategoryModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCategoryModelTask>> FGs2RankingWebSocketClient::GetCategoryModel(
        const Request::FGetCategoryModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCategoryModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCategoryModelMastersTask>> FGs2RankingWebSocketClient::DescribeCategoryModelMasters(
        const Request::FDescribeCategoryModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeCategoryModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateCategoryModelMasterTask>> FGs2RankingWebSocketClient::CreateCategoryModelMaster(
        const Request::FCreateCategoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateCategoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCategoryModelMasterTask>> FGs2RankingWebSocketClient::GetCategoryModelMaster(
        const Request::FGetCategoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCategoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCategoryModelMasterTask>> FGs2RankingWebSocketClient::UpdateCategoryModelMaster(
        const Request::FUpdateCategoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCategoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteCategoryModelMasterTask>> FGs2RankingWebSocketClient::DeleteCategoryModelMaster(
        const Request::FDeleteCategoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteCategoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSubscribeTask>> FGs2RankingWebSocketClient::Subscribe(
        const Request::FSubscribeRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSubscribeTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSubscribeByUserIdTask>> FGs2RankingWebSocketClient::SubscribeByUserId(
        const Request::FSubscribeByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSubscribeByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeScoresTask>> FGs2RankingWebSocketClient::DescribeScores(
        const Request::FDescribeScoresRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeScoresTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeScoresByUserIdTask>> FGs2RankingWebSocketClient::DescribeScoresByUserId(
        const Request::FDescribeScoresByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeScoresByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetScoreTask>> FGs2RankingWebSocketClient::GetScore(
        const Request::FGetScoreRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetScoreTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetScoreByUserIdTask>> FGs2RankingWebSocketClient::GetScoreByUserId(
        const Request::FGetScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRankingsTask>> FGs2RankingWebSocketClient::DescribeRankings(
        const Request::FDescribeRankingsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeRankingsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRankingssByUserIdTask>> FGs2RankingWebSocketClient::DescribeRankingssByUserId(
        const Request::FDescribeRankingssByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeRankingssByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNearRankingsTask>> FGs2RankingWebSocketClient::DescribeNearRankings(
        const Request::FDescribeNearRankingsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNearRankingsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetRankingTask>> FGs2RankingWebSocketClient::GetRanking(
        const Request::FGetRankingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetRankingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetRankingByUserIdTask>> FGs2RankingWebSocketClient::GetRankingByUserId(
        const Request::FGetRankingByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetRankingByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPutScoreTask>> FGs2RankingWebSocketClient::PutScore(
        const Request::FPutScoreRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPutScoreTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPutScoreByUserIdTask>> FGs2RankingWebSocketClient::PutScoreByUserId(
        const Request::FPutScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPutScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCalcRankingTask>> FGs2RankingWebSocketClient::CalcRanking(
        const Request::FCalcRankingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCalcRankingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> FGs2RankingWebSocketClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentRankingMasterTask>> FGs2RankingWebSocketClient::GetCurrentRankingMaster(
        const Request::FGetCurrentRankingMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCurrentRankingMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentRankingMasterTask>> FGs2RankingWebSocketClient::UpdateCurrentRankingMaster(
        const Request::FUpdateCurrentRankingMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentRankingMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentRankingMasterFromGitHubTask>> FGs2RankingWebSocketClient::UpdateCurrentRankingMasterFromGitHub(
        const Request::FUpdateCurrentRankingMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentRankingMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeTask>> FGs2RankingWebSocketClient::GetSubscribe(
        const Request::FGetSubscribeRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSubscribeTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeByUserIdTask>> FGs2RankingWebSocketClient::GetSubscribeByUserId(
        const Request::FGetSubscribeByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSubscribeByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUnsubscribeTask>> FGs2RankingWebSocketClient::Unsubscribe(
        const Request::FUnsubscribeRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUnsubscribeTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUnsubscribeByUserIdTask>> FGs2RankingWebSocketClient::UnsubscribeByUserId(
        const Request::FUnsubscribeByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUnsubscribeByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribesByCategoryNameTask>> FGs2RankingWebSocketClient::DescribeSubscribesByCategoryName(
        const Request::FDescribeSubscribesByCategoryNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSubscribesByCategoryNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribesByCategoryNameAndUserIdTask>> FGs2RankingWebSocketClient::DescribeSubscribesByCategoryNameAndUserId(
        const Request::FDescribeSubscribesByCategoryNameAndUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSubscribesByCategoryNameAndUserIdTask>>(
            Session,
            Request
        );
    }
}