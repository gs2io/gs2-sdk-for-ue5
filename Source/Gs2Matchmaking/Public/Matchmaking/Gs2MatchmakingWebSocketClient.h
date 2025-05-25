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
#include "Request/GetServiceVersionRequest.h"
#include "Task/WebSocket/GetServiceVersionTask.h"
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
#include "Request/PingRequest.h"
#include "Task/WebSocket/PingTask.h"
#include "Request/PingByUserIdRequest.h"
#include "Task/WebSocket/PingByUserIdTask.h"
#include "Request/GetGatheringRequest.h"
#include "Task/WebSocket/GetGatheringTask.h"
#include "Request/CancelMatchmakingRequest.h"
#include "Task/WebSocket/CancelMatchmakingTask.h"
#include "Request/CancelMatchmakingByUserIdRequest.h"
#include "Task/WebSocket/CancelMatchmakingByUserIdTask.h"
#include "Request/EarlyCompleteRequest.h"
#include "Task/WebSocket/EarlyCompleteTask.h"
#include "Request/EarlyCompleteByUserIdRequest.h"
#include "Task/WebSocket/EarlyCompleteByUserIdTask.h"
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
#include "Request/GetCurrentModelMasterRequest.h"
#include "Task/WebSocket/GetCurrentModelMasterTask.h"
#include "Request/PreUpdateCurrentModelMasterRequest.h"
#include "Task/WebSocket/PreUpdateCurrentModelMasterTask.h"
#include "Request/UpdateCurrentModelMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentModelMasterTask.h"
#include "Request/UpdateCurrentModelMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentModelMasterFromGitHubTask.h"
#include "Request/DescribeSeasonModelsRequest.h"
#include "Task/WebSocket/DescribeSeasonModelsTask.h"
#include "Request/GetSeasonModelRequest.h"
#include "Task/WebSocket/GetSeasonModelTask.h"
#include "Request/DescribeSeasonModelMastersRequest.h"
#include "Task/WebSocket/DescribeSeasonModelMastersTask.h"
#include "Request/CreateSeasonModelMasterRequest.h"
#include "Task/WebSocket/CreateSeasonModelMasterTask.h"
#include "Request/GetSeasonModelMasterRequest.h"
#include "Task/WebSocket/GetSeasonModelMasterTask.h"
#include "Request/UpdateSeasonModelMasterRequest.h"
#include "Task/WebSocket/UpdateSeasonModelMasterTask.h"
#include "Request/DeleteSeasonModelMasterRequest.h"
#include "Task/WebSocket/DeleteSeasonModelMasterTask.h"
#include "Request/DescribeSeasonGatheringsRequest.h"
#include "Task/WebSocket/DescribeSeasonGatheringsTask.h"
#include "Request/DescribeMatchmakingSeasonGatheringsRequest.h"
#include "Task/WebSocket/DescribeMatchmakingSeasonGatheringsTask.h"
#include "Request/DoSeasonMatchmakingRequest.h"
#include "Task/WebSocket/DoSeasonMatchmakingTask.h"
#include "Request/DoSeasonMatchmakingByUserIdRequest.h"
#include "Task/WebSocket/DoSeasonMatchmakingByUserIdTask.h"
#include "Request/GetSeasonGatheringRequest.h"
#include "Task/WebSocket/GetSeasonGatheringTask.h"
#include "Request/VerifyIncludeParticipantRequest.h"
#include "Task/WebSocket/VerifyIncludeParticipantTask.h"
#include "Request/VerifyIncludeParticipantByUserIdRequest.h"
#include "Task/WebSocket/VerifyIncludeParticipantByUserIdTask.h"
#include "Request/DeleteSeasonGatheringRequest.h"
#include "Task/WebSocket/DeleteSeasonGatheringTask.h"
#include "Request/VerifyIncludeParticipantByStampTaskRequest.h"
#include "Task/WebSocket/VerifyIncludeParticipantByStampTaskTask.h"
#include "Request/DescribeJoinedSeasonGatheringsRequest.h"
#include "Task/WebSocket/DescribeJoinedSeasonGatheringsTask.h"
#include "Request/DescribeJoinedSeasonGatheringsByUserIdRequest.h"
#include "Task/WebSocket/DescribeJoinedSeasonGatheringsByUserIdTask.h"
#include "Request/GetJoinedSeasonGatheringRequest.h"
#include "Task/WebSocket/GetJoinedSeasonGatheringTask.h"
#include "Request/GetJoinedSeasonGatheringByUserIdRequest.h"
#include "Task/WebSocket/GetJoinedSeasonGatheringByUserIdTask.h"
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetServiceVersionTask>> GetServiceVersion(
            const Request::FGetServiceVersionRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FPingTask>> Ping(
            const Request::FPingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPingByUserIdTask>> PingByUserId(
            const Request::FPingByUserIdRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FEarlyCompleteTask>> EarlyComplete(
            const Request::FEarlyCompleteRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FEarlyCompleteByUserIdTask>> EarlyCompleteByUserId(
            const Request::FEarlyCompleteByUserIdRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentModelMasterTask>> GetCurrentModelMaster(
            const Request::FGetCurrentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPreUpdateCurrentModelMasterTask>> PreUpdateCurrentModelMaster(
            const Request::FPreUpdateCurrentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentModelMasterTask>> UpdateCurrentModelMaster(
            const Request::FUpdateCurrentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentModelMasterFromGitHubTask>> UpdateCurrentModelMasterFromGitHub(
            const Request::FUpdateCurrentModelMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSeasonModelsTask>> DescribeSeasonModels(
            const Request::FDescribeSeasonModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSeasonModelTask>> GetSeasonModel(
            const Request::FGetSeasonModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSeasonModelMastersTask>> DescribeSeasonModelMasters(
            const Request::FDescribeSeasonModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateSeasonModelMasterTask>> CreateSeasonModelMaster(
            const Request::FCreateSeasonModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSeasonModelMasterTask>> GetSeasonModelMaster(
            const Request::FGetSeasonModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateSeasonModelMasterTask>> UpdateSeasonModelMaster(
            const Request::FUpdateSeasonModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSeasonModelMasterTask>> DeleteSeasonModelMaster(
            const Request::FDeleteSeasonModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSeasonGatheringsTask>> DescribeSeasonGatherings(
            const Request::FDescribeSeasonGatheringsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMatchmakingSeasonGatheringsTask>> DescribeMatchmakingSeasonGatherings(
            const Request::FDescribeMatchmakingSeasonGatheringsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDoSeasonMatchmakingTask>> DoSeasonMatchmaking(
            const Request::FDoSeasonMatchmakingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDoSeasonMatchmakingByUserIdTask>> DoSeasonMatchmakingByUserId(
            const Request::FDoSeasonMatchmakingByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSeasonGatheringTask>> GetSeasonGathering(
            const Request::FGetSeasonGatheringRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyIncludeParticipantTask>> VerifyIncludeParticipant(
            const Request::FVerifyIncludeParticipantRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyIncludeParticipantByUserIdTask>> VerifyIncludeParticipantByUserId(
            const Request::FVerifyIncludeParticipantByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSeasonGatheringTask>> DeleteSeasonGathering(
            const Request::FDeleteSeasonGatheringRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyIncludeParticipantByStampTaskTask>> VerifyIncludeParticipantByStampTask(
            const Request::FVerifyIncludeParticipantByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeJoinedSeasonGatheringsTask>> DescribeJoinedSeasonGatherings(
            const Request::FDescribeJoinedSeasonGatheringsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeJoinedSeasonGatheringsByUserIdTask>> DescribeJoinedSeasonGatheringsByUserId(
            const Request::FDescribeJoinedSeasonGatheringsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetJoinedSeasonGatheringTask>> GetJoinedSeasonGathering(
            const Request::FGetJoinedSeasonGatheringRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetJoinedSeasonGatheringByUserIdTask>> GetJoinedSeasonGatheringByUserId(
            const Request::FGetJoinedSeasonGatheringByUserIdRequestPtr Request
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