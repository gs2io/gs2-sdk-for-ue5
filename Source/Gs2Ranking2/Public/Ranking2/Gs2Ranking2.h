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
#include "Model/GlobalRankingModel.h"
#include "Model/GlobalRankingModelMaster.h"
#include "Model/GlobalRankingScore.h"
#include "Model/GlobalRankingReceivedReward.h"
#include "Model/GlobalRankingData.h"
#include "Model/ClusterRankingModel.h"
#include "Model/ClusterRankingModelMaster.h"
#include "Model/ClusterRankingScore.h"
#include "Model/ClusterRankingReceivedReward.h"
#include "Model/ClusterRankingData.h"
#include "Model/SubscribeRankingModel.h"
#include "Model/SubscribeRankingModelMaster.h"
#include "Model/Subscribe.h"
#include "Model/SubscribeRankingScore.h"
#include "Model/SubscribeRankingData.h"
#include "Model/CurrentRankingMaster.h"
#include "Model/SubscribeUser.h"
#include "Model/RankingReward.h"
#include "Model/TransactionSetting.h"
#include "Model/LogSetting.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/AcquireAction.h"
#include "Model/Config.h"

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

// DescribeGlobalRankingModels
#include "Request/DescribeGlobalRankingModelsRequest.h"
#include "Result/DescribeGlobalRankingModelsResult.h"
#include "Task/Rest/DescribeGlobalRankingModelsTask.h"
#include "Task/WebSocket/DescribeGlobalRankingModelsTask.h"

// GetGlobalRankingModel
#include "Request/GetGlobalRankingModelRequest.h"
#include "Result/GetGlobalRankingModelResult.h"
#include "Task/Rest/GetGlobalRankingModelTask.h"
#include "Task/WebSocket/GetGlobalRankingModelTask.h"

// DescribeGlobalRankingModelMasters
#include "Request/DescribeGlobalRankingModelMastersRequest.h"
#include "Result/DescribeGlobalRankingModelMastersResult.h"
#include "Task/Rest/DescribeGlobalRankingModelMastersTask.h"
#include "Task/WebSocket/DescribeGlobalRankingModelMastersTask.h"

// CreateGlobalRankingModelMaster
#include "Request/CreateGlobalRankingModelMasterRequest.h"
#include "Result/CreateGlobalRankingModelMasterResult.h"
#include "Task/Rest/CreateGlobalRankingModelMasterTask.h"
#include "Task/WebSocket/CreateGlobalRankingModelMasterTask.h"

// GetGlobalRankingModelMaster
#include "Request/GetGlobalRankingModelMasterRequest.h"
#include "Result/GetGlobalRankingModelMasterResult.h"
#include "Task/Rest/GetGlobalRankingModelMasterTask.h"
#include "Task/WebSocket/GetGlobalRankingModelMasterTask.h"

// UpdateGlobalRankingModelMaster
#include "Request/UpdateGlobalRankingModelMasterRequest.h"
#include "Result/UpdateGlobalRankingModelMasterResult.h"
#include "Task/Rest/UpdateGlobalRankingModelMasterTask.h"
#include "Task/WebSocket/UpdateGlobalRankingModelMasterTask.h"

// DeleteGlobalRankingModelMaster
#include "Request/DeleteGlobalRankingModelMasterRequest.h"
#include "Result/DeleteGlobalRankingModelMasterResult.h"
#include "Task/Rest/DeleteGlobalRankingModelMasterTask.h"
#include "Task/WebSocket/DeleteGlobalRankingModelMasterTask.h"

// DescribeGlobalRankingScores
#include "Request/DescribeGlobalRankingScoresRequest.h"
#include "Result/DescribeGlobalRankingScoresResult.h"
#include "Task/Rest/DescribeGlobalRankingScoresTask.h"
#include "Task/WebSocket/DescribeGlobalRankingScoresTask.h"

// DescribeGlobalRankingScoresByUserId
#include "Request/DescribeGlobalRankingScoresByUserIdRequest.h"
#include "Result/DescribeGlobalRankingScoresByUserIdResult.h"
#include "Task/Rest/DescribeGlobalRankingScoresByUserIdTask.h"
#include "Task/WebSocket/DescribeGlobalRankingScoresByUserIdTask.h"

