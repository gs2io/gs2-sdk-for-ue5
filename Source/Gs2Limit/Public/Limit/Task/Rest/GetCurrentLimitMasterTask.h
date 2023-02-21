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
#include "Limit/Request/GetCurrentLimitMasterRequest.h"
#include "Limit/Result/GetCurrentLimitMasterResult.h"

namespace Gs2::Limit::Task::Rest
{
    class GS2LIMIT_API FGetCurrentLimitMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FGetCurrentLimitMasterResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FGetCurrentLimitMasterRequestPtr Request;
    public:
        explicit FGetCurrentLimitMasterTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FGetCurrentLimitMasterRequestPtr Request
        );
        FGetCurrentLimitMasterTask(
            const FGetCurrentLimitMasterTask& From
        );
        virtual ~FGetCurrentLimitMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetCurrentLimitMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetCurrentLimitMasterTask, ESPMode::ThreadSafe> FGetCurrentLimitMasterTaskPtr;
}