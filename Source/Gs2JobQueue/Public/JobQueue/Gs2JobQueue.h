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
#include "Model/Job.h"
#include "Model/JobResult.h"
#include "Model/DeadLetterJob.h"
#include "Model/NotificationSetting.h"
#include "Model/LogSetting.h"
#include "Model/JobEntry.h"
#include "Model/JobResultBody.h"

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

// DescribeJobsByUserId
#include "Request/DescribeJobsByUserIdRequest.h"
#include "Result/DescribeJobsByUserIdResult.h"
#include "Task/Rest/DescribeJobsByUserIdTask.h"
#include "Task/WebSocket/DescribeJobsByUserIdTask.h"

// GetJobByUserId
#include "Request/GetJobByUserIdRequest.h"
#include "Result/GetJobByUserIdResult.h"
#include "Task/Rest/GetJobByUserIdTask.h"
#include "Task/WebSocket/GetJobByUserIdTask.h"

// PushByUserId
#include "Request/PushByUserIdRequest.h"
#include "Result/PushByUserIdResult.h"
#include "Task/Rest/PushByUserIdTask.h"
#include "Task/WebSocket/PushByUserIdTask.h"

// Run
#include "Request/RunRequest.h"
#include "Result/RunResult.h"
#include "Task/Rest/RunTask.h"
#include "Task/WebSocket/RunTask.h"

// RunByUserId
#include "Request/RunByUserIdRequest.h"
#include "Result/RunByUserIdResult.h"
#include "Task/Rest/RunByUserIdTask.h"
#include "Task/WebSocket/RunByUserIdTask.h"

// DeleteJobByUserId
#include "Request/DeleteJobByUserIdRequest.h"
#include "Result/DeleteJobByUserIdResult.h"
#include "Task/Rest/DeleteJobByUserIdTask.h"
#include "Task/WebSocket/DeleteJobByUserIdTask.h"

// PushByStampSheet
#include "Request/PushByStampSheetRequest.h"
#include "Result/PushByStampSheetResult.h"
#include "Task/Rest/PushByStampSheetTask.h"
#include "Task/WebSocket/PushByStampSheetTask.h"

// DeleteByStampTask
#include "Request/DeleteByStampTaskRequest.h"
#include "Result/DeleteByStampTaskResult.h"
#include "Task/Rest/DeleteByStampTaskTask.h"
#include "Task/WebSocket/DeleteByStampTaskTask.h"

// GetJobResult
#include "Request/GetJobResultRequest.h"
#include "Result/GetJobResultResult.h"
#include "Task/Rest/GetJobResultTask.h"
#include "Task/WebSocket/GetJobResultTask.h"

// GetJobResultByUserId
#include "Request/GetJobResultByUserIdRequest.h"
#include "Result/GetJobResultByUserIdResult.h"
#include "Task/Rest/GetJobResultByUserIdTask.h"
#include "Task/WebSocket/GetJobResultByUserIdTask.h"

// DescribeDeadLetterJobsByUserId
#include "Request/DescribeDeadLetterJobsByUserIdRequest.h"
#include "Result/DescribeDeadLetterJobsByUserIdResult.h"
#include "Task/Rest/DescribeDeadLetterJobsByUserIdTask.h"
#include "Task/WebSocket/DescribeDeadLetterJobsByUserIdTask.h"

// GetDeadLetterJobByUserId
#include "Request/GetDeadLetterJobByUserIdRequest.h"
#include "Result/GetDeadLetterJobByUserIdResult.h"
#include "Task/Rest/GetDeadLetterJobByUserIdTask.h"
#include "Task/WebSocket/GetDeadLetterJobByUserIdTask.h"

// DeleteDeadLetterJobByUserId
#include "Request/DeleteDeadLetterJobByUserIdRequest.h"
#include "Result/DeleteDeadLetterJobByUserIdResult.h"
#include "Task/Rest/DeleteDeadLetterJobByUserIdTask.h"
#include "Task/WebSocket/DeleteDeadLetterJobByUserIdTask.h"

// Client
#include "Gs2JobQueueRestClient.h"
#include "Gs2JobQueueWebSocketClient.h"