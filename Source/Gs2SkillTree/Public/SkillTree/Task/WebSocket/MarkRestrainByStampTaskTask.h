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
#include "SkillTree/Request/MarkRestrainByStampTaskRequest.h"
#include "SkillTree/Result/MarkRestrainByStampTaskResult.h"

namespace Gs2::SkillTree::Task::WebSocket
{
    class GS2SKILLTREE_API FMarkRestrainByStampTaskTask final : public Gs2::Core::Util::TGs2Future<Result::FMarkRestrainByStampTaskResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FMarkRestrainByStampTaskRequestPtr Request;
    public:
        explicit FMarkRestrainByStampTaskTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FMarkRestrainByStampTaskRequestPtr Request
        );
        FMarkRestrainByStampTaskTask(
            const FMarkRestrainByStampTaskTask& From
        );
        virtual ~FMarkRestrainByStampTaskTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FMarkRestrainByStampTaskResultPtr> Result) override;
    };
    typedef TSharedPtr<FMarkRestrainByStampTaskTask, ESPMode::ThreadSafe> FMarkRestrainByStampTaskTaskPtr;
}