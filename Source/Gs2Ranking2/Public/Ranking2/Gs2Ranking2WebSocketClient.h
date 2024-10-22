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
#include "Request/DescribeGlobalRankingModelsRequest.h"
#include "Task/WebSocket/DescribeGlobalRankingModelsTask.h"
#include "Request/GetGlobalRankingModelRequest.h"
#include "Task/WebSocket/GetGlobalRankingModelTask.h"
#include "Request/DescribeGlobalRankingModelMastersRequest.h"
#include "Task/WebSocket/DescribeGlobalRankingModelMastersTask.h"
#include "Request/CreateGlobalRankingModelMasterRequest.h"
#include "Task/WebSocket/CreateGlobalRankingModelMasterTask.h"
#include "Request/GetGlobalRankingModelMasterRequest.h"
#include "Task/WebSocket/GetGlobalRankingModelMasterTask.h"
#include "Request/UpdateGlobalRankingModelMasterRequest.h"
#include "Task/WebSocket/UpdateGlobalRankingModelMasterTask.h"
#include "Request/DeleteGlobalRankingModelMasterRequest.h"
#include "Task/WebSocket/DeleteGlobalRankingModelMasterTask.h"
#include "Request/DescribeGlobalRankingScoresRequest.h"
#include "Task/WebSocket/DescribeGlobalRankingScoresTask.h"
#include "Request/DescribeGlobalRankingScoresByUserIdRequest.h"
#include "Task/WebSocket/DescribeGlobalRankingScoresByUserIdTask.h"
#include "Request/PutGlobalRankingScoreRequest.h"
#include "Task/WebSocket/PutGlobalRankingScoreTask.h"
#include "Request/PutGlobalRankingScoreByUserIdRequest.h"
#include "Task/WebSocket/PutGlobalRankingScoreByUserIdTask.h"
#include "Request/GetGlobalRankingScoreRequest.h"
#include "Task/WebSocket/GetGlobalRankingScoreTask.h"
#include "Request/GetGlobalRankingScoreByUserIdRequest.h"
#include "Task/WebSocket/GetGlobalRankingScoreByUserIdTask.h"
#include "Request/DeleteGlobalRankingScoreByUserIdRequest.h"
#include "Task/WebSocket/DeleteGlobalRankingScoreByUserIdTask.h"
#include "Request/VerifyGlobalRankingScoreRequest.h"
#include "Task/WebSocket/VerifyGlobalRankingScoreTask.h"
#include "Request/VerifyGlobalRankingScoreByUserIdRequest.h"
#include "Task/WebSocket/VerifyGlobalRankingScoreByUserIdTask.h"
#include "Request/VerifyGlobalRankingScoreByStampTaskRequest.h"
#include "Task/WebSocket/VerifyGlobalRankingScoreByStampTaskTask.h"
#include "Request/DescribeGlobalRankingReceivedRewardsRequest.h"
#include "Task/WebSocket/DescribeGlobalRankingReceivedRewardsTask.h"
#include "Request/DescribeGlobalRankingReceivedRewardsByUserIdRequest.h"
#include "Task/WebSocket/DescribeGlobalRankingReceivedRewardsByUserIdTask.h"
#include "Request/CreateGlobalRankingReceivedRewardRequest.h"
#include "Task/WebSocket/CreateGlobalRankingReceivedRewardTask.h"
#include "Request/CreateGlobalRankingReceivedRewardByUserIdRequest.h"
#include "Task/WebSocket/CreateGlobalRankingReceivedRewardByUserIdTask.h"
#include "Request/ReceiveGlobalRankingReceivedRewardRequest.h"
#include "Task/WebSocket/ReceiveGlobalRankingReceivedRewardTask.h"
#include "Request/ReceiveGlobalRankingReceivedRewardByUserIdRequest.h"
#include "Task/WebSocket/ReceiveGlobalRankingReceivedRewardByUserIdTask.h"
#include "Request/GetGlobalRankingReceivedRewardRequest.h"
#include "Task/WebSocket/GetGlobalRankingReceivedRewardTask.h"
#include "Request/GetGlobalRankingReceivedRewardByUserIdRequest.h"
#include "Task/WebSocket/GetGlobalRankingReceivedRewardByUserIdTask.h"
#include "Request/DeleteGlobalRankingReceivedRewardByUserIdRequest.h"
#include "Task/WebSocket/DeleteGlobalRankingReceivedRewardByUserIdTask.h"
#include "Request/CreateGlobalRankingReceivedRewardByStampTaskRequest.h"
#include "Task/WebSocket/CreateGlobalRankingReceivedRewardByStampTaskTask.h"
#include "Request/DescribeGlobalRankingsRequest.h"
#include "Task/WebSocket/DescribeGlobalRankingsTask.h"
#include "Request/DescribeGlobalRankingsByUserIdRequest.h"
#include "Task/WebSocket/DescribeGlobalRankingsByUserIdTask.h"
#include "Request/GetGlobalRankingRequest.h"
#include "Task/WebSocket/GetGlobalRankingTask.h"
#include "Request/GetGlobalRankingByUserIdRequest.h"
#include "Task/WebSocket/GetGlobalRankingByUserIdTask.h"
#include "Request/DescribeClusterRankingModelsRequest.h"
#include "Task/WebSocket/DescribeClusterRankingModelsTask.h"
#include "Request/GetClusterRankingModelRequest.h"
#include "Task/WebSocket/GetClusterRankingModelTask.h"
#include "Request/DescribeClusterRankingModelMastersRequest.h"
#include "Task/WebSocket/DescribeClusterRankingModelMastersTask.h"
#include "Request/CreateClusterRankingModelMasterRequest.h"
#include "Task/WebSocket/CreateClusterRankingModelMasterTask.h"
#include "Request/GetClusterRankingModelMasterRequest.h"
#include "Task/WebSocket/GetClusterRankingModelMasterTask.h"
#include "Request/UpdateClusterRankingModelMasterRequest.h"
#include "Task/WebSocket/UpdateClusterRankingModelMasterTask.h"
#include "Request/DeleteClusterRankingModelMasterRequest.h"
#include "Task/WebSocket/DeleteClusterRankingModelMasterTask.h"
#include "Request/DescribeClusterRankingScoresRequest.h"
#include "Task/WebSocket/DescribeClusterRankingScoresTask.h"
#include "Request/DescribeClusterRankingScoresByUserIdRequest.h"
#include "Task/WebSocket/DescribeClusterRankingScoresByUserIdTask.h"
#include "Request/PutClusterRankingScoreRequest.h"
#include "Task/WebSocket/PutClusterRankingScoreTask.h"
#include "Request/PutClusterRankingScoreByUserIdRequest.h"
#include "Task/WebSocket/PutClusterRankingScoreByUserIdTask.h"
#include "Request/GetClusterRankingScoreRequest.h"
#include "Task/WebSocket/GetClusterRankingScoreTask.h"
#include "Request/GetClusterRankingScoreByUserIdRequest.h"
#include "Task/WebSocket/GetClusterRankingScoreByUserIdTask.h"
#include "Request/DeleteClusterRankingScoreByUserIdRequest.h"
#include "Task/WebSocket/DeleteClusterRankingScoreByUserIdTask.h"
#include "Request/VerifyClusterRankingScoreRequest.h"
#include "Task/WebSocket/VerifyClusterRankingScoreTask.h"
#include "Request/VerifyClusterRankingScoreByUserIdRequest.h"
#include "Task/WebSocket/VerifyClusterRankingScoreByUserIdTask.h"
#include "Request/VerifyClusterRankingScoreByStampTaskRequest.h"
#include "Task/WebSocket/VerifyClusterRankingScoreByStampTaskTask.h"
#include "Request/DescribeClusterRankingReceivedRewardsRequest.h"
#include "Task/WebSocket/DescribeClusterRankingReceivedRewardsTask.h"
#include "Request/DescribeClusterRankingReceivedRewardsByUserIdRequest.h"
#include "Task/WebSocket/DescribeClusterRankingReceivedRewardsByUserIdTask.h"
#include "Request/CreateClusterRankingReceivedRewardRequest.h"
#include "Task/WebSocket/CreateClusterRankingReceivedRewardTask.h"
#include "Request/CreateClusterRankingReceivedRewardByUserIdRequest.h"
#include "Task/WebSocket/CreateClusterRankingReceivedRewardByUserIdTask.h"
#include "Request/ReceiveClusterRankingReceivedRewardRequest.h"
#include "Task/WebSocket/ReceiveClusterRankingReceivedRewardTask.h"
#include "Request/ReceiveClusterRankingReceivedRewardByUserIdRequest.h"
#include "Task/WebSocket/ReceiveClusterRankingReceivedRewardByUserIdTask.h"
#include "Request/GetClusterRankingReceivedRewardRequest.h"
#include "Task/WebSocket/GetClusterRankingReceivedRewardTask.h"
#include "Request/GetClusterRankingReceivedRewardByUserIdRequest.h"
#include "Task/WebSocket/GetClusterRankingReceivedRewardByUserIdTask.h"
#include "Request/DeleteClusterRankingReceivedRewardByUserIdRequest.h"
#include "Task/WebSocket/DeleteClusterRankingReceivedRewardByUserIdTask.h"
#include "Request/CreateClusterRankingReceivedRewardByStampTaskRequest.h"
#include "Task/WebSocket/CreateClusterRankingReceivedRewardByStampTaskTask.h"
#include "Request/DescribeClusterRankingsRequest.h"
#include "Task/WebSocket/DescribeClusterRankingsTask.h"
#include "Request/DescribeClusterRankingsByUserIdRequest.h"
#include "Task/WebSocket/DescribeClusterRankingsByUserIdTask.h"
#include "Request/GetClusterRankingRequest.h"
#include "Task/WebSocket/GetClusterRankingTask.h"
#include "Request/GetClusterRankingByUserIdRequest.h"
#include "Task/WebSocket/GetClusterRankingByUserIdTask.h"
#include "Request/DescribeSubscribeRankingModelsRequest.h"
#include "Task/WebSocket/DescribeSubscribeRankingModelsTask.h"
#include "Request/GetSubscribeRankingModelRequest.h"
#include "Task/WebSocket/GetSubscribeRankingModelTask.h"
#include "Request/DescribeSubscribeRankingModelMastersRequest.h"
#include "Task/WebSocket/DescribeSubscribeRankingModelMastersTask.h"
#include "Request/CreateSubscribeRankingModelMasterRequest.h"
#include "Task/WebSocket/CreateSubscribeRankingModelMasterTask.h"
#include "Request/GetSubscribeRankingModelMasterRequest.h"
#include "Task/WebSocket/GetSubscribeRankingModelMasterTask.h"
#include "Request/UpdateSubscribeRankingModelMasterRequest.h"
#include "Task/WebSocket/UpdateSubscribeRankingModelMasterTask.h"
#include "Request/DeleteSubscribeRankingModelMasterRequest.h"
#include "Task/WebSocket/DeleteSubscribeRankingModelMasterTask.h"
#include "Request/DescribeSubscribesRequest.h"
#include "Task/WebSocket/DescribeSubscribesTask.h"
#include "Request/DescribeSubscribesByUserIdRequest.h"
#include "Task/WebSocket/DescribeSubscribesByUserIdTask.h"
#include "Request/AddSubscribeRequest.h"
#include "Task/WebSocket/AddSubscribeTask.h"
#include "Request/AddSubscribeByUserIdRequest.h"
#include "Task/WebSocket/AddSubscribeByUserIdTask.h"
#include "Request/DescribeSubscribeRankingScoresRequest.h"
#include "Task/WebSocket/DescribeSubscribeRankingScoresTask.h"
#include "Request/DescribeSubscribeRankingScoresByUserIdRequest.h"
#include "Task/WebSocket/DescribeSubscribeRankingScoresByUserIdTask.h"
#include "Request/PutSubscribeRankingScoreRequest.h"
#include "Task/WebSocket/PutSubscribeRankingScoreTask.h"
#include "Request/PutSubscribeRankingScoreByUserIdRequest.h"
#include "Task/WebSocket/PutSubscribeRankingScoreByUserIdTask.h"
#include "Request/GetSubscribeRankingScoreRequest.h"
#include "Task/WebSocket/GetSubscribeRankingScoreTask.h"
#include "Request/GetSubscribeRankingScoreByUserIdRequest.h"
#include "Task/WebSocket/GetSubscribeRankingScoreByUserIdTask.h"
#include "Request/DeleteSubscribeRankingScoreByUserIdRequest.h"
#include "Task/WebSocket/DeleteSubscribeRankingScoreByUserIdTask.h"
#include "Request/VerifySubscribeRankingScoreRequest.h"
#include "Task/WebSocket/VerifySubscribeRankingScoreTask.h"
#include "Request/VerifySubscribeRankingScoreByUserIdRequest.h"
#include "Task/WebSocket/VerifySubscribeRankingScoreByUserIdTask.h"
#include "Request/VerifySubscribeRankingScoreByStampTaskRequest.h"
#include "Task/WebSocket/VerifySubscribeRankingScoreByStampTaskTask.h"
#include "Request/DescribeSubscribeRankingsRequest.h"
#include "Task/WebSocket/DescribeSubscribeRankingsTask.h"
#include "Request/DescribeSubscribeRankingsByUserIdRequest.h"
#include "Task/WebSocket/DescribeSubscribeRankingsByUserIdTask.h"
#include "Request/GetSubscribeRankingRequest.h"
#include "Task/WebSocket/GetSubscribeRankingTask.h"
#include "Request/GetSubscribeRankingByUserIdRequest.h"
#include "Task/WebSocket/GetSubscribeRankingByUserIdTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentRankingMasterRequest.h"
#include "Task/WebSocket/GetCurrentRankingMasterTask.h"
#include "Request/UpdateCurrentRankingMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentRankingMasterTask.h"
#include "Request/UpdateCurrentRankingMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentRankingMasterFromGitHubTask.h"
#include "Request/GetSubscribeRequest.h"
#include "Task/WebSocket/GetSubscribeTask.h"
#include "Request/GetSubscribeByUserIdRequest.h"
#include "Task/WebSocket/GetSubscribeByUserIdTask.h"
#include "Request/DeleteSubscribeRequest.h"
#include "Task/WebSocket/DeleteSubscribeTask.h"
#include "Request/DeleteSubscribeByUserIdRequest.h"
#include "Task/WebSocket/DeleteSubscribeByUserIdTask.h"

