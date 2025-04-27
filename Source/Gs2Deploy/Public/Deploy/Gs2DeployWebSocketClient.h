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
#include "Request/DescribeStacksRequest.h"
#include "Task/WebSocket/DescribeStacksTask.h"
#include "Request/PreCreateStackRequest.h"
#include "Task/WebSocket/PreCreateStackTask.h"
#include "Request/CreateStackRequest.h"
#include "Task/WebSocket/CreateStackTask.h"
#include "Request/CreateStackFromGitHubRequest.h"
#include "Task/WebSocket/CreateStackFromGitHubTask.h"
#include "Request/PreValidateRequest.h"
#include "Task/WebSocket/PreValidateTask.h"
#include "Request/ValidateRequest.h"
#include "Task/WebSocket/ValidateTask.h"
#include "Request/GetStackStatusRequest.h"
#include "Task/WebSocket/GetStackStatusTask.h"
#include "Request/GetStackRequest.h"
#include "Task/WebSocket/GetStackTask.h"
#include "Request/PreUpdateStackRequest.h"
#include "Task/WebSocket/PreUpdateStackTask.h"
#include "Request/UpdateStackRequest.h"
#include "Task/WebSocket/UpdateStackTask.h"
#include "Request/PreChangeSetRequest.h"
#include "Task/WebSocket/PreChangeSetTask.h"
#include "Request/ChangeSetRequest.h"
#include "Task/WebSocket/ChangeSetTask.h"
#include "Request/UpdateStackFromGitHubRequest.h"
#include "Task/WebSocket/UpdateStackFromGitHubTask.h"
#include "Request/DeleteStackRequest.h"
#include "Task/WebSocket/DeleteStackTask.h"
#include "Request/ForceDeleteStackRequest.h"
#include "Task/WebSocket/ForceDeleteStackTask.h"
#include "Request/DeleteStackResourcesRequest.h"
#include "Task/WebSocket/DeleteStackResourcesTask.h"
#include "Request/DeleteStackEntityRequest.h"
#include "Task/WebSocket/DeleteStackEntityTask.h"
#include "Request/DescribeResourcesRequest.h"
#include "Task/WebSocket/DescribeResourcesTask.h"
#include "Request/GetResourceRequest.h"
#include "Task/WebSocket/GetResourceTask.h"
#include "Request/DescribeEventsRequest.h"
#include "Task/WebSocket/DescribeEventsTask.h"
#include "Request/GetEventRequest.h"
#include "Task/WebSocket/GetEventTask.h"
#include "Request/DescribeOutputsRequest.h"
#include "Task/WebSocket/DescribeOutputsTask.h"
#include "Request/GetOutputRequest.h"
#include "Task/WebSocket/GetOutputTask.h"

namespace Gs2::Deploy
{
    class GS2DEPLOY_API FGs2DeployWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2DeployWebSocketClient(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session
        ): FAbstractWebSocketGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStacksTask>> DescribeStacks(
            const Request::FDescribeStacksRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPreCreateStackTask>> PreCreateStack(
            const Request::FPreCreateStackRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateStackTask>> CreateStack(
            const Request::FCreateStackRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateStackFromGitHubTask>> CreateStackFromGitHub(
            const Request::FCreateStackFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPreValidateTask>> PreValidate(
            const Request::FPreValidateRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FValidateTask>> Validate(
            const Request::FValidateRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStackStatusTask>> GetStackStatus(
            const Request::FGetStackStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStackTask>> GetStack(
            const Request::FGetStackRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPreUpdateStackTask>> PreUpdateStack(
            const Request::FPreUpdateStackRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateStackTask>> UpdateStack(
            const Request::FUpdateStackRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPreChangeSetTask>> PreChangeSet(
            const Request::FPreChangeSetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FChangeSetTask>> ChangeSet(
            const Request::FChangeSetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateStackFromGitHubTask>> UpdateStackFromGitHub(
            const Request::FUpdateStackFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteStackTask>> DeleteStack(
            const Request::FDeleteStackRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FForceDeleteStackTask>> ForceDeleteStack(
            const Request::FForceDeleteStackRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteStackResourcesTask>> DeleteStackResources(
            const Request::FDeleteStackResourcesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteStackEntityTask>> DeleteStackEntity(
            const Request::FDeleteStackEntityRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeResourcesTask>> DescribeResources(
            const Request::FDescribeResourcesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetResourceTask>> GetResource(
            const Request::FGetResourceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeEventsTask>> DescribeEvents(
            const Request::FDescribeEventsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetEventTask>> GetEvent(
            const Request::FGetEventRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeOutputsTask>> DescribeOutputs(
            const Request::FDescribeOutputsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetOutputTask>> GetOutput(
            const Request::FGetOutputRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2DeployWebSocketClient, ESPMode::ThreadSafe> FGs2DeployWebSocketClientPtr;
}