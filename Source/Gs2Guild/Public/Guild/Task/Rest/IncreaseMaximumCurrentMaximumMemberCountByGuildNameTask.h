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
#include "Guild/Request/IncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest.h"
#include "Guild/Result/IncreaseMaximumCurrentMaximumMemberCountByGuildNameResult.h"

namespace Gs2::Guild::Task::Rest
{
    class GS2GUILD_API FIncreaseMaximumCurrentMaximumMemberCountByGuildNameTask final : public Gs2::Core::Util::TGs2Future<Result::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request;
    public:
        explicit FIncreaseMaximumCurrentMaximumMemberCountByGuildNameTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
        );
        FIncreaseMaximumCurrentMaximumMemberCountByGuildNameTask(
            const FIncreaseMaximumCurrentMaximumMemberCountByGuildNameTask& From
        );
        virtual ~FIncreaseMaximumCurrentMaximumMemberCountByGuildNameTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameResultPtr> Result) override;
    };
    typedef TSharedPtr<FIncreaseMaximumCurrentMaximumMemberCountByGuildNameTask, ESPMode::ThreadSafe> FIncreaseMaximumCurrentMaximumMemberCountByGuildNameTaskPtr;
}