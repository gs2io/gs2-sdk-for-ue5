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
#include "SkillTree/Request/UpdateCurrentTreeMasterRequest.h"
#include "SkillTree/Result/UpdateCurrentTreeMasterResult.h"

namespace Gs2::SkillTree::Task::WebSocket
{
    class GS2SKILLTREE_API FUpdateCurrentTreeMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FUpdateCurrentTreeMasterResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FUpdateCurrentTreeMasterRequestPtr Request;
    public:
        explicit FUpdateCurrentTreeMasterTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FUpdateCurrentTreeMasterRequestPtr Request
        );
        FUpdateCurrentTreeMasterTask(
            const FUpdateCurrentTreeMasterTask& From
        );
        virtual ~FUpdateCurrentTreeMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FUpdateCurrentTreeMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FUpdateCurrentTreeMasterTask, ESPMode::ThreadSafe> FUpdateCurrentTreeMasterTaskPtr;
}