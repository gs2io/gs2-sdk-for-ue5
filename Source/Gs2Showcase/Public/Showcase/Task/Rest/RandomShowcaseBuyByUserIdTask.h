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
#include "Showcase/Request/RandomShowcaseBuyByUserIdRequest.h"
#include "Showcase/Result/RandomShowcaseBuyByUserIdResult.h"

namespace Gs2::Showcase::Task::Rest
{
    class GS2SHOWCASE_API FRandomShowcaseBuyByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FRandomShowcaseBuyByUserIdResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FRandomShowcaseBuyByUserIdRequestPtr Request;
    public:
        explicit FRandomShowcaseBuyByUserIdTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FRandomShowcaseBuyByUserIdRequestPtr Request
        );
        FRandomShowcaseBuyByUserIdTask(
            const FRandomShowcaseBuyByUserIdTask& From
        );
        virtual ~FRandomShowcaseBuyByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FRandomShowcaseBuyByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FRandomShowcaseBuyByUserIdTask, ESPMode::ThreadSafe> FRandomShowcaseBuyByUserIdTaskPtr;
}