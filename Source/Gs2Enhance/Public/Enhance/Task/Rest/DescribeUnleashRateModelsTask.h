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
#include "Enhance/Request/DescribeUnleashRateModelsRequest.h"
#include "Enhance/Result/DescribeUnleashRateModelsResult.h"

namespace Gs2::Enhance::Task::Rest
{
    class GS2ENHANCE_API FDescribeUnleashRateModelsTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeUnleashRateModelsResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDescribeUnleashRateModelsRequestPtr Request;
    public:
        explicit FDescribeUnleashRateModelsTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDescribeUnleashRateModelsRequestPtr Request
        );
        FDescribeUnleashRateModelsTask(
            const FDescribeUnleashRateModelsTask& From
        );
        virtual ~FDescribeUnleashRateModelsTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeUnleashRateModelsResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeUnleashRateModelsTask, ESPMode::ThreadSafe> FDescribeUnleashRateModelsTaskPtr;
}