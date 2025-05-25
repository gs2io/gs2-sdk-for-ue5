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
#include "Model/Gathering.h"
#include "Model/RatingModelMaster.h"
#include "Model/RatingModel.h"
#include "Model/CurrentModelMaster.h"
#include "Model/SeasonModel.h"
#include "Model/SeasonModelMaster.h"
#include "Model/SeasonGathering.h"
#include "Model/JoinedSeasonGathering.h"
#include "Model/ScriptSetting.h"
#include "Model/NotificationSetting.h"
#include "Model/LogSetting.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/AttributeRange.h"
#include "Model/CapacityOfRole.h"
#include "Model/Attribute.h"
#include "Model/Player.h"
#include "Model/Rating.h"
#include "Model/GameResult.h"
#include "Model/Ballot.h"
#include "Model/SignedBallot.h"
#include "Model/WrittenBallot.h"
#include "Model/Vote.h"
#include "Model/TimeSpan.h"

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

// GetServiceVersion
#include "Request/GetServiceVersionRequest.h"
#include "Result/GetServiceVersionResult.h"
#include "Task/Rest/GetServiceVersionTask.h"
#include "Task/WebSocket/GetServiceVersionTask.h"

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

// DescribeGatherings
#include "Request/DescribeGatheringsRequest.h"
#include "Result/DescribeGatheringsResult.h"
#include "Task/Rest/DescribeGatheringsTask.h"
#include "Task/WebSocket/DescribeGatheringsTask.h"

// CreateGathering
#include "Request/CreateGatheringRequest.h"
#include "Result/CreateGatheringResult.h"
#include "Task/Rest/CreateGatheringTask.h"
#include "Task/WebSocket/CreateGatheringTask.h"

// CreateGatheringByUserId
#include "Request/CreateGatheringByUserIdRequest.h"
#include "Result/CreateGatheringByUserIdResult.h"
#include "Task/Rest/CreateGatheringByUserIdTask.h"
#include "Task/WebSocket/CreateGatheringByUserIdTask.h"

// UpdateGathering
#include "Request/UpdateGatheringRequest.h"
#include "Result/UpdateGatheringResult.h"
#include "Task/Rest/UpdateGatheringTask.h"
#include "Task/WebSocket/UpdateGatheringTask.h"

// UpdateGatheringByUserId
#include "Request/UpdateGatheringByUserIdRequest.h"
#include "Result/UpdateGatheringByUserIdResult.h"
#include "Task/Rest/UpdateGatheringByUserIdTask.h"
#include "Task/WebSocket/UpdateGatheringByUserIdTask.h"

// DoMatchmakingByPlayer
#include "Request/DoMatchmakingByPlayerRequest.h"
#include "Result/DoMatchmakingByPlayerResult.h"
#include "Task/Rest/DoMatchmakingByPlayerTask.h"
#include "Task/WebSocket/DoMatchmakingByPlayerTask.h"

// DoMatchmaking
#include "Request/DoMatchmakingRequest.h"
#include "Result/DoMatchmakingResult.h"
#include "Task/Rest/DoMatchmakingTask.h"
#include "Task/WebSocket/DoMatchmakingTask.h"

// DoMatchmakingByUserId
#include "Request/DoMatchmakingByUserIdRequest.h"
#include "Result/DoMatchmakingByUserIdResult.h"
#include "Task/Rest/DoMatchmakingByUserIdTask.h"
#include "Task/WebSocket/DoMatchmakingByUserIdTask.h"

// Ping
#include "Request/PingRequest.h"
#include "Result/PingResult.h"
#include "Task/Rest/PingTask.h"
#include "Task/WebSocket/PingTask.h"

// PingByUserId
#include "Request/PingByUserIdRequest.h"
#include "Result/PingByUserIdResult.h"
#include "Task/Rest/PingByUserIdTask.h"
#include "Task/WebSocket/PingByUserIdTask.h"

// GetGathering
#include "Request/GetGatheringRequest.h"
#include "Result/GetGatheringResult.h"
#include "Task/Rest/GetGatheringTask.h"
#include "Task/WebSocket/GetGatheringTask.h"

// CancelMatchmaking
#include "Request/CancelMatchmakingRequest.h"
#include "Result/CancelMatchmakingResult.h"
#include "Task/Rest/CancelMatchmakingTask.h"
#include "Task/WebSocket/CancelMatchmakingTask.h"

// CancelMatchmakingByUserId
#include "Request/CancelMatchmakingByUserIdRequest.h"
#include "Result/CancelMatchmakingByUserIdResult.h"
#include "Task/Rest/CancelMatchmakingByUserIdTask.h"
#include "Task/WebSocket/CancelMatchmakingByUserIdTask.h"

// EarlyComplete
#include "Request/EarlyCompleteRequest.h"
#include "Result/EarlyCompleteResult.h"
#include "Task/Rest/EarlyCompleteTask.h"
#include "Task/WebSocket/EarlyCompleteTask.h"

