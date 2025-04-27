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
#include "Model/CategoryModel.h"
#include "Model/CategoryModelMaster.h"
#include "Model/Subscribe.h"
#include "Model/Score.h"
#include "Model/Ranking.h"
#include "Model/CurrentRankingMaster.h"
#include "Model/Scope.h"
#include "Model/GlobalRankingSetting.h"
#include "Model/FixedTiming.h"
#include "Model/CalculatedAt.h"
#include "Model/SubscribeUser.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/LogSetting.h"

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

// DescribeCategoryModels
#include "Request/DescribeCategoryModelsRequest.h"
#include "Result/DescribeCategoryModelsResult.h"
#include "Task/Rest/DescribeCategoryModelsTask.h"
#include "Task/WebSocket/DescribeCategoryModelsTask.h"

// GetCategoryModel
#include "Request/GetCategoryModelRequest.h"
#include "Result/GetCategoryModelResult.h"
#include "Task/Rest/GetCategoryModelTask.h"
#include "Task/WebSocket/GetCategoryModelTask.h"

// DescribeCategoryModelMasters
#include "Request/DescribeCategoryModelMastersRequest.h"
#include "Result/DescribeCategoryModelMastersResult.h"
#include "Task/Rest/DescribeCategoryModelMastersTask.h"
#include "Task/WebSocket/DescribeCategoryModelMastersTask.h"

// CreateCategoryModelMaster
#include "Request/CreateCategoryModelMasterRequest.h"
#include "Result/CreateCategoryModelMasterResult.h"
#include "Task/Rest/CreateCategoryModelMasterTask.h"
#include "Task/WebSocket/CreateCategoryModelMasterTask.h"

// GetCategoryModelMaster
#include "Request/GetCategoryModelMasterRequest.h"
#include "Result/GetCategoryModelMasterResult.h"
#include "Task/Rest/GetCategoryModelMasterTask.h"
#include "Task/WebSocket/GetCategoryModelMasterTask.h"

// UpdateCategoryModelMaster
#include "Request/UpdateCategoryModelMasterRequest.h"
#include "Result/UpdateCategoryModelMasterResult.h"
#include "Task/Rest/UpdateCategoryModelMasterTask.h"
#include "Task/WebSocket/UpdateCategoryModelMasterTask.h"

// DeleteCategoryModelMaster
#include "Request/DeleteCategoryModelMasterRequest.h"
#include "Result/DeleteCategoryModelMasterResult.h"
#include "Task/Rest/DeleteCategoryModelMasterTask.h"
#include "Task/WebSocket/DeleteCategoryModelMasterTask.h"

// Subscribe
#include "Request/SubscribeRequest.h"
#include "Result/SubscribeResult.h"
#include "Task/Rest/SubscribeTask.h"
#include "Task/WebSocket/SubscribeTask.h"

// SubscribeByUserId
#include "Request/SubscribeByUserIdRequest.h"
#include "Result/SubscribeByUserIdResult.h"
#include "Task/Rest/SubscribeByUserIdTask.h"
#include "Task/WebSocket/SubscribeByUserIdTask.h"

// DescribeScores
#include "Request/DescribeScoresRequest.h"
#include "Result/DescribeScoresResult.h"
#include "Task/Rest/DescribeScoresTask.h"
#include "Task/WebSocket/DescribeScoresTask.h"

// DescribeScoresByUserId
#include "Request/DescribeScoresByUserIdRequest.h"
#include "Result/DescribeScoresByUserIdResult.h"
#include "Task/Rest/DescribeScoresByUserIdTask.h"
#include "Task/WebSocket/DescribeScoresByUserIdTask.h"

// GetScore
#include "Request/GetScoreRequest.h"
#include "Result/GetScoreResult.h"
#include "Task/Rest/GetScoreTask.h"
#include "Task/WebSocket/GetScoreTask.h"

// GetScoreByUserId
#include "Request/GetScoreByUserIdRequest.h"
#include "Result/GetScoreByUserIdResult.h"
#include "Task/Rest/GetScoreByUserIdTask.h"
#include "Task/WebSocket/GetScoreByUserIdTask.h"

