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
#include "Request/DescribeCategoryModelsRequest.h"
#include "Task/Rest/DescribeCategoryModelsTask.h"
#include "Request/GetCategoryModelRequest.h"
#include "Task/Rest/GetCategoryModelTask.h"
#include "Request/DescribeCategoryModelMastersRequest.h"
#include "Task/Rest/DescribeCategoryModelMastersTask.h"
#include "Request/CreateCategoryModelMasterRequest.h"
#include "Task/Rest/CreateCategoryModelMasterTask.h"
#include "Request/GetCategoryModelMasterRequest.h"
#include "Task/Rest/GetCategoryModelMasterTask.h"
#include "Request/UpdateCategoryModelMasterRequest.h"
#include "Task/Rest/UpdateCategoryModelMasterTask.h"
#include "Request/DeleteCategoryModelMasterRequest.h"
#include "Task/Rest/DeleteCategoryModelMasterTask.h"
#include "Request/SubscribeRequest.h"
#include "Task/Rest/SubscribeTask.h"
#include "Request/SubscribeByUserIdRequest.h"
#include "Task/Rest/SubscribeByUserIdTask.h"
#include "Request/DescribeScoresRequest.h"
#include "Task/Rest/DescribeScoresTask.h"
#include "Request/DescribeScoresByUserIdRequest.h"
#include "Task/Rest/DescribeScoresByUserIdTask.h"
#include "Request/GetScoreRequest.h"
#include "Task/Rest/GetScoreTask.h"
#include "Request/GetScoreByUserIdRequest.h"
#include "Task/Rest/GetScoreByUserIdTask.h"
#include "Request/DescribeRankingsRequest.h"
#include "Task/Rest/DescribeRankingsTask.h"
#include "Request/DescribeRankingssByUserIdRequest.h"
#include "Task/Rest/DescribeRankingssByUserIdTask.h"
#include "Request/DescribeNearRankingsRequest.h"
#include "Task/Rest/DescribeNearRankingsTask.h"
#include "Request/GetRankingRequest.h"
#include "Task/Rest/GetRankingTask.h"
#include "Request/GetRankingByUserIdRequest.h"
#include "Task/Rest/GetRankingByUserIdTask.h"
#include "Request/PutScoreRequest.h"
#include "Task/Rest/PutScoreTask.h"
#include "Request/PutScoreByUserIdRequest.h"
#include "Task/Rest/PutScoreByUserIdTask.h"
#include "Request/CalcRankingRequest.h"
#include "Task/Rest/CalcRankingTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentRankingMasterRequest.h"
#include "Task/Rest/GetCurrentRankingMasterTask.h"
#include "Request/UpdateCurrentRankingMasterRequest.h"
#include "Task/Rest/UpdateCurrentRankingMasterTask.h"
#include "Request/UpdateCurrentRankingMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentRankingMasterFromGitHubTask.h"
#include "Request/GetSubscribeRequest.h"
#include "Task/Rest/GetSubscribeTask.h"
#include "Request/GetSubscribeByUserIdRequest.h"
#include "Task/Rest/GetSubscribeByUserIdTask.h"
#include "Request/UnsubscribeRequest.h"
#include "Task/Rest/UnsubscribeTask.h"
#include "Request/UnsubscribeByUserIdRequest.h"
#include "Task/Rest/UnsubscribeByUserIdTask.h"
#include "Request/DescribeSubscribesByCategoryNameRequest.h"
#include "Task/Rest/DescribeSubscribesByCategoryNameTask.h"
#include "Request/DescribeSubscribesByCategoryNameAndUserIdRequest.h"
#include "Task/Rest/DescribeSubscribesByCategoryNameAndUserIdTask.h"

namespace Gs2::Ranking
{
    class GS2RANKING_API FGs2RankingRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2RankingRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCategoryModelsTask>> DescribeCategoryModels(
            const Request::FDescribeCategoryModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCategoryModelTask>> GetCategoryModel(
            const Request::FGetCategoryModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCategoryModelMastersTask>> DescribeCategoryModelMasters(
            const Request::FDescribeCategoryModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateCategoryModelMasterTask>> CreateCategoryModelMaster(
            const Request::FCreateCategoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCategoryModelMasterTask>> GetCategoryModelMaster(
            const Request::FGetCategoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCategoryModelMasterTask>> UpdateCategoryModelMaster(
            const Request::FUpdateCategoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteCategoryModelMasterTask>> DeleteCategoryModelMaster(
            const Request::FDeleteCategoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSubscribeTask>> Subscribe(
            const Request::FSubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSubscribeByUserIdTask>> SubscribeByUserId(
            const Request::FSubscribeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeScoresTask>> DescribeScores(
            const Request::FDescribeScoresRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeScoresByUserIdTask>> DescribeScoresByUserId(
            const Request::FDescribeScoresByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetScoreTask>> GetScore(
            const Request::FGetScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetScoreByUserIdTask>> GetScoreByUserId(
            const Request::FGetScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRankingsTask>> DescribeRankings(
            const Request::FDescribeRankingsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRankingssByUserIdTask>> DescribeRankingssByUserId(
            const Request::FDescribeRankingssByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeNearRankingsTask>> DescribeNearRankings(
            const Request::FDescribeNearRankingsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRankingTask>> GetRanking(
            const Request::FGetRankingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRankingByUserIdTask>> GetRankingByUserId(
            const Request::FGetRankingByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPutScoreTask>> PutScore(
            const Request::FPutScoreRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPutScoreByUserIdTask>> PutScoreByUserId(
            const Request::FPutScoreByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCalcRankingTask>> CalcRanking(
            const Request::FCalcRankingRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentRankingMasterTask>> GetCurrentRankingMaster(
            const Request::FGetCurrentRankingMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentRankingMasterTask>> UpdateCurrentRankingMaster(
            const Request::FUpdateCurrentRankingMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentRankingMasterFromGitHubTask>> UpdateCurrentRankingMasterFromGitHub(
            const Request::FUpdateCurrentRankingMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeTask>> GetSubscribe(
            const Request::FGetSubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeByUserIdTask>> GetSubscribeByUserId(
            const Request::FGetSubscribeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUnsubscribeTask>> Unsubscribe(
            const Request::FUnsubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUnsubscribeByUserIdTask>> UnsubscribeByUserId(
            const Request::FUnsubscribeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribesByCategoryNameTask>> DescribeSubscribesByCategoryName(
            const Request::FDescribeSubscribesByCategoryNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribesByCategoryNameAndUserIdTask>> DescribeSubscribesByCategoryNameAndUserId(
            const Request::FDescribeSubscribesByCategoryNameAndUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2RankingRestClient, ESPMode::ThreadSafe> FGs2RankingRestClientPtr;
}