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
#include "Request/DescribeVersionModelMastersRequest.h"
#include "Task/WebSocket/DescribeVersionModelMastersTask.h"
#include "Request/CreateVersionModelMasterRequest.h"
#include "Task/WebSocket/CreateVersionModelMasterTask.h"
#include "Request/GetVersionModelMasterRequest.h"
#include "Task/WebSocket/GetVersionModelMasterTask.h"
#include "Request/UpdateVersionModelMasterRequest.h"
#include "Task/WebSocket/UpdateVersionModelMasterTask.h"
#include "Request/DeleteVersionModelMasterRequest.h"
#include "Task/WebSocket/DeleteVersionModelMasterTask.h"
#include "Request/DescribeVersionModelsRequest.h"
#include "Task/WebSocket/DescribeVersionModelsTask.h"
#include "Request/GetVersionModelRequest.h"
#include "Task/WebSocket/GetVersionModelTask.h"
#include "Request/DescribeAcceptVersionsRequest.h"
#include "Task/WebSocket/DescribeAcceptVersionsTask.h"
#include "Request/DescribeAcceptVersionsByUserIdRequest.h"
#include "Task/WebSocket/DescribeAcceptVersionsByUserIdTask.h"
#include "Request/AcceptRequest.h"
#include "Task/WebSocket/AcceptTask.h"
#include "Request/AcceptByUserIdRequest.h"
#include "Task/WebSocket/AcceptByUserIdTask.h"
#include "Request/GetAcceptVersionRequest.h"
#include "Task/WebSocket/GetAcceptVersionTask.h"
#include "Request/GetAcceptVersionByUserIdRequest.h"
#include "Task/WebSocket/GetAcceptVersionByUserIdTask.h"
#include "Request/DeleteAcceptVersionRequest.h"
#include "Task/WebSocket/DeleteAcceptVersionTask.h"
#include "Request/DeleteAcceptVersionByUserIdRequest.h"
#include "Task/WebSocket/DeleteAcceptVersionByUserIdTask.h"
#include "Request/CheckVersionRequest.h"
#include "Task/WebSocket/CheckVersionTask.h"
#include "Request/CheckVersionByUserIdRequest.h"
#include "Task/WebSocket/CheckVersionByUserIdTask.h"
#include "Request/CalculateSignatureRequest.h"
#include "Task/WebSocket/CalculateSignatureTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentVersionMasterRequest.h"
#include "Task/WebSocket/GetCurrentVersionMasterTask.h"
#include "Request/UpdateCurrentVersionMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentVersionMasterTask.h"
#include "Request/UpdateCurrentVersionMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentVersionMasterFromGitHubTask.h"

namespace Gs2::Version
{
    class GS2VERSION_API FGs2VersionWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2VersionWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeVersionModelMastersTask>> DescribeVersionModelMasters(
            const Request::FDescribeVersionModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateVersionModelMasterTask>> CreateVersionModelMaster(
            const Request::FCreateVersionModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetVersionModelMasterTask>> GetVersionModelMaster(
            const Request::FGetVersionModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateVersionModelMasterTask>> UpdateVersionModelMaster(
            const Request::FUpdateVersionModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteVersionModelMasterTask>> DeleteVersionModelMaster(
            const Request::FDeleteVersionModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeVersionModelsTask>> DescribeVersionModels(
            const Request::FDescribeVersionModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetVersionModelTask>> GetVersionModel(
            const Request::FGetVersionModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeAcceptVersionsTask>> DescribeAcceptVersions(
            const Request::FDescribeAcceptVersionsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeAcceptVersionsByUserIdTask>> DescribeAcceptVersionsByUserId(
            const Request::FDescribeAcceptVersionsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcceptTask>> Accept(
            const Request::FAcceptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcceptByUserIdTask>> AcceptByUserId(
            const Request::FAcceptByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetAcceptVersionTask>> GetAcceptVersion(
            const Request::FGetAcceptVersionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetAcceptVersionByUserIdTask>> GetAcceptVersionByUserId(
            const Request::FGetAcceptVersionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteAcceptVersionTask>> DeleteAcceptVersion(
            const Request::FDeleteAcceptVersionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteAcceptVersionByUserIdTask>> DeleteAcceptVersionByUserId(
            const Request::FDeleteAcceptVersionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckVersionTask>> CheckVersion(
            const Request::FCheckVersionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckVersionByUserIdTask>> CheckVersionByUserId(
            const Request::FCheckVersionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCalculateSignatureTask>> CalculateSignature(
            const Request::FCalculateSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentVersionMasterTask>> GetCurrentVersionMaster(
            const Request::FGetCurrentVersionMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentVersionMasterTask>> UpdateCurrentVersionMaster(
            const Request::FUpdateCurrentVersionMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentVersionMasterFromGitHubTask>> UpdateCurrentVersionMasterFromGitHub(
            const Request::FUpdateCurrentVersionMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2VersionWebSocketClient, ESPMode::ThreadSafe> FGs2VersionWebSocketClientPtr;
}