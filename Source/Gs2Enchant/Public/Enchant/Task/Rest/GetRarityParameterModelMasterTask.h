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
#include "Enchant/Request/GetRarityParameterModelMasterRequest.h"
#include "Enchant/Result/GetRarityParameterModelMasterResult.h"

namespace Gs2::Enchant::Task::Rest
{
    class GS2ENCHANT_API FGetRarityParameterModelMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FGetRarityParameterModelMasterResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FGetRarityParameterModelMasterRequestPtr Request;
    public:
        explicit FGetRarityParameterModelMasterTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FGetRarityParameterModelMasterRequestPtr Request
        );
        FGetRarityParameterModelMasterTask(
            const FGetRarityParameterModelMasterTask& From
        );
        virtual ~FGetRarityParameterModelMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetRarityParameterModelMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetRarityParameterModelMasterTask, ESPMode::ThreadSafe> FGetRarityParameterModelMasterTaskPtr;
}