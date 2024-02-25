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

// Model
#include "Model/Namespace.h"
#include "Model/MatchSession.h"
#include "Model/SeasonModelMaster.h"
#include "Model/SeasonModel.h"
#include "Model/TierModel.h"
#include "Model/CurrentSeasonModelMaster.h"
#include "Model/TransactionSetting.h"
#include "Model/ScriptSetting.h"
#include "Model/LogSetting.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/GameResult.h"
#include "Model/Ballot.h"
#include "Model/SignedBallot.h"
#include "Model/WrittenBallot.h"
#include "Model/Vote.h"

// DescribeNamespaces
#include "Request/DescribeNamespacesRequest.h"
#include "Result/DescribeNamespacesResult.h"
#include "Task/Rest/DescribeNamespacesTask.h"
#include "Task/WebSocket/DescribeNamespacesTask.h"

// CreateNamespace
#include "Request/CreateNamespaceRequest.h"
#include "Result/CreateNamespaceResult.h"
#include "Task/Rest/CreateNamespaceTask.h"
#include "Task/WebSocket/CreateNamespaceTask.h"

// GetNamespaceStatus
#include "Request/GetNamespaceStatusRequest.h"
#include "Result/GetNamespaceStatusResult.h"
#include "Task/Rest/GetNamespaceStatusTask.h"
#include "Task/WebSocket/GetNamespaceStatusTask.h"

// GetNamespace
#include "Request/GetNamespaceRequest.h"
#include "Result/GetNamespaceResult.h"
#include "Task/Rest/GetNamespaceTask.h"
#include "Task/WebSocket/GetNamespaceTask.h"

// UpdateNamespace
#include "Request/UpdateNamespaceRequest.h"
#include "Result/UpdateNamespaceResult.h"
#include "Task/Rest/UpdateNamespaceTask.h"
#include "Task/WebSocket/UpdateNamespaceTask.h"

// DeleteNamespace
#include "Request/DeleteNamespaceRequest.h"
#include "Result/DeleteNamespaceResult.h"
#include "Task/Rest/DeleteNamespaceTask.h"
#include "Task/WebSocket/DeleteNamespaceTask.h"

// DumpUserDataByUserId
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Result/DumpUserDataByUserIdResult.h"
#include "Task/Rest/DumpUserDataByUserIdTask.h"
#include "Task/WebSocket/DumpUserDataByUserIdTask.h"

// CheckDumpUserDataByUserId
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Result/CheckDumpUserDataByUserIdResult.h"
#include "Task/Rest/CheckDumpUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckDumpUserDataByUserIdTask.h"

// CleanUserDataByUserId
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Result/CleanUserDataByUserIdResult.h"
#include "Task/Rest/CleanUserDataByUserIdTask.h"
#include "Task/WebSocket/CleanUserDataByUserIdTask.h"

// CheckCleanUserDataByUserId
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Result/CheckCleanUserDataByUserIdResult.h"
#include "Task/Rest/CheckCleanUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckCleanUserDataByUserIdTask.h"

// PrepareImportUserDataByUserId
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Result/PrepareImportUserDataByUserIdResult.h"
#include "Task/Rest/PrepareImportUserDataByUserIdTask.h"
#include "Task/WebSocket/PrepareImportUserDataByUserIdTask.h"

// ImportUserDataByUserId
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Result/ImportUserDataByUserIdResult.h"
#include "Task/Rest/ImportUserDataByUserIdTask.h"
#include "Task/WebSocket/ImportUserDataByUserIdTask.h"

// CheckImportUserDataByUserId
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Result/CheckImportUserDataByUserIdResult.h"
#include "Task/Rest/CheckImportUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckImportUserDataByUserIdTask.h"

// DescribeMatchSessions
#include "Request/DescribeMatchSessionsRequest.h"
#include "Result/DescribeMatchSessionsResult.h"
#include "Task/Rest/DescribeMatchSessionsTask.h"
#include "Task/WebSocket/DescribeMatchSessionsTask.h"

// CreateMatchSession
#include "Request/CreateMatchSessionRequest.h"
#include "Result/CreateMatchSessionResult.h"
#include "Task/Rest/CreateMatchSessionTask.h"
#include "Task/WebSocket/CreateMatchSessionTask.h"

// GetMatchSession
#include "Request/GetMatchSessionRequest.h"
#include "Result/GetMatchSessionResult.h"
#include "Task/Rest/GetMatchSessionTask.h"
#include "Task/WebSocket/GetMatchSessionTask.h"

