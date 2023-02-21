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
#include "News/Request/DescribeNewsByUserIdRequest.h"
#include "News/Result/DescribeNewsByUserIdResult.h"

namespace Gs2::News::Task::Rest
{
    class GS2NEWS_API FDescribeNewsByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeNewsByUserIdResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDescribeNewsByUserIdRequestPtr Request;
    public:
        explicit FDescribeNewsByUserIdTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDescribeNewsByUserIdRequestPtr Request
        );
        FDescribeNewsByUserIdTask(
            const FDescribeNewsByUserIdTask& From
        );
        virtual ~FDescribeNewsByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeNewsByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeNewsByUserIdTask, ESPMode::ThreadSafe> FDescribeNewsByUserIdTaskPtr;
}