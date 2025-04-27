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
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Task/Rest/DumpUserDataByUserIdTask.h"
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Task/Rest/CheckDumpUserDataByUserIdTask.h"
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Task/Rest/CleanUserDataByUserIdTask.h"
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Task/Rest/CheckCleanUserDataByUserIdTask.h"
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Task/Rest/PrepareImportUserDataByUserIdTask.h"
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Task/Rest/ImportUserDataByUserIdTask.h"
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Task/Rest/CheckImportUserDataByUserIdTask.h"
#include "Request/DescribeGlobalRankingModelsRequest.h"
#include "Task/Rest/DescribeGlobalRankingModelsTask.h"
#include "Request/GetGlobalRankingModelRequest.h"
#include "Task/Rest/GetGlobalRankingModelTask.h"
#include "Request/DescribeGlobalRankingModelMastersRequest.h"
#include "Task/Rest/DescribeGlobalRankingModelMastersTask.h"
#include "Request/CreateGlobalRankingModelMasterRequest.h"
#include "Task/Rest/CreateGlobalRankingModelMasterTask.h"
#include "Request/GetGlobalRankingModelMasterRequest.h"
#include "Task/Rest/GetGlobalRankingModelMasterTask.h"
#include "Request/UpdateGlobalRankingModelMasterRequest.h"
#include "Task/Rest/UpdateGlobalRankingModelMasterTask.h"
#include "Request/DeleteGlobalRankingModelMasterRequest.h"
#include "Task/Rest/DeleteGlobalRankingModelMasterTask.h"
#include "Request/DescribeGlobalRankingScoresRequest.h"
#include "Task/Rest/DescribeGlobalRankingScoresTask.h"
#include "Request/DescribeGlobalRankingScoresByUserIdRequest.h"
#include "Task/Rest/DescribeGlobalRankingScoresByUserIdTask.h"
#include "Request/PutGlobalRankingScoreRequest.h"
#include "Task/Rest/PutGlobalRankingScoreTask.h"
#include "Request/PutGlobalRankingScoreByUserIdRequest.h"
#include "Task/Rest/PutGlobalRankingScoreByUserIdTask.h"
#include "Request/GetGlobalRankingScoreRequest.h"
#include "Task/Rest/GetGlobalRankingScoreTask.h"
#include "Request/GetGlobalRankingScoreByUserIdRequest.h"
#include "Task/Rest/GetGlobalRankingScoreByUserIdTask.h"
#include "Request/DeleteGlobalRankingScoreByUserIdRequest.h"
#include "Task/Rest/DeleteGlobalRankingScoreByUserIdTask.h"
#include "Request/VerifyGlobalRankingScoreRequest.h"
#include "Task/Rest/VerifyGlobalRankingScoreTask.h"
#include "Request/VerifyGlobalRankingScoreByUserIdRequest.h"
#include "Task/Rest/VerifyGlobalRankingScoreByUserIdTask.h"
#include "Request/VerifyGlobalRankingScoreByStampTaskRequest.h"
#include "Task/Rest/VerifyGlobalRankingScoreByStampTaskTask.h"
#include "Request/DescribeGlobalRankingReceivedRewardsRequest.h"
#include "Task/Rest/DescribeGlobalRankingReceivedRewardsTask.h"
#include "Request/DescribeGlobalRankingReceivedRewardsByUserIdRequest.h"
#include "Task/Rest/DescribeGlobalRankingReceivedRewardsByUserIdTask.h"
#include "Request/CreateGlobalRankingReceivedRewardRequest.h"
#include "Task/Rest/CreateGlobalRankingReceivedRewardTask.h"
#include "Request/CreateGlobalRankingReceivedRewardByUserIdRequest.h"
#include "Task/Rest/CreateGlobalRankingReceivedRewardByUserIdTask.h"
#include "Request/ReceiveGlobalRankingReceivedRewardRequest.h"
#include "Task/Rest/ReceiveGlobalRankingReceivedRewardTask.h"
#include "Request/ReceiveGlobalRankingReceivedRewardByUserIdRequest.h"
#include "Task/Rest/ReceiveGlobalRankingReceivedRewardByUserIdTask.h"
#include "Request/GetGlobalRankingReceivedRewardRequest.h"
#include "Task/Rest/GetGlobalRankingReceivedRewardTask.h"
#include "Request/GetGlobalRankingReceivedRewardByUserIdRequest.h"
#include "Task/Rest/GetGlobalRankingReceivedRewardByUserIdTask.h"
#include "Request/DeleteGlobalRankingReceivedRewardByUserIdRequest.h"
#include "Task/Rest/DeleteGlobalRankingReceivedRewardByUserIdTask.h"
#include "Request/CreateGlobalRankingReceivedRewardByStampTaskRequest.h"
#include "Task/Rest/CreateGlobalRankingReceivedRewardByStampTaskTask.h"
#include "Request/DescribeGlobalRankingsRequest.h"
#include "Task/Rest/DescribeGlobalRankingsTask.h"
#include "Request/DescribeGlobalRankingsByUserIdRequest.h"
#include "Task/Rest/DescribeGlobalRankingsByUserIdTask.h"
#include "Request/GetGlobalRankingRequest.h"
#include "Task/Rest/GetGlobalRankingTask.h"
#include "Request/GetGlobalRankingByUserIdRequest.h"
#include "Task/Rest/GetGlobalRankingByUserIdTask.h"
#include "Request/DescribeClusterRankingModelsRequest.h"
#include "Task/Rest/DescribeClusterRankingModelsTask.h"
#include "Request/GetClusterRankingModelRequest.h"
#include "Task/Rest/GetClusterRankingModelTask.h"
#include "Request/DescribeClusterRankingModelMastersRequest.h"
#include "Task/Rest/DescribeClusterRankingModelMastersTask.h"
#include "Request/CreateClusterRankingModelMasterRequest.h"
#include "Task/Rest/CreateClusterRankingModelMasterTask.h"
#include "Request/GetClusterRankingModelMasterRequest.h"
#include "Task/Rest/GetClusterRankingModelMasterTask.h"
#include "Request/UpdateClusterRankingModelMasterRequest.h"
#include "Task/Rest/UpdateClusterRankingModelMasterTask.h"
#include "Request/DeleteClusterRankingModelMasterRequest.h"
#include "Task/Rest/DeleteClusterRankingModelMasterTask.h"
#include "Request/DescribeClusterRankingScoresRequest.h"
#include "Task/Rest/DescribeClusterRankingScoresTask.h"
#include "Request/DescribeClusterRankingScoresByUserIdRequest.h"
#include "Task/Rest/DescribeClusterRankingScoresByUserIdTask.h"
#include "Request/PutClusterRankingScoreRequest.h"
#include "Task/Rest/PutClusterRankingScoreTask.h"
#include "Request/PutClusterRankingScoreByUserIdRequest.h"
#include "Task/Rest/PutClusterRankingScoreByUserIdTask.h"
#include "Request/GetClusterRankingScoreRequest.h"
#include "Task/Rest/GetClusterRankingScoreTask.h"
#include "Request/GetClusterRankingScoreByUserIdRequest.h"
#include "Task/Rest/GetClusterRankingScoreByUserIdTask.h"
#include "Request/DeleteClusterRankingScoreByUserIdRequest.h"
#include "Task/Rest/DeleteClusterRankingScoreByUserIdTask.h"
#include "Request/VerifyClusterRankingScoreRequest.h"
#include "Task/Rest/VerifyClusterRankingScoreTask.h"
#include "Request/VerifyClusterRankingScoreByUserIdRequest.h"
#include "Task/Rest/VerifyClusterRankingScoreByUserIdTask.h"
#include "Request/VerifyClusterRankingScoreByStampTaskRequest.h"
#include "Task/Rest/VerifyClusterRankingScoreByStampTaskTask.h"
#include "Request/DescribeClusterRankingReceivedRewardsRequest.h"
#include "Task/Rest/DescribeClusterRankingReceivedRewardsTask.h"
#include "Request/DescribeClusterRankingReceivedRewardsByUserIdRequest.h"
#include "Task/Rest/DescribeClusterRankingReceivedRewardsByUserIdTask.h"
#include "Request/CreateClusterRankingReceivedRewardRequest.h"
#include "Task/Rest/CreateClusterRankingReceivedRewardTask.h"
#include "Request/CreateClusterRankingReceivedRewardByUserIdRequest.h"
#include "Task/Rest/CreateClusterRankingReceivedRewardByUserIdTask.h"
#include "Request/ReceiveClusterRankingReceivedRewardRequest.h"
#include "Task/Rest/ReceiveClusterRankingReceivedRewardTask.h"
#include "Request/ReceiveClusterRankingReceivedRewardByUserIdRequest.h"
#include "Task/Rest/ReceiveClusterRankingReceivedRewardByUserIdTask.h"
#include "Request/GetClusterRankingReceivedRewardRequest.h"
#include "Task/Rest/GetClusterRankingReceivedRewardTask.h"
#include "Request/GetClusterRankingReceivedRewardByUserIdRequest.h"
#include "Task/Rest/GetClusterRankingReceivedRewardByUserIdTask.h"
#include "Request/DeleteClusterRankingReceivedRewardByUserIdRequest.h"
#include "Task/Rest/DeleteClusterRankingReceivedRewardByUserIdTask.h"
#include "Request/CreateClusterRankingReceivedRewardByStampTaskRequest.h"
#include "Task/Rest/CreateClusterRankingReceivedRewardByStampTaskTask.h"
#include "Request/DescribeClusterRankingsRequest.h"
#include "Task/Rest/DescribeClusterRankingsTask.h"
#include "Request/DescribeClusterRankingsByUserIdRequest.h"
#include "Task/Rest/DescribeClusterRankingsByUserIdTask.h"
#include "Request/GetClusterRankingRequest.h"
#include "Task/Rest/GetClusterRankingTask.h"
#include "Request/GetClusterRankingByUserIdRequest.h"
#include "Task/Rest/GetClusterRankingByUserIdTask.h"
#include "Request/DescribeSubscribeRankingModelsRequest.h"
#include "Task/Rest/DescribeSubscribeRankingModelsTask.h"
#include "Request/GetSubscribeRankingModelRequest.h"
#include "Task/Rest/GetSubscribeRankingModelTask.h"
#include "Request/DescribeSubscribeRankingModelMastersRequest.h"
#include "Task/Rest/DescribeSubscribeRankingModelMastersTask.h"
#include "Request/CreateSubscribeRankingModelMasterRequest.h"
#include "Task/Rest/CreateSubscribeRankingModelMasterTask.h"
#include "Request/GetSubscribeRankingModelMasterRequest.h"
#include "Task/Rest/GetSubscribeRankingModelMasterTask.h"
#include "Request/UpdateSubscribeRankingModelMasterRequest.h"
#include "Task/Rest/UpdateSubscribeRankingModelMasterTask.h"
#include "Request/DeleteSubscribeRankingModelMasterRequest.h"
#include "Task/Rest/DeleteSubscribeRankingModelMasterTask.h"
#include "Request/DescribeSubscribesRequest.h"
#include "Task/Rest/DescribeSubscribesTask.h"
#include "Request/DescribeSubscribesByUserIdRequest.h"
#include "Task/Rest/DescribeSubscribesByUserIdTask.h"
#include "Request/AddSubscribeRequest.h"
#include "Task/Rest/AddSubscribeTask.h"
#include "Request/AddSubscribeByUserIdRequest.h"
#include "Task/Rest/AddSubscribeByUserIdTask.h"
#include "Request/DescribeSubscribeRankingScoresRequest.h"
#include "Task/Rest/DescribeSubscribeRankingScoresTask.h"
#include "Request/DescribeSubscribeRankingScoresByUserIdRequest.h"
#include "Task/Rest/DescribeSubscribeRankingScoresByUserIdTask.h"
#include "Request/PutSubscribeRankingScoreRequest.h"
#include "Task/Rest/PutSubscribeRankingScoreTask.h"
#include "Request/PutSubscribeRankingScoreByUserIdRequest.h"
#include "Task/Rest/PutSubscribeRankingScoreByUserIdTask.h"
#include "Request/GetSubscribeRankingScoreRequest.h"
#include "Task/Rest/GetSubscribeRankingScoreTask.h"
#include "Request/GetSubscribeRankingScoreByUserIdRequest.h"
#include "Task/Rest/GetSubscribeRankingScoreByUserIdTask.h"
#include "Request/DeleteSubscribeRankingScoreByUserIdRequest.h"
#include "Task/Rest/DeleteSubscribeRankingScoreByUserIdTask.h"
#include "Request/VerifySubscribeRankingScoreRequest.h"
#include "Task/Rest/VerifySubscribeRankingScoreTask.h"
#include "Request/VerifySubscribeRankingScoreByUserIdRequest.h"
#include "Task/Rest/VerifySubscribeRankingScoreByUserIdTask.h"
#include "Request/VerifySubscribeRankingScoreByStampTaskRequest.h"
#include "Task/Rest/VerifySubscribeRankingScoreByStampTaskTask.h"
#include "Request/DescribeSubscribeRankingsRequest.h"
#include "Task/Rest/DescribeSubscribeRankingsTask.h"
#include "Request/DescribeSubscribeRankingsByUserIdRequest.h"
#include "Task/Rest/DescribeSubscribeRankingsByUserIdTask.h"
#include "Request/GetSubscribeRankingRequest.h"
#include "Task/Rest/GetSubscribeRankingTask.h"
#include "Request/GetSubscribeRankingByUserIdRequest.h"
#include "Task/Rest/GetSubscribeRankingByUserIdTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentRankingMasterRequest.h"
#include "Task/Rest/GetCurrentRankingMasterTask.h"
#include "Request/PreUpdateCurrentRankingMasterRequest.h"
#include "Task/Rest/PreUpdateCurrentRankingMasterTask.h"
#include "Request/UpdateCurrentRankingMasterRequest.h"
#include "Task/Rest/UpdateCurrentRankingMasterTask.h"
#include "Request/UpdateCurrentRankingMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentRankingMasterFromGitHubTask.h"
#include "Request/GetSubscribeRequest.h"
#include "Task/Rest/GetSubscribeTask.h"
#include "Request/GetSubscribeByUserIdRequest.h"
#include "Task/Rest/GetSubscribeByUserIdTask.h"
#include "Request/DeleteSubscribeRequest.h"
#include "Task/Rest/DeleteSubscribeTask.h"
#include "Request/DeleteSubscribeByUserIdRequest.h"
#include "Task/Rest/DeleteSubscribeByUserIdTask.h"

