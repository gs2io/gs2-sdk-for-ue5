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
#include "Request/DescribeAreaModelsRequest.h"
#include "Task/WebSocket/DescribeAreaModelsTask.h"
#include "Request/GetAreaModelRequest.h"
#include "Task/WebSocket/GetAreaModelTask.h"
#include "Request/DescribeAreaModelMastersRequest.h"
#include "Task/WebSocket/DescribeAreaModelMastersTask.h"
#include "Request/CreateAreaModelMasterRequest.h"
#include "Task/WebSocket/CreateAreaModelMasterTask.h"
#include "Request/GetAreaModelMasterRequest.h"
#include "Task/WebSocket/GetAreaModelMasterTask.h"
#include "Request/UpdateAreaModelMasterRequest.h"
#include "Task/WebSocket/UpdateAreaModelMasterTask.h"
#include "Request/DeleteAreaModelMasterRequest.h"
#include "Task/WebSocket/DeleteAreaModelMasterTask.h"
#include "Request/DescribeLayerModelsRequest.h"
#include "Task/WebSocket/DescribeLayerModelsTask.h"
#include "Request/GetLayerModelRequest.h"
#include "Task/WebSocket/GetLayerModelTask.h"
#include "Request/DescribeLayerModelMastersRequest.h"
#include "Task/WebSocket/DescribeLayerModelMastersTask.h"
#include "Request/CreateLayerModelMasterRequest.h"
#include "Task/WebSocket/CreateLayerModelMasterTask.h"
#include "Request/GetLayerModelMasterRequest.h"
#include "Task/WebSocket/GetLayerModelMasterTask.h"
#include "Request/UpdateLayerModelMasterRequest.h"
#include "Task/WebSocket/UpdateLayerModelMasterTask.h"
#include "Request/DeleteLayerModelMasterRequest.h"
#include "Task/WebSocket/DeleteLayerModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentFieldMasterRequest.h"
#include "Task/WebSocket/GetCurrentFieldMasterTask.h"
#include "Request/PreUpdateCurrentFieldMasterRequest.h"
#include "Task/WebSocket/PreUpdateCurrentFieldMasterTask.h"
#include "Request/UpdateCurrentFieldMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentFieldMasterTask.h"
#include "Request/UpdateCurrentFieldMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentFieldMasterFromGitHubTask.h"
#include "Request/PutPositionRequest.h"
#include "Task/WebSocket/PutPositionTask.h"
#include "Request/PutPositionByUserIdRequest.h"
#include "Task/WebSocket/PutPositionByUserIdTask.h"
#include "Request/FetchPositionRequest.h"
#include "Task/WebSocket/FetchPositionTask.h"
#include "Request/FetchPositionFromSystemRequest.h"
#include "Task/WebSocket/FetchPositionFromSystemTask.h"
#include "Request/NearUserIdsRequest.h"
#include "Task/WebSocket/NearUserIdsTask.h"
#include "Request/NearUserIdsFromSystemRequest.h"
#include "Task/WebSocket/NearUserIdsFromSystemTask.h"
#include "Request/ActionRequest.h"
#include "Task/WebSocket/ActionTask.h"
#include "Request/ActionByUserIdRequest.h"
#include "Task/WebSocket/ActionByUserIdTask.h"

namespace Gs2::MegaField
{
    class GS2MEGAFIELD_API FGs2MegaFieldWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2MegaFieldWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeAreaModelsTask>> DescribeAreaModels(
            const Request::FDescribeAreaModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetAreaModelTask>> GetAreaModel(
            const Request::FGetAreaModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeAreaModelMastersTask>> DescribeAreaModelMasters(
            const Request::FDescribeAreaModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateAreaModelMasterTask>> CreateAreaModelMaster(
            const Request::FCreateAreaModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetAreaModelMasterTask>> GetAreaModelMaster(
            const Request::FGetAreaModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateAreaModelMasterTask>> UpdateAreaModelMaster(
            const Request::FUpdateAreaModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteAreaModelMasterTask>> DeleteAreaModelMaster(
            const Request::FDeleteAreaModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeLayerModelsTask>> DescribeLayerModels(
            const Request::FDescribeLayerModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetLayerModelTask>> GetLayerModel(
            const Request::FGetLayerModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeLayerModelMastersTask>> DescribeLayerModelMasters(
            const Request::FDescribeLayerModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateLayerModelMasterTask>> CreateLayerModelMaster(
            const Request::FCreateLayerModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetLayerModelMasterTask>> GetLayerModelMaster(
            const Request::FGetLayerModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateLayerModelMasterTask>> UpdateLayerModelMaster(
            const Request::FUpdateLayerModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteLayerModelMasterTask>> DeleteLayerModelMaster(
            const Request::FDeleteLayerModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentFieldMasterTask>> GetCurrentFieldMaster(
            const Request::FGetCurrentFieldMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPreUpdateCurrentFieldMasterTask>> PreUpdateCurrentFieldMaster(
            const Request::FPreUpdateCurrentFieldMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentFieldMasterTask>> UpdateCurrentFieldMaster(
            const Request::FUpdateCurrentFieldMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentFieldMasterFromGitHubTask>> UpdateCurrentFieldMasterFromGitHub(
            const Request::FUpdateCurrentFieldMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPutPositionTask>> PutPosition(
            const Request::FPutPositionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPutPositionByUserIdTask>> PutPositionByUserId(
            const Request::FPutPositionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FFetchPositionTask>> FetchPosition(
            const Request::FFetchPositionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FFetchPositionFromSystemTask>> FetchPositionFromSystem(
            const Request::FFetchPositionFromSystemRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FNearUserIdsTask>> NearUserIds(
            const Request::FNearUserIdsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FNearUserIdsFromSystemTask>> NearUserIdsFromSystem(
            const Request::FNearUserIdsFromSystemRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FActionTask>> Action(
            const Request::FActionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FActionByUserIdTask>> ActionByUserId(
            const Request::FActionByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2MegaFieldWebSocketClient, ESPMode::ThreadSafe> FGs2MegaFieldWebSocketClientPtr;
}