// PutGlobalRankingScore
#include "Request/PutGlobalRankingScoreRequest.h"
#include "Result/PutGlobalRankingScoreResult.h"
#include "Task/Rest/PutGlobalRankingScoreTask.h"
#include "Task/WebSocket/PutGlobalRankingScoreTask.h"

// PutGlobalRankingScoreByUserId
#include "Request/PutGlobalRankingScoreByUserIdRequest.h"
#include "Result/PutGlobalRankingScoreByUserIdResult.h"
#include "Task/Rest/PutGlobalRankingScoreByUserIdTask.h"
#include "Task/WebSocket/PutGlobalRankingScoreByUserIdTask.h"

// GetGlobalRankingScore
#include "Request/GetGlobalRankingScoreRequest.h"
#include "Result/GetGlobalRankingScoreResult.h"
#include "Task/Rest/GetGlobalRankingScoreTask.h"
#include "Task/WebSocket/GetGlobalRankingScoreTask.h"

// GetGlobalRankingScoreByUserId
#include "Request/GetGlobalRankingScoreByUserIdRequest.h"
#include "Result/GetGlobalRankingScoreByUserIdResult.h"
#include "Task/Rest/GetGlobalRankingScoreByUserIdTask.h"
#include "Task/WebSocket/GetGlobalRankingScoreByUserIdTask.h"

// DeleteGlobalRankingScoreByUserId
#include "Request/DeleteGlobalRankingScoreByUserIdRequest.h"
#include "Result/DeleteGlobalRankingScoreByUserIdResult.h"
#include "Task/Rest/DeleteGlobalRankingScoreByUserIdTask.h"
#include "Task/WebSocket/DeleteGlobalRankingScoreByUserIdTask.h"

// DescribeGlobalRankingReceivedRewards
#include "Request/DescribeGlobalRankingReceivedRewardsRequest.h"
#include "Result/DescribeGlobalRankingReceivedRewardsResult.h"
#include "Task/Rest/DescribeGlobalRankingReceivedRewardsTask.h"
#include "Task/WebSocket/DescribeGlobalRankingReceivedRewardsTask.h"

// DescribeGlobalRankingReceivedRewardsByUserId
#include "Request/DescribeGlobalRankingReceivedRewardsByUserIdRequest.h"
#include "Result/DescribeGlobalRankingReceivedRewardsByUserIdResult.h"
#include "Task/Rest/DescribeGlobalRankingReceivedRewardsByUserIdTask.h"
#include "Task/WebSocket/DescribeGlobalRankingReceivedRewardsByUserIdTask.h"

// CreateGlobalRankingReceivedReward
#include "Request/CreateGlobalRankingReceivedRewardRequest.h"
#include "Result/CreateGlobalRankingReceivedRewardResult.h"
#include "Task/Rest/CreateGlobalRankingReceivedRewardTask.h"
#include "Task/WebSocket/CreateGlobalRankingReceivedRewardTask.h"

// CreateGlobalRankingReceivedRewardByUserId
#include "Request/CreateGlobalRankingReceivedRewardByUserIdRequest.h"
#include "Result/CreateGlobalRankingReceivedRewardByUserIdResult.h"
#include "Task/Rest/CreateGlobalRankingReceivedRewardByUserIdTask.h"
#include "Task/WebSocket/CreateGlobalRankingReceivedRewardByUserIdTask.h"

// ReceiveGlobalRankingReceivedReward
#include "Request/ReceiveGlobalRankingReceivedRewardRequest.h"
#include "Result/ReceiveGlobalRankingReceivedRewardResult.h"
#include "Task/Rest/ReceiveGlobalRankingReceivedRewardTask.h"
#include "Task/WebSocket/ReceiveGlobalRankingReceivedRewardTask.h"

// ReceiveGlobalRankingReceivedRewardByUserId
#include "Request/ReceiveGlobalRankingReceivedRewardByUserIdRequest.h"
#include "Result/ReceiveGlobalRankingReceivedRewardByUserIdResult.h"
#include "Task/Rest/ReceiveGlobalRankingReceivedRewardByUserIdTask.h"
#include "Task/WebSocket/ReceiveGlobalRankingReceivedRewardByUserIdTask.h"

// GetGlobalRankingReceivedReward
#include "Request/GetGlobalRankingReceivedRewardRequest.h"
#include "Result/GetGlobalRankingReceivedRewardResult.h"
#include "Task/Rest/GetGlobalRankingReceivedRewardTask.h"
#include "Task/WebSocket/GetGlobalRankingReceivedRewardTask.h"

