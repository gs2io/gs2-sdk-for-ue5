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
#include "Request/DescribeLotteryModelMastersRequest.h"
#include "Task/Rest/DescribeLotteryModelMastersTask.h"
#include "Request/CreateLotteryModelMasterRequest.h"
#include "Task/Rest/CreateLotteryModelMasterTask.h"
#include "Request/GetLotteryModelMasterRequest.h"
#include "Task/Rest/GetLotteryModelMasterTask.h"
#include "Request/UpdateLotteryModelMasterRequest.h"
#include "Task/Rest/UpdateLotteryModelMasterTask.h"
#include "Request/DeleteLotteryModelMasterRequest.h"
#include "Task/Rest/DeleteLotteryModelMasterTask.h"
#include "Request/DescribePrizeTableMastersRequest.h"
#include "Task/Rest/DescribePrizeTableMastersTask.h"
#include "Request/CreatePrizeTableMasterRequest.h"
#include "Task/Rest/CreatePrizeTableMasterTask.h"
#include "Request/GetPrizeTableMasterRequest.h"
#include "Task/Rest/GetPrizeTableMasterTask.h"
#include "Request/UpdatePrizeTableMasterRequest.h"
#include "Task/Rest/UpdatePrizeTableMasterTask.h"
#include "Request/DeletePrizeTableMasterRequest.h"
#include "Task/Rest/DeletePrizeTableMasterTask.h"
#include "Request/DescribeLotteryModelsRequest.h"
#include "Task/Rest/DescribeLotteryModelsTask.h"
#include "Request/GetLotteryModelRequest.h"
#include "Task/Rest/GetLotteryModelTask.h"
#include "Request/DescribePrizeTablesRequest.h"
#include "Task/Rest/DescribePrizeTablesTask.h"
#include "Request/GetPrizeTableRequest.h"
#include "Task/Rest/GetPrizeTableTask.h"
#include "Request/DrawByUserIdRequest.h"
#include "Task/Rest/DrawByUserIdTask.h"
#include "Request/PredictionRequest.h"
#include "Task/Rest/PredictionTask.h"
#include "Request/PredictionByUserIdRequest.h"
#include "Task/Rest/PredictionByUserIdTask.h"
#include "Request/DrawWithRandomSeedByUserIdRequest.h"
#include "Task/Rest/DrawWithRandomSeedByUserIdTask.h"
#include "Request/DrawByStampSheetRequest.h"
#include "Task/Rest/DrawByStampSheetTask.h"
#include "Request/DescribeProbabilitiesRequest.h"
#include "Task/Rest/DescribeProbabilitiesTask.h"
#include "Request/DescribeProbabilitiesByUserIdRequest.h"
#include "Task/Rest/DescribeProbabilitiesByUserIdTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentLotteryMasterRequest.h"
#include "Task/Rest/GetCurrentLotteryMasterTask.h"
#include "Request/UpdateCurrentLotteryMasterRequest.h"
#include "Task/Rest/UpdateCurrentLotteryMasterTask.h"
#include "Request/UpdateCurrentLotteryMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentLotteryMasterFromGitHubTask.h"
#include "Request/DescribePrizeLimitsRequest.h"
#include "Task/Rest/DescribePrizeLimitsTask.h"
#include "Request/GetPrizeLimitRequest.h"
#include "Task/Rest/GetPrizeLimitTask.h"
#include "Request/ResetPrizeLimitRequest.h"
#include "Task/Rest/ResetPrizeLimitTask.h"
#include "Request/DescribeBoxesRequest.h"
#include "Task/Rest/DescribeBoxesTask.h"
#include "Request/DescribeBoxesByUserIdRequest.h"
#include "Task/Rest/DescribeBoxesByUserIdTask.h"
#include "Request/GetBoxRequest.h"
#include "Task/Rest/GetBoxTask.h"
#include "Request/GetBoxByUserIdRequest.h"
#include "Task/Rest/GetBoxByUserIdTask.h"
#include "Request/ResetBoxRequest.h"
#include "Task/Rest/ResetBoxTask.h"
#include "Request/ResetBoxByUserIdRequest.h"
#include "Task/Rest/ResetBoxByUserIdTask.h"

