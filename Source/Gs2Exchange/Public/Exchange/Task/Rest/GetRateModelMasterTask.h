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
#include "Exchange/Request/GetRateModelMasterRequest.h"
#include "Exchange/Result/GetRateModelMasterResult.h"

namespace Gs2::Exchange::Task::Rest
{
    class GS2EXCHANGE_API FGetRateModelMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FGetRateModelMasterResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FGetRateModelMasterRequestPtr Request;
    public:
        explicit FGetRateModelMasterTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FGetRateModelMasterRequestPtr Request
        );
        FGetRateModelMasterTask(
            const FGetRateModelMasterTask& From
        );
        virtual ~FGetRateModelMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetRateModelMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetRateModelMasterTask, ESPMode::ThreadSafe> FGetRateModelMasterTaskPtr;
}