// GetGlobalRankingReceivedRewardByUserId
#include "Request/GetGlobalRankingReceivedRewardByUserIdRequest.h"
#include "Result/GetGlobalRankingReceivedRewardByUserIdResult.h"
#include "Task/Rest/GetGlobalRankingReceivedRewardByUserIdTask.h"
#include "Task/WebSocket/GetGlobalRankingReceivedRewardByUserIdTask.h"

// DeleteGlobalRankingReceivedRewardByUserId
#include "Request/DeleteGlobalRankingReceivedRewardByUserIdRequest.h"
#include "Result/DeleteGlobalRankingReceivedRewardByUserIdResult.h"
#include "Task/Rest/DeleteGlobalRankingReceivedRewardByUserIdTask.h"
#include "Task/WebSocket/DeleteGlobalRankingReceivedRewardByUserIdTask.h"

// CreateGlobalRankingReceivedRewardByStampTask
#include "Request/CreateGlobalRankingReceivedRewardByStampTaskRequest.h"
#include "Result/CreateGlobalRankingReceivedRewardByStampTaskResult.h"
#include "Task/Rest/CreateGlobalRankingReceivedRewardByStampTaskTask.h"
#include "Task/WebSocket/CreateGlobalRankingReceivedRewardByStampTaskTask.h"

// DescribeGlobalRankings
#include "Request/DescribeGlobalRankingsRequest.h"
#include "Result/DescribeGlobalRankingsResult.h"
#include "Task/Rest/DescribeGlobalRankingsTask.h"
#include "Task/WebSocket/DescribeGlobalRankingsTask.h"

// DescribeGlobalRankingsByUserId
#include "Request/DescribeGlobalRankingsByUserIdRequest.h"
#include "Result/DescribeGlobalRankingsByUserIdResult.h"
#include "Task/Rest/DescribeGlobalRankingsByUserIdTask.h"
#include "Task/WebSocket/DescribeGlobalRankingsByUserIdTask.h"

// GetGlobalRanking
#include "Request/GetGlobalRankingRequest.h"
#include "Result/GetGlobalRankingResult.h"
#include "Task/Rest/GetGlobalRankingTask.h"
#include "Task/WebSocket/GetGlobalRankingTask.h"

// GetGlobalRankingByUserId
#include "Request/GetGlobalRankingByUserIdRequest.h"
#include "Result/GetGlobalRankingByUserIdResult.h"
#include "Task/Rest/GetGlobalRankingByUserIdTask.h"
#include "Task/WebSocket/GetGlobalRankingByUserIdTask.h"

// DescribeClusterRankingModels
#include "Request/DescribeClusterRankingModelsRequest.h"
#include "Result/DescribeClusterRankingModelsResult.h"
#include "Task/Rest/DescribeClusterRankingModelsTask.h"
#include "Task/WebSocket/DescribeClusterRankingModelsTask.h"

// GetClusterRankingModel
#include "Request/GetClusterRankingModelRequest.h"
#include "Result/GetClusterRankingModelResult.h"
#include "Task/Rest/GetClusterRankingModelTask.h"
#include "Task/WebSocket/GetClusterRankingModelTask.h"

// DescribeClusterRankingModelMasters
#include "Request/DescribeClusterRankingModelMastersRequest.h"
#include "Result/DescribeClusterRankingModelMastersResult.h"
#include "Task/Rest/DescribeClusterRankingModelMastersTask.h"
#include "Task/WebSocket/DescribeClusterRankingModelMastersTask.h"

// CreateClusterRankingModelMaster
#include "Request/CreateClusterRankingModelMasterRequest.h"
#include "Result/CreateClusterRankingModelMasterResult.h"
#include "Task/Rest/CreateClusterRankingModelMasterTask.h"
#include "Task/WebSocket/CreateClusterRankingModelMasterTask.h"

// GetClusterRankingModelMaster
#include "Request/GetClusterRankingModelMasterRequest.h"
#include "Result/GetClusterRankingModelMasterResult.h"
#include "Task/Rest/GetClusterRankingModelMasterTask.h"
#include "Task/WebSocket/GetClusterRankingModelMasterTask.h"

// UpdateClusterRankingModelMaster
#include "Request/UpdateClusterRankingModelMasterRequest.h"
#include "Result/UpdateClusterRankingModelMasterResult.h"
#include "Task/Rest/UpdateClusterRankingModelMasterTask.h"
#include "Task/WebSocket/UpdateClusterRankingModelMasterTask.h"