// EarlyCompleteByUserId
#include "Request/EarlyCompleteByUserIdRequest.h"
#include "Result/EarlyCompleteByUserIdResult.h"
#include "Task/Rest/EarlyCompleteByUserIdTask.h"
#include "Task/WebSocket/EarlyCompleteByUserIdTask.h"

// DeleteGathering
#include "Request/DeleteGatheringRequest.h"
#include "Result/DeleteGatheringResult.h"
#include "Task/Rest/DeleteGatheringTask.h"
#include "Task/WebSocket/DeleteGatheringTask.h"

// DescribeRatingModelMasters
#include "Request/DescribeRatingModelMastersRequest.h"
#include "Result/DescribeRatingModelMastersResult.h"
#include "Task/Rest/DescribeRatingModelMastersTask.h"
#include "Task/WebSocket/DescribeRatingModelMastersTask.h"

// CreateRatingModelMaster
#include "Request/CreateRatingModelMasterRequest.h"
#include "Result/CreateRatingModelMasterResult.h"
#include "Task/Rest/CreateRatingModelMasterTask.h"
#include "Task/WebSocket/CreateRatingModelMasterTask.h"

// GetRatingModelMaster
#include "Request/GetRatingModelMasterRequest.h"
#include "Result/GetRatingModelMasterResult.h"
#include "Task/Rest/GetRatingModelMasterTask.h"
#include "Task/WebSocket/GetRatingModelMasterTask.h"

// UpdateRatingModelMaster
#include "Request/UpdateRatingModelMasterRequest.h"
#include "Result/UpdateRatingModelMasterResult.h"
#include "Task/Rest/UpdateRatingModelMasterTask.h"
#include "Task/WebSocket/UpdateRatingModelMasterTask.h"

// DeleteRatingModelMaster
#include "Request/DeleteRatingModelMasterRequest.h"
#include "Result/DeleteRatingModelMasterResult.h"
#include "Task/Rest/DeleteRatingModelMasterTask.h"
#include "Task/WebSocket/DeleteRatingModelMasterTask.h"

// DescribeRatingModels
#include "Request/DescribeRatingModelsRequest.h"
#include "Result/DescribeRatingModelsResult.h"
#include "Task/Rest/DescribeRatingModelsTask.h"
#include "Task/WebSocket/DescribeRatingModelsTask.h"

// GetRatingModel
#include "Request/GetRatingModelRequest.h"
#include "Result/GetRatingModelResult.h"
#include "Task/Rest/GetRatingModelTask.h"
#include "Task/WebSocket/GetRatingModelTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentModelMaster
#include "Request/GetCurrentModelMasterRequest.h"
#include "Result/GetCurrentModelMasterResult.h"
#include "Task/Rest/GetCurrentModelMasterTask.h"
#include "Task/WebSocket/GetCurrentModelMasterTask.h"

// PreUpdateCurrentModelMaster
#include "Request/PreUpdateCurrentModelMasterRequest.h"
#include "Result/PreUpdateCurrentModelMasterResult.h"
#include "Task/Rest/PreUpdateCurrentModelMasterTask.h"
#include "Task/WebSocket/PreUpdateCurrentModelMasterTask.h"

// UpdateCurrentModelMaster
#include "Request/UpdateCurrentModelMasterRequest.h"
#include "Result/UpdateCurrentModelMasterResult.h"
#include "Task/Rest/UpdateCurrentModelMasterTask.h"
#include "Task/WebSocket/UpdateCurrentModelMasterTask.h"

// UpdateCurrentModelMasterFromGitHub
#include "Request/UpdateCurrentModelMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentModelMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentModelMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentModelMasterFromGitHubTask.h"

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

// DescribeSeasonGatherings
#include "Request/DescribeSeasonGatheringsRequest.h"
#include "Result/DescribeSeasonGatheringsResult.h"
#include "Task/Rest/DescribeSeasonGatheringsTask.h"
#include "Task/WebSocket/DescribeSeasonGatheringsTask.h"

// DescribeMatchmakingSeasonGatherings
#include "Request/DescribeMatchmakingSeasonGatheringsRequest.h"
#include "Result/DescribeMatchmakingSeasonGatheringsResult.h"
#include "Task/Rest/DescribeMatchmakingSeasonGatheringsTask.h"
#include "Task/WebSocket/DescribeMatchmakingSeasonGatheringsTask.h"

// DoSeasonMatchmaking
#include "Request/DoSeasonMatchmakingRequest.h"
#include "Result/DoSeasonMatchmakingResult.h"
#include "Task/Rest/DoSeasonMatchmakingTask.h"
#include "Task/WebSocket/DoSeasonMatchmakingTask.h"

// DoSeasonMatchmakingByUserId
#include "Request/DoSeasonMatchmakingByUserIdRequest.h"
#include "Result/DoSeasonMatchmakingByUserIdResult.h"
#include "Task/Rest/DoSeasonMatchmakingByUserIdTask.h"
#include "Task/WebSocket/DoSeasonMatchmakingByUserIdTask.h"

