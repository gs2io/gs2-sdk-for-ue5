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
#include "Model/Room.h"
#include "Model/NotificationSetting.h"
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

// Now
#include "Request/NowRequest.h"
#include "Result/NowResult.h"
#include "Task/Rest/NowTask.h"
#include "Task/WebSocket/NowTask.h"

// DescribeRooms
#include "Request/DescribeRoomsRequest.h"
#include "Result/DescribeRoomsResult.h"
#include "Task/Rest/DescribeRoomsTask.h"
#include "Task/WebSocket/DescribeRoomsTask.h"

// WantRoom
#include "Request/WantRoomRequest.h"
#include "Result/WantRoomResult.h"
#include "Task/Rest/WantRoomTask.h"
#include "Task/WebSocket/WantRoomTask.h"

// GetRoom
#include "Request/GetRoomRequest.h"
#include "Result/GetRoomResult.h"
#include "Task/Rest/GetRoomTask.h"
#include "Task/WebSocket/GetRoomTask.h"

// DeleteRoom
#include "Request/DeleteRoomRequest.h"
#include "Result/DeleteRoomResult.h"
#include "Task/Rest/DeleteRoomTask.h"
#include "Task/WebSocket/DeleteRoomTask.h"

// Client
#include "Gs2RealtimeRestClient.h"
#include "Gs2RealtimeWebSocketClient.h"