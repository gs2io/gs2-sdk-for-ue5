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
#include "Lottery/Request/DescribeProbabilitiesByUserIdRequest.h"
#include "Lottery/Result/DescribeProbabilitiesByUserIdResult.h"

namespace Gs2::Lottery::Task::Rest
{
    class GS2LOTTERY_API FDescribeProbabilitiesByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeProbabilitiesByUserIdResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDescribeProbabilitiesByUserIdRequestPtr Request;
    public:
        explicit FDescribeProbabilitiesByUserIdTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDescribeProbabilitiesByUserIdRequestPtr Request
        );
        FDescribeProbabilitiesByUserIdTask(
            const FDescribeProbabilitiesByUserIdTask& From
        );
        virtual ~FDescribeProbabilitiesByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeProbabilitiesByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeProbabilitiesByUserIdTask, ESPMode::ThreadSafe> FDescribeProbabilitiesByUserIdTaskPtr;
}