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
#include "Request/DescribeAreaModelsRequest.h"
#include "Task/Rest/DescribeAreaModelsTask.h"
#include "Request/GetAreaModelRequest.h"
#include "Task/Rest/GetAreaModelTask.h"
#include "Request/DescribeAreaModelMastersRequest.h"
#include "Task/Rest/DescribeAreaModelMastersTask.h"
#include "Request/CreateAreaModelMasterRequest.h"
#include "Task/Rest/CreateAreaModelMasterTask.h"
#include "Request/GetAreaModelMasterRequest.h"
#include "Task/Rest/GetAreaModelMasterTask.h"
#include "Request/UpdateAreaModelMasterRequest.h"
#include "Task/Rest/UpdateAreaModelMasterTask.h"
#include "Request/DeleteAreaModelMasterRequest.h"
#include "Task/Rest/DeleteAreaModelMasterTask.h"
#include "Request/DescribeLayerModelsRequest.h"
#include "Task/Rest/DescribeLayerModelsTask.h"
#include "Request/GetLayerModelRequest.h"
#include "Task/Rest/GetLayerModelTask.h"
#include "Request/DescribeLayerModelMastersRequest.h"
#include "Task/Rest/DescribeLayerModelMastersTask.h"
#include "Request/CreateLayerModelMasterRequest.h"
#include "Task/Rest/CreateLayerModelMasterTask.h"
#include "Request/GetLayerModelMasterRequest.h"
#include "Task/Rest/GetLayerModelMasterTask.h"
#include "Request/UpdateLayerModelMasterRequest.h"
#include "Task/Rest/UpdateLayerModelMasterTask.h"
#include "Request/DeleteLayerModelMasterRequest.h"
#include "Task/Rest/DeleteLayerModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentFieldMasterRequest.h"
#include "Task/Rest/GetCurrentFieldMasterTask.h"
#include "Request/PreUpdateCurrentFieldMasterRequest.h"
#include "Task/Rest/PreUpdateCurrentFieldMasterTask.h"
#include "Request/UpdateCurrentFieldMasterRequest.h"
#include "Task/Rest/UpdateCurrentFieldMasterTask.h"
#include "Request/UpdateCurrentFieldMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentFieldMasterFromGitHubTask.h"
#include "Request/PutPositionRequest.h"
#include "Task/Rest/PutPositionTask.h"
#include "Request/PutPositionByUserIdRequest.h"
#include "Task/Rest/PutPositionByUserIdTask.h"
#include "Request/FetchPositionRequest.h"
#include "Task/Rest/FetchPositionTask.h"
#include "Request/FetchPositionFromSystemRequest.h"
#include "Task/Rest/FetchPositionFromSystemTask.h"
#include "Request/NearUserIdsRequest.h"
#include "Task/Rest/NearUserIdsTask.h"
#include "Request/NearUserIdsFromSystemRequest.h"
#include "Task/Rest/NearUserIdsFromSystemTask.h"
#include "Request/ActionRequest.h"
#include "Task/Rest/ActionTask.h"
#include "Request/ActionByUserIdRequest.h"
#include "Task/Rest/ActionByUserIdTask.h"

namespace Gs2::MegaField
{
    class GS2MEGAFIELD_API FGs2MegaFieldRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2MegaFieldRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeAreaModelsTask>> DescribeAreaModels(
            const Request::FDescribeAreaModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetAreaModelTask>> GetAreaModel(
            const Request::FGetAreaModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeAreaModelMastersTask>> DescribeAreaModelMasters(
            const Request::FDescribeAreaModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateAreaModelMasterTask>> CreateAreaModelMaster(
            const Request::FCreateAreaModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetAreaModelMasterTask>> GetAreaModelMaster(
            const Request::FGetAreaModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateAreaModelMasterTask>> UpdateAreaModelMaster(
            const Request::FUpdateAreaModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteAreaModelMasterTask>> DeleteAreaModelMaster(
            const Request::FDeleteAreaModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeLayerModelsTask>> DescribeLayerModels(
            const Request::FDescribeLayerModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetLayerModelTask>> GetLayerModel(
            const Request::FGetLayerModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeLayerModelMastersTask>> DescribeLayerModelMasters(
            const Request::FDescribeLayerModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateLayerModelMasterTask>> CreateLayerModelMaster(
            const Request::FCreateLayerModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetLayerModelMasterTask>> GetLayerModelMaster(
            const Request::FGetLayerModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateLayerModelMasterTask>> UpdateLayerModelMaster(
            const Request::FUpdateLayerModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteLayerModelMasterTask>> DeleteLayerModelMaster(
            const Request::FDeleteLayerModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentFieldMasterTask>> GetCurrentFieldMaster(
            const Request::FGetCurrentFieldMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPreUpdateCurrentFieldMasterTask>> PreUpdateCurrentFieldMaster(
            const Request::FPreUpdateCurrentFieldMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentFieldMasterTask>> UpdateCurrentFieldMaster(
            const Request::FUpdateCurrentFieldMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentFieldMasterFromGitHubTask>> UpdateCurrentFieldMasterFromGitHub(
            const Request::FUpdateCurrentFieldMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPutPositionTask>> PutPosition(
            const Request::FPutPositionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPutPositionByUserIdTask>> PutPositionByUserId(
            const Request::FPutPositionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FFetchPositionTask>> FetchPosition(
            const Request::FFetchPositionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FFetchPositionFromSystemTask>> FetchPositionFromSystem(
            const Request::FFetchPositionFromSystemRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FNearUserIdsTask>> NearUserIds(
            const Request::FNearUserIdsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FNearUserIdsFromSystemTask>> NearUserIdsFromSystem(
            const Request::FNearUserIdsFromSystemRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FActionTask>> Action(
            const Request::FActionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FActionByUserIdTask>> ActionByUserId(
            const Request::FActionByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2MegaFieldRestClient, ESPMode::ThreadSafe> FGs2MegaFieldRestClientPtr;
}