namespace Gs2::Lottery
{
    class GS2LOTTERY_API FGs2LotteryRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2LotteryRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeLotteryModelMastersTask>> DescribeLotteryModelMasters(
            const Request::FDescribeLotteryModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateLotteryModelMasterTask>> CreateLotteryModelMaster(
            const Request::FCreateLotteryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetLotteryModelMasterTask>> GetLotteryModelMaster(
            const Request::FGetLotteryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateLotteryModelMasterTask>> UpdateLotteryModelMaster(
            const Request::FUpdateLotteryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteLotteryModelMasterTask>> DeleteLotteryModelMaster(
            const Request::FDeleteLotteryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribePrizeTableMastersTask>> DescribePrizeTableMasters(
            const Request::FDescribePrizeTableMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreatePrizeTableMasterTask>> CreatePrizeTableMaster(
            const Request::FCreatePrizeTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetPrizeTableMasterTask>> GetPrizeTableMaster(
            const Request::FGetPrizeTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdatePrizeTableMasterTask>> UpdatePrizeTableMaster(
            const Request::FUpdatePrizeTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeletePrizeTableMasterTask>> DeletePrizeTableMaster(
            const Request::FDeletePrizeTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeLotteryModelsTask>> DescribeLotteryModels(
            const Request::FDescribeLotteryModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetLotteryModelTask>> GetLotteryModel(
            const Request::FGetLotteryModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribePrizeTablesTask>> DescribePrizeTables(
            const Request::FDescribePrizeTablesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetPrizeTableTask>> GetPrizeTable(
            const Request::FGetPrizeTableRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDrawByUserIdTask>> DrawByUserId(
            const Request::FDrawByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPredictionTask>> Prediction(
            const Request::FPredictionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPredictionByUserIdTask>> PredictionByUserId(
            const Request::FPredictionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDrawWithRandomSeedByUserIdTask>> DrawWithRandomSeedByUserId(
            const Request::FDrawWithRandomSeedByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDrawByStampSheetTask>> DrawByStampSheet(
            const Request::FDrawByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeProbabilitiesTask>> DescribeProbabilities(
            const Request::FDescribeProbabilitiesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeProbabilitiesByUserIdTask>> DescribeProbabilitiesByUserId(
            const Request::FDescribeProbabilitiesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentLotteryMasterTask>> GetCurrentLotteryMaster(
            const Request::FGetCurrentLotteryMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentLotteryMasterTask>> UpdateCurrentLotteryMaster(
            const Request::FUpdateCurrentLotteryMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentLotteryMasterFromGitHubTask>> UpdateCurrentLotteryMasterFromGitHub(
            const Request::FUpdateCurrentLotteryMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribePrizeLimitsTask>> DescribePrizeLimits(
            const Request::FDescribePrizeLimitsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetPrizeLimitTask>> GetPrizeLimit(
            const Request::FGetPrizeLimitRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FResetPrizeLimitTask>> ResetPrizeLimit(
            const Request::FResetPrizeLimitRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeBoxesTask>> DescribeBoxes(
            const Request::FDescribeBoxesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeBoxesByUserIdTask>> DescribeBoxesByUserId(
            const Request::FDescribeBoxesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetBoxTask>> GetBox(
            const Request::FGetBoxRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetBoxByUserIdTask>> GetBoxByUserId(
            const Request::FGetBoxByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FResetBoxTask>> ResetBox(
            const Request::FResetBoxRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FResetBoxByUserIdTask>> ResetBoxByUserId(
            const Request::FResetBoxByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2LotteryRestClient, ESPMode::ThreadSafe> FGs2LotteryRestClientPtr;
}