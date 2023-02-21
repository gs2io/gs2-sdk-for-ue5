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
#include "JobQueue/Request/RunRequest.h"
#include "JobQueue/Result/RunResult.h"

namespace Gs2::JobQueue::Task::Rest
{
    class GS2JOBQUEUE_API FRunTask final : public Gs2::Core::Util::TGs2Future<Result::FRunResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FRunRequestPtr Request;
    public:
        explicit FRunTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FRunRequestPtr Request
        );
        FRunTask(
            const FRunTask& From
        );
        virtual ~FRunTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FRunResultPtr> Result) override;
    };
    typedef TSharedPtr<FRunTask, ESPMode::ThreadSafe> FRunTaskPtr;
}