namespace Gs2::Ranking2
{
    class GS2RANKING2_API FGs2Ranking2RestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2Ranking2RestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDumpUserDataByUserIdTask>> DumpUserDataByUserId(
            const Request::FDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckDumpUserDataByUserIdTask>> CheckDumpUserDataByUserId(
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCleanUserDataByUserIdTask>> CleanUserDataByUserId(
            const Request::FCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckCleanUserDataByUserIdTask>> CheckCleanUserDataByUserId(
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareImportUserDataByUserIdTask>> PrepareImportUserDataByUserId(
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FImportUserDataByUserIdTask>> ImportUserDataByUserId(
            const Request::FImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckImportUserDataByUserIdTask>> CheckImportUserDataByUserId(
            const Request::FCheckImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalRankingModelsTask>> DescribeGlobalRankingModels(
            const Request::FDescribeGlobalRankingModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalRankingModelTask>> GetGlobalRankingModel(
            const Request::FGetGlobalRankingModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalRankingModelMastersTask>> DescribeGlobalRankingModelMasters(
            const Request::FDescribeGlobalRankingModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateGlobalRankingModelMasterTask>> CreateGlobalRankingModelMaster(
            const Request::FCreateGlobalRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalRankingModelMasterTask>> GetGlobalRankingModelMaster(
            const Request::FGetGlobalRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateGlobalRankingModelMasterTask>> UpdateGlobalRankingModelMaster(
            const Request::FUpdateGlobalRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteGlobalRankingModelMasterTask>> DeleteGlobalRankingModelMaster(
            const Request::FDeleteGlobalRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalRankingScoresTask>> DescribeGlobalRankingScores(
            const Request::FDescribeGlobalRankingScoresRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalRankingScoresByUserIdTask>> DescribeGlobalRankingScoresByUserId(
            const Request::FDescribeGlobalRankingScoresByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPutGlobalRankingScoreTask>> PutGlobalRankingScore(
            const Request::FPutGlobalRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPutGlobalRankingScoreByUserIdTask>> PutGlobalRankingScoreByUserId(
            const Request::FPutGlobalRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalRankingScoreTask>> GetGlobalRankingScore(
            const Request::FGetGlobalRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalRankingScoreByUserIdTask>> GetGlobalRankingScoreByUserId(
            const Request::FGetGlobalRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteGlobalRankingScoreByUserIdTask>> DeleteGlobalRankingScoreByUserId(
            const Request::FDeleteGlobalRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyGlobalRankingScoreTask>> VerifyGlobalRankingScore(
            const Request::FVerifyGlobalRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyGlobalRankingScoreByUserIdTask>> VerifyGlobalRankingScoreByUserId(
            const Request::FVerifyGlobalRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyGlobalRankingScoreByStampTaskTask>> VerifyGlobalRankingScoreByStampTask(
            const Request::FVerifyGlobalRankingScoreByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalRankingReceivedRewardsTask>> DescribeGlobalRankingReceivedRewards(
            const Request::FDescribeGlobalRankingReceivedRewardsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalRankingReceivedRewardsByUserIdTask>> DescribeGlobalRankingReceivedRewardsByUserId(
            const Request::FDescribeGlobalRankingReceivedRewardsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateGlobalRankingReceivedRewardTask>> CreateGlobalRankingReceivedReward(
            const Request::FCreateGlobalRankingReceivedRewardRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateGlobalRankingReceivedRewardByUserIdTask>> CreateGlobalRankingReceivedRewardByUserId(
            const Request::FCreateGlobalRankingReceivedRewardByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReceiveGlobalRankingReceivedRewardTask>> ReceiveGlobalRankingReceivedReward(
            const Request::FReceiveGlobalRankingReceivedRewardRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReceiveGlobalRankingReceivedRewardByUserIdTask>> ReceiveGlobalRankingReceivedRewardByUserId(
            const Request::FReceiveGlobalRankingReceivedRewardByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalRankingReceivedRewardTask>> GetGlobalRankingReceivedReward(
            const Request::FGetGlobalRankingReceivedRewardRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalRankingReceivedRewardByUserIdTask>> GetGlobalRankingReceivedRewardByUserId(
            const Request::FGetGlobalRankingReceivedRewardByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteGlobalRankingReceivedRewardByUserIdTask>> DeleteGlobalRankingReceivedRewardByUserId(
            const Request::FDeleteGlobalRankingReceivedRewardByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateGlobalRankingReceivedRewardByStampTaskTask>> CreateGlobalRankingReceivedRewardByStampTask(
            const Request::FCreateGlobalRankingReceivedRewardByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalRankingsTask>> DescribeGlobalRankings(
            const Request::FDescribeGlobalRankingsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalRankingsByUserIdTask>> DescribeGlobalRankingsByUserId(
            const Request::FDescribeGlobalRankingsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalRankingTask>> GetGlobalRanking(
            const Request::FGetGlobalRankingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalRankingByUserIdTask>> GetGlobalRankingByUserId(
            const Request::FGetGlobalRankingByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeClusterRankingModelsTask>> DescribeClusterRankingModels(
            const Request::FDescribeClusterRankingModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetClusterRankingModelTask>> GetClusterRankingModel(
            const Request::FGetClusterRankingModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeClusterRankingModelMastersTask>> DescribeClusterRankingModelMasters(
            const Request::FDescribeClusterRankingModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateClusterRankingModelMasterTask>> CreateClusterRankingModelMaster(
            const Request::FCreateClusterRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetClusterRankingModelMasterTask>> GetClusterRankingModelMaster(
            const Request::FGetClusterRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateClusterRankingModelMasterTask>> UpdateClusterRankingModelMaster(
            const Request::FUpdateClusterRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteClusterRankingModelMasterTask>> DeleteClusterRankingModelMaster(
            const Request::FDeleteClusterRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeClusterRankingScoresTask>> DescribeClusterRankingScores(
            const Request::FDescribeClusterRankingScoresRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeClusterRankingScoresByUserIdTask>> DescribeClusterRankingScoresByUserId(
            const Request::FDescribeClusterRankingScoresByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPutClusterRankingScoreTask>> PutClusterRankingScore(
            const Request::FPutClusterRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPutClusterRankingScoreByUserIdTask>> PutClusterRankingScoreByUserId(
            const Request::FPutClusterRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetClusterRankingScoreTask>> GetClusterRankingScore(
            const Request::FGetClusterRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetClusterRankingScoreByUserIdTask>> GetClusterRankingScoreByUserId(
            const Request::FGetClusterRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteClusterRankingScoreByUserIdTask>> DeleteClusterRankingScoreByUserId(
            const Request::FDeleteClusterRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyClusterRankingScoreTask>> VerifyClusterRankingScore(
            const Request::FVerifyClusterRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyClusterRankingScoreByUserIdTask>> VerifyClusterRankingScoreByUserId(
            const Request::FVerifyClusterRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyClusterRankingScoreByStampTaskTask>> VerifyClusterRankingScoreByStampTask(
            const Request::FVerifyClusterRankingScoreByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeClusterRankingReceivedRewardsTask>> DescribeClusterRankingReceivedRewards(
            const Request::FDescribeClusterRankingReceivedRewardsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeClusterRankingReceivedRewardsByUserIdTask>> DescribeClusterRankingReceivedRewardsByUserId(
            const Request::FDescribeClusterRankingReceivedRewardsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateClusterRankingReceivedRewardTask>> CreateClusterRankingReceivedReward(
            const Request::FCreateClusterRankingReceivedRewardRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateClusterRankingReceivedRewardByUserIdTask>> CreateClusterRankingReceivedRewardByUserId(
            const Request::FCreateClusterRankingReceivedRewardByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReceiveClusterRankingReceivedRewardTask>> ReceiveClusterRankingReceivedReward(
            const Request::FReceiveClusterRankingReceivedRewardRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReceiveClusterRankingReceivedRewardByUserIdTask>> ReceiveClusterRankingReceivedRewardByUserId(
            const Request::FReceiveClusterRankingReceivedRewardByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetClusterRankingReceivedRewardTask>> GetClusterRankingReceivedReward(
            const Request::FGetClusterRankingReceivedRewardRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetClusterRankingReceivedRewardByUserIdTask>> GetClusterRankingReceivedRewardByUserId(
            const Request::FGetClusterRankingReceivedRewardByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteClusterRankingReceivedRewardByUserIdTask>> DeleteClusterRankingReceivedRewardByUserId(
            const Request::FDeleteClusterRankingReceivedRewardByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateClusterRankingReceivedRewardByStampTaskTask>> CreateClusterRankingReceivedRewardByStampTask(
            const Request::FCreateClusterRankingReceivedRewardByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeClusterRankingsTask>> DescribeClusterRankings(
            const Request::FDescribeClusterRankingsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeClusterRankingsByUserIdTask>> DescribeClusterRankingsByUserId(
            const Request::FDescribeClusterRankingsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetClusterRankingTask>> GetClusterRanking(
            const Request::FGetClusterRankingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetClusterRankingByUserIdTask>> GetClusterRankingByUserId(
            const Request::FGetClusterRankingByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribeRankingModelsTask>> DescribeSubscribeRankingModels(
            const Request::FDescribeSubscribeRankingModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeRankingModelTask>> GetSubscribeRankingModel(
            const Request::FGetSubscribeRankingModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribeRankingModelMastersTask>> DescribeSubscribeRankingModelMasters(
            const Request::FDescribeSubscribeRankingModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateSubscribeRankingModelMasterTask>> CreateSubscribeRankingModelMaster(
            const Request::FCreateSubscribeRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeRankingModelMasterTask>> GetSubscribeRankingModelMaster(
            const Request::FGetSubscribeRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateSubscribeRankingModelMasterTask>> UpdateSubscribeRankingModelMaster(
            const Request::FUpdateSubscribeRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteSubscribeRankingModelMasterTask>> DeleteSubscribeRankingModelMaster(
            const Request::FDeleteSubscribeRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribesTask>> DescribeSubscribes(
            const Request::FDescribeSubscribesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribesByUserIdTask>> DescribeSubscribesByUserId(
            const Request::FDescribeSubscribesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddSubscribeTask>> AddSubscribe(
            const Request::FAddSubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddSubscribeByUserIdTask>> AddSubscribeByUserId(
            const Request::FAddSubscribeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribeRankingScoresTask>> DescribeSubscribeRankingScores(
            const Request::FDescribeSubscribeRankingScoresRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribeRankingScoresByUserIdTask>> DescribeSubscribeRankingScoresByUserId(
            const Request::FDescribeSubscribeRankingScoresByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPutSubscribeRankingScoreTask>> PutSubscribeRankingScore(
            const Request::FPutSubscribeRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPutSubscribeRankingScoreByUserIdTask>> PutSubscribeRankingScoreByUserId(
            const Request::FPutSubscribeRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeRankingScoreTask>> GetSubscribeRankingScore(
            const Request::FGetSubscribeRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeRankingScoreByUserIdTask>> GetSubscribeRankingScoreByUserId(
            const Request::FGetSubscribeRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteSubscribeRankingScoreByUserIdTask>> DeleteSubscribeRankingScoreByUserId(
            const Request::FDeleteSubscribeRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifySubscribeRankingScoreTask>> VerifySubscribeRankingScore(
            const Request::FVerifySubscribeRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifySubscribeRankingScoreByUserIdTask>> VerifySubscribeRankingScoreByUserId(
            const Request::FVerifySubscribeRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifySubscribeRankingScoreByStampTaskTask>> VerifySubscribeRankingScoreByStampTask(
            const Request::FVerifySubscribeRankingScoreByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribeRankingsTask>> DescribeSubscribeRankings(
            const Request::FDescribeSubscribeRankingsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribeRankingsByUserIdTask>> DescribeSubscribeRankingsByUserId(
            const Request::FDescribeSubscribeRankingsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeRankingTask>> GetSubscribeRanking(
            const Request::FGetSubscribeRankingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeRankingByUserIdTask>> GetSubscribeRankingByUserId(
            const Request::FGetSubscribeRankingByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentRankingMasterTask>> GetCurrentRankingMaster(
            const Request::FGetCurrentRankingMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPreUpdateCurrentRankingMasterTask>> PreUpdateCurrentRankingMaster(
            const Request::FPreUpdateCurrentRankingMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentRankingMasterTask>> UpdateCurrentRankingMaster(
            const Request::FUpdateCurrentRankingMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentRankingMasterFromGitHubTask>> UpdateCurrentRankingMasterFromGitHub(
            const Request::FUpdateCurrentRankingMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeTask>> GetSubscribe(
            const Request::FGetSubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeByUserIdTask>> GetSubscribeByUserId(
            const Request::FGetSubscribeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteSubscribeTask>> DeleteSubscribe(
            const Request::FDeleteSubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteSubscribeByUserIdTask>> DeleteSubscribeByUserId(
            const Request::FDeleteSubscribeByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2Ranking2RestClient, ESPMode::ThreadSafe> FGs2Ranking2RestClientPtr;
}