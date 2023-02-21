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
#include "Formation/Request/UpdateCurrentFormMasterRequest.h"
#include "Formation/Result/UpdateCurrentFormMasterResult.h"

namespace Gs2::Formation::Task::Rest
{
    class GS2FORMATION_API FUpdateCurrentFormMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FUpdateCurrentFormMasterResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FUpdateCurrentFormMasterRequestPtr Request;
    public:
        explicit FUpdateCurrentFormMasterTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FUpdateCurrentFormMasterRequestPtr Request
        );
        FUpdateCurrentFormMasterTask(
            const FUpdateCurrentFormMasterTask& From
        );
        virtual ~FUpdateCurrentFormMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FUpdateCurrentFormMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FUpdateCurrentFormMasterTask, ESPMode::ThreadSafe> FUpdateCurrentFormMasterTaskPtr;
}