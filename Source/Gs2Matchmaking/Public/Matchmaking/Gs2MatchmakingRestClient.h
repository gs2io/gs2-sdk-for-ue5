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
#include "Request/DescribeGatheringsRequest.h"
#include "Task/Rest/DescribeGatheringsTask.h"
#include "Request/CreateGatheringRequest.h"
#include "Task/Rest/CreateGatheringTask.h"
#include "Request/CreateGatheringByUserIdRequest.h"
#include "Task/Rest/CreateGatheringByUserIdTask.h"
#include "Request/UpdateGatheringRequest.h"
#include "Task/Rest/UpdateGatheringTask.h"
#include "Request/UpdateGatheringByUserIdRequest.h"
#include "Task/Rest/UpdateGatheringByUserIdTask.h"
#include "Request/DoMatchmakingByPlayerRequest.h"
#include "Task/Rest/DoMatchmakingByPlayerTask.h"
#include "Request/DoMatchmakingRequest.h"
#include "Task/Rest/DoMatchmakingTask.h"
#include "Request/DoMatchmakingByUserIdRequest.h"
#include "Task/Rest/DoMatchmakingByUserIdTask.h"
#include "Request/PingRequest.h"
#include "Task/Rest/PingTask.h"
#include "Request/PingByUserIdRequest.h"
#include "Task/Rest/PingByUserIdTask.h"
#include "Request/GetGatheringRequest.h"
#include "Task/Rest/GetGatheringTask.h"
#include "Request/CancelMatchmakingRequest.h"
#include "Task/Rest/CancelMatchmakingTask.h"
#include "Request/CancelMatchmakingByUserIdRequest.h"
#include "Task/Rest/CancelMatchmakingByUserIdTask.h"
#include "Request/EarlyCompleteRequest.h"
#include "Task/Rest/EarlyCompleteTask.h"
#include "Request/EarlyCompleteByUserIdRequest.h"
#include "Task/Rest/EarlyCompleteByUserIdTask.h"
#include "Request/DeleteGatheringRequest.h"
#include "Task/Rest/DeleteGatheringTask.h"
#include "Request/DescribeRatingModelMastersRequest.h"
#include "Task/Rest/DescribeRatingModelMastersTask.h"
#include "Request/CreateRatingModelMasterRequest.h"
#include "Task/Rest/CreateRatingModelMasterTask.h"
#include "Request/GetRatingModelMasterRequest.h"
#include "Task/Rest/GetRatingModelMasterTask.h"
#include "Request/UpdateRatingModelMasterRequest.h"
#include "Task/Rest/UpdateRatingModelMasterTask.h"
#include "Request/DeleteRatingModelMasterRequest.h"
#include "Task/Rest/DeleteRatingModelMasterTask.h"
#include "Request/DescribeRatingModelsRequest.h"
#include "Task/Rest/DescribeRatingModelsTask.h"
#include "Request/GetRatingModelRequest.h"
#include "Task/Rest/GetRatingModelTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentModelMasterRequest.h"
#include "Task/Rest/GetCurrentModelMasterTask.h"
#include "Request/UpdateCurrentModelMasterRequest.h"
#include "Task/Rest/UpdateCurrentModelMasterTask.h"
#include "Request/UpdateCurrentModelMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentModelMasterFromGitHubTask.h"
#include "Request/DescribeSeasonModelsRequest.h"
#include "Task/Rest/DescribeSeasonModelsTask.h"
#include "Request/GetSeasonModelRequest.h"
#include "Task/Rest/GetSeasonModelTask.h"
#include "Request/DescribeSeasonModelMastersRequest.h"
#include "Task/Rest/DescribeSeasonModelMastersTask.h"
#include "Request/CreateSeasonModelMasterRequest.h"
#include "Task/Rest/CreateSeasonModelMasterTask.h"
#include "Request/GetSeasonModelMasterRequest.h"
#include "Task/Rest/GetSeasonModelMasterTask.h"
#include "Request/UpdateSeasonModelMasterRequest.h"
#include "Task/Rest/UpdateSeasonModelMasterTask.h"
#include "Request/DeleteSeasonModelMasterRequest.h"
#include "Task/Rest/DeleteSeasonModelMasterTask.h"
#include "Request/DescribeSeasonGatheringsRequest.h"
#include "Task/Rest/DescribeSeasonGatheringsTask.h"
#include "Request/DescribeMatchmakingSeasonGatheringsRequest.h"
#include "Task/Rest/DescribeMatchmakingSeasonGatheringsTask.h"
#include "Request/DoSeasonMatchmakingRequest.h"
#include "Task/Rest/DoSeasonMatchmakingTask.h"
#include "Request/DoSeasonMatchmakingByUserIdRequest.h"
#include "Task/Rest/DoSeasonMatchmakingByUserIdTask.h"
#include "Request/GetSeasonGatheringRequest.h"
#include "Task/Rest/GetSeasonGatheringTask.h"
#include "Request/DeleteSeasonGatheringRequest.h"
#include "Task/Rest/DeleteSeasonGatheringTask.h"
#include "Request/DescribeJoinedSeasonGatheringsRequest.h"
#include "Task/Rest/DescribeJoinedSeasonGatheringsTask.h"
#include "Request/DescribeJoinedSeasonGatheringsByUserIdRequest.h"
#include "Task/Rest/DescribeJoinedSeasonGatheringsByUserIdTask.h"
#include "Request/GetJoinedSeasonGatheringRequest.h"
#include "Task/Rest/GetJoinedSeasonGatheringTask.h"
#include "Request/GetJoinedSeasonGatheringByUserIdRequest.h"
#include "Task/Rest/GetJoinedSeasonGatheringByUserIdTask.h"
#include "Request/DescribeRatingsRequest.h"
#include "Task/Rest/DescribeRatingsTask.h"
#include "Request/DescribeRatingsByUserIdRequest.h"
#include "Task/Rest/DescribeRatingsByUserIdTask.h"
#include "Request/GetRatingRequest.h"
#include "Task/Rest/GetRatingTask.h"
#include "Request/GetRatingByUserIdRequest.h"
#include "Task/Rest/GetRatingByUserIdTask.h"
#include "Request/PutResultRequest.h"
#include "Task/Rest/PutResultTask.h"
#include "Request/DeleteRatingRequest.h"
#include "Task/Rest/DeleteRatingTask.h"
#include "Request/GetBallotRequest.h"
#include "Task/Rest/GetBallotTask.h"
#include "Request/GetBallotByUserIdRequest.h"
#include "Task/Rest/GetBallotByUserIdTask.h"
#include "Request/VoteRequest.h"
#include "Task/Rest/VoteTask.h"
#include "Request/VoteMultipleRequest.h"
#include "Task/Rest/VoteMultipleTask.h"
#include "Request/CommitVoteRequest.h"
#include "Task/Rest/CommitVoteTask.h"

