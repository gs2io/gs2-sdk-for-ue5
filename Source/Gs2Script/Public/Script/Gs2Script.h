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
#include "Model/Script.h"
#include "Model/RandomStatus.h"
#include "Model/RandomUsed.h"
#include "Model/AcquireAction.h"
#include "Model/ConsumeAction.h"
#include "Model/VerifyAction.h"
#include "Model/Transaction.h"
#include "Model/VerifyActionResult.h"
#include "Model/ConsumeActionResult.h"
#include "Model/AcquireActionResult.h"
#include "Model/TransactionResult.h"
#include "Model/TransactionSetting.h"
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

// DescribeScripts
#include "Request/DescribeScriptsRequest.h"
#include "Result/DescribeScriptsResult.h"
#include "Task/Rest/DescribeScriptsTask.h"
#include "Task/WebSocket/DescribeScriptsTask.h"

// CreateScript
#include "Request/CreateScriptRequest.h"
#include "Result/CreateScriptResult.h"
#include "Task/Rest/CreateScriptTask.h"
#include "Task/WebSocket/CreateScriptTask.h"

// CreateScriptFromGitHub
#include "Request/CreateScriptFromGitHubRequest.h"
#include "Result/CreateScriptFromGitHubResult.h"
#include "Task/Rest/CreateScriptFromGitHubTask.h"
#include "Task/WebSocket/CreateScriptFromGitHubTask.h"

// GetScript
#include "Request/GetScriptRequest.h"
#include "Result/GetScriptResult.h"
#include "Task/Rest/GetScriptTask.h"
#include "Task/WebSocket/GetScriptTask.h"

// UpdateScript
#include "Request/UpdateScriptRequest.h"
#include "Result/UpdateScriptResult.h"
#include "Task/Rest/UpdateScriptTask.h"
#include "Task/WebSocket/UpdateScriptTask.h"

// UpdateScriptFromGitHub
#include "Request/UpdateScriptFromGitHubRequest.h"
#include "Result/UpdateScriptFromGitHubResult.h"
#include "Task/Rest/UpdateScriptFromGitHubTask.h"
#include "Task/WebSocket/UpdateScriptFromGitHubTask.h"

// DeleteScript
#include "Request/DeleteScriptRequest.h"
#include "Result/DeleteScriptResult.h"
#include "Task/Rest/DeleteScriptTask.h"
#include "Task/WebSocket/DeleteScriptTask.h"

// InvokeScript
#include "Request/InvokeScriptRequest.h"
#include "Result/InvokeScriptResult.h"
#include "Task/Rest/InvokeScriptTask.h"
#include "Task/WebSocket/InvokeScriptTask.h"

// DebugInvoke
#include "Request/DebugInvokeRequest.h"
#include "Result/DebugInvokeResult.h"
#include "Task/Rest/DebugInvokeTask.h"
#include "Task/WebSocket/DebugInvokeTask.h"

// InvokeByStampSheet
#include "Request/InvokeByStampSheetRequest.h"
#include "Result/InvokeByStampSheetResult.h"
#include "Task/Rest/InvokeByStampSheetTask.h"
#include "Task/WebSocket/InvokeByStampSheetTask.h"

// Client
#include "Gs2ScriptRestClient.h"
#include "Gs2ScriptWebSocketClient.h"