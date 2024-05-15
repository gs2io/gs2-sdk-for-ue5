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
#include "Guild/Request/AssumeRequest.h"
#include "Guild/Result/AssumeResult.h"

namespace Gs2::Guild::Task::Rest
{
    class GS2GUILD_API FAssumeTask final : public Gs2::Core::Util::TGs2Future<Result::FAssumeResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FAssumeRequestPtr Request;
    public:
        explicit FAssumeTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FAssumeRequestPtr Request
        );
        FAssumeTask(
            const FAssumeTask& From
        );
        virtual ~FAssumeTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FAssumeResultPtr> Result) override;
    };
    typedef TSharedPtr<FAssumeTask, ESPMode::ThreadSafe> FAssumeTaskPtr;
}