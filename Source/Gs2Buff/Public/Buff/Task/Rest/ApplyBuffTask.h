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
#include "Buff/Request/ApplyBuffRequest.h"
#include "Buff/Result/ApplyBuffResult.h"

namespace Gs2::Buff::Task::Rest
{
    class GS2BUFF_API FApplyBuffTask final : public Gs2::Core::Util::TGs2Future<Result::FApplyBuffResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FApplyBuffRequestPtr Request;
    public:
        explicit FApplyBuffTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FApplyBuffRequestPtr Request
        );
        FApplyBuffTask(
            const FApplyBuffTask& From
        );
        virtual ~FApplyBuffTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FApplyBuffResultPtr> Result) override;
    };
    typedef TSharedPtr<FApplyBuffTask, ESPMode::ThreadSafe> FApplyBuffTaskPtr;
}