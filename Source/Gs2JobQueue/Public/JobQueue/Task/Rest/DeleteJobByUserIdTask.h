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
#include "JobQueue/Request/DeleteJobByUserIdRequest.h"
#include "JobQueue/Result/DeleteJobByUserIdResult.h"

namespace Gs2::JobQueue::Task::Rest
{
    class GS2JOBQUEUE_API FDeleteJobByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FDeleteJobByUserIdResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDeleteJobByUserIdRequestPtr Request;
    public:
        explicit FDeleteJobByUserIdTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDeleteJobByUserIdRequestPtr Request
        );
        FDeleteJobByUserIdTask(
            const FDeleteJobByUserIdTask& From
        );
        virtual ~FDeleteJobByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDeleteJobByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FDeleteJobByUserIdTask, ESPMode::ThreadSafe> FDeleteJobByUserIdTaskPtr;
}