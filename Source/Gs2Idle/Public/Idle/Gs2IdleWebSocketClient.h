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
#include "Request/DescribeCategoryModelMastersRequest.h"
#include "Task/WebSocket/DescribeCategoryModelMastersTask.h"
#include "Request/CreateCategoryModelMasterRequest.h"
#include "Task/WebSocket/CreateCategoryModelMasterTask.h"
#include "Request/GetCategoryModelMasterRequest.h"
#include "Task/WebSocket/GetCategoryModelMasterTask.h"
#include "Request/UpdateCategoryModelMasterRequest.h"
#include "Task/WebSocket/UpdateCategoryModelMasterTask.h"
#include "Request/DeleteCategoryModelMasterRequest.h"
#include "Task/WebSocket/DeleteCategoryModelMasterTask.h"
#include "Request/DescribeCategoryModelsRequest.h"
#include "Task/WebSocket/DescribeCategoryModelsTask.h"
#include "Request/GetCategoryModelRequest.h"
#include "Task/WebSocket/GetCategoryModelTask.h"
#include "Request/DescribeStatusesRequest.h"
#include "Task/WebSocket/DescribeStatusesTask.h"
#include "Request/DescribeStatusesByUserIdRequest.h"
#include "Task/WebSocket/DescribeStatusesByUserIdTask.h"
#include "Request/GetStatusRequest.h"
#include "Task/WebSocket/GetStatusTask.h"
#include "Request/GetStatusByUserIdRequest.h"
#include "Task/WebSocket/GetStatusByUserIdTask.h"
#include "Request/PredictionRequest.h"
#include "Task/WebSocket/PredictionTask.h"
#include "Request/PredictionByUserIdRequest.h"
#include "Task/WebSocket/PredictionByUserIdTask.h"
#include "Request/ReceiveRequest.h"
#include "Task/WebSocket/ReceiveTask.h"
#include "Request/ReceiveByUserIdRequest.h"
#include "Task/WebSocket/ReceiveByUserIdTask.h"
#include "Request/IncreaseMaximumIdleMinutesByUserIdRequest.h"
#include "Task/WebSocket/IncreaseMaximumIdleMinutesByUserIdTask.h"
#include "Request/IncreaseMaximumIdleMinutesByStampSheetRequest.h"
#include "Task/WebSocket/IncreaseMaximumIdleMinutesByStampSheetTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentIdleMasterRequest.h"
#include "Task/WebSocket/GetCurrentIdleMasterTask.h"
#include "Request/UpdateCurrentIdleMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentIdleMasterTask.h"
#include "Request/UpdateCurrentIdleMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentIdleMasterFromGitHubTask.h"

namespace Gs2::Idle
{
    class GS2IDLE_API FGs2IdleWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2IdleWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCategoryModelMastersTask>> DescribeCategoryModelMasters(
            const Request::FDescribeCategoryModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateCategoryModelMasterTask>> CreateCategoryModelMaster(
            const Request::FCreateCategoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCategoryModelMasterTask>> GetCategoryModelMaster(
            const Request::FGetCategoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCategoryModelMasterTask>> UpdateCategoryModelMaster(
            const Request::FUpdateCategoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteCategoryModelMasterTask>> DeleteCategoryModelMaster(
            const Request::FDeleteCategoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCategoryModelsTask>> DescribeCategoryModels(
            const Request::FDescribeCategoryModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCategoryModelTask>> GetCategoryModel(
            const Request::FGetCategoryModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStatusesTask>> DescribeStatuses(
            const Request::FDescribeStatusesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStatusesByUserIdTask>> DescribeStatusesByUserId(
            const Request::FDescribeStatusesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStatusTask>> GetStatus(
            const Request::FGetStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStatusByUserIdTask>> GetStatusByUserId(
            const Request::FGetStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPredictionTask>> Prediction(
            const Request::FPredictionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPredictionByUserIdTask>> PredictionByUserId(
            const Request::FPredictionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveTask>> Receive(
            const Request::FReceiveRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveByUserIdTask>> ReceiveByUserId(
            const Request::FReceiveByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FIncreaseMaximumIdleMinutesByUserIdTask>> IncreaseMaximumIdleMinutesByUserId(
            const Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FIncreaseMaximumIdleMinutesByStampSheetTask>> IncreaseMaximumIdleMinutesByStampSheet(
            const Request::FIncreaseMaximumIdleMinutesByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentIdleMasterTask>> GetCurrentIdleMaster(
            const Request::FGetCurrentIdleMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentIdleMasterTask>> UpdateCurrentIdleMaster(
            const Request::FUpdateCurrentIdleMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentIdleMasterFromGitHubTask>> UpdateCurrentIdleMasterFromGitHub(
            const Request::FUpdateCurrentIdleMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2IdleWebSocketClient, ESPMode::ThreadSafe> FGs2IdleWebSocketClientPtr;
}