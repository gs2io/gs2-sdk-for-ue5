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

// Model
#include "Model/Namespace.h"
#include "Model/AreaModel.h"
#include "Model/AreaModelMaster.h"
#include "Model/LayerModel.h"
#include "Model/LayerModelMaster.h"
#include "Model/CurrentFieldMaster.h"
#include "Model/Layer.h"
#include "Model/Spatial.h"
#include "Model/Position.h"
#include "Model/MyPosition.h"
#include "Model/Scope.h"
#include "Model/Vector.h"
#include "Model/LogSetting.h"
#include "Model/GitHubCheckoutSetting.h"

// DescribeNamespaces
#include "Request/DescribeNamespacesRequest.h"
#include "Result/DescribeNamespacesResult.h"
#include "Task/Rest/DescribeNamespacesTask.h"
#include "Task/WebSocket/DescribeNamespacesTask.h"

// CreateNamespace
#include "Request/CreateNamespaceRequest.h"
#include "Result/CreateNamespaceResult.h"
#include "Task/Rest/CreateNamespaceTask.h"
#include "Task/WebSocket/CreateNamespaceTask.h"

// GetNamespaceStatus
#include "Request/GetNamespaceStatusRequest.h"
#include "Result/GetNamespaceStatusResult.h"
#include "Task/Rest/GetNamespaceStatusTask.h"
#include "Task/WebSocket/GetNamespaceStatusTask.h"

// GetNamespace
#include "Request/GetNamespaceRequest.h"
#include "Result/GetNamespaceResult.h"
#include "Task/Rest/GetNamespaceTask.h"
#include "Task/WebSocket/GetNamespaceTask.h"

// UpdateNamespace
#include "Request/UpdateNamespaceRequest.h"
#include "Result/UpdateNamespaceResult.h"
#include "Task/Rest/UpdateNamespaceTask.h"
#include "Task/WebSocket/UpdateNamespaceTask.h"

// DeleteNamespace
#include "Request/DeleteNamespaceRequest.h"
#include "Result/DeleteNamespaceResult.h"
#include "Task/Rest/DeleteNamespaceTask.h"
#include "Task/WebSocket/DeleteNamespaceTask.h"

// DescribeAreaModels
#include "Request/DescribeAreaModelsRequest.h"
#include "Result/DescribeAreaModelsResult.h"
#include "Task/Rest/DescribeAreaModelsTask.h"
#include "Task/WebSocket/DescribeAreaModelsTask.h"

// GetAreaModel
#include "Request/GetAreaModelRequest.h"
#include "Result/GetAreaModelResult.h"
#include "Task/Rest/GetAreaModelTask.h"
#include "Task/WebSocket/GetAreaModelTask.h"

// DescribeAreaModelMasters
#include "Request/DescribeAreaModelMastersRequest.h"
#include "Result/DescribeAreaModelMastersResult.h"
#include "Task/Rest/DescribeAreaModelMastersTask.h"
#include "Task/WebSocket/DescribeAreaModelMastersTask.h"

// CreateAreaModelMaster
#include "Request/CreateAreaModelMasterRequest.h"
#include "Result/CreateAreaModelMasterResult.h"
#include "Task/Rest/CreateAreaModelMasterTask.h"
#include "Task/WebSocket/CreateAreaModelMasterTask.h"

// GetAreaModelMaster
#include "Request/GetAreaModelMasterRequest.h"
#include "Result/GetAreaModelMasterResult.h"
#include "Task/Rest/GetAreaModelMasterTask.h"
#include "Task/WebSocket/GetAreaModelMasterTask.h"

// UpdateAreaModelMaster
#include "Request/UpdateAreaModelMasterRequest.h"
#include "Result/UpdateAreaModelMasterResult.h"
#include "Task/Rest/UpdateAreaModelMasterTask.h"
#include "Task/WebSocket/UpdateAreaModelMasterTask.h"

// DeleteAreaModelMaster
#include "Request/DeleteAreaModelMasterRequest.h"
#include "Result/DeleteAreaModelMasterResult.h"
#include "Task/Rest/DeleteAreaModelMasterTask.h"
#include "Task/WebSocket/DeleteAreaModelMasterTask.h"

// DescribeLayerModels
#include "Request/DescribeLayerModelsRequest.h"
#include "Result/DescribeLayerModelsResult.h"
#include "Task/Rest/DescribeLayerModelsTask.h"
#include "Task/WebSocket/DescribeLayerModelsTask.h"

// GetLayerModel
#include "Request/GetLayerModelRequest.h"
#include "Result/GetLayerModelResult.h"
#include "Task/Rest/GetLayerModelTask.h"
#include "Task/WebSocket/GetLayerModelTask.h"

