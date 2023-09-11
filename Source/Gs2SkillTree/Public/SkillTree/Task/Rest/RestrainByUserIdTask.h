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
#include "SkillTree/Request/RestrainByUserIdRequest.h"
#include "SkillTree/Result/RestrainByUserIdResult.h"

namespace Gs2::SkillTree::Task::Rest
{
    class GS2SKILLTREE_API FRestrainByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FRestrainByUserIdResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FRestrainByUserIdRequestPtr Request;
    public:
        explicit FRestrainByUserIdTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FRestrainByUserIdRequestPtr Request
        );
        FRestrainByUserIdTask(
            const FRestrainByUserIdTask& From
        );
        virtual ~FRestrainByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FRestrainByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FRestrainByUserIdTask, ESPMode::ThreadSafe> FRestrainByUserIdTaskPtr;
}