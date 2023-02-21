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

#include "Core/Gs2Core.h"
#include "JobQueue/Request/DescribeDeadLetterJobsByUserIdRequest.h"
#include "JobQueue/Result/DescribeDeadLetterJobsByUserIdResult.h"

namespace Gs2::JobQueue::Task::Rest
{
    class GS2JOBQUEUE_API FDescribeDeadLetterJobsByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeDeadLetterJobsByUserIdResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDescribeDeadLetterJobsByUserIdRequestPtr Request;
    public:
        explicit FDescribeDeadLetterJobsByUserIdTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDescribeDeadLetterJobsByUserIdRequestPtr Request
        );
        FDescribeDeadLetterJobsByUserIdTask(
            const FDescribeDeadLetterJobsByUserIdTask& From
        );
        virtual ~FDescribeDeadLetterJobsByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeDeadLetterJobsByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeDeadLetterJobsByUserIdTask, ESPMode::ThreadSafe> FDescribeDeadLetterJobsByUserIdTaskPtr;
}