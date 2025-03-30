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
#include "Stamina/Request/VerifyStaminaOverflowValueRequest.h"
#include "Stamina/Result/VerifyStaminaOverflowValueResult.h"

namespace Gs2::Stamina::Task::Rest
{
    class GS2STAMINA_API FVerifyStaminaOverflowValueTask final : public Gs2::Core::Util::TGs2Future<Result::FVerifyStaminaOverflowValueResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FVerifyStaminaOverflowValueRequestPtr Request;
    public:
        explicit FVerifyStaminaOverflowValueTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FVerifyStaminaOverflowValueRequestPtr Request
        );
        FVerifyStaminaOverflowValueTask(
            const FVerifyStaminaOverflowValueTask& From
        );
        virtual ~FVerifyStaminaOverflowValueTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FVerifyStaminaOverflowValueResultPtr> Result) override;
    };
    typedef TSharedPtr<FVerifyStaminaOverflowValueTask, ESPMode::ThreadSafe> FVerifyStaminaOverflowValueTaskPtr;
}