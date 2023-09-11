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
#include "Model/NodeModel.h"
#include "Model/NodeModelMaster.h"
#include "Model/Status.h"
#include "Model/CurrentTreeMaster.h"
#include "Model/Config.h"
#include "Model/ConsumeAction.h"
#include "Model/AcquireAction.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/ScriptSetting.h"
#include "Model/TransactionSetting.h"
#include "Model/LogSetting.h"

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

// DescribeNodeModels
#include "Request/DescribeNodeModelsRequest.h"
#include "Result/DescribeNodeModelsResult.h"
#include "Task/Rest/DescribeNodeModelsTask.h"
#include "Task/WebSocket/DescribeNodeModelsTask.h"

// GetNodeModel
#include "Request/GetNodeModelRequest.h"
#include "Result/GetNodeModelResult.h"
#include "Task/Rest/GetNodeModelTask.h"
#include "Task/WebSocket/GetNodeModelTask.h"

// DescribeNodeModelMasters
#include "Request/DescribeNodeModelMastersRequest.h"
#include "Result/DescribeNodeModelMastersResult.h"
#include "Task/Rest/DescribeNodeModelMastersTask.h"
#include "Task/WebSocket/DescribeNodeModelMastersTask.h"

// CreateNodeModelMaster
#include "Request/CreateNodeModelMasterRequest.h"
#include "Result/CreateNodeModelMasterResult.h"
#include "Task/Rest/CreateNodeModelMasterTask.h"
#include "Task/WebSocket/CreateNodeModelMasterTask.h"

// GetNodeModelMaster
#include "Request/GetNodeModelMasterRequest.h"
#include "Result/GetNodeModelMasterResult.h"
#include "Task/Rest/GetNodeModelMasterTask.h"
#include "Task/WebSocket/GetNodeModelMasterTask.h"

// UpdateNodeModelMaster
#include "Request/UpdateNodeModelMasterRequest.h"
#include "Result/UpdateNodeModelMasterResult.h"
#include "Task/Rest/UpdateNodeModelMasterTask.h"
#include "Task/WebSocket/UpdateNodeModelMasterTask.h"

// DeleteNodeModelMaster
#include "Request/DeleteNodeModelMasterRequest.h"
#include "Result/DeleteNodeModelMasterResult.h"
#include "Task/Rest/DeleteNodeModelMasterTask.h"
#include "Task/WebSocket/DeleteNodeModelMasterTask.h"

// MarkReleaseByUserId
#include "Request/MarkReleaseByUserIdRequest.h"
#include "Result/MarkReleaseByUserIdResult.h"
#include "Task/Rest/MarkReleaseByUserIdTask.h"
#include "Task/WebSocket/MarkReleaseByUserIdTask.h"

// Release
#include "Request/ReleaseRequest.h"
#include "Result/ReleaseResult.h"
#include "Task/Rest/ReleaseTask.h"
#include "Task/WebSocket/ReleaseTask.h"

// ReleaseByUserId
#include "Request/ReleaseByUserIdRequest.h"
#include "Result/ReleaseByUserIdResult.h"
#include "Task/Rest/ReleaseByUserIdTask.h"
#include "Task/WebSocket/ReleaseByUserIdTask.h"

// MarkRestrainByUserId
#include "Request/MarkRestrainByUserIdRequest.h"
#include "Result/MarkRestrainByUserIdResult.h"
#include "Task/Rest/MarkRestrainByUserIdTask.h"
#include "Task/WebSocket/MarkRestrainByUserIdTask.h"

// Restrain
#include "Request/RestrainRequest.h"
#include "Result/RestrainResult.h"
#include "Task/Rest/RestrainTask.h"
#include "Task/WebSocket/RestrainTask.h"

// RestrainByUserId
#include "Request/RestrainByUserIdRequest.h"
#include "Result/RestrainByUserIdResult.h"
#include "Task/Rest/RestrainByUserIdTask.h"
#include "Task/WebSocket/RestrainByUserIdTask.h"

// GetStatus
#include "Request/GetStatusRequest.h"
#include "Result/GetStatusResult.h"
#include "Task/Rest/GetStatusTask.h"
#include "Task/WebSocket/GetStatusTask.h"

// GetStatusByUserId
#include "Request/GetStatusByUserIdRequest.h"
#include "Result/GetStatusByUserIdResult.h"
#include "Task/Rest/GetStatusByUserIdTask.h"
#include "Task/WebSocket/GetStatusByUserIdTask.h"

// Reset
#include "Request/ResetRequest.h"
#include "Result/ResetResult.h"
#include "Task/Rest/ResetTask.h"
#include "Task/WebSocket/ResetTask.h"

// ResetByUserId
#include "Request/ResetByUserIdRequest.h"
#include "Result/ResetByUserIdResult.h"
#include "Task/Rest/ResetByUserIdTask.h"
#include "Task/WebSocket/ResetByUserIdTask.h"

// MarkReleaseByStampSheet
#include "Request/MarkReleaseByStampSheetRequest.h"
#include "Result/MarkReleaseByStampSheetResult.h"
#include "Task/Rest/MarkReleaseByStampSheetTask.h"
#include "Task/WebSocket/MarkReleaseByStampSheetTask.h"

// MarkRestrainByStampTask
#include "Request/MarkRestrainByStampTaskRequest.h"
#include "Result/MarkRestrainByStampTaskResult.h"
#include "Task/Rest/MarkRestrainByStampTaskTask.h"
#include "Task/WebSocket/MarkRestrainByStampTaskTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentTreeMaster
#include "Request/GetCurrentTreeMasterRequest.h"
#include "Result/GetCurrentTreeMasterResult.h"
#include "Task/Rest/GetCurrentTreeMasterTask.h"
#include "Task/WebSocket/GetCurrentTreeMasterTask.h"

// UpdateCurrentTreeMaster
#include "Request/UpdateCurrentTreeMasterRequest.h"
#include "Result/UpdateCurrentTreeMasterResult.h"
#include "Task/Rest/UpdateCurrentTreeMasterTask.h"
#include "Task/WebSocket/UpdateCurrentTreeMasterTask.h"

// UpdateCurrentTreeMasterFromGitHub
#include "Request/UpdateCurrentTreeMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentTreeMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentTreeMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentTreeMasterFromGitHubTask.h"

// Client
#include "Gs2SkillTreeRestClient.h"
#include "Gs2SkillTreeWebSocketClient.h"