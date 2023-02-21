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
#include "Request/DescribeRateModelsRequest.h"
#include "Task/Rest/DescribeRateModelsTask.h"
#include "Request/GetRateModelRequest.h"
#include "Task/Rest/GetRateModelTask.h"
#include "Request/DescribeRateModelMastersRequest.h"
#include "Task/Rest/DescribeRateModelMastersTask.h"
#include "Request/CreateRateModelMasterRequest.h"
#include "Task/Rest/CreateRateModelMasterTask.h"
#include "Request/GetRateModelMasterRequest.h"
#include "Task/Rest/GetRateModelMasterTask.h"
#include "Request/UpdateRateModelMasterRequest.h"
#include "Task/Rest/UpdateRateModelMasterTask.h"
#include "Request/DeleteRateModelMasterRequest.h"
#include "Task/Rest/DeleteRateModelMasterTask.h"
#include "Request/DirectEnhanceRequest.h"
#include "Task/Rest/DirectEnhanceTask.h"
#include "Request/DirectEnhanceByUserIdRequest.h"
#include "Task/Rest/DirectEnhanceByUserIdTask.h"
#include "Request/DirectEnhanceByStampSheetRequest.h"
#include "Task/Rest/DirectEnhanceByStampSheetTask.h"
#include "Request/CreateProgressByUserIdRequest.h"
#include "Task/Rest/CreateProgressByUserIdTask.h"
#include "Request/GetProgressRequest.h"
#include "Task/Rest/GetProgressTask.h"
#include "Request/GetProgressByUserIdRequest.h"
#include "Task/Rest/GetProgressByUserIdTask.h"
#include "Request/StartRequest.h"
#include "Task/Rest/StartTask.h"
#include "Request/StartByUserIdRequest.h"
#include "Task/Rest/StartByUserIdTask.h"
#include "Request/EndRequest.h"
#include "Task/Rest/EndTask.h"
#include "Request/EndByUserIdRequest.h"
#include "Task/Rest/EndByUserIdTask.h"
#include "Request/DeleteProgressRequest.h"
#include "Task/Rest/DeleteProgressTask.h"
#include "Request/DeleteProgressByUserIdRequest.h"
#include "Task/Rest/DeleteProgressByUserIdTask.h"
#include "Request/CreateProgressByStampSheetRequest.h"
#include "Task/Rest/CreateProgressByStampSheetTask.h"
#include "Request/DeleteProgressByStampTaskRequest.h"
#include "Task/Rest/DeleteProgressByStampTaskTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentRateMasterRequest.h"
#include "Task/Rest/GetCurrentRateMasterTask.h"
#include "Request/UpdateCurrentRateMasterRequest.h"
#include "Task/Rest/UpdateCurrentRateMasterTask.h"
#include "Request/UpdateCurrentRateMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentRateMasterFromGitHubTask.h"

namespace Gs2::Enhance
{
    class GS2ENHANCE_API FGs2EnhanceRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2EnhanceRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRateModelsTask>> DescribeRateModels(
            const Request::FDescribeRateModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRateModelTask>> GetRateModel(
            const Request::FGetRateModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRateModelMastersTask>> DescribeRateModelMasters(
            const Request::FDescribeRateModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateRateModelMasterTask>> CreateRateModelMaster(
            const Request::FCreateRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRateModelMasterTask>> GetRateModelMaster(
            const Request::FGetRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateRateModelMasterTask>> UpdateRateModelMaster(
            const Request::FUpdateRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteRateModelMasterTask>> DeleteRateModelMaster(
            const Request::FDeleteRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDirectEnhanceTask>> DirectEnhance(
            const Request::FDirectEnhanceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDirectEnhanceByUserIdTask>> DirectEnhanceByUserId(
            const Request::FDirectEnhanceByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDirectEnhanceByStampSheetTask>> DirectEnhanceByStampSheet(
            const Request::FDirectEnhanceByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateProgressByUserIdTask>> CreateProgressByUserId(
            const Request::FCreateProgressByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetProgressTask>> GetProgress(
            const Request::FGetProgressRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetProgressByUserIdTask>> GetProgressByUserId(
            const Request::FGetProgressByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FStartTask>> Start(
            const Request::FStartRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FStartByUserIdTask>> StartByUserId(
            const Request::FStartByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FEndTask>> End(
            const Request::FEndRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FEndByUserIdTask>> EndByUserId(
            const Request::FEndByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteProgressTask>> DeleteProgress(
            const Request::FDeleteProgressRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteProgressByUserIdTask>> DeleteProgressByUserId(
            const Request::FDeleteProgressByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateProgressByStampSheetTask>> CreateProgressByStampSheet(
            const Request::FCreateProgressByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteProgressByStampTaskTask>> DeleteProgressByStampTask(
            const Request::FDeleteProgressByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentRateMasterTask>> GetCurrentRateMaster(
            const Request::FGetCurrentRateMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentRateMasterTask>> UpdateCurrentRateMaster(
            const Request::FUpdateCurrentRateMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentRateMasterFromGitHubTask>> UpdateCurrentRateMasterFromGitHub(
            const Request::FUpdateCurrentRateMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2EnhanceRestClient, ESPMode::ThreadSafe> FGs2EnhanceRestClientPtr;
}