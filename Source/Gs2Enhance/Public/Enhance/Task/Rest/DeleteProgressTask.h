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
#include "Enhance/Request/DeleteProgressRequest.h"
#include "Enhance/Result/DeleteProgressResult.h"

namespace Gs2::Enhance::Task::Rest
{
    class GS2ENHANCE_API FDeleteProgressTask final : public Gs2::Core::Util::TGs2Future<Result::FDeleteProgressResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDeleteProgressRequestPtr Request;
    public:
        explicit FDeleteProgressTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDeleteProgressRequestPtr Request
        );
        FDeleteProgressTask(
            const FDeleteProgressTask& From
        );
        virtual ~FDeleteProgressTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDeleteProgressResultPtr> Result) override;
    };
    typedef TSharedPtr<FDeleteProgressTask, ESPMode::ThreadSafe> FDeleteProgressTaskPtr;
}