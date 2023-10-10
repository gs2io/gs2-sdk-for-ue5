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
#include "Model/StateMachineMaster.h"
#include "Model/Status.h"
#include "Model/StackEntry.h"
#include "Model/Variable.h"
#include "Model/LogSetting.h"
#include "Model/ScriptSetting.h"

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

// DescribeStateMachineMasters
#include "Request/DescribeStateMachineMastersRequest.h"
#include "Result/DescribeStateMachineMastersResult.h"
#include "Task/Rest/DescribeStateMachineMastersTask.h"
#include "Task/WebSocket/DescribeStateMachineMastersTask.h"

// UpdateStateMachineMaster
#include "Request/UpdateStateMachineMasterRequest.h"
#include "Result/UpdateStateMachineMasterResult.h"
#include "Task/Rest/UpdateStateMachineMasterTask.h"
#include "Task/WebSocket/UpdateStateMachineMasterTask.h"

// GetStateMachineMaster
#include "Request/GetStateMachineMasterRequest.h"
#include "Result/GetStateMachineMasterResult.h"
#include "Task/Rest/GetStateMachineMasterTask.h"
#include "Task/WebSocket/GetStateMachineMasterTask.h"

// DeleteStateMachineMaster
#include "Request/DeleteStateMachineMasterRequest.h"
#include "Result/DeleteStateMachineMasterResult.h"
#include "Task/Rest/DeleteStateMachineMasterTask.h"
#include "Task/WebSocket/DeleteStateMachineMasterTask.h"

// DescribeStatuses
#include "Request/DescribeStatusesRequest.h"
#include "Result/DescribeStatusesResult.h"
#include "Task/Rest/DescribeStatusesTask.h"
#include "Task/WebSocket/DescribeStatusesTask.h"

// DescribeStatusesByUserId
#include "Request/DescribeStatusesByUserIdRequest.h"
#include "Result/DescribeStatusesByUserIdResult.h"
#include "Task/Rest/DescribeStatusesByUserIdTask.h"
#include "Task/WebSocket/DescribeStatusesByUserIdTask.h"

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

// StartStateMachineByUserId
#include "Request/StartStateMachineByUserIdRequest.h"
#include "Result/StartStateMachineByUserIdResult.h"
#include "Task/Rest/StartStateMachineByUserIdTask.h"
#include "Task/WebSocket/StartStateMachineByUserIdTask.h"

// StartStateMachineByStampSheet
#include "Request/StartStateMachineByStampSheetRequest.h"
#include "Result/StartStateMachineByStampSheetResult.h"
#include "Task/Rest/StartStateMachineByStampSheetTask.h"
#include "Task/WebSocket/StartStateMachineByStampSheetTask.h"

// Emit
#include "Request/EmitRequest.h"
#include "Result/EmitResult.h"
#include "Task/Rest/EmitTask.h"
#include "Task/WebSocket/EmitTask.h"

// EmitByUserId
#include "Request/EmitByUserIdRequest.h"
#include "Result/EmitByUserIdResult.h"
#include "Task/Rest/EmitByUserIdTask.h"
#include "Task/WebSocket/EmitByUserIdTask.h"

// DeleteStatusByUserId
#include "Request/DeleteStatusByUserIdRequest.h"
#include "Result/DeleteStatusByUserIdResult.h"
#include "Task/Rest/DeleteStatusByUserIdTask.h"
#include "Task/WebSocket/DeleteStatusByUserIdTask.h"

// ExitStateMachine
#include "Request/ExitStateMachineRequest.h"
#include "Result/ExitStateMachineResult.h"
#include "Task/Rest/ExitStateMachineTask.h"
#include "Task/WebSocket/ExitStateMachineTask.h"

// ExitStateMachineByUserId
#include "Request/ExitStateMachineByUserIdRequest.h"
#include "Result/ExitStateMachineByUserIdResult.h"
#include "Task/Rest/ExitStateMachineByUserIdTask.h"
#include "Task/WebSocket/ExitStateMachineByUserIdTask.h"

// Client
#include "Gs2StateMachineRestClient.h"
#include "Gs2StateMachineWebSocketClient.h"