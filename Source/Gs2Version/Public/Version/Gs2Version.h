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
#include "Model/VersionModelMaster.h"
#include "Model/VersionModel.h"
#include "Model/AcceptVersion.h"
#include "Model/Status.h"
#include "Model/TargetVersion.h"
#include "Model/SignTargetVersion.h"
#include "Model/CurrentVersionMaster.h"
#include "Model/ScriptSetting.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/LogSetting.h"
#include "Model/Version.h"
#include "Model/ScheduleVersion.h"

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

// DescribeVersionModelMasters
#include "Request/DescribeVersionModelMastersRequest.h"
#include "Result/DescribeVersionModelMastersResult.h"
#include "Task/Rest/DescribeVersionModelMastersTask.h"
#include "Task/WebSocket/DescribeVersionModelMastersTask.h"

// CreateVersionModelMaster
#include "Request/CreateVersionModelMasterRequest.h"
#include "Result/CreateVersionModelMasterResult.h"
#include "Task/Rest/CreateVersionModelMasterTask.h"
#include "Task/WebSocket/CreateVersionModelMasterTask.h"

// GetVersionModelMaster
#include "Request/GetVersionModelMasterRequest.h"
#include "Result/GetVersionModelMasterResult.h"
#include "Task/Rest/GetVersionModelMasterTask.h"
#include "Task/WebSocket/GetVersionModelMasterTask.h"

// UpdateVersionModelMaster
#include "Request/UpdateVersionModelMasterRequest.h"
#include "Result/UpdateVersionModelMasterResult.h"
#include "Task/Rest/UpdateVersionModelMasterTask.h"
#include "Task/WebSocket/UpdateVersionModelMasterTask.h"

// DeleteVersionModelMaster
#include "Request/DeleteVersionModelMasterRequest.h"
#include "Result/DeleteVersionModelMasterResult.h"
#include "Task/Rest/DeleteVersionModelMasterTask.h"
#include "Task/WebSocket/DeleteVersionModelMasterTask.h"

// DescribeVersionModels
#include "Request/DescribeVersionModelsRequest.h"
#include "Result/DescribeVersionModelsResult.h"
#include "Task/Rest/DescribeVersionModelsTask.h"
#include "Task/WebSocket/DescribeVersionModelsTask.h"

// GetVersionModel
#include "Request/GetVersionModelRequest.h"
#include "Result/GetVersionModelResult.h"
#include "Task/Rest/GetVersionModelTask.h"
#include "Task/WebSocket/GetVersionModelTask.h"

// DescribeAcceptVersions
#include "Request/DescribeAcceptVersionsRequest.h"
#include "Result/DescribeAcceptVersionsResult.h"
#include "Task/Rest/DescribeAcceptVersionsTask.h"
#include "Task/WebSocket/DescribeAcceptVersionsTask.h"

// DescribeAcceptVersionsByUserId
#include "Request/DescribeAcceptVersionsByUserIdRequest.h"
#include "Result/DescribeAcceptVersionsByUserIdResult.h"
#include "Task/Rest/DescribeAcceptVersionsByUserIdTask.h"
#include "Task/WebSocket/DescribeAcceptVersionsByUserIdTask.h"

// Accept
#include "Request/AcceptRequest.h"
#include "Result/AcceptResult.h"
#include "Task/Rest/AcceptTask.h"
#include "Task/WebSocket/AcceptTask.h"

// AcceptByUserId
#include "Request/AcceptByUserIdRequest.h"
#include "Result/AcceptByUserIdResult.h"
#include "Task/Rest/AcceptByUserIdTask.h"
#include "Task/WebSocket/AcceptByUserIdTask.h"

// GetAcceptVersion
#include "Request/GetAcceptVersionRequest.h"
#include "Result/GetAcceptVersionResult.h"
#include "Task/Rest/GetAcceptVersionTask.h"
#include "Task/WebSocket/GetAcceptVersionTask.h"

// GetAcceptVersionByUserId
#include "Request/GetAcceptVersionByUserIdRequest.h"
#include "Result/GetAcceptVersionByUserIdResult.h"
#include "Task/Rest/GetAcceptVersionByUserIdTask.h"
#include "Task/WebSocket/GetAcceptVersionByUserIdTask.h"

// DeleteAcceptVersion
#include "Request/DeleteAcceptVersionRequest.h"
#include "Result/DeleteAcceptVersionResult.h"
#include "Task/Rest/DeleteAcceptVersionTask.h"
#include "Task/WebSocket/DeleteAcceptVersionTask.h"

// DeleteAcceptVersionByUserId
#include "Request/DeleteAcceptVersionByUserIdRequest.h"
#include "Result/DeleteAcceptVersionByUserIdResult.h"
#include "Task/Rest/DeleteAcceptVersionByUserIdTask.h"
#include "Task/WebSocket/DeleteAcceptVersionByUserIdTask.h"

// CheckVersion
#include "Request/CheckVersionRequest.h"
#include "Result/CheckVersionResult.h"
#include "Task/Rest/CheckVersionTask.h"
#include "Task/WebSocket/CheckVersionTask.h"

// CheckVersionByUserId
#include "Request/CheckVersionByUserIdRequest.h"
#include "Result/CheckVersionByUserIdResult.h"
#include "Task/Rest/CheckVersionByUserIdTask.h"
#include "Task/WebSocket/CheckVersionByUserIdTask.h"

// CalculateSignature
#include "Request/CalculateSignatureRequest.h"
#include "Result/CalculateSignatureResult.h"
#include "Task/Rest/CalculateSignatureTask.h"
#include "Task/WebSocket/CalculateSignatureTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentVersionMaster
#include "Request/GetCurrentVersionMasterRequest.h"
#include "Result/GetCurrentVersionMasterResult.h"
#include "Task/Rest/GetCurrentVersionMasterTask.h"
#include "Task/WebSocket/GetCurrentVersionMasterTask.h"

// UpdateCurrentVersionMaster
#include "Request/UpdateCurrentVersionMasterRequest.h"
#include "Result/UpdateCurrentVersionMasterResult.h"
#include "Task/Rest/UpdateCurrentVersionMasterTask.h"
#include "Task/WebSocket/UpdateCurrentVersionMasterTask.h"

// UpdateCurrentVersionMasterFromGitHub
#include "Request/UpdateCurrentVersionMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentVersionMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentVersionMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentVersionMasterFromGitHubTask.h"

// Client
#include "Gs2VersionRestClient.h"
#include "Gs2VersionWebSocketClient.h"