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
#include "Experience/Request/CreateThresholdMasterRequest.h"
#include "Experience/Result/CreateThresholdMasterResult.h"

namespace Gs2::Experience::Task::Rest
{
    class GS2EXPERIENCE_API FCreateThresholdMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FCreateThresholdMasterResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FCreateThresholdMasterRequestPtr Request;
    public:
        explicit FCreateThresholdMasterTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FCreateThresholdMasterRequestPtr Request
        );
        FCreateThresholdMasterTask(
            const FCreateThresholdMasterTask& From
        );
        virtual ~FCreateThresholdMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FCreateThresholdMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FCreateThresholdMasterTask, ESPMode::ThreadSafe> FCreateThresholdMasterTaskPtr;
}