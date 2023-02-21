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
#include "Exchange/Request/GetCurrentRateMasterRequest.h"
#include "Exchange/Result/GetCurrentRateMasterResult.h"

namespace Gs2::Exchange::Task::Rest
{
    class GS2EXCHANGE_API FGetCurrentRateMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FGetCurrentRateMasterResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FGetCurrentRateMasterRequestPtr Request;
    public:
        explicit FGetCurrentRateMasterTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FGetCurrentRateMasterRequestPtr Request
        );
        FGetCurrentRateMasterTask(
            const FGetCurrentRateMasterTask& From
        );
        virtual ~FGetCurrentRateMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetCurrentRateMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetCurrentRateMasterTask, ESPMode::ThreadSafe> FGetCurrentRateMasterTaskPtr;
}