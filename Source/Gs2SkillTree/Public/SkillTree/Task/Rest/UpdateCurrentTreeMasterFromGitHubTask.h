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
#include "SkillTree/Request/UpdateCurrentTreeMasterFromGitHubRequest.h"
#include "SkillTree/Result/UpdateCurrentTreeMasterFromGitHubResult.h"

namespace Gs2::SkillTree::Task::Rest
{
    class GS2SKILLTREE_API FUpdateCurrentTreeMasterFromGitHubTask final : public Gs2::Core::Util::TGs2Future<Result::FUpdateCurrentTreeMasterFromGitHubResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FUpdateCurrentTreeMasterFromGitHubRequestPtr Request;
    public:
        explicit FUpdateCurrentTreeMasterFromGitHubTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FUpdateCurrentTreeMasterFromGitHubRequestPtr Request
        );
        FUpdateCurrentTreeMasterFromGitHubTask(
            const FUpdateCurrentTreeMasterFromGitHubTask& From
        );
        virtual ~FUpdateCurrentTreeMasterFromGitHubTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FUpdateCurrentTreeMasterFromGitHubResultPtr> Result) override;
    };
    typedef TSharedPtr<FUpdateCurrentTreeMasterFromGitHubTask, ESPMode::ThreadSafe> FUpdateCurrentTreeMasterFromGitHubTaskPtr;
}