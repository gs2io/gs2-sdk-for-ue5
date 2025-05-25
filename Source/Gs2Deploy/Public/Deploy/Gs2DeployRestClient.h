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
#include "Core/Net/AbstractGs2Client.h"
#include "Request/DescribeStacksRequest.h"
#include "Task/Rest/DescribeStacksTask.h"
#include "Request/PreCreateStackRequest.h"
#include "Task/Rest/PreCreateStackTask.h"
#include "Request/CreateStackRequest.h"
#include "Task/Rest/CreateStackTask.h"
#include "Request/CreateStackFromGitHubRequest.h"
#include "Task/Rest/CreateStackFromGitHubTask.h"
#include "Request/PreValidateRequest.h"
#include "Task/Rest/PreValidateTask.h"
#include "Request/ValidateRequest.h"
#include "Task/Rest/ValidateTask.h"
#include "Request/GetStackStatusRequest.h"
#include "Task/Rest/GetStackStatusTask.h"
#include "Request/GetStackRequest.h"
#include "Task/Rest/GetStackTask.h"
#include "Request/PreUpdateStackRequest.h"
#include "Task/Rest/PreUpdateStackTask.h"
#include "Request/UpdateStackRequest.h"
#include "Task/Rest/UpdateStackTask.h"
#include "Request/PreChangeSetRequest.h"
#include "Task/Rest/PreChangeSetTask.h"
#include "Request/ChangeSetRequest.h"
#include "Task/Rest/ChangeSetTask.h"
#include "Request/UpdateStackFromGitHubRequest.h"
#include "Task/Rest/UpdateStackFromGitHubTask.h"
#include "Request/DeleteStackRequest.h"
#include "Task/Rest/DeleteStackTask.h"
#include "Request/ForceDeleteStackRequest.h"
#include "Task/Rest/ForceDeleteStackTask.h"
#include "Request/DeleteStackResourcesRequest.h"
#include "Task/Rest/DeleteStackResourcesTask.h"
#include "Request/DeleteStackEntityRequest.h"
#include "Task/Rest/DeleteStackEntityTask.h"
#include "Request/GetServiceVersionRequest.h"
#include "Task/Rest/GetServiceVersionTask.h"
#include "Request/DescribeResourcesRequest.h"
#include "Task/Rest/DescribeResourcesTask.h"
#include "Request/GetResourceRequest.h"
#include "Task/Rest/GetResourceTask.h"
#include "Request/DescribeEventsRequest.h"
#include "Task/Rest/DescribeEventsTask.h"
#include "Request/GetEventRequest.h"
#include "Task/Rest/GetEventTask.h"
#include "Request/DescribeOutputsRequest.h"
#include "Task/Rest/DescribeOutputsTask.h"
#include "Request/GetOutputRequest.h"
#include "Task/Rest/GetOutputTask.h"

namespace Gs2::Deploy
{
    class GS2DEPLOY_API FGs2DeployRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2DeployRestClient(
            const Core::Net::Rest::FGs2RestSessionPtr Session
        ): FAbstractGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeStacksTask>> DescribeStacks(
            const Request::FDescribeStacksRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPreCreateStackTask>> PreCreateStack(
            const Request::FPreCreateStackRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateStackTask>> CreateStack(
            const Request::FCreateStackRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateStackFromGitHubTask>> CreateStackFromGitHub(
            const Request::FCreateStackFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPreValidateTask>> PreValidate(
            const Request::FPreValidateRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FValidateTask>> Validate(
            const Request::FValidateRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStackStatusTask>> GetStackStatus(
            const Request::FGetStackStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStackTask>> GetStack(
            const Request::FGetStackRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPreUpdateStackTask>> PreUpdateStack(
            const Request::FPreUpdateStackRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateStackTask>> UpdateStack(
            const Request::FUpdateStackRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPreChangeSetTask>> PreChangeSet(
            const Request::FPreChangeSetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FChangeSetTask>> ChangeSet(
            const Request::FChangeSetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateStackFromGitHubTask>> UpdateStackFromGitHub(
            const Request::FUpdateStackFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteStackTask>> DeleteStack(
            const Request::FDeleteStackRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FForceDeleteStackTask>> ForceDeleteStack(
            const Request::FForceDeleteStackRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteStackResourcesTask>> DeleteStackResources(
            const Request::FDeleteStackResourcesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteStackEntityTask>> DeleteStackEntity(
            const Request::FDeleteStackEntityRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetServiceVersionTask>> GetServiceVersion(
            const Request::FGetServiceVersionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeResourcesTask>> DescribeResources(
            const Request::FDescribeResourcesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetResourceTask>> GetResource(
            const Request::FGetResourceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeEventsTask>> DescribeEvents(
            const Request::FDescribeEventsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetEventTask>> GetEvent(
            const Request::FGetEventRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeOutputsTask>> DescribeOutputs(
            const Request::FDescribeOutputsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetOutputTask>> GetOutput(
            const Request::FGetOutputRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2DeployRestClient, ESPMode::ThreadSafe> FGs2DeployRestClientPtr;
}