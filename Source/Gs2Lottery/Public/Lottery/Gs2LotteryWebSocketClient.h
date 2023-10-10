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
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/DumpUserDataByUserIdTask.h"
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckDumpUserDataByUserIdTask.h"
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CleanUserDataByUserIdTask.h"
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckCleanUserDataByUserIdTask.h"
#include "Request/DescribeLotteryModelMastersRequest.h"
#include "Task/WebSocket/DescribeLotteryModelMastersTask.h"
#include "Request/CreateLotteryModelMasterRequest.h"
#include "Task/WebSocket/CreateLotteryModelMasterTask.h"
#include "Request/GetLotteryModelMasterRequest.h"
#include "Task/WebSocket/GetLotteryModelMasterTask.h"
#include "Request/UpdateLotteryModelMasterRequest.h"
#include "Task/WebSocket/UpdateLotteryModelMasterTask.h"
#include "Request/DeleteLotteryModelMasterRequest.h"
#include "Task/WebSocket/DeleteLotteryModelMasterTask.h"
#include "Request/DescribePrizeTableMastersRequest.h"
#include "Task/WebSocket/DescribePrizeTableMastersTask.h"
#include "Request/CreatePrizeTableMasterRequest.h"
#include "Task/WebSocket/CreatePrizeTableMasterTask.h"
#include "Request/GetPrizeTableMasterRequest.h"
#include "Task/WebSocket/GetPrizeTableMasterTask.h"
#include "Request/UpdatePrizeTableMasterRequest.h"
#include "Task/WebSocket/UpdatePrizeTableMasterTask.h"
#include "Request/DeletePrizeTableMasterRequest.h"
#include "Task/WebSocket/DeletePrizeTableMasterTask.h"
#include "Request/DescribeLotteryModelsRequest.h"
#include "Task/WebSocket/DescribeLotteryModelsTask.h"
#include "Request/GetLotteryModelRequest.h"
#include "Task/WebSocket/GetLotteryModelTask.h"
#include "Request/DescribePrizeTablesRequest.h"
#include "Task/WebSocket/DescribePrizeTablesTask.h"
#include "Request/GetPrizeTableRequest.h"
#include "Task/WebSocket/GetPrizeTableTask.h"
#include "Request/DrawByUserIdRequest.h"
#include "Task/WebSocket/DrawByUserIdTask.h"
#include "Request/PredictionRequest.h"
#include "Task/WebSocket/PredictionTask.h"
#include "Request/PredictionByUserIdRequest.h"
#include "Task/WebSocket/PredictionByUserIdTask.h"
#include "Request/DrawWithRandomSeedByUserIdRequest.h"
#include "Task/WebSocket/DrawWithRandomSeedByUserIdTask.h"
#include "Request/DrawByStampSheetRequest.h"
#include "Task/WebSocket/DrawByStampSheetTask.h"
#include "Request/DescribeProbabilitiesRequest.h"
#include "Task/WebSocket/DescribeProbabilitiesTask.h"
#include "Request/DescribeProbabilitiesByUserIdRequest.h"
#include "Task/WebSocket/DescribeProbabilitiesByUserIdTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentLotteryMasterRequest.h"
#include "Task/WebSocket/GetCurrentLotteryMasterTask.h"
#include "Request/UpdateCurrentLotteryMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentLotteryMasterTask.h"
#include "Request/UpdateCurrentLotteryMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentLotteryMasterFromGitHubTask.h"
#include "Request/DescribePrizeLimitsRequest.h"
#include "Task/WebSocket/DescribePrizeLimitsTask.h"
#include "Request/GetPrizeLimitRequest.h"
#include "Task/WebSocket/GetPrizeLimitTask.h"
#include "Request/ResetPrizeLimitRequest.h"
#include "Task/WebSocket/ResetPrizeLimitTask.h"
#include "Request/DescribeBoxesRequest.h"
#include "Task/WebSocket/DescribeBoxesTask.h"
#include "Request/DescribeBoxesByUserIdRequest.h"
#include "Task/WebSocket/DescribeBoxesByUserIdTask.h"
#include "Request/GetBoxRequest.h"
#include "Task/WebSocket/GetBoxTask.h"
#include "Request/GetBoxByUserIdRequest.h"
#include "Task/WebSocket/GetBoxByUserIdTask.h"
#include "Request/ResetBoxRequest.h"
#include "Task/WebSocket/ResetBoxTask.h"
#include "Request/ResetBoxByUserIdRequest.h"
#include "Task/WebSocket/ResetBoxByUserIdTask.h"