namespace Gs2::Matchmaking
{
    class GS2MATCHMAKING_API FGs2MatchmakingRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2MatchmakingRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeGatheringsTask>> DescribeGatherings(
            const Request::FDescribeGatheringsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateGatheringTask>> CreateGathering(
            const Request::FCreateGatheringRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateGatheringByUserIdTask>> CreateGatheringByUserId(
            const Request::FCreateGatheringByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateGatheringTask>> UpdateGathering(
            const Request::FUpdateGatheringRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateGatheringByUserIdTask>> UpdateGatheringByUserId(
            const Request::FUpdateGatheringByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDoMatchmakingByPlayerTask>> DoMatchmakingByPlayer(
            const Request::FDoMatchmakingByPlayerRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDoMatchmakingTask>> DoMatchmaking(
            const Request::FDoMatchmakingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDoMatchmakingByUserIdTask>> DoMatchmakingByUserId(
            const Request::FDoMatchmakingByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPingTask>> Ping(
            const Request::FPingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPingByUserIdTask>> PingByUserId(
            const Request::FPingByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGatheringTask>> GetGathering(
            const Request::FGetGatheringRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCancelMatchmakingTask>> CancelMatchmaking(
            const Request::FCancelMatchmakingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCancelMatchmakingByUserIdTask>> CancelMatchmakingByUserId(
            const Request::FCancelMatchmakingByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FEarlyCompleteTask>> EarlyComplete(
            const Request::FEarlyCompleteRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FEarlyCompleteByUserIdTask>> EarlyCompleteByUserId(
            const Request::FEarlyCompleteByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteGatheringTask>> DeleteGathering(
            const Request::FDeleteGatheringRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRatingModelMastersTask>> DescribeRatingModelMasters(
            const Request::FDescribeRatingModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateRatingModelMasterTask>> CreateRatingModelMaster(
            const Request::FCreateRatingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRatingModelMasterTask>> GetRatingModelMaster(
            const Request::FGetRatingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateRatingModelMasterTask>> UpdateRatingModelMaster(
            const Request::FUpdateRatingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteRatingModelMasterTask>> DeleteRatingModelMaster(
            const Request::FDeleteRatingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRatingModelsTask>> DescribeRatingModels(
            const Request::FDescribeRatingModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRatingModelTask>> GetRatingModel(
            const Request::FGetRatingModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentModelMasterTask>> GetCurrentModelMaster(
            const Request::FGetCurrentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentModelMasterTask>> UpdateCurrentModelMaster(
            const Request::FUpdateCurrentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentModelMasterFromGitHubTask>> UpdateCurrentModelMasterFromGitHub(
            const Request::FUpdateCurrentModelMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSeasonModelsTask>> DescribeSeasonModels(
            const Request::FDescribeSeasonModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSeasonModelTask>> GetSeasonModel(
            const Request::FGetSeasonModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSeasonModelMastersTask>> DescribeSeasonModelMasters(
            const Request::FDescribeSeasonModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateSeasonModelMasterTask>> CreateSeasonModelMaster(
            const Request::FCreateSeasonModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSeasonModelMasterTask>> GetSeasonModelMaster(
            const Request::FGetSeasonModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateSeasonModelMasterTask>> UpdateSeasonModelMaster(
            const Request::FUpdateSeasonModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteSeasonModelMasterTask>> DeleteSeasonModelMaster(
            const Request::FDeleteSeasonModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSeasonGatheringsTask>> DescribeSeasonGatherings(
            const Request::FDescribeSeasonGatheringsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeMatchmakingSeasonGatheringsTask>> DescribeMatchmakingSeasonGatherings(
            const Request::FDescribeMatchmakingSeasonGatheringsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDoSeasonMatchmakingTask>> DoSeasonMatchmaking(
            const Request::FDoSeasonMatchmakingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDoSeasonMatchmakingByUserIdTask>> DoSeasonMatchmakingByUserId(
            const Request::FDoSeasonMatchmakingByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSeasonGatheringTask>> GetSeasonGathering(
            const Request::FGetSeasonGatheringRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteSeasonGatheringTask>> DeleteSeasonGathering(
            const Request::FDeleteSeasonGatheringRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeJoinedSeasonGatheringsTask>> DescribeJoinedSeasonGatherings(
            const Request::FDescribeJoinedSeasonGatheringsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeJoinedSeasonGatheringsByUserIdTask>> DescribeJoinedSeasonGatheringsByUserId(
            const Request::FDescribeJoinedSeasonGatheringsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetJoinedSeasonGatheringTask>> GetJoinedSeasonGathering(
            const Request::FGetJoinedSeasonGatheringRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetJoinedSeasonGatheringByUserIdTask>> GetJoinedSeasonGatheringByUserId(
            const Request::FGetJoinedSeasonGatheringByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRatingsTask>> DescribeRatings(
            const Request::FDescribeRatingsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRatingsByUserIdTask>> DescribeRatingsByUserId(
            const Request::FDescribeRatingsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRatingTask>> GetRating(
            const Request::FGetRatingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRatingByUserIdTask>> GetRatingByUserId(
            const Request::FGetRatingByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPutResultTask>> PutResult(
            const Request::FPutResultRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteRatingTask>> DeleteRating(
            const Request::FDeleteRatingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetBallotTask>> GetBallot(
            const Request::FGetBallotRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetBallotByUserIdTask>> GetBallotByUserId(
            const Request::FGetBallotByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVoteTask>> Vote(
            const Request::FVoteRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVoteMultipleTask>> VoteMultiple(
            const Request::FVoteMultipleRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCommitVoteTask>> CommitVote(
            const Request::FCommitVoteRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2MatchmakingRestClient, ESPMode::ThreadSafe> FGs2MatchmakingRestClientPtr;
}