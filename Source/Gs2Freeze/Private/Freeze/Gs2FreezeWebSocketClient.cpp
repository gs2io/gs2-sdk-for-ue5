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

#include "Freeze/Gs2FreezeWebSocketClient.h"

namespace Gs2::Freeze
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStagesTask>> FGs2FreezeWebSocketClient::DescribeStages(
        const Request::FDescribeStagesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeStagesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetStageTask>> FGs2FreezeWebSocketClient::GetStage(
        const Request::FGetStageRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetStageTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPromoteStageTask>> FGs2FreezeWebSocketClient::PromoteStage(
        const Request::FPromoteStageRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPromoteStageTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRollbackStageTask>> FGs2FreezeWebSocketClient::RollbackStage(
        const Request::FRollbackStageRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRollbackStageTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeOutputsTask>> FGs2FreezeWebSocketClient::DescribeOutputs(
        const Request::FDescribeOutputsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeOutputsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetOutputTask>> FGs2FreezeWebSocketClient::GetOutput(
        const Request::FGetOutputRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetOutputTask>>(
            Session,
            Request
        );
    }
}