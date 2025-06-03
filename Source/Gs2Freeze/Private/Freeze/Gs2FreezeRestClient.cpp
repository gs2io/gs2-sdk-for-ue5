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

#include "Freeze/Gs2FreezeRestClient.h"

namespace Gs2::Freeze
{

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeStagesTask>> FGs2FreezeRestClient::DescribeStages(
        const Request::FDescribeStagesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeStagesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetStageTask>> FGs2FreezeRestClient::GetStage(
        const Request::FGetStageRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetStageTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPromoteStageTask>> FGs2FreezeRestClient::PromoteStage(
        const Request::FPromoteStageRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPromoteStageTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRollbackStageTask>> FGs2FreezeRestClient::RollbackStage(
        const Request::FRollbackStageRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRollbackStageTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeOutputsTask>> FGs2FreezeRestClient::DescribeOutputs(
        const Request::FDescribeOutputsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeOutputsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetOutputTask>> FGs2FreezeRestClient::GetOutput(
        const Request::FGetOutputRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetOutputTask>>(
            Session,
            Request
        );
    }
}