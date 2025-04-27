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
#include "Deploy/Request/PreCreateStackRequest.h"
#include "Deploy/Result/PreCreateStackResult.h"

namespace Gs2::Deploy::Task::Rest
{
    class GS2DEPLOY_API FPreCreateStackTask final : public Gs2::Core::Util::TGs2Future<Result::FPreCreateStackResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FPreCreateStackRequestPtr Request;
    public:
        explicit FPreCreateStackTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FPreCreateStackRequestPtr Request
        );
        FPreCreateStackTask(
            const FPreCreateStackTask& From
        );
        virtual ~FPreCreateStackTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FPreCreateStackResultPtr> Result) override;
    };
    typedef TSharedPtr<FPreCreateStackTask, ESPMode::ThreadSafe> FPreCreateStackTaskPtr;
}