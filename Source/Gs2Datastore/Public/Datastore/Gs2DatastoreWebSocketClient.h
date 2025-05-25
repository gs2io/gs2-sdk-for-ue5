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
#include "Request/GetServiceVersionRequest.h"
#include "Task/WebSocket/GetServiceVersionTask.h"
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/DumpUserDataByUserIdTask.h"
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckDumpUserDataByUserIdTask.h"
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CleanUserDataByUserIdTask.h"
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckCleanUserDataByUserIdTask.h"
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/PrepareImportUserDataByUserIdTask.h"
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/ImportUserDataByUserIdTask.h"
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckImportUserDataByUserIdTask.h"
#include "Request/DescribeDataObjectsRequest.h"
#include "Task/WebSocket/DescribeDataObjectsTask.h"
#include "Request/DescribeDataObjectsByUserIdRequest.h"
#include "Task/WebSocket/DescribeDataObjectsByUserIdTask.h"
#include "Request/PrepareUploadRequest.h"
#include "Task/WebSocket/PrepareUploadTask.h"
#include "Request/PrepareUploadByUserIdRequest.h"
#include "Task/WebSocket/PrepareUploadByUserIdTask.h"
#include "Request/UpdateDataObjectRequest.h"
#include "Task/WebSocket/UpdateDataObjectTask.h"
#include "Request/UpdateDataObjectByUserIdRequest.h"
#include "Task/WebSocket/UpdateDataObjectByUserIdTask.h"
#include "Request/PrepareReUploadRequest.h"
#include "Task/WebSocket/PrepareReUploadTask.h"
#include "Request/PrepareReUploadByUserIdRequest.h"
#include "Task/WebSocket/PrepareReUploadByUserIdTask.h"
#include "Request/DoneUploadRequest.h"
#include "Task/WebSocket/DoneUploadTask.h"
#include "Request/DoneUploadByUserIdRequest.h"
#include "Task/WebSocket/DoneUploadByUserIdTask.h"
#include "Request/DeleteDataObjectRequest.h"
#include "Task/WebSocket/DeleteDataObjectTask.h"
#include "Request/DeleteDataObjectByUserIdRequest.h"
#include "Task/WebSocket/DeleteDataObjectByUserIdTask.h"
#include "Request/PrepareDownloadRequest.h"
#include "Task/WebSocket/PrepareDownloadTask.h"
#include "Request/PrepareDownloadByUserIdRequest.h"
#include "Task/WebSocket/PrepareDownloadByUserIdTask.h"
#include "Request/PrepareDownloadByGenerationRequest.h"
#include "Task/WebSocket/PrepareDownloadByGenerationTask.h"
#include "Request/PrepareDownloadByGenerationAndUserIdRequest.h"
#include "Task/WebSocket/PrepareDownloadByGenerationAndUserIdTask.h"
#include "Request/PrepareDownloadOwnDataRequest.h"
#include "Task/WebSocket/PrepareDownloadOwnDataTask.h"
#include "Request/PrepareDownloadByUserIdAndDataObjectNameRequest.h"
#include "Task/WebSocket/PrepareDownloadByUserIdAndDataObjectNameTask.h"
#include "Request/PrepareDownloadOwnDataByGenerationRequest.h"
#include "Task/WebSocket/PrepareDownloadOwnDataByGenerationTask.h"
#include "Request/PrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest.h"
#include "Task/WebSocket/PrepareDownloadByUserIdAndDataObjectNameAndGenerationTask.h"
#include "Request/RestoreDataObjectRequest.h"
#include "Task/WebSocket/RestoreDataObjectTask.h"
#include "Request/DescribeDataObjectHistoriesRequest.h"
#include "Task/WebSocket/DescribeDataObjectHistoriesTask.h"
#include "Request/DescribeDataObjectHistoriesByUserIdRequest.h"
#include "Task/WebSocket/DescribeDataObjectHistoriesByUserIdTask.h"
#include "Request/GetDataObjectHistoryRequest.h"
#include "Task/WebSocket/GetDataObjectHistoryTask.h"
#include "Request/GetDataObjectHistoryByUserIdRequest.h"
#include "Task/WebSocket/GetDataObjectHistoryByUserIdTask.h"

namespace Gs2::Datastore
{
    class GS2DATASTORE_API FGs2DatastoreWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2DatastoreWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetServiceVersionTask>> GetServiceVersion(
            const Request::FGetServiceVersionRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>> PrepareImportUserDataByUserId(
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>> ImportUserDataByUserId(
            const Request::FImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>> CheckImportUserDataByUserId(
            const Request::FCheckImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeDataObjectsTask>> DescribeDataObjects(
            const Request::FDescribeDataObjectsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeDataObjectsByUserIdTask>> DescribeDataObjectsByUserId(
            const Request::FDescribeDataObjectsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareUploadTask>> PrepareUpload(
            const Request::FPrepareUploadRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareUploadByUserIdTask>> PrepareUploadByUserId(
            const Request::FPrepareUploadByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateDataObjectTask>> UpdateDataObject(
            const Request::FUpdateDataObjectRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateDataObjectByUserIdTask>> UpdateDataObjectByUserId(
            const Request::FUpdateDataObjectByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareReUploadTask>> PrepareReUpload(
            const Request::FPrepareReUploadRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareReUploadByUserIdTask>> PrepareReUploadByUserId(
            const Request::FPrepareReUploadByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDoneUploadTask>> DoneUpload(
            const Request::FDoneUploadRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDoneUploadByUserIdTask>> DoneUploadByUserId(
            const Request::FDoneUploadByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteDataObjectTask>> DeleteDataObject(
            const Request::FDeleteDataObjectRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteDataObjectByUserIdTask>> DeleteDataObjectByUserId(
            const Request::FDeleteDataObjectByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareDownloadTask>> PrepareDownload(
            const Request::FPrepareDownloadRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareDownloadByUserIdTask>> PrepareDownloadByUserId(
            const Request::FPrepareDownloadByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareDownloadByGenerationTask>> PrepareDownloadByGeneration(
            const Request::FPrepareDownloadByGenerationRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareDownloadByGenerationAndUserIdTask>> PrepareDownloadByGenerationAndUserId(
            const Request::FPrepareDownloadByGenerationAndUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareDownloadOwnDataTask>> PrepareDownloadOwnData(
            const Request::FPrepareDownloadOwnDataRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareDownloadByUserIdAndDataObjectNameTask>> PrepareDownloadByUserIdAndDataObjectName(
            const Request::FPrepareDownloadByUserIdAndDataObjectNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareDownloadOwnDataByGenerationTask>> PrepareDownloadOwnDataByGeneration(
            const Request::FPrepareDownloadOwnDataByGenerationRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask>> PrepareDownloadByUserIdAndDataObjectNameAndGeneration(
            const Request::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRestoreDataObjectTask>> RestoreDataObject(
            const Request::FRestoreDataObjectRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeDataObjectHistoriesTask>> DescribeDataObjectHistories(
            const Request::FDescribeDataObjectHistoriesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeDataObjectHistoriesByUserIdTask>> DescribeDataObjectHistoriesByUserId(
            const Request::FDescribeDataObjectHistoriesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetDataObjectHistoryTask>> GetDataObjectHistory(
            const Request::FGetDataObjectHistoryRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetDataObjectHistoryByUserIdTask>> GetDataObjectHistoryByUserId(
            const Request::FGetDataObjectHistoryByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2DatastoreWebSocketClient, ESPMode::ThreadSafe> FGs2DatastoreWebSocketClientPtr;
}