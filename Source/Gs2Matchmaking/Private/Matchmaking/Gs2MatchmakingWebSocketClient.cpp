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

#include "Matchmaking/Gs2MatchmakingWebSocketClient.h"

namespace Gs2::Matchmaking
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> FGs2MatchmakingWebSocketClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> FGs2MatchmakingWebSocketClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> FGs2MatchmakingWebSocketClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> FGs2MatchmakingWebSocketClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> FGs2MatchmakingWebSocketClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> FGs2MatchmakingWebSocketClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>> FGs2MatchmakingWebSocketClient::DumpUserDataByUserId(
        const Request::FDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>> FGs2MatchmakingWebSocketClient::CheckDumpUserDataByUserId(
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>> FGs2MatchmakingWebSocketClient::CleanUserDataByUserId(
        const Request::FCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>> FGs2MatchmakingWebSocketClient::CheckCleanUserDataByUserId(
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>> FGs2MatchmakingWebSocketClient::PrepareImportUserDataByUserId(
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>> FGs2MatchmakingWebSocketClient::ImportUserDataByUserId(
        const Request::FImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>> FGs2MatchmakingWebSocketClient::CheckImportUserDataByUserId(
        const Request::FCheckImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGatheringsTask>> FGs2MatchmakingWebSocketClient::DescribeGatherings(
        const Request::FDescribeGatheringsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeGatheringsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGatheringTask>> FGs2MatchmakingWebSocketClient::CreateGathering(
        const Request::FCreateGatheringRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateGatheringTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGatheringByUserIdTask>> FGs2MatchmakingWebSocketClient::CreateGatheringByUserId(
        const Request::FCreateGatheringByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateGatheringByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateGatheringTask>> FGs2MatchmakingWebSocketClient::UpdateGathering(
        const Request::FUpdateGatheringRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateGatheringTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateGatheringByUserIdTask>> FGs2MatchmakingWebSocketClient::UpdateGatheringByUserId(
        const Request::FUpdateGatheringByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateGatheringByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDoMatchmakingByPlayerTask>> FGs2MatchmakingWebSocketClient::DoMatchmakingByPlayer(
        const Request::FDoMatchmakingByPlayerRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDoMatchmakingByPlayerTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDoMatchmakingTask>> FGs2MatchmakingWebSocketClient::DoMatchmaking(
        const Request::FDoMatchmakingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDoMatchmakingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDoMatchmakingByUserIdTask>> FGs2MatchmakingWebSocketClient::DoMatchmakingByUserId(
        const Request::FDoMatchmakingByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDoMatchmakingByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPingTask>> FGs2MatchmakingWebSocketClient::Ping(
        const Request::FPingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPingByUserIdTask>> FGs2MatchmakingWebSocketClient::PingByUserId(
        const Request::FPingByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPingByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetGatheringTask>> FGs2MatchmakingWebSocketClient::GetGathering(
        const Request::FGetGatheringRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetGatheringTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCancelMatchmakingTask>> FGs2MatchmakingWebSocketClient::CancelMatchmaking(
        const Request::FCancelMatchmakingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCancelMatchmakingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCancelMatchmakingByUserIdTask>> FGs2MatchmakingWebSocketClient::CancelMatchmakingByUserId(
        const Request::FCancelMatchmakingByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCancelMatchmakingByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FEarlyCompleteTask>> FGs2MatchmakingWebSocketClient::EarlyComplete(
        const Request::FEarlyCompleteRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FEarlyCompleteTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FEarlyCompleteByUserIdTask>> FGs2MatchmakingWebSocketClient::EarlyCompleteByUserId(
        const Request::FEarlyCompleteByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FEarlyCompleteByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteGatheringTask>> FGs2MatchmakingWebSocketClient::DeleteGathering(
        const Request::FDeleteGatheringRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteGatheringTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRatingModelMastersTask>> FGs2MatchmakingWebSocketClient::DescribeRatingModelMasters(
        const Request::FDescribeRatingModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeRatingModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateRatingModelMasterTask>> FGs2MatchmakingWebSocketClient::CreateRatingModelMaster(
        const Request::FCreateRatingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateRatingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetRatingModelMasterTask>> FGs2MatchmakingWebSocketClient::GetRatingModelMaster(
        const Request::FGetRatingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetRatingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateRatingModelMasterTask>> FGs2MatchmakingWebSocketClient::UpdateRatingModelMaster(
        const Request::FUpdateRatingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateRatingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRatingModelMasterTask>> FGs2MatchmakingWebSocketClient::DeleteRatingModelMaster(
        const Request::FDeleteRatingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteRatingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRatingModelsTask>> FGs2MatchmakingWebSocketClient::DescribeRatingModels(
        const Request::FDescribeRatingModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeRatingModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetRatingModelTask>> FGs2MatchmakingWebSocketClient::GetRatingModel(
        const Request::FGetRatingModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetRatingModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> FGs2MatchmakingWebSocketClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentModelMasterTask>> FGs2MatchmakingWebSocketClient::GetCurrentModelMaster(
        const Request::FGetCurrentModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCurrentModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentModelMasterTask>> FGs2MatchmakingWebSocketClient::UpdateCurrentModelMaster(
        const Request::FUpdateCurrentModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentModelMasterFromGitHubTask>> FGs2MatchmakingWebSocketClient::UpdateCurrentModelMasterFromGitHub(
        const Request::FUpdateCurrentModelMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentModelMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSeasonModelsTask>> FGs2MatchmakingWebSocketClient::DescribeSeasonModels(
        const Request::FDescribeSeasonModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSeasonModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSeasonModelTask>> FGs2MatchmakingWebSocketClient::GetSeasonModel(
        const Request::FGetSeasonModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSeasonModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSeasonModelMastersTask>> FGs2MatchmakingWebSocketClient::DescribeSeasonModelMasters(
        const Request::FDescribeSeasonModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSeasonModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateSeasonModelMasterTask>> FGs2MatchmakingWebSocketClient::CreateSeasonModelMaster(
        const Request::FCreateSeasonModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateSeasonModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSeasonModelMasterTask>> FGs2MatchmakingWebSocketClient::GetSeasonModelMaster(
        const Request::FGetSeasonModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSeasonModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateSeasonModelMasterTask>> FGs2MatchmakingWebSocketClient::UpdateSeasonModelMaster(
        const Request::FUpdateSeasonModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateSeasonModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSeasonModelMasterTask>> FGs2MatchmakingWebSocketClient::DeleteSeasonModelMaster(
        const Request::FDeleteSeasonModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteSeasonModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSeasonGatheringsTask>> FGs2MatchmakingWebSocketClient::DescribeSeasonGatherings(
        const Request::FDescribeSeasonGatheringsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSeasonGatheringsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMatchmakingSeasonGatheringsTask>> FGs2MatchmakingWebSocketClient::DescribeMatchmakingSeasonGatherings(
        const Request::FDescribeMatchmakingSeasonGatheringsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeMatchmakingSeasonGatheringsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDoSeasonMatchmakingTask>> FGs2MatchmakingWebSocketClient::DoSeasonMatchmaking(
        const Request::FDoSeasonMatchmakingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDoSeasonMatchmakingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDoSeasonMatchmakingByUserIdTask>> FGs2MatchmakingWebSocketClient::DoSeasonMatchmakingByUserId(
        const Request::FDoSeasonMatchmakingByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDoSeasonMatchmakingByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSeasonGatheringTask>> FGs2MatchmakingWebSocketClient::GetSeasonGathering(
        const Request::FGetSeasonGatheringRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSeasonGatheringTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSeasonGatheringTask>> FGs2MatchmakingWebSocketClient::DeleteSeasonGathering(
        const Request::FDeleteSeasonGatheringRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteSeasonGatheringTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeJoinedSeasonGatheringsTask>> FGs2MatchmakingWebSocketClient::DescribeJoinedSeasonGatherings(
        const Request::FDescribeJoinedSeasonGatheringsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeJoinedSeasonGatheringsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeJoinedSeasonGatheringsByUserIdTask>> FGs2MatchmakingWebSocketClient::DescribeJoinedSeasonGatheringsByUserId(
        const Request::FDescribeJoinedSeasonGatheringsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeJoinedSeasonGatheringsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetJoinedSeasonGatheringTask>> FGs2MatchmakingWebSocketClient::GetJoinedSeasonGathering(
        const Request::FGetJoinedSeasonGatheringRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetJoinedSeasonGatheringTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetJoinedSeasonGatheringByUserIdTask>> FGs2MatchmakingWebSocketClient::GetJoinedSeasonGatheringByUserId(
        const Request::FGetJoinedSeasonGatheringByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetJoinedSeasonGatheringByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRatingsTask>> FGs2MatchmakingWebSocketClient::DescribeRatings(
        const Request::FDescribeRatingsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeRatingsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRatingsByUserIdTask>> FGs2MatchmakingWebSocketClient::DescribeRatingsByUserId(
        const Request::FDescribeRatingsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeRatingsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetRatingTask>> FGs2MatchmakingWebSocketClient::GetRating(
        const Request::FGetRatingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetRatingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetRatingByUserIdTask>> FGs2MatchmakingWebSocketClient::GetRatingByUserId(
        const Request::FGetRatingByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetRatingByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPutResultTask>> FGs2MatchmakingWebSocketClient::PutResult(
        const Request::FPutResultRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPutResultTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRatingTask>> FGs2MatchmakingWebSocketClient::DeleteRating(
        const Request::FDeleteRatingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteRatingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetBallotTask>> FGs2MatchmakingWebSocketClient::GetBallot(
        const Request::FGetBallotRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetBallotTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetBallotByUserIdTask>> FGs2MatchmakingWebSocketClient::GetBallotByUserId(
        const Request::FGetBallotByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetBallotByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVoteTask>> FGs2MatchmakingWebSocketClient::Vote(
        const Request::FVoteRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVoteTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVoteMultipleTask>> FGs2MatchmakingWebSocketClient::VoteMultiple(
        const Request::FVoteMultipleRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVoteMultipleTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCommitVoteTask>> FGs2MatchmakingWebSocketClient::CommitVote(
        const Request::FCommitVoteRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCommitVoteTask>>(
            Session,
            Request
        );
    }
}