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
#include "Model/Mutex.h"
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

// GetServiceVersion
#include "Request/GetServiceVersionRequest.h"
#include "Result/GetServiceVersionResult.h"
#include "Task/Rest/GetServiceVersionTask.h"
#include "Task/WebSocket/GetServiceVersionTask.h"

// Lock
#include "Request/LockRequest.h"
#include "Result/LockResult.h"
#include "Task/Rest/LockTask.h"
#include "Task/WebSocket/LockTask.h"

// LockByUserId
#include "Request/LockByUserIdRequest.h"
#include "Result/LockByUserIdResult.h"
#include "Task/Rest/LockByUserIdTask.h"
#include "Task/WebSocket/LockByUserIdTask.h"

// Unlock
#include "Request/UnlockRequest.h"
#include "Result/UnlockResult.h"
#include "Task/Rest/UnlockTask.h"
#include "Task/WebSocket/UnlockTask.h"

// UnlockByUserId
#include "Request/UnlockByUserIdRequest.h"
#include "Result/UnlockByUserIdResult.h"
#include "Task/Rest/UnlockByUserIdTask.h"
#include "Task/WebSocket/UnlockByUserIdTask.h"

// GetMutex
#include "Request/GetMutexRequest.h"
#include "Result/GetMutexResult.h"
#include "Task/Rest/GetMutexTask.h"
#include "Task/WebSocket/GetMutexTask.h"

// GetMutexByUserId
#include "Request/GetMutexByUserIdRequest.h"
#include "Result/GetMutexByUserIdResult.h"
#include "Task/Rest/GetMutexByUserIdTask.h"
#include "Task/WebSocket/GetMutexByUserIdTask.h"

// DeleteMutexByUserId
#include "Request/DeleteMutexByUserIdRequest.h"
#include "Result/DeleteMutexByUserIdResult.h"
#include "Task/Rest/DeleteMutexByUserIdTask.h"
#include "Task/WebSocket/DeleteMutexByUserIdTask.h"

// Client
#include "Gs2LockRestClient.h"
#include "Gs2LockWebSocketClient.h"