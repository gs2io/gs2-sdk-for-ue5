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
#include "Idle/Request/UpdateCategoryModelMasterRequest.h"
#include "Idle/Result/UpdateCategoryModelMasterResult.h"

namespace Gs2::Idle::Task::Rest
{
    class GS2IDLE_API FUpdateCategoryModelMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FUpdateCategoryModelMasterResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FUpdateCategoryModelMasterRequestPtr Request;
    public:
        explicit FUpdateCategoryModelMasterTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FUpdateCategoryModelMasterRequestPtr Request
        );
        FUpdateCategoryModelMasterTask(
            const FUpdateCategoryModelMasterTask& From
        );
        virtual ~FUpdateCategoryModelMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FUpdateCategoryModelMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FUpdateCategoryModelMasterTask, ESPMode::ThreadSafe> FUpdateCategoryModelMasterTaskPtr;
}