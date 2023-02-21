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
#include "Model/WebSocketSession.h"
#include "Model/FirebaseToken.h"
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

// DescribeWebSocketSessions
#include "Request/DescribeWebSocketSessionsRequest.h"
#include "Result/DescribeWebSocketSessionsResult.h"
#include "Task/Rest/DescribeWebSocketSessionsTask.h"
#include "Task/WebSocket/DescribeWebSocketSessionsTask.h"

// DescribeWebSocketSessionsByUserId
#include "Request/DescribeWebSocketSessionsByUserIdRequest.h"
#include "Result/DescribeWebSocketSessionsByUserIdResult.h"
#include "Task/Rest/DescribeWebSocketSessionsByUserIdTask.h"
#include "Task/WebSocket/DescribeWebSocketSessionsByUserIdTask.h"

// SetUserId
#include "Request/SetUserIdRequest.h"
#include "Result/SetUserIdResult.h"
#include "Task/Rest/SetUserIdTask.h"
#include "Task/WebSocket/SetUserIdTask.h"

// SetUserIdByUserId
#include "Request/SetUserIdByUserIdRequest.h"
#include "Result/SetUserIdByUserIdResult.h"
#include "Task/Rest/SetUserIdByUserIdTask.h"
#include "Task/WebSocket/SetUserIdByUserIdTask.h"

// SendNotification
#include "Request/SendNotificationRequest.h"
#include "Result/SendNotificationResult.h"
#include "Task/Rest/SendNotificationTask.h"
#include "Task/WebSocket/SendNotificationTask.h"

// DisconnectByUserId
#include "Request/DisconnectByUserIdRequest.h"
#include "Result/DisconnectByUserIdResult.h"
#include "Task/Rest/DisconnectByUserIdTask.h"
#include "Task/WebSocket/DisconnectByUserIdTask.h"

// DisconnectAll
#include "Request/DisconnectAllRequest.h"
#include "Result/DisconnectAllResult.h"
#include "Task/Rest/DisconnectAllTask.h"
#include "Task/WebSocket/DisconnectAllTask.h"

// SetFirebaseToken
#include "Request/SetFirebaseTokenRequest.h"
#include "Result/SetFirebaseTokenResult.h"
#include "Task/Rest/SetFirebaseTokenTask.h"
#include "Task/WebSocket/SetFirebaseTokenTask.h"

// SetFirebaseTokenByUserId
#include "Request/SetFirebaseTokenByUserIdRequest.h"
#include "Result/SetFirebaseTokenByUserIdResult.h"
#include "Task/Rest/SetFirebaseTokenByUserIdTask.h"
#include "Task/WebSocket/SetFirebaseTokenByUserIdTask.h"

// GetFirebaseToken
#include "Request/GetFirebaseTokenRequest.h"
#include "Result/GetFirebaseTokenResult.h"
#include "Task/Rest/GetFirebaseTokenTask.h"
#include "Task/WebSocket/GetFirebaseTokenTask.h"

// GetFirebaseTokenByUserId
#include "Request/GetFirebaseTokenByUserIdRequest.h"
#include "Result/GetFirebaseTokenByUserIdResult.h"
#include "Task/Rest/GetFirebaseTokenByUserIdTask.h"
#include "Task/WebSocket/GetFirebaseTokenByUserIdTask.h"

// DeleteFirebaseToken
#include "Request/DeleteFirebaseTokenRequest.h"
#include "Result/DeleteFirebaseTokenResult.h"
#include "Task/Rest/DeleteFirebaseTokenTask.h"
#include "Task/WebSocket/DeleteFirebaseTokenTask.h"

// DeleteFirebaseTokenByUserId
#include "Request/DeleteFirebaseTokenByUserIdRequest.h"
#include "Result/DeleteFirebaseTokenByUserIdResult.h"
#include "Task/Rest/DeleteFirebaseTokenByUserIdTask.h"
#include "Task/WebSocket/DeleteFirebaseTokenByUserIdTask.h"

// SendMobileNotificationByUserId
#include "Request/SendMobileNotificationByUserIdRequest.h"
#include "Result/SendMobileNotificationByUserIdResult.h"
#include "Task/Rest/SendMobileNotificationByUserIdTask.h"
#include "Task/WebSocket/SendMobileNotificationByUserIdTask.h"

// Client
#include "Gs2GatewayRestClient.h"
#include "Gs2GatewayWebSocketClient.h"