// DescribeRankings
#include "Request/DescribeRankingsRequest.h"
#include "Result/DescribeRankingsResult.h"
#include "Task/Rest/DescribeRankingsTask.h"
#include "Task/WebSocket/DescribeRankingsTask.h"

// DescribeRankingssByUserId
#include "Request/DescribeRankingssByUserIdRequest.h"
#include "Result/DescribeRankingssByUserIdResult.h"
#include "Task/Rest/DescribeRankingssByUserIdTask.h"
#include "Task/WebSocket/DescribeRankingssByUserIdTask.h"

// DescribeNearRankings
#include "Request/DescribeNearRankingsRequest.h"
#include "Result/DescribeNearRankingsResult.h"
#include "Task/Rest/DescribeNearRankingsTask.h"
#include "Task/WebSocket/DescribeNearRankingsTask.h"

// GetRanking
#include "Request/GetRankingRequest.h"
#include "Result/GetRankingResult.h"
#include "Task/Rest/GetRankingTask.h"
#include "Task/WebSocket/GetRankingTask.h"

// GetRankingByUserId
#include "Request/GetRankingByUserIdRequest.h"
#include "Result/GetRankingByUserIdResult.h"
#include "Task/Rest/GetRankingByUserIdTask.h"
#include "Task/WebSocket/GetRankingByUserIdTask.h"

// PutScore
#include "Request/PutScoreRequest.h"
#include "Result/PutScoreResult.h"
#include "Task/Rest/PutScoreTask.h"
#include "Task/WebSocket/PutScoreTask.h"

// PutScoreByUserId
#include "Request/PutScoreByUserIdRequest.h"
#include "Result/PutScoreByUserIdResult.h"
#include "Task/Rest/PutScoreByUserIdTask.h"
#include "Task/WebSocket/PutScoreByUserIdTask.h"

// CalcRanking
#include "Request/CalcRankingRequest.h"
#include "Result/CalcRankingResult.h"
#include "Task/Rest/CalcRankingTask.h"
#include "Task/WebSocket/CalcRankingTask.h"

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

// PreUpdateCurrentRankingMaster
#include "Request/PreUpdateCurrentRankingMasterRequest.h"
#include "Result/PreUpdateCurrentRankingMasterResult.h"
#include "Task/Rest/PreUpdateCurrentRankingMasterTask.h"
#include "Task/WebSocket/PreUpdateCurrentRankingMasterTask.h"

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

// Unsubscribe
#include "Request/UnsubscribeRequest.h"
#include "Result/UnsubscribeResult.h"
#include "Task/Rest/UnsubscribeTask.h"
#include "Task/WebSocket/UnsubscribeTask.h"

// UnsubscribeByUserId
#include "Request/UnsubscribeByUserIdRequest.h"
#include "Result/UnsubscribeByUserIdResult.h"
#include "Task/Rest/UnsubscribeByUserIdTask.h"
#include "Task/WebSocket/UnsubscribeByUserIdTask.h"

// DescribeSubscribesByCategoryName
#include "Request/DescribeSubscribesByCategoryNameRequest.h"
#include "Result/DescribeSubscribesByCategoryNameResult.h"
#include "Task/Rest/DescribeSubscribesByCategoryNameTask.h"
#include "Task/WebSocket/DescribeSubscribesByCategoryNameTask.h"

// DescribeSubscribesByCategoryNameAndUserId
#include "Request/DescribeSubscribesByCategoryNameAndUserIdRequest.h"
#include "Result/DescribeSubscribesByCategoryNameAndUserIdResult.h"
#include "Task/Rest/DescribeSubscribesByCategoryNameAndUserIdTask.h"
#include "Task/WebSocket/DescribeSubscribesByCategoryNameAndUserIdTask.h"

// Client
#include "Gs2RankingRestClient.h"
#include "Gs2RankingWebSocketClient.h"