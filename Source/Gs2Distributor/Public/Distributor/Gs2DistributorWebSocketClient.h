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
#include "Request/DescribeDistributorModelMastersRequest.h"
#include "Task/WebSocket/DescribeDistributorModelMastersTask.h"
#include "Request/CreateDistributorModelMasterRequest.h"
#include "Task/WebSocket/CreateDistributorModelMasterTask.h"
#include "Request/GetDistributorModelMasterRequest.h"
#include "Task/WebSocket/GetDistributorModelMasterTask.h"
#include "Request/UpdateDistributorModelMasterRequest.h"
#include "Task/WebSocket/UpdateDistributorModelMasterTask.h"
#include "Request/DeleteDistributorModelMasterRequest.h"
#include "Task/WebSocket/DeleteDistributorModelMasterTask.h"
#include "Request/DescribeDistributorModelsRequest.h"
#include "Task/WebSocket/DescribeDistributorModelsTask.h"
#include "Request/GetDistributorModelRequest.h"
#include "Task/WebSocket/GetDistributorModelTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentDistributorMasterRequest.h"
#include "Task/WebSocket/GetCurrentDistributorMasterTask.h"
#include "Request/UpdateCurrentDistributorMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentDistributorMasterTask.h"
#include "Request/UpdateCurrentDistributorMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentDistributorMasterFromGitHubTask.h"
#include "Request/DistributeRequest.h"
#include "Task/WebSocket/DistributeTask.h"
#include "Request/DistributeWithoutOverflowProcessRequest.h"
#include "Task/WebSocket/DistributeWithoutOverflowProcessTask.h"
#include "Request/RunVerifyTaskRequest.h"
#include "Task/WebSocket/RunVerifyTaskTask.h"
#include "Request/RunStampTaskRequest.h"
#include "Task/WebSocket/RunStampTaskTask.h"
#include "Request/RunStampSheetRequest.h"
#include "Task/WebSocket/RunStampSheetTask.h"
#include "Request/RunStampSheetExpressRequest.h"
#include "Task/WebSocket/RunStampSheetExpressTask.h"
#include "Request/RunVerifyTaskWithoutNamespaceRequest.h"
#include "Task/WebSocket/RunVerifyTaskWithoutNamespaceTask.h"
#include "Request/RunStampTaskWithoutNamespaceRequest.h"
#include "Task/WebSocket/RunStampTaskWithoutNamespaceTask.h"
#include "Request/RunStampSheetWithoutNamespaceRequest.h"
#include "Task/WebSocket/RunStampSheetWithoutNamespaceTask.h"
#include "Request/RunStampSheetExpressWithoutNamespaceRequest.h"
#include "Task/WebSocket/RunStampSheetExpressWithoutNamespaceTask.h"
#include "Request/SetTransactionDefaultConfigRequest.h"
#include "Task/WebSocket/SetTransactionDefaultConfigTask.h"
#include "Request/SetTransactionDefaultConfigByUserIdRequest.h"
#include "Task/WebSocket/SetTransactionDefaultConfigByUserIdTask.h"
#include "Request/IfExpressionByUserIdRequest.h"
#include "Task/WebSocket/IfExpressionByUserIdTask.h"
#include "Request/AndExpressionByUserIdRequest.h"
#include "Task/WebSocket/AndExpressionByUserIdTask.h"
#include "Request/OrExpressionByUserIdRequest.h"
#include "Task/WebSocket/OrExpressionByUserIdTask.h"
#include "Request/IfExpressionByUserByStampTaskRequest.h"
#include "Task/WebSocket/IfExpressionByUserByStampTaskTask.h"
#include "Request/AndExpressionByUserByStampTaskRequest.h"
#include "Task/WebSocket/AndExpressionByUserByStampTaskTask.h"
#include "Request/OrExpressionByUserByStampTaskRequest.h"
#include "Task/WebSocket/OrExpressionByUserByStampTaskTask.h"
#include "Request/GetStampSheetResultRequest.h"
#include "Task/WebSocket/GetStampSheetResultTask.h"
#include "Request/GetStampSheetResultByUserIdRequest.h"
#include "Task/WebSocket/GetStampSheetResultByUserIdTask.h"

