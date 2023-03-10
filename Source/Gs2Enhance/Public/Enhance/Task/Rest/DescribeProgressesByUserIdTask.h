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
#include "Enhance/Request/DescribeProgressesByUserIdRequest.h"
#include "Enhance/Result/DescribeProgressesByUserIdResult.h"

namespace Gs2::Enhance::Task::Rest
{
    class GS2ENHANCE_API FDescribeProgressesByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeProgressesByUserIdResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDescribeProgressesByUserIdRequestPtr Request;
    public:
        explicit FDescribeProgressesByUserIdTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDescribeProgressesByUserIdRequestPtr Request
        );
        FDescribeProgressesByUserIdTask(
            const FDescribeProgressesByUserIdTask& From
        );
        virtual ~FDescribeProgressesByUserIdTask() override = default;

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeProgressesByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeProgressesByUserIdTask, ESPMode::ThreadSafe> FDescribeProgressesByUserIdTaskPtr;
}