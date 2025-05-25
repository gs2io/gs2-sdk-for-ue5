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
#include "Request/GetServiceVersionRequest.h"
#include "Task/Rest/GetServiceVersionTask.h"
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
#include "Request/DescribeMatchSessionsRequest.h"
#include "Task/Rest/DescribeMatchSessionsTask.h"
#include "Request/CreateMatchSessionRequest.h"
#include "Task/Rest/CreateMatchSessionTask.h"
#include "Request/GetMatchSessionRequest.h"
#include "Task/Rest/GetMatchSessionTask.h"
#include "Request/DeleteMatchSessionRequest.h"
#include "Task/Rest/DeleteMatchSessionTask.h"
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
#include "Request/DescribeSeasonModelsRequest.h"
#include "Task/Rest/DescribeSeasonModelsTask.h"
#include "Request/GetSeasonModelRequest.h"
#include "Task/Rest/GetSeasonModelTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentSeasonModelMasterRequest.h"
#include "Task/Rest/GetCurrentSeasonModelMasterTask.h"
#include "Request/PreUpdateCurrentSeasonModelMasterRequest.h"
#include "Task/Rest/PreUpdateCurrentSeasonModelMasterTask.h"
#include "Request/UpdateCurrentSeasonModelMasterRequest.h"
#include "Task/Rest/UpdateCurrentSeasonModelMasterTask.h"
#include "Request/UpdateCurrentSeasonModelMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentSeasonModelMasterFromGitHubTask.h"
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

namespace Gs2::SeasonRating
{
    class GS2SEASONRATING_API FGs2SeasonRatingRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2SeasonRatingRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FGetServiceVersionTask>> GetServiceVersion(
            const Request::FGetServiceVersionRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeMatchSessionsTask>> DescribeMatchSessions(
            const Request::FDescribeMatchSessionsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateMatchSessionTask>> CreateMatchSession(
            const Request::FCreateMatchSessionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMatchSessionTask>> GetMatchSession(
            const Request::FGetMatchSessionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteMatchSessionTask>> DeleteMatchSession(
            const Request::FDeleteMatchSessionRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSeasonModelsTask>> DescribeSeasonModels(
            const Request::FDescribeSeasonModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSeasonModelTask>> GetSeasonModel(
            const Request::FGetSeasonModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentSeasonModelMasterTask>> GetCurrentSeasonModelMaster(
            const Request::FGetCurrentSeasonModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPreUpdateCurrentSeasonModelMasterTask>> PreUpdateCurrentSeasonModelMaster(
            const Request::FPreUpdateCurrentSeasonModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentSeasonModelMasterTask>> UpdateCurrentSeasonModelMaster(
            const Request::FUpdateCurrentSeasonModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentSeasonModelMasterFromGitHubTask>> UpdateCurrentSeasonModelMasterFromGitHub(
            const Request::FUpdateCurrentSeasonModelMasterFromGitHubRequestPtr Request
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
    typedef TSharedPtr<FGs2SeasonRatingRestClient, ESPMode::ThreadSafe> FGs2SeasonRatingRestClientPtr;
}