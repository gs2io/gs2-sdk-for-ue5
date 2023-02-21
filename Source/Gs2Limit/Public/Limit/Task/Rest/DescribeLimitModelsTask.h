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
#include "Limit/Request/DescribeLimitModelsRequest.h"
#include "Limit/Result/DescribeLimitModelsResult.h"

namespace Gs2::Limit::Task::Rest
{
    class GS2LIMIT_API FDescribeLimitModelsTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeLimitModelsResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDescribeLimitModelsRequestPtr Request;
    public:
        explicit FDescribeLimitModelsTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDescribeLimitModelsRequestPtr Request
        );
        FDescribeLimitModelsTask(
            const FDescribeLimitModelsTask& From
        );
        virtual ~FDescribeLimitModelsTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeLimitModelsResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeLimitModelsTask, ESPMode::ThreadSafe> FDescribeLimitModelsTaskPtr;
}