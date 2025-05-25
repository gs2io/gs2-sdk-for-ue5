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
#include "Request/GetServiceVersionRequest.h"
#include "Task/Rest/GetServiceVersionTask.h"
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
#include "Request/DescribeCountersRequest.h"
#include "Task/Rest/DescribeCountersTask.h"
#include "Request/DescribeCountersByUserIdRequest.h"
#include "Task/Rest/DescribeCountersByUserIdTask.h"
#include "Request/GetCounterRequest.h"
#include "Task/Rest/GetCounterTask.h"
#include "Request/GetCounterByUserIdRequest.h"
#include "Task/Rest/GetCounterByUserIdTask.h"
#include "Request/CountUpRequest.h"
#include "Task/Rest/CountUpTask.h"
#include "Request/CountUpByUserIdRequest.h"
#include "Task/Rest/CountUpByUserIdTask.h"
#include "Request/CountDownByUserIdRequest.h"
#include "Task/Rest/CountDownByUserIdTask.h"
#include "Request/DeleteCounterByUserIdRequest.h"
#include "Task/Rest/DeleteCounterByUserIdTask.h"
#include "Request/VerifyCounterRequest.h"
#include "Task/Rest/VerifyCounterTask.h"
#include "Request/VerifyCounterByUserIdRequest.h"
#include "Task/Rest/VerifyCounterByUserIdTask.h"
#include "Request/CountUpByStampTaskRequest.h"
#include "Task/Rest/CountUpByStampTaskTask.h"
#include "Request/CountDownByStampSheetRequest.h"
#include "Task/Rest/CountDownByStampSheetTask.h"
#include "Request/DeleteByStampSheetRequest.h"
#include "Task/Rest/DeleteByStampSheetTask.h"
#include "Request/VerifyCounterByStampTaskRequest.h"
#include "Task/Rest/VerifyCounterByStampTaskTask.h"
#include "Request/DescribeLimitModelMastersRequest.h"
#include "Task/Rest/DescribeLimitModelMastersTask.h"
#include "Request/CreateLimitModelMasterRequest.h"
#include "Task/Rest/CreateLimitModelMasterTask.h"
#include "Request/GetLimitModelMasterRequest.h"
#include "Task/Rest/GetLimitModelMasterTask.h"
#include "Request/UpdateLimitModelMasterRequest.h"
#include "Task/Rest/UpdateLimitModelMasterTask.h"
#include "Request/DeleteLimitModelMasterRequest.h"
#include "Task/Rest/DeleteLimitModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentLimitMasterRequest.h"
#include "Task/Rest/GetCurrentLimitMasterTask.h"
#include "Request/PreUpdateCurrentLimitMasterRequest.h"
#include "Task/Rest/PreUpdateCurrentLimitMasterTask.h"
#include "Request/UpdateCurrentLimitMasterRequest.h"
#include "Task/Rest/UpdateCurrentLimitMasterTask.h"
#include "Request/UpdateCurrentLimitMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentLimitMasterFromGitHubTask.h"
#include "Request/DescribeLimitModelsRequest.h"
#include "Task/Rest/DescribeLimitModelsTask.h"
#include "Request/GetLimitModelRequest.h"
#include "Task/Rest/GetLimitModelTask.h"

namespace Gs2::Limit
{
    class GS2LIMIT_API FGs2LimitRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2LimitRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FGetServiceVersionTask>> GetServiceVersion(
            const Request::FGetServiceVersionRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCountersTask>> DescribeCounters(
            const Request::FDescribeCountersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCountersByUserIdTask>> DescribeCountersByUserId(
            const Request::FDescribeCountersByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCounterTask>> GetCounter(
            const Request::FGetCounterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCounterByUserIdTask>> GetCounterByUserId(
            const Request::FGetCounterByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCountUpTask>> CountUp(
            const Request::FCountUpRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCountUpByUserIdTask>> CountUpByUserId(
            const Request::FCountUpByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCountDownByUserIdTask>> CountDownByUserId(
            const Request::FCountDownByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteCounterByUserIdTask>> DeleteCounterByUserId(
            const Request::FDeleteCounterByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyCounterTask>> VerifyCounter(
            const Request::FVerifyCounterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyCounterByUserIdTask>> VerifyCounterByUserId(
            const Request::FVerifyCounterByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCountUpByStampTaskTask>> CountUpByStampTask(
            const Request::FCountUpByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCountDownByStampSheetTask>> CountDownByStampSheet(
            const Request::FCountDownByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteByStampSheetTask>> DeleteByStampSheet(
            const Request::FDeleteByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyCounterByStampTaskTask>> VerifyCounterByStampTask(
            const Request::FVerifyCounterByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeLimitModelMastersTask>> DescribeLimitModelMasters(
            const Request::FDescribeLimitModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateLimitModelMasterTask>> CreateLimitModelMaster(
            const Request::FCreateLimitModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetLimitModelMasterTask>> GetLimitModelMaster(
            const Request::FGetLimitModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateLimitModelMasterTask>> UpdateLimitModelMaster(
            const Request::FUpdateLimitModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteLimitModelMasterTask>> DeleteLimitModelMaster(
            const Request::FDeleteLimitModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentLimitMasterTask>> GetCurrentLimitMaster(
            const Request::FGetCurrentLimitMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPreUpdateCurrentLimitMasterTask>> PreUpdateCurrentLimitMaster(
            const Request::FPreUpdateCurrentLimitMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentLimitMasterTask>> UpdateCurrentLimitMaster(
            const Request::FUpdateCurrentLimitMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentLimitMasterFromGitHubTask>> UpdateCurrentLimitMasterFromGitHub(
            const Request::FUpdateCurrentLimitMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeLimitModelsTask>> DescribeLimitModels(
            const Request::FDescribeLimitModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetLimitModelTask>> GetLimitModel(
            const Request::FGetLimitModelRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2LimitRestClient, ESPMode::ThreadSafe> FGs2LimitRestClientPtr;
}