// DeleteMatchSession
#include "Request/DeleteMatchSessionRequest.h"
#include "Result/DeleteMatchSessionResult.h"
#include "Task/Rest/DeleteMatchSessionTask.h"
#include "Task/WebSocket/DeleteMatchSessionTask.h"

// DescribeSeasonModelMasters
#include "Request/DescribeSeasonModelMastersRequest.h"
#include "Result/DescribeSeasonModelMastersResult.h"
#include "Task/Rest/DescribeSeasonModelMastersTask.h"
#include "Task/WebSocket/DescribeSeasonModelMastersTask.h"

// CreateSeasonModelMaster
#include "Request/CreateSeasonModelMasterRequest.h"
#include "Result/CreateSeasonModelMasterResult.h"
#include "Task/Rest/CreateSeasonModelMasterTask.h"
#include "Task/WebSocket/CreateSeasonModelMasterTask.h"

// GetSeasonModelMaster
#include "Request/GetSeasonModelMasterRequest.h"
#include "Result/GetSeasonModelMasterResult.h"
#include "Task/Rest/GetSeasonModelMasterTask.h"
#include "Task/WebSocket/GetSeasonModelMasterTask.h"

// UpdateSeasonModelMaster
#include "Request/UpdateSeasonModelMasterRequest.h"
#include "Result/UpdateSeasonModelMasterResult.h"
#include "Task/Rest/UpdateSeasonModelMasterTask.h"
#include "Task/WebSocket/UpdateSeasonModelMasterTask.h"

// DeleteSeasonModelMaster
#include "Request/DeleteSeasonModelMasterRequest.h"
#include "Result/DeleteSeasonModelMasterResult.h"
#include "Task/Rest/DeleteSeasonModelMasterTask.h"
#include "Task/WebSocket/DeleteSeasonModelMasterTask.h"

// DescribeSeasonModels
#include "Request/DescribeSeasonModelsRequest.h"
#include "Result/DescribeSeasonModelsResult.h"
#include "Task/Rest/DescribeSeasonModelsTask.h"
#include "Task/WebSocket/DescribeSeasonModelsTask.h"

// GetSeasonModel
#include "Request/GetSeasonModelRequest.h"
#include "Result/GetSeasonModelResult.h"
#include "Task/Rest/GetSeasonModelTask.h"
#include "Task/WebSocket/GetSeasonModelTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentSeasonModelMaster
#include "Request/GetCurrentSeasonModelMasterRequest.h"
#include "Result/GetCurrentSeasonModelMasterResult.h"
#include "Task/Rest/GetCurrentSeasonModelMasterTask.h"
#include "Task/WebSocket/GetCurrentSeasonModelMasterTask.h"

// UpdateCurrentSeasonModelMaster
#include "Request/UpdateCurrentSeasonModelMasterRequest.h"
#include "Result/UpdateCurrentSeasonModelMasterResult.h"
#include "Task/Rest/UpdateCurrentSeasonModelMasterTask.h"
#include "Task/WebSocket/UpdateCurrentSeasonModelMasterTask.h"

// UpdateCurrentSeasonModelMasterFromGitHub
#include "Request/UpdateCurrentSeasonModelMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentSeasonModelMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentSeasonModelMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentSeasonModelMasterFromGitHubTask.h"

// GetBallot
#include "Request/GetBallotRequest.h"
#include "Result/GetBallotResult.h"
#include "Task/Rest/GetBallotTask.h"
#include "Task/WebSocket/GetBallotTask.h"

// GetBallotByUserId
#include "Request/GetBallotByUserIdRequest.h"
#include "Result/GetBallotByUserIdResult.h"
#include "Task/Rest/GetBallotByUserIdTask.h"
#include "Task/WebSocket/GetBallotByUserIdTask.h"

// Vote
#include "Request/VoteRequest.h"
#include "Result/VoteResult.h"
#include "Task/Rest/VoteTask.h"
#include "Task/WebSocket/VoteTask.h"

// VoteMultiple
#include "Request/VoteMultipleRequest.h"
#include "Result/VoteMultipleResult.h"
#include "Task/Rest/VoteMultipleTask.h"
#include "Task/WebSocket/VoteMultipleTask.h"

// CommitVote
#include "Request/CommitVoteRequest.h"
#include "Result/CommitVoteResult.h"
#include "Task/Rest/CommitVoteTask.h"
#include "Task/WebSocket/CommitVoteTask.h"

// Client
#include "Gs2SeasonRatingRestClient.h"
#include "Gs2SeasonRatingWebSocketClient.h"