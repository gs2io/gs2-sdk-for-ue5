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
#include "Model/News.h"
#include "Model/SetCookieRequestEntry.h"
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

// PrepareUpdateCurrentNewsMaster
#include "Request/PrepareUpdateCurrentNewsMasterRequest.h"
#include "Result/PrepareUpdateCurrentNewsMasterResult.h"
#include "Task/Rest/PrepareUpdateCurrentNewsMasterTask.h"
#include "Task/WebSocket/PrepareUpdateCurrentNewsMasterTask.h"

// UpdateCurrentNewsMaster
#include "Request/UpdateCurrentNewsMasterRequest.h"
#include "Result/UpdateCurrentNewsMasterResult.h"
#include "Task/Rest/UpdateCurrentNewsMasterTask.h"
#include "Task/WebSocket/UpdateCurrentNewsMasterTask.h"

// PrepareUpdateCurrentNewsMasterFromGitHub
#include "Request/PrepareUpdateCurrentNewsMasterFromGitHubRequest.h"
#include "Result/PrepareUpdateCurrentNewsMasterFromGitHubResult.h"
#include "Task/Rest/PrepareUpdateCurrentNewsMasterFromGitHubTask.h"
#include "Task/WebSocket/PrepareUpdateCurrentNewsMasterFromGitHubTask.h"

// DescribeNews
#include "Request/DescribeNewsRequest.h"
#include "Result/DescribeNewsResult.h"
#include "Task/Rest/DescribeNewsTask.h"
#include "Task/WebSocket/DescribeNewsTask.h"

// DescribeNewsByUserId
#include "Request/DescribeNewsByUserIdRequest.h"
#include "Result/DescribeNewsByUserIdResult.h"
#include "Task/Rest/DescribeNewsByUserIdTask.h"
#include "Task/WebSocket/DescribeNewsByUserIdTask.h"

// WantGrant
#include "Request/WantGrantRequest.h"
#include "Result/WantGrantResult.h"
#include "Task/Rest/WantGrantTask.h"
#include "Task/WebSocket/WantGrantTask.h"

// WantGrantByUserId
#include "Request/WantGrantByUserIdRequest.h"
#include "Result/WantGrantByUserIdResult.h"
#include "Task/Rest/WantGrantByUserIdTask.h"
#include "Task/WebSocket/WantGrantByUserIdTask.h"

// Client
#include "Gs2NewsRestClient.h"
#include "Gs2NewsWebSocketClient.h"