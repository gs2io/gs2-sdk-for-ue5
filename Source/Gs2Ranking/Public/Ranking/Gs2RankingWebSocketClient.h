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
#include "Request/DescribeCategoryModelsRequest.h"
#include "Task/WebSocket/DescribeCategoryModelsTask.h"
#include "Request/GetCategoryModelRequest.h"
#include "Task/WebSocket/GetCategoryModelTask.h"
#include "Request/DescribeCategoryModelMastersRequest.h"
#include "Task/WebSocket/DescribeCategoryModelMastersTask.h"
#include "Request/CreateCategoryModelMasterRequest.h"
#include "Task/WebSocket/CreateCategoryModelMasterTask.h"
#include "Request/GetCategoryModelMasterRequest.h"
#include "Task/WebSocket/GetCategoryModelMasterTask.h"
#include "Request/UpdateCategoryModelMasterRequest.h"
#include "Task/WebSocket/UpdateCategoryModelMasterTask.h"
#include "Request/DeleteCategoryModelMasterRequest.h"
#include "Task/WebSocket/DeleteCategoryModelMasterTask.h"
#include "Request/SubscribeRequest.h"
#include "Task/WebSocket/SubscribeTask.h"
#include "Request/SubscribeByUserIdRequest.h"
#include "Task/WebSocket/SubscribeByUserIdTask.h"
#include "Request/DescribeScoresRequest.h"
#include "Task/WebSocket/DescribeScoresTask.h"
#include "Request/DescribeScoresByUserIdRequest.h"
#include "Task/WebSocket/DescribeScoresByUserIdTask.h"
#include "Request/GetScoreRequest.h"
#include "Task/WebSocket/GetScoreTask.h"
#include "Request/GetScoreByUserIdRequest.h"
#include "Task/WebSocket/GetScoreByUserIdTask.h"
#include "Request/DescribeRankingsRequest.h"
#include "Task/WebSocket/DescribeRankingsTask.h"
#include "Request/DescribeRankingssByUserIdRequest.h"
#include "Task/WebSocket/DescribeRankingssByUserIdTask.h"
#include "Request/DescribeNearRankingsRequest.h"
#include "Task/WebSocket/DescribeNearRankingsTask.h"
#include "Request/GetRankingRequest.h"
#include "Task/WebSocket/GetRankingTask.h"
#include "Request/GetRankingByUserIdRequest.h"
#include "Task/WebSocket/GetRankingByUserIdTask.h"
#include "Request/PutScoreRequest.h"
#include "Task/WebSocket/PutScoreTask.h"
#include "Request/PutScoreByUserIdRequest.h"
#include "Task/WebSocket/PutScoreByUserIdTask.h"
#include "Request/CalcRankingRequest.h"
#include "Task/WebSocket/CalcRankingTask.h"
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
#include "Request/UnsubscribeRequest.h"
#include "Task/WebSocket/UnsubscribeTask.h"
#include "Request/UnsubscribeByUserIdRequest.h"
#include "Task/WebSocket/UnsubscribeByUserIdTask.h"
#include "Request/DescribeSubscribesByCategoryNameRequest.h"
#include "Task/WebSocket/DescribeSubscribesByCategoryNameTask.h"
#include "Request/DescribeSubscribesByCategoryNameAndUserIdRequest.h"
#include "Task/WebSocket/DescribeSubscribesByCategoryNameAndUserIdTask.h"

namespace Gs2::Ranking
{
    class GS2RANKING_API FGs2RankingWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2RankingWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCategoryModelsTask>> DescribeCategoryModels(
            const Request::FDescribeCategoryModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCategoryModelTask>> GetCategoryModel(
            const Request::FGetCategoryModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCategoryModelMastersTask>> DescribeCategoryModelMasters(
            const Request::FDescribeCategoryModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateCategoryModelMasterTask>> CreateCategoryModelMaster(
            const Request::FCreateCategoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCategoryModelMasterTask>> GetCategoryModelMaster(
            const Request::FGetCategoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCategoryModelMasterTask>> UpdateCategoryModelMaster(
            const Request::FUpdateCategoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteCategoryModelMasterTask>> DeleteCategoryModelMaster(
            const Request::FDeleteCategoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSubscribeTask>> Subscribe(
            const Request::FSubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSubscribeByUserIdTask>> SubscribeByUserId(
            const Request::FSubscribeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeScoresTask>> DescribeScores(
            const Request::FDescribeScoresRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeScoresByUserIdTask>> DescribeScoresByUserId(
            const Request::FDescribeScoresByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetScoreTask>> GetScore(
            const Request::FGetScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetScoreByUserIdTask>> GetScoreByUserId(
            const Request::FGetScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRankingsTask>> DescribeRankings(
            const Request::FDescribeRankingsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRankingssByUserIdTask>> DescribeRankingssByUserId(
            const Request::FDescribeRankingssByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNearRankingsTask>> DescribeNearRankings(
            const Request::FDescribeNearRankingsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRankingTask>> GetRanking(
            const Request::FGetRankingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRankingByUserIdTask>> GetRankingByUserId(
            const Request::FGetRankingByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPutScoreTask>> PutScore(
            const Request::FPutScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPutScoreByUserIdTask>> PutScoreByUserId(
            const Request::FPutScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCalcRankingTask>> CalcRanking(
            const Request::FCalcRankingRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FUnsubscribeTask>> Unsubscribe(
            const Request::FUnsubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUnsubscribeByUserIdTask>> UnsubscribeByUserId(
            const Request::FUnsubscribeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribesByCategoryNameTask>> DescribeSubscribesByCategoryName(
            const Request::FDescribeSubscribesByCategoryNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribesByCategoryNameAndUserIdTask>> DescribeSubscribesByCategoryNameAndUserId(
            const Request::FDescribeSubscribesByCategoryNameAndUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2RankingWebSocketClient, ESPMode::ThreadSafe> FGs2RankingWebSocketClientPtr;
}