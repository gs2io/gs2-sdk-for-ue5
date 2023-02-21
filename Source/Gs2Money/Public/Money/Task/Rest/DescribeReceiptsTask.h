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
#include "Money/Request/DescribeReceiptsRequest.h"
#include "Money/Result/DescribeReceiptsResult.h"

namespace Gs2::Money::Task::Rest
{
    class GS2MONEY_API FDescribeReceiptsTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeReceiptsResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDescribeReceiptsRequestPtr Request;
    public:
        explicit FDescribeReceiptsTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDescribeReceiptsRequestPtr Request
        );
        FDescribeReceiptsTask(
            const FDescribeReceiptsTask& From
        );
        virtual ~FDescribeReceiptsTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeReceiptsResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeReceiptsTask, ESPMode::ThreadSafe> FDescribeReceiptsTaskPtr;
}