// DeleteClusterRankingModelMaster
#include "Request/DeleteClusterRankingModelMasterRequest.h"
#include "Result/DeleteClusterRankingModelMasterResult.h"
#include "Task/Rest/DeleteClusterRankingModelMasterTask.h"
#include "Task/WebSocket/DeleteClusterRankingModelMasterTask.h"

// DescribeClusterRankingScores
#include "Request/DescribeClusterRankingScoresRequest.h"
#include "Result/DescribeClusterRankingScoresResult.h"
#include "Task/Rest/DescribeClusterRankingScoresTask.h"
#include "Task/WebSocket/DescribeClusterRankingScoresTask.h"

// DescribeClusterRankingScoresByUserId
#include "Request/DescribeClusterRankingScoresByUserIdRequest.h"
#include "Result/DescribeClusterRankingScoresByUserIdResult.h"
#include "Task/Rest/DescribeClusterRankingScoresByUserIdTask.h"
#include "Task/WebSocket/DescribeClusterRankingScoresByUserIdTask.h"

// PutClusterRankingScore
#include "Request/PutClusterRankingScoreRequest.h"
#include "Result/PutClusterRankingScoreResult.h"
#include "Task/Rest/PutClusterRankingScoreTask.h"
#include "Task/WebSocket/PutClusterRankingScoreTask.h"

// PutClusterRankingScoreByUserId
#include "Request/PutClusterRankingScoreByUserIdRequest.h"
#include "Result/PutClusterRankingScoreByUserIdResult.h"
#include "Task/Rest/PutClusterRankingScoreByUserIdTask.h"
#include "Task/WebSocket/PutClusterRankingScoreByUserIdTask.h"

// GetClusterRankingScore
#include "Request/GetClusterRankingScoreRequest.h"
#include "Result/GetClusterRankingScoreResult.h"
#include "Task/Rest/GetClusterRankingScoreTask.h"
#include "Task/WebSocket/GetClusterRankingScoreTask.h"

// GetClusterRankingScoreByUserId
#include "Request/GetClusterRankingScoreByUserIdRequest.h"
#include "Result/GetClusterRankingScoreByUserIdResult.h"
#include "Task/Rest/GetClusterRankingScoreByUserIdTask.h"
#include "Task/WebSocket/GetClusterRankingScoreByUserIdTask.h"

// DeleteClusterRankingScoreByUserId
#include "Request/DeleteClusterRankingScoreByUserIdRequest.h"
#include "Result/DeleteClusterRankingScoreByUserIdResult.h"
#include "Task/Rest/DeleteClusterRankingScoreByUserIdTask.h"
#include "Task/WebSocket/DeleteClusterRankingScoreByUserIdTask.h"

// DescribeClusterRankingReceivedRewards
#include "Request/DescribeClusterRankingReceivedRewardsRequest.h"
#include "Result/DescribeClusterRankingReceivedRewardsResult.h"
#include "Task/Rest/DescribeClusterRankingReceivedRewardsTask.h"
#include "Task/WebSocket/DescribeClusterRankingReceivedRewardsTask.h"

// DescribeClusterRankingReceivedRewardsByUserId
#include "Request/DescribeClusterRankingReceivedRewardsByUserIdRequest.h"
#include "Result/DescribeClusterRankingReceivedRewardsByUserIdResult.h"
#include "Task/Rest/DescribeClusterRankingReceivedRewardsByUserIdTask.h"
#include "Task/WebSocket/DescribeClusterRankingReceivedRewardsByUserIdTask.h"

// CreateClusterRankingReceivedReward
#include "Request/CreateClusterRankingReceivedRewardRequest.h"
#include "Result/CreateClusterRankingReceivedRewardResult.h"
#include "Task/Rest/CreateClusterRankingReceivedRewardTask.h"
#include "Task/WebSocket/CreateClusterRankingReceivedRewardTask.h"

// CreateClusterRankingReceivedRewardByUserId
#include "Request/CreateClusterRankingReceivedRewardByUserIdRequest.h"
#include "Result/CreateClusterRankingReceivedRewardByUserIdResult.h"
#include "Task/Rest/CreateClusterRankingReceivedRewardByUserIdTask.h"
#include "Task/WebSocket/CreateClusterRankingReceivedRewardByUserIdTask.h"

