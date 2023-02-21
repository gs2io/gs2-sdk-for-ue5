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
#include "Limit/Request/DescribeCountersRequest.h"
#include "Limit/Result/DescribeCountersResult.h"

namespace Gs2::Limit::Task::Rest
{
    class GS2LIMIT_API FDescribeCountersTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeCountersResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDescribeCountersRequestPtr Request;
    public:
        explicit FDescribeCountersTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDescribeCountersRequestPtr Request
        );
        FDescribeCountersTask(
            const FDescribeCountersTask& From
        );
        virtual ~FDescribeCountersTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeCountersResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeCountersTask, ESPMode::ThreadSafe> FDescribeCountersTaskPtr;
}