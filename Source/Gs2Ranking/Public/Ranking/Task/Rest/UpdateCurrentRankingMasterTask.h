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
#include "Ranking/Request/UpdateCurrentRankingMasterRequest.h"
#include "Ranking/Result/UpdateCurrentRankingMasterResult.h"

namespace Gs2::Ranking::Task::Rest
{
    class GS2RANKING_API FUpdateCurrentRankingMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FUpdateCurrentRankingMasterResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FUpdateCurrentRankingMasterRequestPtr Request;
    public:
        explicit FUpdateCurrentRankingMasterTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FUpdateCurrentRankingMasterRequestPtr Request
        );
        FUpdateCurrentRankingMasterTask(
            const FUpdateCurrentRankingMasterTask& From
        );
        virtual ~FUpdateCurrentRankingMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FUpdateCurrentRankingMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FUpdateCurrentRankingMasterTask, ESPMode::ThreadSafe> FUpdateCurrentRankingMasterTaskPtr;
}