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
#include "Request/DescribeGatheringsRequest.h"
#include "Task/WebSocket/DescribeGatheringsTask.h"
#include "Request/CreateGatheringRequest.h"
#include "Task/WebSocket/CreateGatheringTask.h"
#include "Request/CreateGatheringByUserIdRequest.h"
#include "Task/WebSocket/CreateGatheringByUserIdTask.h"
#include "Request/UpdateGatheringRequest.h"
#include "Task/WebSocket/UpdateGatheringTask.h"
#include "Request/UpdateGatheringByUserIdRequest.h"
#include "Task/WebSocket/UpdateGatheringByUserIdTask.h"
#include "Request/DoMatchmakingByPlayerRequest.h"
#include "Task/WebSocket/DoMatchmakingByPlayerTask.h"
#include "Request/DoMatchmakingRequest.h"
#include "Task/WebSocket/DoMatchmakingTask.h"
#include "Request/DoMatchmakingByUserIdRequest.h"
#include "Task/WebSocket/DoMatchmakingByUserIdTask.h"
#include "Request/GetGatheringRequest.h"
#include "Task/WebSocket/GetGatheringTask.h"
#include "Request/CancelMatchmakingRequest.h"
#include "Task/WebSocket/CancelMatchmakingTask.h"
#include "Request/CancelMatchmakingByUserIdRequest.h"
#include "Task/WebSocket/CancelMatchmakingByUserIdTask.h"
#include "Request/DeleteGatheringRequest.h"
#include "Task/WebSocket/DeleteGatheringTask.h"
#include "Request/DescribeRatingModelMastersRequest.h"
#include "Task/WebSocket/DescribeRatingModelMastersTask.h"
#include "Request/CreateRatingModelMasterRequest.h"
#include "Task/WebSocket/CreateRatingModelMasterTask.h"
#include "Request/GetRatingModelMasterRequest.h"
#include "Task/WebSocket/GetRatingModelMasterTask.h"
#include "Request/UpdateRatingModelMasterRequest.h"
#include "Task/WebSocket/UpdateRatingModelMasterTask.h"
#include "Request/DeleteRatingModelMasterRequest.h"
#include "Task/WebSocket/DeleteRatingModelMasterTask.h"
#include "Request/DescribeRatingModelsRequest.h"
#include "Task/WebSocket/DescribeRatingModelsTask.h"
#include "Request/GetRatingModelRequest.h"
#include "Task/WebSocket/GetRatingModelTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentRatingModelMasterRequest.h"
#include "Task/WebSocket/GetCurrentRatingModelMasterTask.h"
#include "Request/UpdateCurrentRatingModelMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentRatingModelMasterTask.h"
#include "Request/UpdateCurrentRatingModelMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentRatingModelMasterFromGitHubTask.h"
#include "Request/DescribeRatingsRequest.h"
#include "Task/WebSocket/DescribeRatingsTask.h"
#include "Request/DescribeRatingsByUserIdRequest.h"
#include "Task/WebSocket/DescribeRatingsByUserIdTask.h"
#include "Request/GetRatingRequest.h"
#include "Task/WebSocket/GetRatingTask.h"
#include "Request/GetRatingByUserIdRequest.h"
#include "Task/WebSocket/GetRatingByUserIdTask.h"
#include "Request/PutResultRequest.h"
#include "Task/WebSocket/PutResultTask.h"
#include "Request/DeleteRatingRequest.h"
#include "Task/WebSocket/DeleteRatingTask.h"
#include "Request/GetBallotRequest.h"
#include "Task/WebSocket/GetBallotTask.h"
#include "Request/GetBallotByUserIdRequest.h"
#include "Task/WebSocket/GetBallotByUserIdTask.h"
#include "Request/VoteRequest.h"
#include "Task/WebSocket/VoteTask.h"
#include "Request/VoteMultipleRequest.h"
#include "Task/WebSocket/VoteMultipleTask.h"
#include "Request/CommitVoteRequest.h"
#include "Task/WebSocket/CommitVoteTask.h"

namespace Gs2::Matchmaking
{
    class GS2MATCHMAKING_API FGs2MatchmakingWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2MatchmakingWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGatheringsTask>> DescribeGatherings(
            const Request::FDescribeGatheringsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGatheringTask>> CreateGathering(
            const Request::FCreateGatheringRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGatheringByUserIdTask>> CreateGatheringByUserId(
            const Request::FCreateGatheringByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateGatheringTask>> UpdateGathering(
            const Request::FUpdateGatheringRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateGatheringByUserIdTask>> UpdateGatheringByUserId(
            const Request::FUpdateGatheringByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDoMatchmakingByPlayerTask>> DoMatchmakingByPlayer(
            const Request::FDoMatchmakingByPlayerRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDoMatchmakingTask>> DoMatchmaking(
            const Request::FDoMatchmakingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDoMatchmakingByUserIdTask>> DoMatchmakingByUserId(
            const Request::FDoMatchmakingByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGatheringTask>> GetGathering(
            const Request::FGetGatheringRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCancelMatchmakingTask>> CancelMatchmaking(
            const Request::FCancelMatchmakingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCancelMatchmakingByUserIdTask>> CancelMatchmakingByUserId(
            const Request::FCancelMatchmakingByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteGatheringTask>> DeleteGathering(
            const Request::FDeleteGatheringRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRatingModelMastersTask>> DescribeRatingModelMasters(
            const Request::FDescribeRatingModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateRatingModelMasterTask>> CreateRatingModelMaster(
            const Request::FCreateRatingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRatingModelMasterTask>> GetRatingModelMaster(
            const Request::FGetRatingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateRatingModelMasterTask>> UpdateRatingModelMaster(
            const Request::FUpdateRatingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRatingModelMasterTask>> DeleteRatingModelMaster(
            const Request::FDeleteRatingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRatingModelsTask>> DescribeRatingModels(
            const Request::FDescribeRatingModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRatingModelTask>> GetRatingModel(
            const Request::FGetRatingModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentRatingModelMasterTask>> GetCurrentRatingModelMaster(
            const Request::FGetCurrentRatingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentRatingModelMasterTask>> UpdateCurrentRatingModelMaster(
            const Request::FUpdateCurrentRatingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentRatingModelMasterFromGitHubTask>> UpdateCurrentRatingModelMasterFromGitHub(
            const Request::FUpdateCurrentRatingModelMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRatingsTask>> DescribeRatings(
            const Request::FDescribeRatingsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRatingsByUserIdTask>> DescribeRatingsByUserId(
            const Request::FDescribeRatingsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRatingTask>> GetRating(
            const Request::FGetRatingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRatingByUserIdTask>> GetRatingByUserId(
            const Request::FGetRatingByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPutResultTask>> PutResult(
            const Request::FPutResultRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRatingTask>> DeleteRating(
            const Request::FDeleteRatingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBallotTask>> GetBallot(
            const Request::FGetBallotRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBallotByUserIdTask>> GetBallotByUserId(
            const Request::FGetBallotByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVoteTask>> Vote(
            const Request::FVoteRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVoteMultipleTask>> VoteMultiple(
            const Request::FVoteMultipleRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCommitVoteTask>> CommitVote(
            const Request::FCommitVoteRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2MatchmakingWebSocketClient, ESPMode::ThreadSafe> FGs2MatchmakingWebSocketClientPtr;
}