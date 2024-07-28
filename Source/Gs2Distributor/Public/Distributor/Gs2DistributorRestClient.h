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
#include "Request/DescribeDistributorModelMastersRequest.h"
#include "Task/Rest/DescribeDistributorModelMastersTask.h"
#include "Request/CreateDistributorModelMasterRequest.h"
#include "Task/Rest/CreateDistributorModelMasterTask.h"
#include "Request/GetDistributorModelMasterRequest.h"
#include "Task/Rest/GetDistributorModelMasterTask.h"
#include "Request/UpdateDistributorModelMasterRequest.h"
#include "Task/Rest/UpdateDistributorModelMasterTask.h"
#include "Request/DeleteDistributorModelMasterRequest.h"
#include "Task/Rest/DeleteDistributorModelMasterTask.h"
#include "Request/DescribeDistributorModelsRequest.h"
#include "Task/Rest/DescribeDistributorModelsTask.h"
#include "Request/GetDistributorModelRequest.h"
#include "Task/Rest/GetDistributorModelTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentDistributorMasterRequest.h"
#include "Task/Rest/GetCurrentDistributorMasterTask.h"
#include "Request/UpdateCurrentDistributorMasterRequest.h"
#include "Task/Rest/UpdateCurrentDistributorMasterTask.h"
#include "Request/UpdateCurrentDistributorMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentDistributorMasterFromGitHubTask.h"
#include "Request/DistributeRequest.h"
#include "Task/Rest/DistributeTask.h"
#include "Request/DistributeWithoutOverflowProcessRequest.h"
#include "Task/Rest/DistributeWithoutOverflowProcessTask.h"
#include "Request/RunVerifyTaskRequest.h"
#include "Task/Rest/RunVerifyTaskTask.h"
#include "Request/RunStampTaskRequest.h"
#include "Task/Rest/RunStampTaskTask.h"
#include "Request/RunStampSheetRequest.h"
#include "Task/Rest/RunStampSheetTask.h"
#include "Request/RunStampSheetExpressRequest.h"
#include "Task/Rest/RunStampSheetExpressTask.h"
#include "Request/RunVerifyTaskWithoutNamespaceRequest.h"
#include "Task/Rest/RunVerifyTaskWithoutNamespaceTask.h"
#include "Request/RunStampTaskWithoutNamespaceRequest.h"
#include "Task/Rest/RunStampTaskWithoutNamespaceTask.h"
#include "Request/RunStampSheetWithoutNamespaceRequest.h"
#include "Task/Rest/RunStampSheetWithoutNamespaceTask.h"
#include "Request/RunStampSheetExpressWithoutNamespaceRequest.h"
#include "Task/Rest/RunStampSheetExpressWithoutNamespaceTask.h"
#include "Request/SetTransactionDefaultConfigRequest.h"
#include "Task/Rest/SetTransactionDefaultConfigTask.h"
#include "Request/SetTransactionDefaultConfigByUserIdRequest.h"
#include "Task/Rest/SetTransactionDefaultConfigByUserIdTask.h"
#include "Request/IfExpressionByUserIdRequest.h"
#include "Task/Rest/IfExpressionByUserIdTask.h"
#include "Request/AndExpressionByUserIdRequest.h"
#include "Task/Rest/AndExpressionByUserIdTask.h"
#include "Request/OrExpressionByUserIdRequest.h"
#include "Task/Rest/OrExpressionByUserIdTask.h"
#include "Request/IfExpressionByUserByStampTaskRequest.h"
#include "Task/Rest/IfExpressionByUserByStampTaskTask.h"
#include "Request/AndExpressionByUserByStampTaskRequest.h"
#include "Task/Rest/AndExpressionByUserByStampTaskTask.h"
#include "Request/OrExpressionByUserByStampTaskRequest.h"
#include "Task/Rest/OrExpressionByUserByStampTaskTask.h"
#include "Request/GetStampSheetResultRequest.h"
#include "Task/Rest/GetStampSheetResultTask.h"
#include "Request/GetStampSheetResultByUserIdRequest.h"
#include "Task/Rest/GetStampSheetResultByUserIdTask.h"