// DescribeLayerModelMasters
#include "Request/DescribeLayerModelMastersRequest.h"
#include "Result/DescribeLayerModelMastersResult.h"
#include "Task/Rest/DescribeLayerModelMastersTask.h"
#include "Task/WebSocket/DescribeLayerModelMastersTask.h"

// CreateLayerModelMaster
#include "Request/CreateLayerModelMasterRequest.h"
#include "Result/CreateLayerModelMasterResult.h"
#include "Task/Rest/CreateLayerModelMasterTask.h"
#include "Task/WebSocket/CreateLayerModelMasterTask.h"

// GetLayerModelMaster
#include "Request/GetLayerModelMasterRequest.h"
#include "Result/GetLayerModelMasterResult.h"
#include "Task/Rest/GetLayerModelMasterTask.h"
#include "Task/WebSocket/GetLayerModelMasterTask.h"

// UpdateLayerModelMaster
#include "Request/UpdateLayerModelMasterRequest.h"
#include "Result/UpdateLayerModelMasterResult.h"
#include "Task/Rest/UpdateLayerModelMasterTask.h"
#include "Task/WebSocket/UpdateLayerModelMasterTask.h"

// DeleteLayerModelMaster
#include "Request/DeleteLayerModelMasterRequest.h"
#include "Result/DeleteLayerModelMasterResult.h"
#include "Task/Rest/DeleteLayerModelMasterTask.h"
#include "Task/WebSocket/DeleteLayerModelMasterTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentFieldMaster
#include "Request/GetCurrentFieldMasterRequest.h"
#include "Result/GetCurrentFieldMasterResult.h"
#include "Task/Rest/GetCurrentFieldMasterTask.h"
#include "Task/WebSocket/GetCurrentFieldMasterTask.h"

// PreUpdateCurrentFieldMaster
#include "Request/PreUpdateCurrentFieldMasterRequest.h"
#include "Result/PreUpdateCurrentFieldMasterResult.h"
#include "Task/Rest/PreUpdateCurrentFieldMasterTask.h"
#include "Task/WebSocket/PreUpdateCurrentFieldMasterTask.h"

// UpdateCurrentFieldMaster
#include "Request/UpdateCurrentFieldMasterRequest.h"
#include "Result/UpdateCurrentFieldMasterResult.h"
#include "Task/Rest/UpdateCurrentFieldMasterTask.h"
#include "Task/WebSocket/UpdateCurrentFieldMasterTask.h"

// UpdateCurrentFieldMasterFromGitHub
#include "Request/UpdateCurrentFieldMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentFieldMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentFieldMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentFieldMasterFromGitHubTask.h"

// PutPosition
#include "Request/PutPositionRequest.h"
#include "Result/PutPositionResult.h"
#include "Task/Rest/PutPositionTask.h"
#include "Task/WebSocket/PutPositionTask.h"

// PutPositionByUserId
#include "Request/PutPositionByUserIdRequest.h"
#include "Result/PutPositionByUserIdResult.h"
#include "Task/Rest/PutPositionByUserIdTask.h"
#include "Task/WebSocket/PutPositionByUserIdTask.h"

// FetchPosition
#include "Request/FetchPositionRequest.h"
#include "Result/FetchPositionResult.h"
#include "Task/Rest/FetchPositionTask.h"
#include "Task/WebSocket/FetchPositionTask.h"

// FetchPositionFromSystem
#include "Request/FetchPositionFromSystemRequest.h"
#include "Result/FetchPositionFromSystemResult.h"
#include "Task/Rest/FetchPositionFromSystemTask.h"
#include "Task/WebSocket/FetchPositionFromSystemTask.h"

// NearUserIds
#include "Request/NearUserIdsRequest.h"
#include "Result/NearUserIdsResult.h"
#include "Task/Rest/NearUserIdsTask.h"
#include "Task/WebSocket/NearUserIdsTask.h"

// NearUserIdsFromSystem
#include "Request/NearUserIdsFromSystemRequest.h"
#include "Result/NearUserIdsFromSystemResult.h"
#include "Task/Rest/NearUserIdsFromSystemTask.h"
#include "Task/WebSocket/NearUserIdsFromSystemTask.h"

// Action
#include "Request/ActionRequest.h"
#include "Result/ActionResult.h"
#include "Task/Rest/ActionTask.h"
#include "Task/WebSocket/ActionTask.h"

// ActionByUserId
#include "Request/ActionByUserIdRequest.h"
#include "Result/ActionByUserIdResult.h"
#include "Task/Rest/ActionByUserIdTask.h"
#include "Task/WebSocket/ActionByUserIdTask.h"

// Client
#include "Gs2MegaFieldRestClient.h"
#include "Gs2MegaFieldWebSocketClient.h"