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
#include "Model/Stage.h"
#include "Model/Output.h"
#include "Model/Microservice.h"

// DescribeStages
#include "Request/DescribeStagesRequest.h"
#include "Result/DescribeStagesResult.h"
#include "Task/Rest/DescribeStagesTask.h"
#include "Task/WebSocket/DescribeStagesTask.h"

// GetStage
#include "Request/GetStageRequest.h"
#include "Result/GetStageResult.h"
#include "Task/Rest/GetStageTask.h"
#include "Task/WebSocket/GetStageTask.h"

// PromoteStage
#include "Request/PromoteStageRequest.h"
#include "Result/PromoteStageResult.h"
#include "Task/Rest/PromoteStageTask.h"
#include "Task/WebSocket/PromoteStageTask.h"

// RollbackStage
#include "Request/RollbackStageRequest.h"
#include "Result/RollbackStageResult.h"
#include "Task/Rest/RollbackStageTask.h"
#include "Task/WebSocket/RollbackStageTask.h"

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
#include "Gs2FreezeRestClient.h"
#include "Gs2FreezeWebSocketClient.h"