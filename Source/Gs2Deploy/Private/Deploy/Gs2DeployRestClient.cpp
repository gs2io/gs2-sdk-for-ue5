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

#include "Deploy/Gs2DeployRestClient.h"

namespace Gs2::Deploy
{

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeStacksTask>> FGs2DeployRestClient::DescribeStacks(
        const Request::FDescribeStacksRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeStacksTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPreCreateStackTask>> FGs2DeployRestClient::PreCreateStack(
        const Request::FPreCreateStackRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPreCreateStackTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateStackTask>> FGs2DeployRestClient::CreateStack(
        const Request::FCreateStackRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateStackTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateStackFromGitHubTask>> FGs2DeployRestClient::CreateStackFromGitHub(
        const Request::FCreateStackFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateStackFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPreValidateTask>> FGs2DeployRestClient::PreValidate(
        const Request::FPreValidateRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPreValidateTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FValidateTask>> FGs2DeployRestClient::Validate(
        const Request::FValidateRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FValidateTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetStackStatusTask>> FGs2DeployRestClient::GetStackStatus(
        const Request::FGetStackStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetStackStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetStackTask>> FGs2DeployRestClient::GetStack(
        const Request::FGetStackRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetStackTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPreUpdateStackTask>> FGs2DeployRestClient::PreUpdateStack(
        const Request::FPreUpdateStackRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPreUpdateStackTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateStackTask>> FGs2DeployRestClient::UpdateStack(
        const Request::FUpdateStackRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateStackTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPreChangeSetTask>> FGs2DeployRestClient::PreChangeSet(
        const Request::FPreChangeSetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPreChangeSetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FChangeSetTask>> FGs2DeployRestClient::ChangeSet(
        const Request::FChangeSetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FChangeSetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateStackFromGitHubTask>> FGs2DeployRestClient::UpdateStackFromGitHub(
        const Request::FUpdateStackFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateStackFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteStackTask>> FGs2DeployRestClient::DeleteStack(
        const Request::FDeleteStackRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteStackTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FForceDeleteStackTask>> FGs2DeployRestClient::ForceDeleteStack(
        const Request::FForceDeleteStackRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FForceDeleteStackTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteStackResourcesTask>> FGs2DeployRestClient::DeleteStackResources(
        const Request::FDeleteStackResourcesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteStackResourcesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteStackEntityTask>> FGs2DeployRestClient::DeleteStackEntity(
        const Request::FDeleteStackEntityRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteStackEntityTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeResourcesTask>> FGs2DeployRestClient::DescribeResources(
        const Request::FDescribeResourcesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeResourcesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetResourceTask>> FGs2DeployRestClient::GetResource(
        const Request::FGetResourceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetResourceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeEventsTask>> FGs2DeployRestClient::DescribeEvents(
        const Request::FDescribeEventsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeEventsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetEventTask>> FGs2DeployRestClient::GetEvent(
        const Request::FGetEventRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetEventTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeOutputsTask>> FGs2DeployRestClient::DescribeOutputs(
        const Request::FDescribeOutputsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeOutputsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetOutputTask>> FGs2DeployRestClient::GetOutput(
        const Request::FGetOutputRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetOutputTask>>(
            Session,
            Request
        );
    }
}