namespace Gs2::Ranking2
{
    class GS2RANKING2_API FGs2Ranking2WebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2Ranking2WebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingModelsTask>> DescribeGlobalRankingModels(
            const Request::FDescribeGlobalRankingModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalRankingModelTask>> GetGlobalRankingModel(
            const Request::FGetGlobalRankingModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingModelMastersTask>> DescribeGlobalRankingModelMasters(
            const Request::FDescribeGlobalRankingModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGlobalRankingModelMasterTask>> CreateGlobalRankingModelMaster(
            const Request::FCreateGlobalRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalRankingModelMasterTask>> GetGlobalRankingModelMaster(
            const Request::FGetGlobalRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateGlobalRankingModelMasterTask>> UpdateGlobalRankingModelMaster(
            const Request::FUpdateGlobalRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteGlobalRankingModelMasterTask>> DeleteGlobalRankingModelMaster(
            const Request::FDeleteGlobalRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingScoresTask>> DescribeGlobalRankingScores(
            const Request::FDescribeGlobalRankingScoresRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingScoresByUserIdTask>> DescribeGlobalRankingScoresByUserId(
            const Request::FDescribeGlobalRankingScoresByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPutGlobalRankingScoreTask>> PutGlobalRankingScore(
            const Request::FPutGlobalRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPutGlobalRankingScoreByUserIdTask>> PutGlobalRankingScoreByUserId(
            const Request::FPutGlobalRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalRankingScoreTask>> GetGlobalRankingScore(
            const Request::FGetGlobalRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalRankingScoreByUserIdTask>> GetGlobalRankingScoreByUserId(
            const Request::FGetGlobalRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteGlobalRankingScoreByUserIdTask>> DeleteGlobalRankingScoreByUserId(
            const Request::FDeleteGlobalRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyGlobalRankingScoreTask>> VerifyGlobalRankingScore(
            const Request::FVerifyGlobalRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyGlobalRankingScoreByUserIdTask>> VerifyGlobalRankingScoreByUserId(
            const Request::FVerifyGlobalRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyGlobalRankingScoreByStampTaskTask>> VerifyGlobalRankingScoreByStampTask(
            const Request::FVerifyGlobalRankingScoreByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingReceivedRewardsTask>> DescribeGlobalRankingReceivedRewards(
            const Request::FDescribeGlobalRankingReceivedRewardsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingReceivedRewardsByUserIdTask>> DescribeGlobalRankingReceivedRewardsByUserId(
            const Request::FDescribeGlobalRankingReceivedRewardsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGlobalRankingReceivedRewardTask>> CreateGlobalRankingReceivedReward(
            const Request::FCreateGlobalRankingReceivedRewardRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGlobalRankingReceivedRewardByUserIdTask>> CreateGlobalRankingReceivedRewardByUserId(
            const Request::FCreateGlobalRankingReceivedRewardByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveGlobalRankingReceivedRewardTask>> ReceiveGlobalRankingReceivedReward(
            const Request::FReceiveGlobalRankingReceivedRewardRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveGlobalRankingReceivedRewardByUserIdTask>> ReceiveGlobalRankingReceivedRewardByUserId(
            const Request::FReceiveGlobalRankingReceivedRewardByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalRankingReceivedRewardTask>> GetGlobalRankingReceivedReward(
            const Request::FGetGlobalRankingReceivedRewardRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalRankingReceivedRewardByUserIdTask>> GetGlobalRankingReceivedRewardByUserId(
            const Request::FGetGlobalRankingReceivedRewardByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteGlobalRankingReceivedRewardByUserIdTask>> DeleteGlobalRankingReceivedRewardByUserId(
            const Request::FDeleteGlobalRankingReceivedRewardByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGlobalRankingReceivedRewardByStampTaskTask>> CreateGlobalRankingReceivedRewardByStampTask(
            const Request::FCreateGlobalRankingReceivedRewardByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingsTask>> DescribeGlobalRankings(
            const Request::FDescribeGlobalRankingsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalRankingsByUserIdTask>> DescribeGlobalRankingsByUserId(
            const Request::FDescribeGlobalRankingsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalRankingTask>> GetGlobalRanking(
            const Request::FGetGlobalRankingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalRankingByUserIdTask>> GetGlobalRankingByUserId(
            const Request::FGetGlobalRankingByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeClusterRankingModelsTask>> DescribeClusterRankingModels(
            const Request::FDescribeClusterRankingModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetClusterRankingModelTask>> GetClusterRankingModel(
            const Request::FGetClusterRankingModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeClusterRankingModelMastersTask>> DescribeClusterRankingModelMasters(
            const Request::FDescribeClusterRankingModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateClusterRankingModelMasterTask>> CreateClusterRankingModelMaster(
            const Request::FCreateClusterRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetClusterRankingModelMasterTask>> GetClusterRankingModelMaster(
            const Request::FGetClusterRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateClusterRankingModelMasterTask>> UpdateClusterRankingModelMaster(
            const Request::FUpdateClusterRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteClusterRankingModelMasterTask>> DeleteClusterRankingModelMaster(
            const Request::FDeleteClusterRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeClusterRankingScoresTask>> DescribeClusterRankingScores(
            const Request::FDescribeClusterRankingScoresRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeClusterRankingScoresByUserIdTask>> DescribeClusterRankingScoresByUserId(
            const Request::FDescribeClusterRankingScoresByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPutClusterRankingScoreTask>> PutClusterRankingScore(
            const Request::FPutClusterRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPutClusterRankingScoreByUserIdTask>> PutClusterRankingScoreByUserId(
            const Request::FPutClusterRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetClusterRankingScoreTask>> GetClusterRankingScore(
            const Request::FGetClusterRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetClusterRankingScoreByUserIdTask>> GetClusterRankingScoreByUserId(
            const Request::FGetClusterRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteClusterRankingScoreByUserIdTask>> DeleteClusterRankingScoreByUserId(
            const Request::FDeleteClusterRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyClusterRankingScoreTask>> VerifyClusterRankingScore(
            const Request::FVerifyClusterRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyClusterRankingScoreByUserIdTask>> VerifyClusterRankingScoreByUserId(
            const Request::FVerifyClusterRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyClusterRankingScoreByStampTaskTask>> VerifyClusterRankingScoreByStampTask(
            const Request::FVerifyClusterRankingScoreByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeClusterRankingReceivedRewardsTask>> DescribeClusterRankingReceivedRewards(
            const Request::FDescribeClusterRankingReceivedRewardsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeClusterRankingReceivedRewardsByUserIdTask>> DescribeClusterRankingReceivedRewardsByUserId(
            const Request::FDescribeClusterRankingReceivedRewardsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateClusterRankingReceivedRewardTask>> CreateClusterRankingReceivedReward(
            const Request::FCreateClusterRankingReceivedRewardRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateClusterRankingReceivedRewardByUserIdTask>> CreateClusterRankingReceivedRewardByUserId(
            const Request::FCreateClusterRankingReceivedRewardByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveClusterRankingReceivedRewardTask>> ReceiveClusterRankingReceivedReward(
            const Request::FReceiveClusterRankingReceivedRewardRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveClusterRankingReceivedRewardByUserIdTask>> ReceiveClusterRankingReceivedRewardByUserId(
            const Request::FReceiveClusterRankingReceivedRewardByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetClusterRankingReceivedRewardTask>> GetClusterRankingReceivedReward(
            const Request::FGetClusterRankingReceivedRewardRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetClusterRankingReceivedRewardByUserIdTask>> GetClusterRankingReceivedRewardByUserId(
            const Request::FGetClusterRankingReceivedRewardByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteClusterRankingReceivedRewardByUserIdTask>> DeleteClusterRankingReceivedRewardByUserId(
            const Request::FDeleteClusterRankingReceivedRewardByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateClusterRankingReceivedRewardByStampTaskTask>> CreateClusterRankingReceivedRewardByStampTask(
            const Request::FCreateClusterRankingReceivedRewardByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeClusterRankingsTask>> DescribeClusterRankings(
            const Request::FDescribeClusterRankingsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeClusterRankingsByUserIdTask>> DescribeClusterRankingsByUserId(
            const Request::FDescribeClusterRankingsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetClusterRankingTask>> GetClusterRanking(
            const Request::FGetClusterRankingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetClusterRankingByUserIdTask>> GetClusterRankingByUserId(
            const Request::FGetClusterRankingByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingModelsTask>> DescribeSubscribeRankingModels(
            const Request::FDescribeSubscribeRankingModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeRankingModelTask>> GetSubscribeRankingModel(
            const Request::FGetSubscribeRankingModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingModelMastersTask>> DescribeSubscribeRankingModelMasters(
            const Request::FDescribeSubscribeRankingModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateSubscribeRankingModelMasterTask>> CreateSubscribeRankingModelMaster(
            const Request::FCreateSubscribeRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeRankingModelMasterTask>> GetSubscribeRankingModelMaster(
            const Request::FGetSubscribeRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateSubscribeRankingModelMasterTask>> UpdateSubscribeRankingModelMaster(
            const Request::FUpdateSubscribeRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSubscribeRankingModelMasterTask>> DeleteSubscribeRankingModelMaster(
            const Request::FDeleteSubscribeRankingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribesTask>> DescribeSubscribes(
            const Request::FDescribeSubscribesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribesByUserIdTask>> DescribeSubscribesByUserId(
            const Request::FDescribeSubscribesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddSubscribeTask>> AddSubscribe(
            const Request::FAddSubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddSubscribeByUserIdTask>> AddSubscribeByUserId(
            const Request::FAddSubscribeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingScoresTask>> DescribeSubscribeRankingScores(
            const Request::FDescribeSubscribeRankingScoresRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingScoresByUserIdTask>> DescribeSubscribeRankingScoresByUserId(
            const Request::FDescribeSubscribeRankingScoresByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPutSubscribeRankingScoreTask>> PutSubscribeRankingScore(
            const Request::FPutSubscribeRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPutSubscribeRankingScoreByUserIdTask>> PutSubscribeRankingScoreByUserId(
            const Request::FPutSubscribeRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeRankingScoreTask>> GetSubscribeRankingScore(
            const Request::FGetSubscribeRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeRankingScoreByUserIdTask>> GetSubscribeRankingScoreByUserId(
            const Request::FGetSubscribeRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSubscribeRankingScoreByUserIdTask>> DeleteSubscribeRankingScoreByUserId(
            const Request::FDeleteSubscribeRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifySubscribeRankingScoreTask>> VerifySubscribeRankingScore(
            const Request::FVerifySubscribeRankingScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifySubscribeRankingScoreByUserIdTask>> VerifySubscribeRankingScoreByUserId(
            const Request::FVerifySubscribeRankingScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifySubscribeRankingScoreByStampTaskTask>> VerifySubscribeRankingScoreByStampTask(
            const Request::FVerifySubscribeRankingScoreByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingsTask>> DescribeSubscribeRankings(
            const Request::FDescribeSubscribeRankingsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribeRankingsByUserIdTask>> DescribeSubscribeRankingsByUserId(
            const Request::FDescribeSubscribeRankingsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeRankingTask>> GetSubscribeRanking(
            const Request::FGetSubscribeRankingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeRankingByUserIdTask>> GetSubscribeRankingByUserId(
            const Request::FGetSubscribeRankingByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentRankingMasterTask>> GetCurrentRankingMaster(
            const Request::FGetCurrentRankingMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentRankingMasterTask>> UpdateCurrentRankingMaster(
            const Request::FUpdateCurrentRankingMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentRankingMasterFromGitHubTask>> UpdateCurrentRankingMasterFromGitHub(
            const Request::FUpdateCurrentRankingMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeTask>> GetSubscribe(
            const Request::FGetSubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeByUserIdTask>> GetSubscribeByUserId(
            const Request::FGetSubscribeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSubscribeTask>> DeleteSubscribe(
            const Request::FDeleteSubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSubscribeByUserIdTask>> DeleteSubscribeByUserId(
            const Request::FDeleteSubscribeByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2Ranking2WebSocketClient, ESPMode::ThreadSafe> FGs2Ranking2WebSocketClientPtr;
}