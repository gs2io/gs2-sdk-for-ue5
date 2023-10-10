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
#include "Request/GetGatheringRequest.h"
#include "Task/Rest/GetGatheringTask.h"
#include "Request/CancelMatchmakingRequest.h"
#include "Task/Rest/CancelMatchmakingTask.h"
#include "Request/CancelMatchmakingByUserIdRequest.h"
#include "Task/Rest/CancelMatchmakingByUserIdTask.h"
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
#include "Request/GetCurrentRatingModelMasterRequest.h"
#include "Task/Rest/GetCurrentRatingModelMasterTask.h"
#include "Request/UpdateCurrentRatingModelMasterRequest.h"
#include "Task/Rest/UpdateCurrentRatingModelMasterTask.h"
#include "Request/UpdateCurrentRatingModelMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentRatingModelMasterFromGitHubTask.h"
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

        TSharedPtr<FAsyncTask<Task::Rest::FGetGatheringTask>> GetGathering(
            const Request::FGetGatheringRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCancelMatchmakingTask>> CancelMatchmaking(
            const Request::FCancelMatchmakingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCancelMatchmakingByUserIdTask>> CancelMatchmakingByUserId(
            const Request::FCancelMatchmakingByUserIdRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentRatingModelMasterTask>> GetCurrentRatingModelMaster(
            const Request::FGetCurrentRatingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentRatingModelMasterTask>> UpdateCurrentRatingModelMaster(
            const Request::FUpdateCurrentRatingModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentRatingModelMasterFromGitHubTask>> UpdateCurrentRatingModelMasterFromGitHub(
            const Request::FUpdateCurrentRatingModelMasterFromGitHubRequestPtr Request
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