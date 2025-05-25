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
#include "Request/DescribeMatchSessionsRequest.h"
#include "Task/WebSocket/DescribeMatchSessionsTask.h"
#include "Request/CreateMatchSessionRequest.h"
#include "Task/WebSocket/CreateMatchSessionTask.h"
#include "Request/GetMatchSessionRequest.h"
#include "Task/WebSocket/GetMatchSessionTask.h"
#include "Request/DeleteMatchSessionRequest.h"
#include "Task/WebSocket/DeleteMatchSessionTask.h"
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
#include "Request/DescribeSeasonModelsRequest.h"
#include "Task/WebSocket/DescribeSeasonModelsTask.h"
#include "Request/GetSeasonModelRequest.h"
#include "Task/WebSocket/GetSeasonModelTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentSeasonModelMasterRequest.h"
#include "Task/WebSocket/GetCurrentSeasonModelMasterTask.h"
#include "Request/PreUpdateCurrentSeasonModelMasterRequest.h"
#include "Task/WebSocket/PreUpdateCurrentSeasonModelMasterTask.h"
#include "Request/UpdateCurrentSeasonModelMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentSeasonModelMasterTask.h"
#include "Request/UpdateCurrentSeasonModelMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentSeasonModelMasterFromGitHubTask.h"
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

namespace Gs2::SeasonRating
{
    class GS2SEASONRATING_API FGs2SeasonRatingWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2SeasonRatingWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMatchSessionsTask>> DescribeMatchSessions(
            const Request::FDescribeMatchSessionsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateMatchSessionTask>> CreateMatchSession(
            const Request::FCreateMatchSessionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetMatchSessionTask>> GetMatchSession(
            const Request::FGetMatchSessionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMatchSessionTask>> DeleteMatchSession(
            const Request::FDeleteMatchSessionRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSeasonModelsTask>> DescribeSeasonModels(
            const Request::FDescribeSeasonModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSeasonModelTask>> GetSeasonModel(
            const Request::FGetSeasonModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentSeasonModelMasterTask>> GetCurrentSeasonModelMaster(
            const Request::FGetCurrentSeasonModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPreUpdateCurrentSeasonModelMasterTask>> PreUpdateCurrentSeasonModelMaster(
            const Request::FPreUpdateCurrentSeasonModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentSeasonModelMasterTask>> UpdateCurrentSeasonModelMaster(
            const Request::FUpdateCurrentSeasonModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentSeasonModelMasterFromGitHubTask>> UpdateCurrentSeasonModelMasterFromGitHub(
            const Request::FUpdateCurrentSeasonModelMasterFromGitHubRequestPtr Request
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
    typedef TSharedPtr<FGs2SeasonRatingWebSocketClient, ESPMode::ThreadSafe> FGs2SeasonRatingWebSocketClientPtr;
}