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
#include "Request/DescribeDataObjectsRequest.h"
#include "Task/Rest/DescribeDataObjectsTask.h"
#include "Request/DescribeDataObjectsByUserIdRequest.h"
#include "Task/Rest/DescribeDataObjectsByUserIdTask.h"
#include "Request/PrepareUploadRequest.h"
#include "Task/Rest/PrepareUploadTask.h"
#include "Request/PrepareUploadByUserIdRequest.h"
#include "Task/Rest/PrepareUploadByUserIdTask.h"
#include "Request/UpdateDataObjectRequest.h"
#include "Task/Rest/UpdateDataObjectTask.h"
#include "Request/UpdateDataObjectByUserIdRequest.h"
#include "Task/Rest/UpdateDataObjectByUserIdTask.h"
#include "Request/PrepareReUploadRequest.h"
#include "Task/Rest/PrepareReUploadTask.h"
#include "Request/PrepareReUploadByUserIdRequest.h"
#include "Task/Rest/PrepareReUploadByUserIdTask.h"
#include "Request/DoneUploadRequest.h"
#include "Task/Rest/DoneUploadTask.h"
#include "Request/DoneUploadByUserIdRequest.h"
#include "Task/Rest/DoneUploadByUserIdTask.h"
#include "Request/DeleteDataObjectRequest.h"
#include "Task/Rest/DeleteDataObjectTask.h"
#include "Request/DeleteDataObjectByUserIdRequest.h"
#include "Task/Rest/DeleteDataObjectByUserIdTask.h"
#include "Request/PrepareDownloadRequest.h"
#include "Task/Rest/PrepareDownloadTask.h"
#include "Request/PrepareDownloadByUserIdRequest.h"
#include "Task/Rest/PrepareDownloadByUserIdTask.h"
#include "Request/PrepareDownloadByGenerationRequest.h"
#include "Task/Rest/PrepareDownloadByGenerationTask.h"
#include "Request/PrepareDownloadByGenerationAndUserIdRequest.h"
#include "Task/Rest/PrepareDownloadByGenerationAndUserIdTask.h"
#include "Request/PrepareDownloadOwnDataRequest.h"
#include "Task/Rest/PrepareDownloadOwnDataTask.h"
#include "Request/PrepareDownloadByUserIdAndDataObjectNameRequest.h"
#include "Task/Rest/PrepareDownloadByUserIdAndDataObjectNameTask.h"
#include "Request/PrepareDownloadOwnDataByGenerationRequest.h"
#include "Task/Rest/PrepareDownloadOwnDataByGenerationTask.h"
#include "Request/PrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest.h"
#include "Task/Rest/PrepareDownloadByUserIdAndDataObjectNameAndGenerationTask.h"
#include "Request/RestoreDataObjectRequest.h"
#include "Task/Rest/RestoreDataObjectTask.h"
#include "Request/DescribeDataObjectHistoriesRequest.h"
#include "Task/Rest/DescribeDataObjectHistoriesTask.h"
#include "Request/DescribeDataObjectHistoriesByUserIdRequest.h"
#include "Task/Rest/DescribeDataObjectHistoriesByUserIdTask.h"
#include "Request/GetDataObjectHistoryRequest.h"
#include "Task/Rest/GetDataObjectHistoryTask.h"
#include "Request/GetDataObjectHistoryByUserIdRequest.h"
#include "Task/Rest/GetDataObjectHistoryByUserIdTask.h"

namespace Gs2::Datastore
{
    class GS2DATASTORE_API FGs2DatastoreRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2DatastoreRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeDataObjectsTask>> DescribeDataObjects(
            const Request::FDescribeDataObjectsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeDataObjectsByUserIdTask>> DescribeDataObjectsByUserId(
            const Request::FDescribeDataObjectsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareUploadTask>> PrepareUpload(
            const Request::FPrepareUploadRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareUploadByUserIdTask>> PrepareUploadByUserId(
            const Request::FPrepareUploadByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateDataObjectTask>> UpdateDataObject(
            const Request::FUpdateDataObjectRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateDataObjectByUserIdTask>> UpdateDataObjectByUserId(
            const Request::FUpdateDataObjectByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareReUploadTask>> PrepareReUpload(
            const Request::FPrepareReUploadRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareReUploadByUserIdTask>> PrepareReUploadByUserId(
            const Request::FPrepareReUploadByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDoneUploadTask>> DoneUpload(
            const Request::FDoneUploadRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDoneUploadByUserIdTask>> DoneUploadByUserId(
            const Request::FDoneUploadByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteDataObjectTask>> DeleteDataObject(
            const Request::FDeleteDataObjectRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteDataObjectByUserIdTask>> DeleteDataObjectByUserId(
            const Request::FDeleteDataObjectByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareDownloadTask>> PrepareDownload(
            const Request::FPrepareDownloadRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareDownloadByUserIdTask>> PrepareDownloadByUserId(
            const Request::FPrepareDownloadByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareDownloadByGenerationTask>> PrepareDownloadByGeneration(
            const Request::FPrepareDownloadByGenerationRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareDownloadByGenerationAndUserIdTask>> PrepareDownloadByGenerationAndUserId(
            const Request::FPrepareDownloadByGenerationAndUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareDownloadOwnDataTask>> PrepareDownloadOwnData(
            const Request::FPrepareDownloadOwnDataRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareDownloadByUserIdAndDataObjectNameTask>> PrepareDownloadByUserIdAndDataObjectName(
            const Request::FPrepareDownloadByUserIdAndDataObjectNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareDownloadOwnDataByGenerationTask>> PrepareDownloadOwnDataByGeneration(
            const Request::FPrepareDownloadOwnDataByGenerationRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask>> PrepareDownloadByUserIdAndDataObjectNameAndGeneration(
            const Request::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRestoreDataObjectTask>> RestoreDataObject(
            const Request::FRestoreDataObjectRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeDataObjectHistoriesTask>> DescribeDataObjectHistories(
            const Request::FDescribeDataObjectHistoriesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeDataObjectHistoriesByUserIdTask>> DescribeDataObjectHistoriesByUserId(
            const Request::FDescribeDataObjectHistoriesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetDataObjectHistoryTask>> GetDataObjectHistory(
            const Request::FGetDataObjectHistoryRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetDataObjectHistoryByUserIdTask>> GetDataObjectHistoryByUserId(
            const Request::FGetDataObjectHistoryByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2DatastoreRestClient, ESPMode::ThreadSafe> FGs2DatastoreRestClientPtr;
}