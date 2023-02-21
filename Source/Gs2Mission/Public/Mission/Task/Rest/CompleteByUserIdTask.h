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
#include "Mission/Request/CompleteByUserIdRequest.h"
#include "Mission/Result/CompleteByUserIdResult.h"

namespace Gs2::Mission::Task::Rest
{
    class GS2MISSION_API FCompleteByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FCompleteByUserIdResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FCompleteByUserIdRequestPtr Request;
    public:
        explicit FCompleteByUserIdTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FCompleteByUserIdRequestPtr Request
        );
        FCompleteByUserIdTask(
            const FCompleteByUserIdTask& From
        );
        virtual ~FCompleteByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FCompleteByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FCompleteByUserIdTask, ESPMode::ThreadSafe> FCompleteByUserIdTaskPtr;
}