// ReceiveClusterRankingReceivedReward
#include "Request/ReceiveClusterRankingReceivedRewardRequest.h"
#include "Result/ReceiveClusterRankingReceivedRewardResult.h"
#include "Task/Rest/ReceiveClusterRankingReceivedRewardTask.h"
#include "Task/WebSocket/ReceiveClusterRankingReceivedRewardTask.h"

// ReceiveClusterRankingReceivedRewardByUserId
#include "Request/ReceiveClusterRankingReceivedRewardByUserIdRequest.h"
#include "Result/ReceiveClusterRankingReceivedRewardByUserIdResult.h"
#include "Task/Rest/ReceiveClusterRankingReceivedRewardByUserIdTask.h"
#include "Task/WebSocket/ReceiveClusterRankingReceivedRewardByUserIdTask.h"

// GetClusterRankingReceivedReward
#include "Request/GetClusterRankingReceivedRewardRequest.h"
#include "Result/GetClusterRankingReceivedRewardResult.h"
#include "Task/Rest/GetClusterRankingReceivedRewardTask.h"
#include "Task/WebSocket/GetClusterRankingReceivedRewardTask.h"

// GetClusterRankingReceivedRewardByUserId
#include "Request/GetClusterRankingReceivedRewardByUserIdRequest.h"
#include "Result/GetClusterRankingReceivedRewardByUserIdResult.h"
#include "Task/Rest/GetClusterRankingReceivedRewardByUserIdTask.h"
#include "Task/WebSocket/GetClusterRankingReceivedRewardByUserIdTask.h"

// DeleteClusterRankingReceivedRewardByUserId
#include "Request/DeleteClusterRankingReceivedRewardByUserIdRequest.h"
#include "Result/DeleteClusterRankingReceivedRewardByUserIdResult.h"
#include "Task/Rest/DeleteClusterRankingReceivedRewardByUserIdTask.h"
#include "Task/WebSocket/DeleteClusterRankingReceivedRewardByUserIdTask.h"

// CreateClusterRankingReceivedRewardByStampTask
#include "Request/CreateClusterRankingReceivedRewardByStampTaskRequest.h"
#include "Result/CreateClusterRankingReceivedRewardByStampTaskResult.h"
#include "Task/Rest/CreateClusterRankingReceivedRewardByStampTaskTask.h"
#include "Task/WebSocket/CreateClusterRankingReceivedRewardByStampTaskTask.h"

// DescribeClusterRankings
#include "Request/DescribeClusterRankingsRequest.h"
#include "Result/DescribeClusterRankingsResult.h"
#include "Task/Rest/DescribeClusterRankingsTask.h"
#include "Task/WebSocket/DescribeClusterRankingsTask.h"

// DescribeClusterRankingsByUserId
#include "Request/DescribeClusterRankingsByUserIdRequest.h"
#include "Result/DescribeClusterRankingsByUserIdResult.h"
#include "Task/Rest/DescribeClusterRankingsByUserIdTask.h"
#include "Task/WebSocket/DescribeClusterRankingsByUserIdTask.h"

// GetClusterRanking
#include "Request/GetClusterRankingRequest.h"
#include "Result/GetClusterRankingResult.h"
#include "Task/Rest/GetClusterRankingTask.h"
#include "Task/WebSocket/GetClusterRankingTask.h"

// GetClusterRankingByUserId
#include "Request/GetClusterRankingByUserIdRequest.h"
#include "Result/GetClusterRankingByUserIdResult.h"
#include "Task/Rest/GetClusterRankingByUserIdTask.h"
#include "Task/WebSocket/GetClusterRankingByUserIdTask.h"

// DescribeSubscribeRankingModels
#include "Request/DescribeSubscribeRankingModelsRequest.h"
#include "Result/DescribeSubscribeRankingModelsResult.h"
#include "Task/Rest/DescribeSubscribeRankingModelsTask.h"
#include "Task/WebSocket/DescribeSubscribeRankingModelsTask.h"

// GetSubscribeRankingModel
#include "Request/GetSubscribeRankingModelRequest.h"
#include "Result/GetSubscribeRankingModelResult.h"
#include "Task/Rest/GetSubscribeRankingModelTask.h"
#include "Task/WebSocket/GetSubscribeRankingModelTask.h"

