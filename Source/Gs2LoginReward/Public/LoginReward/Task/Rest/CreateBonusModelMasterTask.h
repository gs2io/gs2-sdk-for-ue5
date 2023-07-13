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
#include "LoginReward/Request/CreateBonusModelMasterRequest.h"
#include "LoginReward/Result/CreateBonusModelMasterResult.h"

namespace Gs2::LoginReward::Task::Rest
{
    class GS2LOGINREWARD_API FCreateBonusModelMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FCreateBonusModelMasterResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FCreateBonusModelMasterRequestPtr Request;
    public:
        explicit FCreateBonusModelMasterTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FCreateBonusModelMasterRequestPtr Request
        );
        FCreateBonusModelMasterTask(
            const FCreateBonusModelMasterTask& From
        );
        virtual ~FCreateBonusModelMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FCreateBonusModelMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FCreateBonusModelMasterTask, ESPMode::ThreadSafe> FCreateBonusModelMasterTaskPtr;
}