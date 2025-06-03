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
#include "Request/DescribeStagesRequest.h"
#include "Task/Rest/DescribeStagesTask.h"
#include "Request/GetStageRequest.h"
#include "Task/Rest/GetStageTask.h"
#include "Request/PromoteStageRequest.h"
#include "Task/Rest/PromoteStageTask.h"
#include "Request/RollbackStageRequest.h"
#include "Task/Rest/RollbackStageTask.h"
#include "Request/DescribeOutputsRequest.h"
#include "Task/Rest/DescribeOutputsTask.h"
#include "Request/GetOutputRequest.h"
#include "Task/Rest/GetOutputTask.h"

namespace Gs2::Freeze
{
    class GS2FREEZE_API FGs2FreezeRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2FreezeRestClient(
            const Core::Net::Rest::FGs2RestSessionPtr Session
        ): FAbstractGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeStagesTask>> DescribeStages(
            const Request::FDescribeStagesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStageTask>> GetStage(
            const Request::FGetStageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPromoteStageTask>> PromoteStage(
            const Request::FPromoteStageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRollbackStageTask>> RollbackStage(
            const Request::FRollbackStageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeOutputsTask>> DescribeOutputs(
            const Request::FDescribeOutputsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetOutputTask>> GetOutput(
            const Request::FGetOutputRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2FreezeRestClient, ESPMode::ThreadSafe> FGs2FreezeRestClientPtr;
}