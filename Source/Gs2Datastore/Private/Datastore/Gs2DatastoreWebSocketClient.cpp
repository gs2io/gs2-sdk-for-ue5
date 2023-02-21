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

#include "Datastore/Gs2DatastoreWebSocketClient.h"

namespace Gs2::Datastore
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> FGs2DatastoreWebSocketClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> FGs2DatastoreWebSocketClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> FGs2DatastoreWebSocketClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> FGs2DatastoreWebSocketClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> FGs2DatastoreWebSocketClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> FGs2DatastoreWebSocketClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeDataObjectsTask>> FGs2DatastoreWebSocketClient::DescribeDataObjects(
        const Request::FDescribeDataObjectsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeDataObjectsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeDataObjectsByUserIdTask>> FGs2DatastoreWebSocketClient::DescribeDataObjectsByUserId(
        const Request::FDescribeDataObjectsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeDataObjectsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareUploadTask>> FGs2DatastoreWebSocketClient::PrepareUpload(
        const Request::FPrepareUploadRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareUploadTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareUploadByUserIdTask>> FGs2DatastoreWebSocketClient::PrepareUploadByUserId(
        const Request::FPrepareUploadByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareUploadByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateDataObjectTask>> FGs2DatastoreWebSocketClient::UpdateDataObject(
        const Request::FUpdateDataObjectRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateDataObjectTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateDataObjectByUserIdTask>> FGs2DatastoreWebSocketClient::UpdateDataObjectByUserId(
        const Request::FUpdateDataObjectByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateDataObjectByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareReUploadTask>> FGs2DatastoreWebSocketClient::PrepareReUpload(
        const Request::FPrepareReUploadRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareReUploadTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareReUploadByUserIdTask>> FGs2DatastoreWebSocketClient::PrepareReUploadByUserId(
        const Request::FPrepareReUploadByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareReUploadByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDoneUploadTask>> FGs2DatastoreWebSocketClient::DoneUpload(
        const Request::FDoneUploadRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDoneUploadTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDoneUploadByUserIdTask>> FGs2DatastoreWebSocketClient::DoneUploadByUserId(
        const Request::FDoneUploadByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDoneUploadByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteDataObjectTask>> FGs2DatastoreWebSocketClient::DeleteDataObject(
        const Request::FDeleteDataObjectRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteDataObjectTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteDataObjectByUserIdTask>> FGs2DatastoreWebSocketClient::DeleteDataObjectByUserId(
        const Request::FDeleteDataObjectByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteDataObjectByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareDownloadTask>> FGs2DatastoreWebSocketClient::PrepareDownload(
        const Request::FPrepareDownloadRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareDownloadTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareDownloadByUserIdTask>> FGs2DatastoreWebSocketClient::PrepareDownloadByUserId(
        const Request::FPrepareDownloadByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareDownloadByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareDownloadByGenerationTask>> FGs2DatastoreWebSocketClient::PrepareDownloadByGeneration(
        const Request::FPrepareDownloadByGenerationRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareDownloadByGenerationTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareDownloadByGenerationAndUserIdTask>> FGs2DatastoreWebSocketClient::PrepareDownloadByGenerationAndUserId(
        const Request::FPrepareDownloadByGenerationAndUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareDownloadByGenerationAndUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareDownloadOwnDataTask>> FGs2DatastoreWebSocketClient::PrepareDownloadOwnData(
        const Request::FPrepareDownloadOwnDataRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareDownloadOwnDataTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareDownloadByUserIdAndDataObjectNameTask>> FGs2DatastoreWebSocketClient::PrepareDownloadByUserIdAndDataObjectName(
        const Request::FPrepareDownloadByUserIdAndDataObjectNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareDownloadByUserIdAndDataObjectNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareDownloadOwnDataByGenerationTask>> FGs2DatastoreWebSocketClient::PrepareDownloadOwnDataByGeneration(
        const Request::FPrepareDownloadOwnDataByGenerationRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareDownloadOwnDataByGenerationTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask>> FGs2DatastoreWebSocketClient::PrepareDownloadByUserIdAndDataObjectNameAndGeneration(
        const Request::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRestoreDataObjectTask>> FGs2DatastoreWebSocketClient::RestoreDataObject(
        const Request::FRestoreDataObjectRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRestoreDataObjectTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeDataObjectHistoriesTask>> FGs2DatastoreWebSocketClient::DescribeDataObjectHistories(
        const Request::FDescribeDataObjectHistoriesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeDataObjectHistoriesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeDataObjectHistoriesByUserIdTask>> FGs2DatastoreWebSocketClient::DescribeDataObjectHistoriesByUserId(
        const Request::FDescribeDataObjectHistoriesByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeDataObjectHistoriesByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetDataObjectHistoryTask>> FGs2DatastoreWebSocketClient::GetDataObjectHistory(
        const Request::FGetDataObjectHistoryRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetDataObjectHistoryTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetDataObjectHistoryByUserIdTask>> FGs2DatastoreWebSocketClient::GetDataObjectHistoryByUserId(
        const Request::FGetDataObjectHistoryByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetDataObjectHistoryByUserIdTask>>(
            Session,
            Request
        );
    }
}