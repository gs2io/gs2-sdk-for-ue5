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

#include "Version/Gs2VersionWebSocketClient.h"

namespace Gs2::Version
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> FGs2VersionWebSocketClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> FGs2VersionWebSocketClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> FGs2VersionWebSocketClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> FGs2VersionWebSocketClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> FGs2VersionWebSocketClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> FGs2VersionWebSocketClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeVersionModelMastersTask>> FGs2VersionWebSocketClient::DescribeVersionModelMasters(
        const Request::FDescribeVersionModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeVersionModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateVersionModelMasterTask>> FGs2VersionWebSocketClient::CreateVersionModelMaster(
        const Request::FCreateVersionModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateVersionModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetVersionModelMasterTask>> FGs2VersionWebSocketClient::GetVersionModelMaster(
        const Request::FGetVersionModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetVersionModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateVersionModelMasterTask>> FGs2VersionWebSocketClient::UpdateVersionModelMaster(
        const Request::FUpdateVersionModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateVersionModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteVersionModelMasterTask>> FGs2VersionWebSocketClient::DeleteVersionModelMaster(
        const Request::FDeleteVersionModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteVersionModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeVersionModelsTask>> FGs2VersionWebSocketClient::DescribeVersionModels(
        const Request::FDescribeVersionModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeVersionModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetVersionModelTask>> FGs2VersionWebSocketClient::GetVersionModel(
        const Request::FGetVersionModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetVersionModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeAcceptVersionsTask>> FGs2VersionWebSocketClient::DescribeAcceptVersions(
        const Request::FDescribeAcceptVersionsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeAcceptVersionsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeAcceptVersionsByUserIdTask>> FGs2VersionWebSocketClient::DescribeAcceptVersionsByUserId(
        const Request::FDescribeAcceptVersionsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeAcceptVersionsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAcceptTask>> FGs2VersionWebSocketClient::Accept(
        const Request::FAcceptRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAcceptTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAcceptByUserIdTask>> FGs2VersionWebSocketClient::AcceptByUserId(
        const Request::FAcceptByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAcceptByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetAcceptVersionTask>> FGs2VersionWebSocketClient::GetAcceptVersion(
        const Request::FGetAcceptVersionRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetAcceptVersionTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetAcceptVersionByUserIdTask>> FGs2VersionWebSocketClient::GetAcceptVersionByUserId(
        const Request::FGetAcceptVersionByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetAcceptVersionByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteAcceptVersionTask>> FGs2VersionWebSocketClient::DeleteAcceptVersion(
        const Request::FDeleteAcceptVersionRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteAcceptVersionTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteAcceptVersionByUserIdTask>> FGs2VersionWebSocketClient::DeleteAcceptVersionByUserId(
        const Request::FDeleteAcceptVersionByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteAcceptVersionByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckVersionTask>> FGs2VersionWebSocketClient::CheckVersion(
        const Request::FCheckVersionRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckVersionTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckVersionByUserIdTask>> FGs2VersionWebSocketClient::CheckVersionByUserId(
        const Request::FCheckVersionByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckVersionByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCalculateSignatureTask>> FGs2VersionWebSocketClient::CalculateSignature(
        const Request::FCalculateSignatureRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCalculateSignatureTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> FGs2VersionWebSocketClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentVersionMasterTask>> FGs2VersionWebSocketClient::GetCurrentVersionMaster(
        const Request::FGetCurrentVersionMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCurrentVersionMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentVersionMasterTask>> FGs2VersionWebSocketClient::UpdateCurrentVersionMaster(
        const Request::FUpdateCurrentVersionMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentVersionMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentVersionMasterFromGitHubTask>> FGs2VersionWebSocketClient::UpdateCurrentVersionMasterFromGitHub(
        const Request::FUpdateCurrentVersionMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentVersionMasterFromGitHubTask>>(
            Session,
            Request
        );
    }
}