namespace Gs2::Distributor
{
    class GS2DISTRIBUTOR_API FGs2DistributorRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2DistributorRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeDistributorModelMastersTask>> DescribeDistributorModelMasters(
            const Request::FDescribeDistributorModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateDistributorModelMasterTask>> CreateDistributorModelMaster(
            const Request::FCreateDistributorModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetDistributorModelMasterTask>> GetDistributorModelMaster(
            const Request::FGetDistributorModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateDistributorModelMasterTask>> UpdateDistributorModelMaster(
            const Request::FUpdateDistributorModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteDistributorModelMasterTask>> DeleteDistributorModelMaster(
            const Request::FDeleteDistributorModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeDistributorModelsTask>> DescribeDistributorModels(
            const Request::FDescribeDistributorModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetDistributorModelTask>> GetDistributorModel(
            const Request::FGetDistributorModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentDistributorMasterTask>> GetCurrentDistributorMaster(
            const Request::FGetCurrentDistributorMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentDistributorMasterTask>> UpdateCurrentDistributorMaster(
            const Request::FUpdateCurrentDistributorMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentDistributorMasterFromGitHubTask>> UpdateCurrentDistributorMasterFromGitHub(
            const Request::FUpdateCurrentDistributorMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDistributeTask>> Distribute(
            const Request::FDistributeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDistributeWithoutOverflowProcessTask>> DistributeWithoutOverflowProcess(
            const Request::FDistributeWithoutOverflowProcessRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRunVerifyTaskTask>> RunVerifyTask(
            const Request::FRunVerifyTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRunStampTaskTask>> RunStampTask(
            const Request::FRunStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRunStampSheetTask>> RunStampSheet(
            const Request::FRunStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRunStampSheetExpressTask>> RunStampSheetExpress(
            const Request::FRunStampSheetExpressRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRunVerifyTaskWithoutNamespaceTask>> RunVerifyTaskWithoutNamespace(
            const Request::FRunVerifyTaskWithoutNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRunStampTaskWithoutNamespaceTask>> RunStampTaskWithoutNamespace(
            const Request::FRunStampTaskWithoutNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRunStampSheetWithoutNamespaceTask>> RunStampSheetWithoutNamespace(
            const Request::FRunStampSheetWithoutNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRunStampSheetExpressWithoutNamespaceTask>> RunStampSheetExpressWithoutNamespace(
            const Request::FRunStampSheetExpressWithoutNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetTransactionDefaultConfigTask>> SetTransactionDefaultConfig(
            const Request::FSetTransactionDefaultConfigRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetTransactionDefaultConfigByUserIdTask>> SetTransactionDefaultConfigByUserId(
            const Request::FSetTransactionDefaultConfigByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FIfExpressionByUserIdTask>> IfExpressionByUserId(
            const Request::FIfExpressionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAndExpressionByUserIdTask>> AndExpressionByUserId(
            const Request::FAndExpressionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FOrExpressionByUserIdTask>> OrExpressionByUserId(
            const Request::FOrExpressionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FIfExpressionByUserByStampTaskTask>> IfExpressionByUserByStampTask(
            const Request::FIfExpressionByUserByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAndExpressionByUserByStampTaskTask>> AndExpressionByUserByStampTask(
            const Request::FAndExpressionByUserByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FOrExpressionByUserByStampTaskTask>> OrExpressionByUserByStampTask(
            const Request::FOrExpressionByUserByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStampSheetResultTask>> GetStampSheetResult(
            const Request::FGetStampSheetResultRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStampSheetResultByUserIdTask>> GetStampSheetResultByUserId(
            const Request::FGetStampSheetResultByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2DistributorRestClient, ESPMode::ThreadSafe> FGs2DistributorRestClientPtr;
}