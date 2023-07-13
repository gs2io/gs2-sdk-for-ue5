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
#include "LoginReward/Request/GetBonusModelRequest.h"
#include "LoginReward/Result/GetBonusModelResult.h"

namespace Gs2::LoginReward::Task::Rest
{
    class GS2LOGINREWARD_API FGetBonusModelTask final : public Gs2::Core::Util::TGs2Future<Result::FGetBonusModelResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FGetBonusModelRequestPtr Request;
    public:
        explicit FGetBonusModelTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FGetBonusModelRequestPtr Request
        );
        FGetBonusModelTask(
            const FGetBonusModelTask& From
        );
        virtual ~FGetBonusModelTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetBonusModelResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetBonusModelTask, ESPMode::ThreadSafe> FGetBonusModelTaskPtr;
}