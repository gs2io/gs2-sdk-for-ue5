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

#include "Matchmaking/Gs2MatchmakingRestClient.h"

namespace Gs2::Matchmaking
{

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> FGs2MatchmakingRestClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> FGs2MatchmakingRestClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> FGs2MatchmakingRestClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> FGs2MatchmakingRestClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> FGs2MatchmakingRestClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> FGs2MatchmakingRestClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeGatheringsTask>> FGs2MatchmakingRestClient::DescribeGatherings(
        const Request::FDescribeGatheringsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeGatheringsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateGatheringTask>> FGs2MatchmakingRestClient::CreateGathering(
        const Request::FCreateGatheringRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateGatheringTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateGatheringByUserIdTask>> FGs2MatchmakingRestClient::CreateGatheringByUserId(
        const Request::FCreateGatheringByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateGatheringByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateGatheringTask>> FGs2MatchmakingRestClient::UpdateGathering(
        const Request::FUpdateGatheringRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateGatheringTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateGatheringByUserIdTask>> FGs2MatchmakingRestClient::UpdateGatheringByUserId(
        const Request::FUpdateGatheringByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateGatheringByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDoMatchmakingByPlayerTask>> FGs2MatchmakingRestClient::DoMatchmakingByPlayer(
        const Request::FDoMatchmakingByPlayerRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDoMatchmakingByPlayerTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDoMatchmakingTask>> FGs2MatchmakingRestClient::DoMatchmaking(
        const Request::FDoMatchmakingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDoMatchmakingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDoMatchmakingByUserIdTask>> FGs2MatchmakingRestClient::DoMatchmakingByUserId(
        const Request::FDoMatchmakingByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDoMatchmakingByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetGatheringTask>> FGs2MatchmakingRestClient::GetGathering(
        const Request::FGetGatheringRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetGatheringTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCancelMatchmakingTask>> FGs2MatchmakingRestClient::CancelMatchmaking(
        const Request::FCancelMatchmakingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCancelMatchmakingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCancelMatchmakingByUserIdTask>> FGs2MatchmakingRestClient::CancelMatchmakingByUserId(
        const Request::FCancelMatchmakingByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCancelMatchmakingByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteGatheringTask>> FGs2MatchmakingRestClient::DeleteGathering(
        const Request::FDeleteGatheringRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteGatheringTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeRatingModelMastersTask>> FGs2MatchmakingRestClient::DescribeRatingModelMasters(
        const Request::FDescribeRatingModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeRatingModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateRatingModelMasterTask>> FGs2MatchmakingRestClient::CreateRatingModelMaster(
        const Request::FCreateRatingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateRatingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetRatingModelMasterTask>> FGs2MatchmakingRestClient::GetRatingModelMaster(
        const Request::FGetRatingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetRatingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateRatingModelMasterTask>> FGs2MatchmakingRestClient::UpdateRatingModelMaster(
        const Request::FUpdateRatingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateRatingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteRatingModelMasterTask>> FGs2MatchmakingRestClient::DeleteRatingModelMaster(
        const Request::FDeleteRatingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteRatingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeRatingModelsTask>> FGs2MatchmakingRestClient::DescribeRatingModels(
        const Request::FDescribeRatingModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeRatingModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetRatingModelTask>> FGs2MatchmakingRestClient::GetRatingModel(
        const Request::FGetRatingModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetRatingModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> FGs2MatchmakingRestClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentRatingModelMasterTask>> FGs2MatchmakingRestClient::GetCurrentRatingModelMaster(
        const Request::FGetCurrentRatingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetCurrentRatingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentRatingModelMasterTask>> FGs2MatchmakingRestClient::UpdateCurrentRatingModelMaster(
        const Request::FUpdateCurrentRatingModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentRatingModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentRatingModelMasterFromGitHubTask>> FGs2MatchmakingRestClient::UpdateCurrentRatingModelMasterFromGitHub(
        const Request::FUpdateCurrentRatingModelMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentRatingModelMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeRatingsTask>> FGs2MatchmakingRestClient::DescribeRatings(
        const Request::FDescribeRatingsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeRatingsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeRatingsByUserIdTask>> FGs2MatchmakingRestClient::DescribeRatingsByUserId(
        const Request::FDescribeRatingsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeRatingsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetRatingTask>> FGs2MatchmakingRestClient::GetRating(
        const Request::FGetRatingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetRatingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetRatingByUserIdTask>> FGs2MatchmakingRestClient::GetRatingByUserId(
        const Request::FGetRatingByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetRatingByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPutResultTask>> FGs2MatchmakingRestClient::PutResult(
        const Request::FPutResultRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPutResultTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteRatingTask>> FGs2MatchmakingRestClient::DeleteRating(
        const Request::FDeleteRatingRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteRatingTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetBallotTask>> FGs2MatchmakingRestClient::GetBallot(
        const Request::FGetBallotRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetBallotTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetBallotByUserIdTask>> FGs2MatchmakingRestClient::GetBallotByUserId(
        const Request::FGetBallotByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetBallotByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVoteTask>> FGs2MatchmakingRestClient::Vote(
        const Request::FVoteRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVoteTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVoteMultipleTask>> FGs2MatchmakingRestClient::VoteMultiple(
        const Request::FVoteMultipleRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVoteMultipleTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCommitVoteTask>> FGs2MatchmakingRestClient::CommitVote(
        const Request::FCommitVoteRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCommitVoteTask>>(
            Session,
            Request
        );
    }
}