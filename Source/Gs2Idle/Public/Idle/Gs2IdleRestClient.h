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
#include "Request/DescribeCategoryModelsRequest.h"
#include "Task/Rest/DescribeCategoryModelsTask.h"
#include "Request/GetCategoryModelRequest.h"
#include "Task/Rest/GetCategoryModelTask.h"
#include "Request/DescribeStatusesRequest.h"
#include "Task/Rest/DescribeStatusesTask.h"
#include "Request/DescribeStatusesByUserIdRequest.h"
#include "Task/Rest/DescribeStatusesByUserIdTask.h"
#include "Request/GetStatusRequest.h"
#include "Task/Rest/GetStatusTask.h"
#include "Request/GetStatusByUserIdRequest.h"
#include "Task/Rest/GetStatusByUserIdTask.h"
#include "Request/PredictionRequest.h"
#include "Task/Rest/PredictionTask.h"
#include "Request/PredictionByUserIdRequest.h"
#include "Task/Rest/PredictionByUserIdTask.h"
#include "Request/ReceiveRequest.h"
#include "Task/Rest/ReceiveTask.h"
#include "Request/ReceiveByUserIdRequest.h"
#include "Task/Rest/ReceiveByUserIdTask.h"
#include "Request/IncreaseMaximumIdleMinutesByUserIdRequest.h"
#include "Task/Rest/IncreaseMaximumIdleMinutesByUserIdTask.h"
#include "Request/DecreaseMaximumIdleMinutesRequest.h"
#include "Task/Rest/DecreaseMaximumIdleMinutesTask.h"
#include "Request/DecreaseMaximumIdleMinutesByUserIdRequest.h"
#include "Task/Rest/DecreaseMaximumIdleMinutesByUserIdTask.h"
#include "Request/SetMaximumIdleMinutesByUserIdRequest.h"
#include "Task/Rest/SetMaximumIdleMinutesByUserIdTask.h"
#include "Request/IncreaseMaximumIdleMinutesByStampSheetRequest.h"
#include "Task/Rest/IncreaseMaximumIdleMinutesByStampSheetTask.h"
#include "Request/DecreaseMaximumIdleMinutesByStampTaskRequest.h"
#include "Task/Rest/DecreaseMaximumIdleMinutesByStampTaskTask.h"
#include "Request/SetMaximumIdleMinutesByStampSheetRequest.h"
#include "Task/Rest/SetMaximumIdleMinutesByStampSheetTask.h"
#include "Request/ReceiveByStampSheetRequest.h"
#include "Task/Rest/ReceiveByStampSheetTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentCategoryMasterRequest.h"
#include "Task/Rest/GetCurrentCategoryMasterTask.h"
#include "Request/PreUpdateCurrentCategoryMasterRequest.h"
#include "Task/Rest/PreUpdateCurrentCategoryMasterTask.h"
#include "Request/UpdateCurrentCategoryMasterRequest.h"
#include "Task/Rest/UpdateCurrentCategoryMasterTask.h"
#include "Request/UpdateCurrentCategoryMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentCategoryMasterFromGitHubTask.h"

namespace Gs2::Idle
{
    class GS2IDLE_API FGs2IdleRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2IdleRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCategoryModelsTask>> DescribeCategoryModels(
            const Request::FDescribeCategoryModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCategoryModelTask>> GetCategoryModel(
            const Request::FGetCategoryModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeStatusesTask>> DescribeStatuses(
            const Request::FDescribeStatusesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeStatusesByUserIdTask>> DescribeStatusesByUserId(
            const Request::FDescribeStatusesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStatusTask>> GetStatus(
            const Request::FGetStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStatusByUserIdTask>> GetStatusByUserId(
            const Request::FGetStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPredictionTask>> Prediction(
            const Request::FPredictionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPredictionByUserIdTask>> PredictionByUserId(
            const Request::FPredictionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReceiveTask>> Receive(
            const Request::FReceiveRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReceiveByUserIdTask>> ReceiveByUserId(
            const Request::FReceiveByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FIncreaseMaximumIdleMinutesByUserIdTask>> IncreaseMaximumIdleMinutesByUserId(
            const Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDecreaseMaximumIdleMinutesTask>> DecreaseMaximumIdleMinutes(
            const Request::FDecreaseMaximumIdleMinutesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDecreaseMaximumIdleMinutesByUserIdTask>> DecreaseMaximumIdleMinutesByUserId(
            const Request::FDecreaseMaximumIdleMinutesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetMaximumIdleMinutesByUserIdTask>> SetMaximumIdleMinutesByUserId(
            const Request::FSetMaximumIdleMinutesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FIncreaseMaximumIdleMinutesByStampSheetTask>> IncreaseMaximumIdleMinutesByStampSheet(
            const Request::FIncreaseMaximumIdleMinutesByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDecreaseMaximumIdleMinutesByStampTaskTask>> DecreaseMaximumIdleMinutesByStampTask(
            const Request::FDecreaseMaximumIdleMinutesByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetMaximumIdleMinutesByStampSheetTask>> SetMaximumIdleMinutesByStampSheet(
            const Request::FSetMaximumIdleMinutesByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReceiveByStampSheetTask>> ReceiveByStampSheet(
            const Request::FReceiveByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentCategoryMasterTask>> GetCurrentCategoryMaster(
            const Request::FGetCurrentCategoryMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPreUpdateCurrentCategoryMasterTask>> PreUpdateCurrentCategoryMaster(
            const Request::FPreUpdateCurrentCategoryMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentCategoryMasterTask>> UpdateCurrentCategoryMaster(
            const Request::FUpdateCurrentCategoryMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentCategoryMasterFromGitHubTask>> UpdateCurrentCategoryMasterFromGitHub(
            const Request::FUpdateCurrentCategoryMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2IdleRestClient, ESPMode::ThreadSafe> FGs2IdleRestClientPtr;
}