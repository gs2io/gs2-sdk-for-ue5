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
#include "Model/BuffTargetModel.h"
#include "Model/BuffTargetAction.h"
#include "Model/BuffTargetGrn.h"
#include "Model/BuffEntryModel.h"
#include "Model/BuffEntryModelMaster.h"
#include "Model/CurrentBuffMaster.h"
#include "Model/OverrideBuffRate.h"
#include "Model/ScriptSetting.h"
#include "Model/GitHubCheckoutSetting.h"
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

// DumpUserDataByUserId
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Result/DumpUserDataByUserIdResult.h"
#include "Task/Rest/DumpUserDataByUserIdTask.h"
#include "Task/WebSocket/DumpUserDataByUserIdTask.h"

// CheckDumpUserDataByUserId
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Result/CheckDumpUserDataByUserIdResult.h"
#include "Task/Rest/CheckDumpUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckDumpUserDataByUserIdTask.h"

// CleanUserDataByUserId
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Result/CleanUserDataByUserIdResult.h"
#include "Task/Rest/CleanUserDataByUserIdTask.h"
#include "Task/WebSocket/CleanUserDataByUserIdTask.h"

// CheckCleanUserDataByUserId
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Result/CheckCleanUserDataByUserIdResult.h"
#include "Task/Rest/CheckCleanUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckCleanUserDataByUserIdTask.h"

// PrepareImportUserDataByUserId
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Result/PrepareImportUserDataByUserIdResult.h"
#include "Task/Rest/PrepareImportUserDataByUserIdTask.h"
#include "Task/WebSocket/PrepareImportUserDataByUserIdTask.h"

// ImportUserDataByUserId
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Result/ImportUserDataByUserIdResult.h"
#include "Task/Rest/ImportUserDataByUserIdTask.h"
#include "Task/WebSocket/ImportUserDataByUserIdTask.h"

// CheckImportUserDataByUserId
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Result/CheckImportUserDataByUserIdResult.h"
#include "Task/Rest/CheckImportUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckImportUserDataByUserIdTask.h"

// DescribeBuffEntryModels
#include "Request/DescribeBuffEntryModelsRequest.h"
#include "Result/DescribeBuffEntryModelsResult.h"
#include "Task/Rest/DescribeBuffEntryModelsTask.h"
#include "Task/WebSocket/DescribeBuffEntryModelsTask.h"

// GetBuffEntryModel
#include "Request/GetBuffEntryModelRequest.h"
#include "Result/GetBuffEntryModelResult.h"
#include "Task/Rest/GetBuffEntryModelTask.h"
#include "Task/WebSocket/GetBuffEntryModelTask.h"

// DescribeBuffEntryModelMasters
#include "Request/DescribeBuffEntryModelMastersRequest.h"
#include "Result/DescribeBuffEntryModelMastersResult.h"
#include "Task/Rest/DescribeBuffEntryModelMastersTask.h"
#include "Task/WebSocket/DescribeBuffEntryModelMastersTask.h"

// CreateBuffEntryModelMaster
#include "Request/CreateBuffEntryModelMasterRequest.h"
#include "Result/CreateBuffEntryModelMasterResult.h"
#include "Task/Rest/CreateBuffEntryModelMasterTask.h"
#include "Task/WebSocket/CreateBuffEntryModelMasterTask.h"

// GetBuffEntryModelMaster
#include "Request/GetBuffEntryModelMasterRequest.h"
#include "Result/GetBuffEntryModelMasterResult.h"
#include "Task/Rest/GetBuffEntryModelMasterTask.h"
#include "Task/WebSocket/GetBuffEntryModelMasterTask.h"

// UpdateBuffEntryModelMaster
#include "Request/UpdateBuffEntryModelMasterRequest.h"
#include "Result/UpdateBuffEntryModelMasterResult.h"
#include "Task/Rest/UpdateBuffEntryModelMasterTask.h"
#include "Task/WebSocket/UpdateBuffEntryModelMasterTask.h"

// DeleteBuffEntryModelMaster
#include "Request/DeleteBuffEntryModelMasterRequest.h"
#include "Result/DeleteBuffEntryModelMasterResult.h"
#include "Task/Rest/DeleteBuffEntryModelMasterTask.h"
#include "Task/WebSocket/DeleteBuffEntryModelMasterTask.h"

// ApplyBuff
#include "Request/ApplyBuffRequest.h"
#include "Result/ApplyBuffResult.h"
#include "Task/Rest/ApplyBuffTask.h"
#include "Task/WebSocket/ApplyBuffTask.h"

// ApplyBuffByUserId
#include "Request/ApplyBuffByUserIdRequest.h"
#include "Result/ApplyBuffByUserIdResult.h"
#include "Task/Rest/ApplyBuffByUserIdTask.h"
#include "Task/WebSocket/ApplyBuffByUserIdTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentBuffMaster
#include "Request/GetCurrentBuffMasterRequest.h"
#include "Result/GetCurrentBuffMasterResult.h"
#include "Task/Rest/GetCurrentBuffMasterTask.h"
#include "Task/WebSocket/GetCurrentBuffMasterTask.h"

// UpdateCurrentBuffMaster
#include "Request/UpdateCurrentBuffMasterRequest.h"
#include "Result/UpdateCurrentBuffMasterResult.h"
#include "Task/Rest/UpdateCurrentBuffMasterTask.h"
#include "Task/WebSocket/UpdateCurrentBuffMasterTask.h"

// UpdateCurrentBuffMasterFromGitHub
#include "Request/UpdateCurrentBuffMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentBuffMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentBuffMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentBuffMasterFromGitHubTask.h"

// Client
#include "Gs2BuffRestClient.h"
#include "Gs2BuffWebSocketClient.h"