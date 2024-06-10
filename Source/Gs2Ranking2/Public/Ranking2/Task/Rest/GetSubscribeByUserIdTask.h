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
#include "Ranking2/Request/GetSubscribeByUserIdRequest.h"
#include "Ranking2/Result/GetSubscribeByUserIdResult.h"

namespace Gs2::Ranking2::Task::Rest
{
    class GS2RANKING2_API FGetSubscribeByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FGetSubscribeByUserIdResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FGetSubscribeByUserIdRequestPtr Request;
    public:
        explicit FGetSubscribeByUserIdTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FGetSubscribeByUserIdRequestPtr Request
        );
        FGetSubscribeByUserIdTask(
            const FGetSubscribeByUserIdTask& From
        );
        virtual ~FGetSubscribeByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetSubscribeByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetSubscribeByUserIdTask, ESPMode::ThreadSafe> FGetSubscribeByUserIdTaskPtr;
}