namespace Gs2::Lottery
{
    class GS2LOTTERY_API FGs2LotteryWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2LotteryWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeLotteryModelMastersTask>> DescribeLotteryModelMasters(
            const Request::FDescribeLotteryModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateLotteryModelMasterTask>> CreateLotteryModelMaster(
            const Request::FCreateLotteryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetLotteryModelMasterTask>> GetLotteryModelMaster(
            const Request::FGetLotteryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateLotteryModelMasterTask>> UpdateLotteryModelMaster(
            const Request::FUpdateLotteryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteLotteryModelMasterTask>> DeleteLotteryModelMaster(
            const Request::FDeleteLotteryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribePrizeTableMastersTask>> DescribePrizeTableMasters(
            const Request::FDescribePrizeTableMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreatePrizeTableMasterTask>> CreatePrizeTableMaster(
            const Request::FCreatePrizeTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetPrizeTableMasterTask>> GetPrizeTableMaster(
            const Request::FGetPrizeTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdatePrizeTableMasterTask>> UpdatePrizeTableMaster(
            const Request::FUpdatePrizeTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeletePrizeTableMasterTask>> DeletePrizeTableMaster(
            const Request::FDeletePrizeTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeLotteryModelsTask>> DescribeLotteryModels(
            const Request::FDescribeLotteryModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetLotteryModelTask>> GetLotteryModel(
            const Request::FGetLotteryModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribePrizeTablesTask>> DescribePrizeTables(
            const Request::FDescribePrizeTablesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetPrizeTableTask>> GetPrizeTable(
            const Request::FGetPrizeTableRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDrawByUserIdTask>> DrawByUserId(
            const Request::FDrawByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPredictionTask>> Prediction(
            const Request::FPredictionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPredictionByUserIdTask>> PredictionByUserId(
            const Request::FPredictionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDrawWithRandomSeedByUserIdTask>> DrawWithRandomSeedByUserId(
            const Request::FDrawWithRandomSeedByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDrawByStampSheetTask>> DrawByStampSheet(
            const Request::FDrawByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeProbabilitiesTask>> DescribeProbabilities(
            const Request::FDescribeProbabilitiesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeProbabilitiesByUserIdTask>> DescribeProbabilitiesByUserId(
            const Request::FDescribeProbabilitiesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentLotteryMasterTask>> GetCurrentLotteryMaster(
            const Request::FGetCurrentLotteryMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentLotteryMasterTask>> UpdateCurrentLotteryMaster(
            const Request::FUpdateCurrentLotteryMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentLotteryMasterFromGitHubTask>> UpdateCurrentLotteryMasterFromGitHub(
            const Request::FUpdateCurrentLotteryMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribePrizeLimitsTask>> DescribePrizeLimits(
            const Request::FDescribePrizeLimitsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetPrizeLimitTask>> GetPrizeLimit(
            const Request::FGetPrizeLimitRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FResetPrizeLimitTask>> ResetPrizeLimit(
            const Request::FResetPrizeLimitRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBoxesTask>> DescribeBoxes(
            const Request::FDescribeBoxesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBoxesByUserIdTask>> DescribeBoxesByUserId(
            const Request::FDescribeBoxesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBoxTask>> GetBox(
            const Request::FGetBoxRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBoxByUserIdTask>> GetBoxByUserId(
            const Request::FGetBoxByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FResetBoxTask>> ResetBox(
            const Request::FResetBoxRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FResetBoxByUserIdTask>> ResetBoxByUserId(
            const Request::FResetBoxByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2LotteryWebSocketClient, ESPMode::ThreadSafe> FGs2LotteryWebSocketClientPtr;
}