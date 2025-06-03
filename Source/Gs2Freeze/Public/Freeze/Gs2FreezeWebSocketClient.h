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

#include "CoreMinimal.h"
#include "Core/Net/AbstractWebSocketGs2Client.h"
#include "Request/DescribeStagesRequest.h"
#include "Task/WebSocket/DescribeStagesTask.h"
#include "Request/GetStageRequest.h"
#include "Task/WebSocket/GetStageTask.h"
#include "Request/PromoteStageRequest.h"
#include "Task/WebSocket/PromoteStageTask.h"
#include "Request/RollbackStageRequest.h"
#include "Task/WebSocket/RollbackStageTask.h"
#include "Request/DescribeOutputsRequest.h"
#include "Task/WebSocket/DescribeOutputsTask.h"
#include "Request/GetOutputRequest.h"
#include "Task/WebSocket/GetOutputTask.h"

namespace Gs2::Freeze
{
    class GS2FREEZE_API FGs2FreezeWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2FreezeWebSocketClient(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session
        ): FAbstractWebSocketGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStagesTask>> DescribeStages(
            const Request::FDescribeStagesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStageTask>> GetStage(
            const Request::FGetStageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPromoteStageTask>> PromoteStage(
            const Request::FPromoteStageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRollbackStageTask>> RollbackStage(
            const Request::FRollbackStageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeOutputsTask>> DescribeOutputs(
            const Request::FDescribeOutputsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetOutputTask>> GetOutput(
            const Request::FGetOutputRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2FreezeWebSocketClient, ESPMode::ThreadSafe> FGs2FreezeWebSocketClientPtr;
}