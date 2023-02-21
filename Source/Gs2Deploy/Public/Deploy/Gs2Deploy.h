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
#include "Model/Stack.h"
#include "Model/Resource.h"
#include "Model/Event.h"
#include "Model/Output.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/OutputField.h"

// DescribeStacks
#include "Request/DescribeStacksRequest.h"
#include "Result/DescribeStacksResult.h"
#include "Task/Rest/DescribeStacksTask.h"
#include "Task/WebSocket/DescribeStacksTask.h"

// CreateStack
#include "Request/CreateStackRequest.h"
#include "Result/CreateStackResult.h"
#include "Task/Rest/CreateStackTask.h"
#include "Task/WebSocket/CreateStackTask.h"

// CreateStackFromGitHub
#include "Request/CreateStackFromGitHubRequest.h"
#include "Result/CreateStackFromGitHubResult.h"
#include "Task/Rest/CreateStackFromGitHubTask.h"
#include "Task/WebSocket/CreateStackFromGitHubTask.h"

// Validate
#include "Request/ValidateRequest.h"
#include "Result/ValidateResult.h"
#include "Task/Rest/ValidateTask.h"
#include "Task/WebSocket/ValidateTask.h"

// GetStackStatus
#include "Request/GetStackStatusRequest.h"
#include "Result/GetStackStatusResult.h"
#include "Task/Rest/GetStackStatusTask.h"
#include "Task/WebSocket/GetStackStatusTask.h"

// GetStack
#include "Request/GetStackRequest.h"
#include "Result/GetStackResult.h"
#include "Task/Rest/GetStackTask.h"
#include "Task/WebSocket/GetStackTask.h"

// UpdateStack
#include "Request/UpdateStackRequest.h"
#include "Result/UpdateStackResult.h"
#include "Task/Rest/UpdateStackTask.h"
#include "Task/WebSocket/UpdateStackTask.h"

// UpdateStackFromGitHub
#include "Request/UpdateStackFromGitHubRequest.h"
#include "Result/UpdateStackFromGitHubResult.h"
#include "Task/Rest/UpdateStackFromGitHubTask.h"
#include "Task/WebSocket/UpdateStackFromGitHubTask.h"

// DeleteStack
#include "Request/DeleteStackRequest.h"
#include "Result/DeleteStackResult.h"
#include "Task/Rest/DeleteStackTask.h"
#include "Task/WebSocket/DeleteStackTask.h"

// ForceDeleteStack
#include "Request/ForceDeleteStackRequest.h"
#include "Result/ForceDeleteStackResult.h"
#include "Task/Rest/ForceDeleteStackTask.h"
#include "Task/WebSocket/ForceDeleteStackTask.h"

// DeleteStackResources
#include "Request/DeleteStackResourcesRequest.h"
#include "Result/DeleteStackResourcesResult.h"
#include "Task/Rest/DeleteStackResourcesTask.h"
#include "Task/WebSocket/DeleteStackResourcesTask.h"

// DeleteStackEntity
#include "Request/DeleteStackEntityRequest.h"
#include "Result/DeleteStackEntityResult.h"
#include "Task/Rest/DeleteStackEntityTask.h"
#include "Task/WebSocket/DeleteStackEntityTask.h"

// DescribeResources
#include "Request/DescribeResourcesRequest.h"
#include "Result/DescribeResourcesResult.h"
#include "Task/Rest/DescribeResourcesTask.h"
#include "Task/WebSocket/DescribeResourcesTask.h"

// GetResource
#include "Request/GetResourceRequest.h"
#include "Result/GetResourceResult.h"
#include "Task/Rest/GetResourceTask.h"
#include "Task/WebSocket/GetResourceTask.h"

// DescribeEvents
#include "Request/DescribeEventsRequest.h"
#include "Result/DescribeEventsResult.h"
#include "Task/Rest/DescribeEventsTask.h"
#include "Task/WebSocket/DescribeEventsTask.h"

// GetEvent
#include "Request/GetEventRequest.h"
#include "Result/GetEventResult.h"
#include "Task/Rest/GetEventTask.h"
#include "Task/WebSocket/GetEventTask.h"

// DescribeOutputs
#include "Request/DescribeOutputsRequest.h"
#include "Result/DescribeOutputsResult.h"
#include "Task/Rest/DescribeOutputsTask.h"
#include "Task/WebSocket/DescribeOutputsTask.h"

// GetOutput
#include "Request/GetOutputRequest.h"
#include "Result/GetOutputResult.h"
#include "Task/Rest/GetOutputTask.h"
#include "Task/WebSocket/GetOutputTask.h"

// Client
#include "Gs2DeployRestClient.h"
#include "Gs2DeployWebSocketClient.h"