// DescribeSubscribeRankingModelMasters
#include "Request/DescribeSubscribeRankingModelMastersRequest.h"
#include "Result/DescribeSubscribeRankingModelMastersResult.h"
#include "Task/Rest/DescribeSubscribeRankingModelMastersTask.h"
#include "Task/WebSocket/DescribeSubscribeRankingModelMastersTask.h"

// CreateSubscribeRankingModelMaster
#include "Request/CreateSubscribeRankingModelMasterRequest.h"
#include "Result/CreateSubscribeRankingModelMasterResult.h"
#include "Task/Rest/CreateSubscribeRankingModelMasterTask.h"
#include "Task/WebSocket/CreateSubscribeRankingModelMasterTask.h"

// GetSubscribeRankingModelMaster
#include "Request/GetSubscribeRankingModelMasterRequest.h"
#include "Result/GetSubscribeRankingModelMasterResult.h"
#include "Task/Rest/GetSubscribeRankingModelMasterTask.h"
#include "Task/WebSocket/GetSubscribeRankingModelMasterTask.h"

// UpdateSubscribeRankingModelMaster
#include "Request/UpdateSubscribeRankingModelMasterRequest.h"
#include "Result/UpdateSubscribeRankingModelMasterResult.h"
#include "Task/Rest/UpdateSubscribeRankingModelMasterTask.h"
#include "Task/WebSocket/UpdateSubscribeRankingModelMasterTask.h"

// DeleteSubscribeRankingModelMaster
#include "Request/DeleteSubscribeRankingModelMasterRequest.h"
#include "Result/DeleteSubscribeRankingModelMasterResult.h"
#include "Task/Rest/DeleteSubscribeRankingModelMasterTask.h"
#include "Task/WebSocket/DeleteSubscribeRankingModelMasterTask.h"

// DescribeSubscribes
#include "Request/DescribeSubscribesRequest.h"
#include "Result/DescribeSubscribesResult.h"
#include "Task/Rest/DescribeSubscribesTask.h"
#include "Task/WebSocket/DescribeSubscribesTask.h"

// DescribeSubscribesByUserId
#include "Request/DescribeSubscribesByUserIdRequest.h"
#include "Result/DescribeSubscribesByUserIdResult.h"
#include "Task/Rest/DescribeSubscribesByUserIdTask.h"
#include "Task/WebSocket/DescribeSubscribesByUserIdTask.h"

// AddSubscribe
#include "Request/AddSubscribeRequest.h"
#include "Result/AddSubscribeResult.h"
#include "Task/Rest/AddSubscribeTask.h"
#include "Task/WebSocket/AddSubscribeTask.h"

// AddSubscribeByUserId
#include "Request/AddSubscribeByUserIdRequest.h"
#include "Result/AddSubscribeByUserIdResult.h"
#include "Task/Rest/AddSubscribeByUserIdTask.h"
#include "Task/WebSocket/AddSubscribeByUserIdTask.h"

// DescribeSubscribeRankingScores
#include "Request/DescribeSubscribeRankingScoresRequest.h"
#include "Result/DescribeSubscribeRankingScoresResult.h"
#include "Task/Rest/DescribeSubscribeRankingScoresTask.h"
#include "Task/WebSocket/DescribeSubscribeRankingScoresTask.h"

// DescribeSubscribeRankingScoresByUserId
#include "Request/DescribeSubscribeRankingScoresByUserIdRequest.h"
#include "Result/DescribeSubscribeRankingScoresByUserIdResult.h"
#include "Task/Rest/DescribeSubscribeRankingScoresByUserIdTask.h"
#include "Task/WebSocket/DescribeSubscribeRankingScoresByUserIdTask.h"

// PutSubscribeRankingScore
#include "Request/PutSubscribeRankingScoreRequest.h"
#include "Result/PutSubscribeRankingScoreResult.h"
#include "Task/Rest/PutSubscribeRankingScoreTask.h"
#include "Task/WebSocket/PutSubscribeRankingScoreTask.h"

// PutSubscribeRankingScoreByUserId
#include "Request/PutSubscribeRankingScoreByUserIdRequest.h"
#include "Result/PutSubscribeRankingScoreByUserIdResult.h"
#include "Task/Rest/PutSubscribeRankingScoreByUserIdTask.h"
#include "Task/WebSocket/PutSubscribeRankingScoreByUserIdTask.h"

