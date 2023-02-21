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
#include "Matchmaking/Request/DescribeRatingModelsRequest.h"
#include "Matchmaking/Result/DescribeRatingModelsResult.h"

namespace Gs2::Matchmaking::Task::Rest
{
    class GS2MATCHMAKING_API FDescribeRatingModelsTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeRatingModelsResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDescribeRatingModelsRequestPtr Request;
    public:
        explicit FDescribeRatingModelsTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDescribeRatingModelsRequestPtr Request
        );
        FDescribeRatingModelsTask(
            const FDescribeRatingModelsTask& From
        );
        virtual ~FDescribeRatingModelsTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeRatingModelsResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeRatingModelsTask, ESPMode::ThreadSafe> FDescribeRatingModelsTaskPtr;
}