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
#include "Lottery/Request/GetCurrentLotteryMasterRequest.h"
#include "Lottery/Result/GetCurrentLotteryMasterResult.h"

namespace Gs2::Lottery::Task::Rest
{
    class GS2LOTTERY_API FGetCurrentLotteryMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FGetCurrentLotteryMasterResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FGetCurrentLotteryMasterRequestPtr Request;
    public:
        explicit FGetCurrentLotteryMasterTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FGetCurrentLotteryMasterRequestPtr Request
        );
        FGetCurrentLotteryMasterTask(
            const FGetCurrentLotteryMasterTask& From
        );
        virtual ~FGetCurrentLotteryMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetCurrentLotteryMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetCurrentLotteryMasterTask, ESPMode::ThreadSafe> FGetCurrentLotteryMasterTaskPtr;
}