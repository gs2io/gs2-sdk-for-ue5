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

#include "Distributor/Gs2DistributorRestClient.h"

namespace Gs2::Distributor
{

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> FGs2DistributorRestClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> FGs2DistributorRestClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> FGs2DistributorRestClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> FGs2DistributorRestClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> FGs2DistributorRestClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> FGs2DistributorRestClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeDistributorModelMastersTask>> FGs2DistributorRestClient::DescribeDistributorModelMasters(
        const Request::FDescribeDistributorModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeDistributorModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateDistributorModelMasterTask>> FGs2DistributorRestClient::CreateDistributorModelMaster(
        const Request::FCreateDistributorModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateDistributorModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetDistributorModelMasterTask>> FGs2DistributorRestClient::GetDistributorModelMaster(
        const Request::FGetDistributorModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetDistributorModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateDistributorModelMasterTask>> FGs2DistributorRestClient::UpdateDistributorModelMaster(
        const Request::FUpdateDistributorModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateDistributorModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteDistributorModelMasterTask>> FGs2DistributorRestClient::DeleteDistributorModelMaster(
        const Request::FDeleteDistributorModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteDistributorModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeDistributorModelsTask>> FGs2DistributorRestClient::DescribeDistributorModels(
        const Request::FDescribeDistributorModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeDistributorModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetDistributorModelTask>> FGs2DistributorRestClient::GetDistributorModel(
        const Request::FGetDistributorModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetDistributorModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> FGs2DistributorRestClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentDistributorMasterTask>> FGs2DistributorRestClient::GetCurrentDistributorMaster(
        const Request::FGetCurrentDistributorMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetCurrentDistributorMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentDistributorMasterTask>> FGs2DistributorRestClient::UpdateCurrentDistributorMaster(
        const Request::FUpdateCurrentDistributorMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentDistributorMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentDistributorMasterFromGitHubTask>> FGs2DistributorRestClient::UpdateCurrentDistributorMasterFromGitHub(
        const Request::FUpdateCurrentDistributorMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentDistributorMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDistributeTask>> FGs2DistributorRestClient::Distribute(
        const Request::FDistributeRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDistributeTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDistributeWithoutOverflowProcessTask>> FGs2DistributorRestClient::DistributeWithoutOverflowProcess(
        const Request::FDistributeWithoutOverflowProcessRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDistributeWithoutOverflowProcessTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRunStampTaskTask>> FGs2DistributorRestClient::RunStampTask(
        const Request::FRunStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRunStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRunStampSheetTask>> FGs2DistributorRestClient::RunStampSheet(
        const Request::FRunStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRunStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRunStampSheetExpressTask>> FGs2DistributorRestClient::RunStampSheetExpress(
        const Request::FRunStampSheetExpressRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRunStampSheetExpressTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRunStampTaskWithoutNamespaceTask>> FGs2DistributorRestClient::RunStampTaskWithoutNamespace(
        const Request::FRunStampTaskWithoutNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRunStampTaskWithoutNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRunStampSheetWithoutNamespaceTask>> FGs2DistributorRestClient::RunStampSheetWithoutNamespace(
        const Request::FRunStampSheetWithoutNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRunStampSheetWithoutNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRunStampSheetExpressWithoutNamespaceTask>> FGs2DistributorRestClient::RunStampSheetExpressWithoutNamespace(
        const Request::FRunStampSheetExpressWithoutNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRunStampSheetExpressWithoutNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetStampSheetResultTask>> FGs2DistributorRestClient::GetStampSheetResult(
        const Request::FGetStampSheetResultRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetStampSheetResultTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetStampSheetResultByUserIdTask>> FGs2DistributorRestClient::GetStampSheetResultByUserId(
        const Request::FGetStampSheetResultByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetStampSheetResultByUserIdTask>>(
            Session,
            Request
        );
    }
}