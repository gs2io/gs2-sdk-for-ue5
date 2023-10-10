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
#include "Model/Point.h"
#include "Model/History.h"
#include "Model/AdMob.h"
#include "Model/UnityAd.h"
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

// GetPoint
#include "Request/GetPointRequest.h"
#include "Result/GetPointResult.h"
#include "Task/Rest/GetPointTask.h"
#include "Task/WebSocket/GetPointTask.h"

// GetPointByUserId
#include "Request/GetPointByUserIdRequest.h"
#include "Result/GetPointByUserIdResult.h"
#include "Task/Rest/GetPointByUserIdTask.h"
#include "Task/WebSocket/GetPointByUserIdTask.h"

// AcquirePointByUserId
#include "Request/AcquirePointByUserIdRequest.h"
#include "Result/AcquirePointByUserIdResult.h"
#include "Task/Rest/AcquirePointByUserIdTask.h"
#include "Task/WebSocket/AcquirePointByUserIdTask.h"

// ConsumePoint
#include "Request/ConsumePointRequest.h"
#include "Result/ConsumePointResult.h"
#include "Task/Rest/ConsumePointTask.h"
#include "Task/WebSocket/ConsumePointTask.h"

// ConsumePointByUserId
#include "Request/ConsumePointByUserIdRequest.h"
#include "Result/ConsumePointByUserIdResult.h"
#include "Task/Rest/ConsumePointByUserIdTask.h"
#include "Task/WebSocket/ConsumePointByUserIdTask.h"

// DeletePointByUserId
#include "Request/DeletePointByUserIdRequest.h"
#include "Result/DeletePointByUserIdResult.h"
#include "Task/Rest/DeletePointByUserIdTask.h"
#include "Task/WebSocket/DeletePointByUserIdTask.h"

// ConsumePointByStampTask
#include "Request/ConsumePointByStampTaskRequest.h"
#include "Result/ConsumePointByStampTaskResult.h"
#include "Task/Rest/ConsumePointByStampTaskTask.h"
#include "Task/WebSocket/ConsumePointByStampTaskTask.h"

// AcquirePointByStampSheet
#include "Request/AcquirePointByStampSheetRequest.h"
#include "Result/AcquirePointByStampSheetResult.h"
#include "Task/Rest/AcquirePointByStampSheetTask.h"
#include "Task/WebSocket/AcquirePointByStampSheetTask.h"

// Client
#include "Gs2AdRewardRestClient.h"
#include "Gs2AdRewardWebSocketClient.h"