// GetSubscribeRankingScore
#include "Request/GetSubscribeRankingScoreRequest.h"
#include "Result/GetSubscribeRankingScoreResult.h"
#include "Task/Rest/GetSubscribeRankingScoreTask.h"
#include "Task/WebSocket/GetSubscribeRankingScoreTask.h"

// GetSubscribeRankingScoreByUserId
#include "Request/GetSubscribeRankingScoreByUserIdRequest.h"
#include "Result/GetSubscribeRankingScoreByUserIdResult.h"
#include "Task/Rest/GetSubscribeRankingScoreByUserIdTask.h"
#include "Task/WebSocket/GetSubscribeRankingScoreByUserIdTask.h"

// DeleteSubscribeRankingScoreByUserId
#include "Request/DeleteSubscribeRankingScoreByUserIdRequest.h"
#include "Result/DeleteSubscribeRankingScoreByUserIdResult.h"
#include "Task/Rest/DeleteSubscribeRankingScoreByUserIdTask.h"
#include "Task/WebSocket/DeleteSubscribeRankingScoreByUserIdTask.h"

// DescribeSubscribeRankings
#include "Request/DescribeSubscribeRankingsRequest.h"
#include "Result/DescribeSubscribeRankingsResult.h"
#include "Task/Rest/DescribeSubscribeRankingsTask.h"
#include "Task/WebSocket/DescribeSubscribeRankingsTask.h"

// DescribeSubscribeRankingsByUserId
#include "Request/DescribeSubscribeRankingsByUserIdRequest.h"
#include "Result/DescribeSubscribeRankingsByUserIdResult.h"
#include "Task/Rest/DescribeSubscribeRankingsByUserIdTask.h"
#include "Task/WebSocket/DescribeSubscribeRankingsByUserIdTask.h"

// GetSubscribeRanking
#include "Request/GetSubscribeRankingRequest.h"
#include "Result/GetSubscribeRankingResult.h"
#include "Task/Rest/GetSubscribeRankingTask.h"
#include "Task/WebSocket/GetSubscribeRankingTask.h"

// GetSubscribeRankingByUserId
#include "Request/GetSubscribeRankingByUserIdRequest.h"
#include "Result/GetSubscribeRankingByUserIdResult.h"
#include "Task/Rest/GetSubscribeRankingByUserIdTask.h"
#include "Task/WebSocket/GetSubscribeRankingByUserIdTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentRankingMaster
#include "Request/GetCurrentRankingMasterRequest.h"
#include "Result/GetCurrentRankingMasterResult.h"
#include "Task/Rest/GetCurrentRankingMasterTask.h"
#include "Task/WebSocket/GetCurrentRankingMasterTask.h"

// UpdateCurrentRankingMaster
#include "Request/UpdateCurrentRankingMasterRequest.h"
#include "Result/UpdateCurrentRankingMasterResult.h"
#include "Task/Rest/UpdateCurrentRankingMasterTask.h"
#include "Task/WebSocket/UpdateCurrentRankingMasterTask.h"

// UpdateCurrentRankingMasterFromGitHub
#include "Request/UpdateCurrentRankingMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentRankingMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentRankingMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentRankingMasterFromGitHubTask.h"

// GetSubscribe
#include "Request/GetSubscribeRequest.h"
#include "Result/GetSubscribeResult.h"
#include "Task/Rest/GetSubscribeTask.h"
#include "Task/WebSocket/GetSubscribeTask.h"

// GetSubscribeByUserId
#include "Request/GetSubscribeByUserIdRequest.h"
#include "Result/GetSubscribeByUserIdResult.h"
#include "Task/Rest/GetSubscribeByUserIdTask.h"
#include "Task/WebSocket/GetSubscribeByUserIdTask.h"

// DeleteSubscribe
#include "Request/DeleteSubscribeRequest.h"
#include "Result/DeleteSubscribeResult.h"
#include "Task/Rest/DeleteSubscribeTask.h"
#include "Task/WebSocket/DeleteSubscribeTask.h"

// DeleteSubscribeByUserId
#include "Request/DeleteSubscribeByUserIdRequest.h"
#include "Result/DeleteSubscribeByUserIdResult.h"
#include "Task/Rest/DeleteSubscribeByUserIdTask.h"
#include "Task/WebSocket/DeleteSubscribeByUserIdTask.h"

// Client
#include "Gs2Ranking2RestClient.h"
#include "Gs2Ranking2WebSocketClient.h"