namespace Gs2::Distributor
{
    class GS2DISTRIBUTOR_API FGs2DistributorWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2DistributorWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeDistributorModelMastersTask>> DescribeDistributorModelMasters(
            const Request::FDescribeDistributorModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateDistributorModelMasterTask>> CreateDistributorModelMaster(
            const Request::FCreateDistributorModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetDistributorModelMasterTask>> GetDistributorModelMaster(
            const Request::FGetDistributorModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateDistributorModelMasterTask>> UpdateDistributorModelMaster(
            const Request::FUpdateDistributorModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteDistributorModelMasterTask>> DeleteDistributorModelMaster(
            const Request::FDeleteDistributorModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeDistributorModelsTask>> DescribeDistributorModels(
            const Request::FDescribeDistributorModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetDistributorModelTask>> GetDistributorModel(
            const Request::FGetDistributorModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentDistributorMasterTask>> GetCurrentDistributorMaster(
            const Request::FGetCurrentDistributorMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentDistributorMasterTask>> UpdateCurrentDistributorMaster(
            const Request::FUpdateCurrentDistributorMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentDistributorMasterFromGitHubTask>> UpdateCurrentDistributorMasterFromGitHub(
            const Request::FUpdateCurrentDistributorMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDistributeTask>> Distribute(
            const Request::FDistributeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDistributeWithoutOverflowProcessTask>> DistributeWithoutOverflowProcess(
            const Request::FDistributeWithoutOverflowProcessRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRunVerifyTaskTask>> RunVerifyTask(
            const Request::FRunVerifyTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRunStampTaskTask>> RunStampTask(
            const Request::FRunStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRunStampSheetTask>> RunStampSheet(
            const Request::FRunStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRunStampSheetExpressTask>> RunStampSheetExpress(
            const Request::FRunStampSheetExpressRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRunVerifyTaskWithoutNamespaceTask>> RunVerifyTaskWithoutNamespace(
            const Request::FRunVerifyTaskWithoutNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRunStampTaskWithoutNamespaceTask>> RunStampTaskWithoutNamespace(
            const Request::FRunStampTaskWithoutNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRunStampSheetWithoutNamespaceTask>> RunStampSheetWithoutNamespace(
            const Request::FRunStampSheetWithoutNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRunStampSheetExpressWithoutNamespaceTask>> RunStampSheetExpressWithoutNamespace(
            const Request::FRunStampSheetExpressWithoutNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetTransactionDefaultConfigTask>> SetTransactionDefaultConfig(
            const Request::FSetTransactionDefaultConfigRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetTransactionDefaultConfigByUserIdTask>> SetTransactionDefaultConfigByUserId(
            const Request::FSetTransactionDefaultConfigByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FIfExpressionByUserIdTask>> IfExpressionByUserId(
            const Request::FIfExpressionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAndExpressionByUserIdTask>> AndExpressionByUserId(
            const Request::FAndExpressionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FOrExpressionByUserIdTask>> OrExpressionByUserId(
            const Request::FOrExpressionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FIfExpressionByUserByStampTaskTask>> IfExpressionByUserByStampTask(
            const Request::FIfExpressionByUserByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAndExpressionByUserByStampTaskTask>> AndExpressionByUserByStampTask(
            const Request::FAndExpressionByUserByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FOrExpressionByUserByStampTaskTask>> OrExpressionByUserByStampTask(
            const Request::FOrExpressionByUserByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStampSheetResultTask>> GetStampSheetResult(
            const Request::FGetStampSheetResultRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStampSheetResultByUserIdTask>> GetStampSheetResultByUserId(
            const Request::FGetStampSheetResultByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2DistributorWebSocketClient, ESPMode::ThreadSafe> FGs2DistributorWebSocketClientPtr;
}