// GetSeasonGathering
#include "Request/GetSeasonGatheringRequest.h"
#include "Result/GetSeasonGatheringResult.h"
#include "Task/Rest/GetSeasonGatheringTask.h"
#include "Task/WebSocket/GetSeasonGatheringTask.h"

// VerifyIncludeParticipant
#include "Request/VerifyIncludeParticipantRequest.h"
#include "Result/VerifyIncludeParticipantResult.h"
#include "Task/Rest/VerifyIncludeParticipantTask.h"
#include "Task/WebSocket/VerifyIncludeParticipantTask.h"

// VerifyIncludeParticipantByUserId
#include "Request/VerifyIncludeParticipantByUserIdRequest.h"
#include "Result/VerifyIncludeParticipantByUserIdResult.h"
#include "Task/Rest/VerifyIncludeParticipantByUserIdTask.h"
#include "Task/WebSocket/VerifyIncludeParticipantByUserIdTask.h"

// DeleteSeasonGathering
#include "Request/DeleteSeasonGatheringRequest.h"
#include "Result/DeleteSeasonGatheringResult.h"
#include "Task/Rest/DeleteSeasonGatheringTask.h"
#include "Task/WebSocket/DeleteSeasonGatheringTask.h"

// VerifyIncludeParticipantByStampTask
#include "Request/VerifyIncludeParticipantByStampTaskRequest.h"
#include "Result/VerifyIncludeParticipantByStampTaskResult.h"
#include "Task/Rest/VerifyIncludeParticipantByStampTaskTask.h"
#include "Task/WebSocket/VerifyIncludeParticipantByStampTaskTask.h"

// DescribeJoinedSeasonGatherings
#include "Request/DescribeJoinedSeasonGatheringsRequest.h"
#include "Result/DescribeJoinedSeasonGatheringsResult.h"
#include "Task/Rest/DescribeJoinedSeasonGatheringsTask.h"
#include "Task/WebSocket/DescribeJoinedSeasonGatheringsTask.h"

// DescribeJoinedSeasonGatheringsByUserId
#include "Request/DescribeJoinedSeasonGatheringsByUserIdRequest.h"
#include "Result/DescribeJoinedSeasonGatheringsByUserIdResult.h"
#include "Task/Rest/DescribeJoinedSeasonGatheringsByUserIdTask.h"
#include "Task/WebSocket/DescribeJoinedSeasonGatheringsByUserIdTask.h"

// GetJoinedSeasonGathering
#include "Request/GetJoinedSeasonGatheringRequest.h"
#include "Result/GetJoinedSeasonGatheringResult.h"
#include "Task/Rest/GetJoinedSeasonGatheringTask.h"
#include "Task/WebSocket/GetJoinedSeasonGatheringTask.h"

// GetJoinedSeasonGatheringByUserId
#include "Request/GetJoinedSeasonGatheringByUserIdRequest.h"
#include "Result/GetJoinedSeasonGatheringByUserIdResult.h"
#include "Task/Rest/GetJoinedSeasonGatheringByUserIdTask.h"
#include "Task/WebSocket/GetJoinedSeasonGatheringByUserIdTask.h"

// DescribeRatings
#include "Request/DescribeRatingsRequest.h"
#include "Result/DescribeRatingsResult.h"
#include "Task/Rest/DescribeRatingsTask.h"
#include "Task/WebSocket/DescribeRatingsTask.h"

// DescribeRatingsByUserId
#include "Request/DescribeRatingsByUserIdRequest.h"
#include "Result/DescribeRatingsByUserIdResult.h"
#include "Task/Rest/DescribeRatingsByUserIdTask.h"
#include "Task/WebSocket/DescribeRatingsByUserIdTask.h"

// GetRating
#include "Request/GetRatingRequest.h"
#include "Result/GetRatingResult.h"
#include "Task/Rest/GetRatingTask.h"
#include "Task/WebSocket/GetRatingTask.h"

// GetRatingByUserId
#include "Request/GetRatingByUserIdRequest.h"
#include "Result/GetRatingByUserIdResult.h"
#include "Task/Rest/GetRatingByUserIdTask.h"
#include "Task/WebSocket/GetRatingByUserIdTask.h"

// PutResult
#include "Request/PutResultRequest.h"
#include "Result/PutResultResult.h"
#include "Task/Rest/PutResultTask.h"
#include "Task/WebSocket/PutResultTask.h"

// DeleteRating
#include "Request/DeleteRatingRequest.h"
#include "Result/DeleteRatingResult.h"
#include "Task/Rest/DeleteRatingTask.h"
#include "Task/WebSocket/DeleteRatingTask.h"

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
#include "Gs2MatchmakingRestClient.h"
#include "Gs2MatchmakingWebSocketClient.h"