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

#include "Ranking2/Gs2Ranking2WebSocketClient.h"

namespace Gs2::Ranking2
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> FGs2Ranking2WebSocketClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> FGs2Ranking2WebSocketClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> FGs2Ranking2WebSocketClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> FGs2Ranking2WebSocketClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> FGs2Ranking2WebSocketClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> FGs2Ranking2WebSocketClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>> FGs2Ranking2WebSocketClient::DumpUserDataByUserId(
        const Request::FDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>> FGs2Ranking2WebSocketClient::CheckDumpUserDataByUserId(
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>> FGs2Ranking2WebSocketClient::CleanUserDataByUserId(
        const Request::FCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>> FGs2Ranking2WebSocketClient::CheckCleanUserDataByUserId(
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>> FGs2Ranking2WebSocketClient::PrepareImportUserDataByUserId(
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>> FGs2Ranking2WebSocketClient::ImportUserDataByUserId(
        const Request::FImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>> FGs2Ranking2WebSocketClient::CheckImportUserDataByUserId(
        const Request::FCheckImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingModelsTask>> FGs2Ranking2WebSocketClient::DescribeGlobalRankingModels(
        const Request::FDescribeGlobalRankingModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalRankingModelTask>> FGs2Ranking2WebSocketClient::GetGlobalRankingModel(
        const Request::FGetGlobalRankingModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetGlobalRankingModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingModelMastersTask>> FGs2Ranking2WebSocketClient::DescribeGlobalRankingModelMasters(
        const Request::FDescribeGlobalRankingModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGlobalRankingModelMasterTask>> FGs2Ranking2WebSocketClient::CreateGlobalRankingModelMaster(
        const Request::FCreateGlobalRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateGlobalRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalRankingModelMasterTask>> FGs2Ranking2WebSocketClient::GetGlobalRankingModelMaster(
        const Request::FGetGlobalRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetGlobalRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateGlobalRankingModelMasterTask>> FGs2Ranking2WebSocketClient::UpdateGlobalRankingModelMaster(
        const Request::FUpdateGlobalRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateGlobalRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteGlobalRankingModelMasterTask>> FGs2Ranking2WebSocketClient::DeleteGlobalRankingModelMaster(
        const Request::FDeleteGlobalRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteGlobalRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingScoresTask>> FGs2Ranking2WebSocketClient::DescribeGlobalRankingScores(
        const Request::FDescribeGlobalRankingScoresRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingScoresTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingScoresByUserIdTask>> FGs2Ranking2WebSocketClient::DescribeGlobalRankingScoresByUserId(
        const Request::FDescribeGlobalRankingScoresByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingScoresByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPutGlobalRankingScoreTask>> FGs2Ranking2WebSocketClient::PutGlobalRankingScore(
        const Request::FPutGlobalRankingScoreRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPutGlobalRankingScoreTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPutGlobalRankingScoreByUserIdTask>> FGs2Ranking2WebSocketClient::PutGlobalRankingScoreByUserId(
        const Request::FPutGlobalRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPutGlobalRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalRankingScoreTask>> FGs2Ranking2WebSocketClient::GetGlobalRankingScore(
        const Request::FGetGlobalRankingScoreRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetGlobalRankingScoreTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalRankingScoreByUserIdTask>> FGs2Ranking2WebSocketClient::GetGlobalRankingScoreByUserId(
        const Request::FGetGlobalRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetGlobalRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteGlobalRankingScoreByUserIdTask>> FGs2Ranking2WebSocketClient::DeleteGlobalRankingScoreByUserId(
        const Request::FDeleteGlobalRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteGlobalRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingReceivedRewardsTask>> FGs2Ranking2WebSocketClient::DescribeGlobalRankingReceivedRewards(
        const Request::FDescribeGlobalRankingReceivedRewardsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingReceivedRewardsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingReceivedRewardsByUserIdTask>> FGs2Ranking2WebSocketClient::DescribeGlobalRankingReceivedRewardsByUserId(
        const Request::FDescribeGlobalRankingReceivedRewardsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingReceivedRewardsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGlobalRankingReceivedRewardTask>> FGs2Ranking2WebSocketClient::CreateGlobalRankingReceivedReward(
        const Request::FCreateGlobalRankingReceivedRewardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateGlobalRankingReceivedRewardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGlobalRankingReceivedRewardByUserIdTask>> FGs2Ranking2WebSocketClient::CreateGlobalRankingReceivedRewardByUserId(
        const Request::FCreateGlobalRankingReceivedRewardByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateGlobalRankingReceivedRewardByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveGlobalRankingReceivedRewardTask>> FGs2Ranking2WebSocketClient::ReceiveGlobalRankingReceivedReward(
        const Request::FReceiveGlobalRankingReceivedRewardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FReceiveGlobalRankingReceivedRewardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveGlobalRankingReceivedRewardByUserIdTask>> FGs2Ranking2WebSocketClient::ReceiveGlobalRankingReceivedRewardByUserId(
        const Request::FReceiveGlobalRankingReceivedRewardByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FReceiveGlobalRankingReceivedRewardByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalRankingReceivedRewardTask>> FGs2Ranking2WebSocketClient::GetGlobalRankingReceivedReward(
        const Request::FGetGlobalRankingReceivedRewardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetGlobalRankingReceivedRewardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalRankingReceivedRewardByUserIdTask>> FGs2Ranking2WebSocketClient::GetGlobalRankingReceivedRewardByUserId(
        const Request::FGetGlobalRankingReceivedRewardByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetGlobalRankingReceivedRewardByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteGlobalRankingReceivedRewardByUserIdTask>> FGs2Ranking2WebSocketClient::DeleteGlobalRankingReceivedRewardByUserId(
        const Request::FDeleteGlobalRankingReceivedRewardByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteGlobalRankingReceivedRewardByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGlobalRankingReceivedRewardByStampTaskTask>> FGs2Ranking2WebSocketClient::CreateGlobalRankingReceivedRewardByStampTask(
        const Request::FCreateGlobalRankingReceivedRewardByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateGlobalRankingReceivedRewardByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingsTask>> FGs2Ranking2WebSocketClient::DescribeGlobalRankings(
        const Request::FDescribeGlobalRankingsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingsByUserIdTask>> FGs2Ranking2WebSocketClient::DescribeGlobalRankingsByUserId(
        const Request::FDescribeGlobalRankingsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalRankingTask>> FGs2Ranking2WebSocketClient::GetGlobalRanking(
        const Request::FGetGlobalRankingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetGlobalRankingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalRankingByUserIdTask>> FGs2Ranking2WebSocketClient::GetGlobalRankingByUserId(
        const Request::FGetGlobalRankingByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetGlobalRankingByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeClusterRankingModelsTask>> FGs2Ranking2WebSocketClient::DescribeClusterRankingModels(
        const Request::FDescribeClusterRankingModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeClusterRankingModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetClusterRankingModelTask>> FGs2Ranking2WebSocketClient::GetClusterRankingModel(
        const Request::FGetClusterRankingModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetClusterRankingModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeClusterRankingModelMastersTask>> FGs2Ranking2WebSocketClient::DescribeClusterRankingModelMasters(
        const Request::FDescribeClusterRankingModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeClusterRankingModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateClusterRankingModelMasterTask>> FGs2Ranking2WebSocketClient::CreateClusterRankingModelMaster(
        const Request::FCreateClusterRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateClusterRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetClusterRankingModelMasterTask>> FGs2Ranking2WebSocketClient::GetClusterRankingModelMaster(
        const Request::FGetClusterRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetClusterRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateClusterRankingModelMasterTask>> FGs2Ranking2WebSocketClient::UpdateClusterRankingModelMaster(
        const Request::FUpdateClusterRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateClusterRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteClusterRankingModelMasterTask>> FGs2Ranking2WebSocketClient::DeleteClusterRankingModelMaster(
        const Request::FDeleteClusterRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteClusterRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeClusterRankingScoresTask>> FGs2Ranking2WebSocketClient::DescribeClusterRankingScores(
        const Request::FDescribeClusterRankingScoresRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeClusterRankingScoresTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeClusterRankingScoresByUserIdTask>> FGs2Ranking2WebSocketClient::DescribeClusterRankingScoresByUserId(
        const Request::FDescribeClusterRankingScoresByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeClusterRankingScoresByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPutClusterRankingScoreTask>> FGs2Ranking2WebSocketClient::PutClusterRankingScore(
        const Request::FPutClusterRankingScoreRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPutClusterRankingScoreTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPutClusterRankingScoreByUserIdTask>> FGs2Ranking2WebSocketClient::PutClusterRankingScoreByUserId(
        const Request::FPutClusterRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPutClusterRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetClusterRankingScoreTask>> FGs2Ranking2WebSocketClient::GetClusterRankingScore(
        const Request::FGetClusterRankingScoreRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetClusterRankingScoreTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetClusterRankingScoreByUserIdTask>> FGs2Ranking2WebSocketClient::GetClusterRankingScoreByUserId(
        const Request::FGetClusterRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetClusterRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteClusterRankingScoreByUserIdTask>> FGs2Ranking2WebSocketClient::DeleteClusterRankingScoreByUserId(
        const Request::FDeleteClusterRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteClusterRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeClusterRankingReceivedRewardsTask>> FGs2Ranking2WebSocketClient::DescribeClusterRankingReceivedRewards(
        const Request::FDescribeClusterRankingReceivedRewardsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeClusterRankingReceivedRewardsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeClusterRankingReceivedRewardsByUserIdTask>> FGs2Ranking2WebSocketClient::DescribeClusterRankingReceivedRewardsByUserId(
        const Request::FDescribeClusterRankingReceivedRewardsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeClusterRankingReceivedRewardsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateClusterRankingReceivedRewardTask>> FGs2Ranking2WebSocketClient::CreateClusterRankingReceivedReward(
        const Request::FCreateClusterRankingReceivedRewardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateClusterRankingReceivedRewardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateClusterRankingReceivedRewardByUserIdTask>> FGs2Ranking2WebSocketClient::CreateClusterRankingReceivedRewardByUserId(
        const Request::FCreateClusterRankingReceivedRewardByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateClusterRankingReceivedRewardByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveClusterRankingReceivedRewardTask>> FGs2Ranking2WebSocketClient::ReceiveClusterRankingReceivedReward(
        const Request::FReceiveClusterRankingReceivedRewardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FReceiveClusterRankingReceivedRewardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveClusterRankingReceivedRewardByUserIdTask>> FGs2Ranking2WebSocketClient::ReceiveClusterRankingReceivedRewardByUserId(
        const Request::FReceiveClusterRankingReceivedRewardByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FReceiveClusterRankingReceivedRewardByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetClusterRankingReceivedRewardTask>> FGs2Ranking2WebSocketClient::GetClusterRankingReceivedReward(
        const Request::FGetClusterRankingReceivedRewardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetClusterRankingReceivedRewardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetClusterRankingReceivedRewardByUserIdTask>> FGs2Ranking2WebSocketClient::GetClusterRankingReceivedRewardByUserId(
        const Request::FGetClusterRankingReceivedRewardByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetClusterRankingReceivedRewardByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteClusterRankingReceivedRewardByUserIdTask>> FGs2Ranking2WebSocketClient::DeleteClusterRankingReceivedRewardByUserId(
        const Request::FDeleteClusterRankingReceivedRewardByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteClusterRankingReceivedRewardByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateClusterRankingReceivedRewardByStampTaskTask>> FGs2Ranking2WebSocketClient::CreateClusterRankingReceivedRewardByStampTask(
        const Request::FCreateClusterRankingReceivedRewardByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateClusterRankingReceivedRewardByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeClusterRankingsTask>> FGs2Ranking2WebSocketClient::DescribeClusterRankings(
        const Request::FDescribeClusterRankingsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeClusterRankingsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeClusterRankingsByUserIdTask>> FGs2Ranking2WebSocketClient::DescribeClusterRankingsByUserId(
        const Request::FDescribeClusterRankingsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeClusterRankingsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetClusterRankingTask>> FGs2Ranking2WebSocketClient::GetClusterRanking(
        const Request::FGetClusterRankingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetClusterRankingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetClusterRankingByUserIdTask>> FGs2Ranking2WebSocketClient::GetClusterRankingByUserId(
        const Request::FGetClusterRankingByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetClusterRankingByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingModelsTask>> FGs2Ranking2WebSocketClient::DescribeSubscribeRankingModels(
        const Request::FDescribeSubscribeRankingModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeRankingModelTask>> FGs2Ranking2WebSocketClient::GetSubscribeRankingModel(
        const Request::FGetSubscribeRankingModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSubscribeRankingModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingModelMastersTask>> FGs2Ranking2WebSocketClient::DescribeSubscribeRankingModelMasters(
        const Request::FDescribeSubscribeRankingModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateSubscribeRankingModelMasterTask>> FGs2Ranking2WebSocketClient::CreateSubscribeRankingModelMaster(
        const Request::FCreateSubscribeRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateSubscribeRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeRankingModelMasterTask>> FGs2Ranking2WebSocketClient::GetSubscribeRankingModelMaster(
        const Request::FGetSubscribeRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSubscribeRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateSubscribeRankingModelMasterTask>> FGs2Ranking2WebSocketClient::UpdateSubscribeRankingModelMaster(
        const Request::FUpdateSubscribeRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateSubscribeRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSubscribeRankingModelMasterTask>> FGs2Ranking2WebSocketClient::DeleteSubscribeRankingModelMaster(
        const Request::FDeleteSubscribeRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteSubscribeRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribesTask>> FGs2Ranking2WebSocketClient::DescribeSubscribes(
        const Request::FDescribeSubscribesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSubscribesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribesByUserIdTask>> FGs2Ranking2WebSocketClient::DescribeSubscribesByUserId(
        const Request::FDescribeSubscribesByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSubscribesByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAddSubscribeTask>> FGs2Ranking2WebSocketClient::AddSubscribe(
        const Request::FAddSubscribeRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAddSubscribeTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAddSubscribeByUserIdTask>> FGs2Ranking2WebSocketClient::AddSubscribeByUserId(
        const Request::FAddSubscribeByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAddSubscribeByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingScoresTask>> FGs2Ranking2WebSocketClient::DescribeSubscribeRankingScores(
        const Request::FDescribeSubscribeRankingScoresRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingScoresTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingScoresByUserIdTask>> FGs2Ranking2WebSocketClient::DescribeSubscribeRankingScoresByUserId(
        const Request::FDescribeSubscribeRankingScoresByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingScoresByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPutSubscribeRankingScoreTask>> FGs2Ranking2WebSocketClient::PutSubscribeRankingScore(
        const Request::FPutSubscribeRankingScoreRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPutSubscribeRankingScoreTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPutSubscribeRankingScoreByUserIdTask>> FGs2Ranking2WebSocketClient::PutSubscribeRankingScoreByUserId(
        const Request::FPutSubscribeRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPutSubscribeRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeRankingScoreTask>> FGs2Ranking2WebSocketClient::GetSubscribeRankingScore(
        const Request::FGetSubscribeRankingScoreRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSubscribeRankingScoreTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeRankingScoreByUserIdTask>> FGs2Ranking2WebSocketClient::GetSubscribeRankingScoreByUserId(
        const Request::FGetSubscribeRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSubscribeRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSubscribeRankingScoreByUserIdTask>> FGs2Ranking2WebSocketClient::DeleteSubscribeRankingScoreByUserId(
        const Request::FDeleteSubscribeRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteSubscribeRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingsTask>> FGs2Ranking2WebSocketClient::DescribeSubscribeRankings(
        const Request::FDescribeSubscribeRankingsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingsByUserIdTask>> FGs2Ranking2WebSocketClient::DescribeSubscribeRankingsByUserId(
        const Request::FDescribeSubscribeRankingsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeRankingTask>> FGs2Ranking2WebSocketClient::GetSubscribeRanking(
        const Request::FGetSubscribeRankingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSubscribeRankingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeRankingByUserIdTask>> FGs2Ranking2WebSocketClient::GetSubscribeRankingByUserId(
        const Request::FGetSubscribeRankingByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSubscribeRankingByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> FGs2Ranking2WebSocketClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentRankingMasterTask>> FGs2Ranking2WebSocketClient::GetCurrentRankingMaster(
        const Request::FGetCurrentRankingMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCurrentRankingMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentRankingMasterTask>> FGs2Ranking2WebSocketClient::UpdateCurrentRankingMaster(
        const Request::FUpdateCurrentRankingMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentRankingMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentRankingMasterFromGitHubTask>> FGs2Ranking2WebSocketClient::UpdateCurrentRankingMasterFromGitHub(
        const Request::FUpdateCurrentRankingMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentRankingMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeTask>> FGs2Ranking2WebSocketClient::GetSubscribe(
        const Request::FGetSubscribeRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSubscribeTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeByUserIdTask>> FGs2Ranking2WebSocketClient::GetSubscribeByUserId(
        const Request::FGetSubscribeByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSubscribeByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSubscribeTask>> FGs2Ranking2WebSocketClient::DeleteSubscribe(
        const Request::FDeleteSubscribeRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteSubscribeTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSubscribeByUserIdTask>> FGs2Ranking2WebSocketClient::DeleteSubscribeByUserId(
        const Request::FDeleteSubscribeByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteSubscribeByUserIdTask>>(
            Session,
            Request
        );
    }
}