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

#include "Ranking2/Gs2Ranking2RestClient.h"

namespace Gs2::Ranking2
{

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> FGs2Ranking2RestClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> FGs2Ranking2RestClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> FGs2Ranking2RestClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> FGs2Ranking2RestClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> FGs2Ranking2RestClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> FGs2Ranking2RestClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDumpUserDataByUserIdTask>> FGs2Ranking2RestClient::DumpUserDataByUserId(
        const Request::FDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCheckDumpUserDataByUserIdTask>> FGs2Ranking2RestClient::CheckDumpUserDataByUserId(
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCheckDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCleanUserDataByUserIdTask>> FGs2Ranking2RestClient::CleanUserDataByUserId(
        const Request::FCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCheckCleanUserDataByUserIdTask>> FGs2Ranking2RestClient::CheckCleanUserDataByUserId(
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCheckCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPrepareImportUserDataByUserIdTask>> FGs2Ranking2RestClient::PrepareImportUserDataByUserId(
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPrepareImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FImportUserDataByUserIdTask>> FGs2Ranking2RestClient::ImportUserDataByUserId(
        const Request::FImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCheckImportUserDataByUserIdTask>> FGs2Ranking2RestClient::CheckImportUserDataByUserId(
        const Request::FCheckImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCheckImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalRankingModelsTask>> FGs2Ranking2RestClient::DescribeGlobalRankingModels(
        const Request::FDescribeGlobalRankingModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeGlobalRankingModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalRankingModelTask>> FGs2Ranking2RestClient::GetGlobalRankingModel(
        const Request::FGetGlobalRankingModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetGlobalRankingModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalRankingModelMastersTask>> FGs2Ranking2RestClient::DescribeGlobalRankingModelMasters(
        const Request::FDescribeGlobalRankingModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeGlobalRankingModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateGlobalRankingModelMasterTask>> FGs2Ranking2RestClient::CreateGlobalRankingModelMaster(
        const Request::FCreateGlobalRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateGlobalRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalRankingModelMasterTask>> FGs2Ranking2RestClient::GetGlobalRankingModelMaster(
        const Request::FGetGlobalRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetGlobalRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateGlobalRankingModelMasterTask>> FGs2Ranking2RestClient::UpdateGlobalRankingModelMaster(
        const Request::FUpdateGlobalRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateGlobalRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteGlobalRankingModelMasterTask>> FGs2Ranking2RestClient::DeleteGlobalRankingModelMaster(
        const Request::FDeleteGlobalRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteGlobalRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalRankingScoresTask>> FGs2Ranking2RestClient::DescribeGlobalRankingScores(
        const Request::FDescribeGlobalRankingScoresRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeGlobalRankingScoresTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalRankingScoresByUserIdTask>> FGs2Ranking2RestClient::DescribeGlobalRankingScoresByUserId(
        const Request::FDescribeGlobalRankingScoresByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeGlobalRankingScoresByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPutGlobalRankingScoreTask>> FGs2Ranking2RestClient::PutGlobalRankingScore(
        const Request::FPutGlobalRankingScoreRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPutGlobalRankingScoreTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPutGlobalRankingScoreByUserIdTask>> FGs2Ranking2RestClient::PutGlobalRankingScoreByUserId(
        const Request::FPutGlobalRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPutGlobalRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalRankingScoreTask>> FGs2Ranking2RestClient::GetGlobalRankingScore(
        const Request::FGetGlobalRankingScoreRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetGlobalRankingScoreTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalRankingScoreByUserIdTask>> FGs2Ranking2RestClient::GetGlobalRankingScoreByUserId(
        const Request::FGetGlobalRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetGlobalRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteGlobalRankingScoreByUserIdTask>> FGs2Ranking2RestClient::DeleteGlobalRankingScoreByUserId(
        const Request::FDeleteGlobalRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteGlobalRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalRankingReceivedRewardsTask>> FGs2Ranking2RestClient::DescribeGlobalRankingReceivedRewards(
        const Request::FDescribeGlobalRankingReceivedRewardsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeGlobalRankingReceivedRewardsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalRankingReceivedRewardsByUserIdTask>> FGs2Ranking2RestClient::DescribeGlobalRankingReceivedRewardsByUserId(
        const Request::FDescribeGlobalRankingReceivedRewardsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeGlobalRankingReceivedRewardsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateGlobalRankingReceivedRewardTask>> FGs2Ranking2RestClient::CreateGlobalRankingReceivedReward(
        const Request::FCreateGlobalRankingReceivedRewardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateGlobalRankingReceivedRewardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateGlobalRankingReceivedRewardByUserIdTask>> FGs2Ranking2RestClient::CreateGlobalRankingReceivedRewardByUserId(
        const Request::FCreateGlobalRankingReceivedRewardByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateGlobalRankingReceivedRewardByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FReceiveGlobalRankingReceivedRewardTask>> FGs2Ranking2RestClient::ReceiveGlobalRankingReceivedReward(
        const Request::FReceiveGlobalRankingReceivedRewardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FReceiveGlobalRankingReceivedRewardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FReceiveGlobalRankingReceivedRewardByUserIdTask>> FGs2Ranking2RestClient::ReceiveGlobalRankingReceivedRewardByUserId(
        const Request::FReceiveGlobalRankingReceivedRewardByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FReceiveGlobalRankingReceivedRewardByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalRankingReceivedRewardTask>> FGs2Ranking2RestClient::GetGlobalRankingReceivedReward(
        const Request::FGetGlobalRankingReceivedRewardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetGlobalRankingReceivedRewardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalRankingReceivedRewardByUserIdTask>> FGs2Ranking2RestClient::GetGlobalRankingReceivedRewardByUserId(
        const Request::FGetGlobalRankingReceivedRewardByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetGlobalRankingReceivedRewardByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteGlobalRankingReceivedRewardByUserIdTask>> FGs2Ranking2RestClient::DeleteGlobalRankingReceivedRewardByUserId(
        const Request::FDeleteGlobalRankingReceivedRewardByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteGlobalRankingReceivedRewardByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateGlobalRankingReceivedRewardByStampTaskTask>> FGs2Ranking2RestClient::CreateGlobalRankingReceivedRewardByStampTask(
        const Request::FCreateGlobalRankingReceivedRewardByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateGlobalRankingReceivedRewardByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalRankingsTask>> FGs2Ranking2RestClient::DescribeGlobalRankings(
        const Request::FDescribeGlobalRankingsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeGlobalRankingsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalRankingsByUserIdTask>> FGs2Ranking2RestClient::DescribeGlobalRankingsByUserId(
        const Request::FDescribeGlobalRankingsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeGlobalRankingsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalRankingTask>> FGs2Ranking2RestClient::GetGlobalRanking(
        const Request::FGetGlobalRankingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetGlobalRankingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalRankingByUserIdTask>> FGs2Ranking2RestClient::GetGlobalRankingByUserId(
        const Request::FGetGlobalRankingByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetGlobalRankingByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeClusterRankingModelsTask>> FGs2Ranking2RestClient::DescribeClusterRankingModels(
        const Request::FDescribeClusterRankingModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeClusterRankingModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetClusterRankingModelTask>> FGs2Ranking2RestClient::GetClusterRankingModel(
        const Request::FGetClusterRankingModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetClusterRankingModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeClusterRankingModelMastersTask>> FGs2Ranking2RestClient::DescribeClusterRankingModelMasters(
        const Request::FDescribeClusterRankingModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeClusterRankingModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateClusterRankingModelMasterTask>> FGs2Ranking2RestClient::CreateClusterRankingModelMaster(
        const Request::FCreateClusterRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateClusterRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetClusterRankingModelMasterTask>> FGs2Ranking2RestClient::GetClusterRankingModelMaster(
        const Request::FGetClusterRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetClusterRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateClusterRankingModelMasterTask>> FGs2Ranking2RestClient::UpdateClusterRankingModelMaster(
        const Request::FUpdateClusterRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateClusterRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteClusterRankingModelMasterTask>> FGs2Ranking2RestClient::DeleteClusterRankingModelMaster(
        const Request::FDeleteClusterRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteClusterRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeClusterRankingScoresTask>> FGs2Ranking2RestClient::DescribeClusterRankingScores(
        const Request::FDescribeClusterRankingScoresRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeClusterRankingScoresTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeClusterRankingScoresByUserIdTask>> FGs2Ranking2RestClient::DescribeClusterRankingScoresByUserId(
        const Request::FDescribeClusterRankingScoresByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeClusterRankingScoresByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPutClusterRankingScoreTask>> FGs2Ranking2RestClient::PutClusterRankingScore(
        const Request::FPutClusterRankingScoreRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPutClusterRankingScoreTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPutClusterRankingScoreByUserIdTask>> FGs2Ranking2RestClient::PutClusterRankingScoreByUserId(
        const Request::FPutClusterRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPutClusterRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetClusterRankingScoreTask>> FGs2Ranking2RestClient::GetClusterRankingScore(
        const Request::FGetClusterRankingScoreRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetClusterRankingScoreTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetClusterRankingScoreByUserIdTask>> FGs2Ranking2RestClient::GetClusterRankingScoreByUserId(
        const Request::FGetClusterRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetClusterRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteClusterRankingScoreByUserIdTask>> FGs2Ranking2RestClient::DeleteClusterRankingScoreByUserId(
        const Request::FDeleteClusterRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteClusterRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeClusterRankingReceivedRewardsTask>> FGs2Ranking2RestClient::DescribeClusterRankingReceivedRewards(
        const Request::FDescribeClusterRankingReceivedRewardsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeClusterRankingReceivedRewardsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeClusterRankingReceivedRewardsByUserIdTask>> FGs2Ranking2RestClient::DescribeClusterRankingReceivedRewardsByUserId(
        const Request::FDescribeClusterRankingReceivedRewardsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeClusterRankingReceivedRewardsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateClusterRankingReceivedRewardTask>> FGs2Ranking2RestClient::CreateClusterRankingReceivedReward(
        const Request::FCreateClusterRankingReceivedRewardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateClusterRankingReceivedRewardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateClusterRankingReceivedRewardByUserIdTask>> FGs2Ranking2RestClient::CreateClusterRankingReceivedRewardByUserId(
        const Request::FCreateClusterRankingReceivedRewardByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateClusterRankingReceivedRewardByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FReceiveClusterRankingReceivedRewardTask>> FGs2Ranking2RestClient::ReceiveClusterRankingReceivedReward(
        const Request::FReceiveClusterRankingReceivedRewardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FReceiveClusterRankingReceivedRewardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FReceiveClusterRankingReceivedRewardByUserIdTask>> FGs2Ranking2RestClient::ReceiveClusterRankingReceivedRewardByUserId(
        const Request::FReceiveClusterRankingReceivedRewardByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FReceiveClusterRankingReceivedRewardByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetClusterRankingReceivedRewardTask>> FGs2Ranking2RestClient::GetClusterRankingReceivedReward(
        const Request::FGetClusterRankingReceivedRewardRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetClusterRankingReceivedRewardTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetClusterRankingReceivedRewardByUserIdTask>> FGs2Ranking2RestClient::GetClusterRankingReceivedRewardByUserId(
        const Request::FGetClusterRankingReceivedRewardByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetClusterRankingReceivedRewardByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteClusterRankingReceivedRewardByUserIdTask>> FGs2Ranking2RestClient::DeleteClusterRankingReceivedRewardByUserId(
        const Request::FDeleteClusterRankingReceivedRewardByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteClusterRankingReceivedRewardByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateClusterRankingReceivedRewardByStampTaskTask>> FGs2Ranking2RestClient::CreateClusterRankingReceivedRewardByStampTask(
        const Request::FCreateClusterRankingReceivedRewardByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateClusterRankingReceivedRewardByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeClusterRankingsTask>> FGs2Ranking2RestClient::DescribeClusterRankings(
        const Request::FDescribeClusterRankingsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeClusterRankingsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeClusterRankingsByUserIdTask>> FGs2Ranking2RestClient::DescribeClusterRankingsByUserId(
        const Request::FDescribeClusterRankingsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeClusterRankingsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetClusterRankingTask>> FGs2Ranking2RestClient::GetClusterRanking(
        const Request::FGetClusterRankingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetClusterRankingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetClusterRankingByUserIdTask>> FGs2Ranking2RestClient::GetClusterRankingByUserId(
        const Request::FGetClusterRankingByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetClusterRankingByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribeRankingModelsTask>> FGs2Ranking2RestClient::DescribeSubscribeRankingModels(
        const Request::FDescribeSubscribeRankingModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSubscribeRankingModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeRankingModelTask>> FGs2Ranking2RestClient::GetSubscribeRankingModel(
        const Request::FGetSubscribeRankingModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSubscribeRankingModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribeRankingModelMastersTask>> FGs2Ranking2RestClient::DescribeSubscribeRankingModelMasters(
        const Request::FDescribeSubscribeRankingModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSubscribeRankingModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateSubscribeRankingModelMasterTask>> FGs2Ranking2RestClient::CreateSubscribeRankingModelMaster(
        const Request::FCreateSubscribeRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateSubscribeRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeRankingModelMasterTask>> FGs2Ranking2RestClient::GetSubscribeRankingModelMaster(
        const Request::FGetSubscribeRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSubscribeRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateSubscribeRankingModelMasterTask>> FGs2Ranking2RestClient::UpdateSubscribeRankingModelMaster(
        const Request::FUpdateSubscribeRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateSubscribeRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteSubscribeRankingModelMasterTask>> FGs2Ranking2RestClient::DeleteSubscribeRankingModelMaster(
        const Request::FDeleteSubscribeRankingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteSubscribeRankingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribesTask>> FGs2Ranking2RestClient::DescribeSubscribes(
        const Request::FDescribeSubscribesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSubscribesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribesByUserIdTask>> FGs2Ranking2RestClient::DescribeSubscribesByUserId(
        const Request::FDescribeSubscribesByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSubscribesByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAddSubscribeTask>> FGs2Ranking2RestClient::AddSubscribe(
        const Request::FAddSubscribeRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAddSubscribeTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAddSubscribeByUserIdTask>> FGs2Ranking2RestClient::AddSubscribeByUserId(
        const Request::FAddSubscribeByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAddSubscribeByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribeRankingScoresTask>> FGs2Ranking2RestClient::DescribeSubscribeRankingScores(
        const Request::FDescribeSubscribeRankingScoresRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSubscribeRankingScoresTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribeRankingScoresByUserIdTask>> FGs2Ranking2RestClient::DescribeSubscribeRankingScoresByUserId(
        const Request::FDescribeSubscribeRankingScoresByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSubscribeRankingScoresByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPutSubscribeRankingScoreTask>> FGs2Ranking2RestClient::PutSubscribeRankingScore(
        const Request::FPutSubscribeRankingScoreRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPutSubscribeRankingScoreTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPutSubscribeRankingScoreByUserIdTask>> FGs2Ranking2RestClient::PutSubscribeRankingScoreByUserId(
        const Request::FPutSubscribeRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPutSubscribeRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeRankingScoreTask>> FGs2Ranking2RestClient::GetSubscribeRankingScore(
        const Request::FGetSubscribeRankingScoreRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSubscribeRankingScoreTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeRankingScoreByUserIdTask>> FGs2Ranking2RestClient::GetSubscribeRankingScoreByUserId(
        const Request::FGetSubscribeRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSubscribeRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteSubscribeRankingScoreByUserIdTask>> FGs2Ranking2RestClient::DeleteSubscribeRankingScoreByUserId(
        const Request::FDeleteSubscribeRankingScoreByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteSubscribeRankingScoreByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribeRankingsTask>> FGs2Ranking2RestClient::DescribeSubscribeRankings(
        const Request::FDescribeSubscribeRankingsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSubscribeRankingsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribeRankingsByUserIdTask>> FGs2Ranking2RestClient::DescribeSubscribeRankingsByUserId(
        const Request::FDescribeSubscribeRankingsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSubscribeRankingsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeRankingTask>> FGs2Ranking2RestClient::GetSubscribeRanking(
        const Request::FGetSubscribeRankingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSubscribeRankingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeRankingByUserIdTask>> FGs2Ranking2RestClient::GetSubscribeRankingByUserId(
        const Request::FGetSubscribeRankingByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSubscribeRankingByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> FGs2Ranking2RestClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentRankingMasterTask>> FGs2Ranking2RestClient::GetCurrentRankingMaster(
        const Request::FGetCurrentRankingMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetCurrentRankingMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentRankingMasterTask>> FGs2Ranking2RestClient::UpdateCurrentRankingMaster(
        const Request::FUpdateCurrentRankingMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentRankingMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentRankingMasterFromGitHubTask>> FGs2Ranking2RestClient::UpdateCurrentRankingMasterFromGitHub(
        const Request::FUpdateCurrentRankingMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentRankingMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeTask>> FGs2Ranking2RestClient::GetSubscribe(
        const Request::FGetSubscribeRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSubscribeTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeByUserIdTask>> FGs2Ranking2RestClient::GetSubscribeByUserId(
        const Request::FGetSubscribeByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSubscribeByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteSubscribeTask>> FGs2Ranking2RestClient::DeleteSubscribe(
        const Request::FDeleteSubscribeRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteSubscribeTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteSubscribeByUserIdTask>> FGs2Ranking2RestClient::DeleteSubscribeByUserId(
        const Request::FDeleteSubscribeByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteSubscribeByUserIdTask>>(
            Session,
            Request
        );
    }
}