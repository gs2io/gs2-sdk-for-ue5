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
#include "Matchmaking/Request/CreateSeasonModelMasterRequest.h"
#include "Matchmaking/Result/CreateSeasonModelMasterResult.h"

namespace Gs2::Matchmaking::Task::Rest
{
    class GS2MATCHMAKING_API FCreateSeasonModelMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FCreateSeasonModelMasterResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FCreateSeasonModelMasterRequestPtr Request;
    public:
        explicit FCreateSeasonModelMasterTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FCreateSeasonModelMasterRequestPtr Request
        );
        FCreateSeasonModelMasterTask(
            const FCreateSeasonModelMasterTask& From
        );
        virtual ~FCreateSeasonModelMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FCreateSeasonModelMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FCreateSeasonModelMasterTask, ESPMode::ThreadSafe> FCreateSeasonModelMasterTaskPtr;
}