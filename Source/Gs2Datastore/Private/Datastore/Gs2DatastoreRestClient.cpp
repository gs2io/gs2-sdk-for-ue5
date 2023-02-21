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

#include "Datastore/Gs2DatastoreRestClient.h"

namespace Gs2::Datastore
{

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> FGs2DatastoreRestClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> FGs2DatastoreRestClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> FGs2DatastoreRestClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> FGs2DatastoreRestClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> FGs2DatastoreRestClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> FGs2DatastoreRestClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeDataObjectsTask>> FGs2DatastoreRestClient::DescribeDataObjects(
        const Request::FDescribeDataObjectsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeDataObjectsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeDataObjectsByUserIdTask>> FGs2DatastoreRestClient::DescribeDataObjectsByUserId(
        const Request::FDescribeDataObjectsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeDataObjectsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPrepareUploadTask>> FGs2DatastoreRestClient::PrepareUpload(
        const Request::FPrepareUploadRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPrepareUploadTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPrepareUploadByUserIdTask>> FGs2DatastoreRestClient::PrepareUploadByUserId(
        const Request::FPrepareUploadByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPrepareUploadByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateDataObjectTask>> FGs2DatastoreRestClient::UpdateDataObject(
        const Request::FUpdateDataObjectRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateDataObjectTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateDataObjectByUserIdTask>> FGs2DatastoreRestClient::UpdateDataObjectByUserId(
        const Request::FUpdateDataObjectByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateDataObjectByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPrepareReUploadTask>> FGs2DatastoreRestClient::PrepareReUpload(
        const Request::FPrepareReUploadRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPrepareReUploadTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPrepareReUploadByUserIdTask>> FGs2DatastoreRestClient::PrepareReUploadByUserId(
        const Request::FPrepareReUploadByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPrepareReUploadByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDoneUploadTask>> FGs2DatastoreRestClient::DoneUpload(
        const Request::FDoneUploadRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDoneUploadTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDoneUploadByUserIdTask>> FGs2DatastoreRestClient::DoneUploadByUserId(
        const Request::FDoneUploadByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDoneUploadByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteDataObjectTask>> FGs2DatastoreRestClient::DeleteDataObject(
        const Request::FDeleteDataObjectRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteDataObjectTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteDataObjectByUserIdTask>> FGs2DatastoreRestClient::DeleteDataObjectByUserId(
        const Request::FDeleteDataObjectByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteDataObjectByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPrepareDownloadTask>> FGs2DatastoreRestClient::PrepareDownload(
        const Request::FPrepareDownloadRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPrepareDownloadTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPrepareDownloadByUserIdTask>> FGs2DatastoreRestClient::PrepareDownloadByUserId(
        const Request::FPrepareDownloadByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPrepareDownloadByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPrepareDownloadByGenerationTask>> FGs2DatastoreRestClient::PrepareDownloadByGeneration(
        const Request::FPrepareDownloadByGenerationRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPrepareDownloadByGenerationTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPrepareDownloadByGenerationAndUserIdTask>> FGs2DatastoreRestClient::PrepareDownloadByGenerationAndUserId(
        const Request::FPrepareDownloadByGenerationAndUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPrepareDownloadByGenerationAndUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPrepareDownloadOwnDataTask>> FGs2DatastoreRestClient::PrepareDownloadOwnData(
        const Request::FPrepareDownloadOwnDataRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPrepareDownloadOwnDataTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPrepareDownloadByUserIdAndDataObjectNameTask>> FGs2DatastoreRestClient::PrepareDownloadByUserIdAndDataObjectName(
        const Request::FPrepareDownloadByUserIdAndDataObjectNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPrepareDownloadByUserIdAndDataObjectNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPrepareDownloadOwnDataByGenerationTask>> FGs2DatastoreRestClient::PrepareDownloadOwnDataByGeneration(
        const Request::FPrepareDownloadOwnDataByGenerationRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPrepareDownloadOwnDataByGenerationTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask>> FGs2DatastoreRestClient::PrepareDownloadByUserIdAndDataObjectNameAndGeneration(
        const Request::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRestoreDataObjectTask>> FGs2DatastoreRestClient::RestoreDataObject(
        const Request::FRestoreDataObjectRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRestoreDataObjectTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeDataObjectHistoriesTask>> FGs2DatastoreRestClient::DescribeDataObjectHistories(
        const Request::FDescribeDataObjectHistoriesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeDataObjectHistoriesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeDataObjectHistoriesByUserIdTask>> FGs2DatastoreRestClient::DescribeDataObjectHistoriesByUserId(
        const Request::FDescribeDataObjectHistoriesByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeDataObjectHistoriesByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetDataObjectHistoryTask>> FGs2DatastoreRestClient::GetDataObjectHistory(
        const Request::FGetDataObjectHistoryRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetDataObjectHistoryTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetDataObjectHistoryByUserIdTask>> FGs2DatastoreRestClient::GetDataObjectHistoryByUserId(
        const Request::FGetDataObjectHistoryByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetDataObjectHistoryByUserIdTask>>(
            Session,
            Request
        );
    }
}