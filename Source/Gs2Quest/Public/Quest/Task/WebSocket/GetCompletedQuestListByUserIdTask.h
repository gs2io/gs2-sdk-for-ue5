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
#include "Quest/Request/GetCompletedQuestListByUserIdRequest.h"
#include "Quest/Result/GetCompletedQuestListByUserIdResult.h"

namespace Gs2::Quest::Task::WebSocket
{
    class GS2QUEST_API FGetCompletedQuestListByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FGetCompletedQuestListByUserIdResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FGetCompletedQuestListByUserIdRequestPtr Request;
    public:
        explicit FGetCompletedQuestListByUserIdTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FGetCompletedQuestListByUserIdRequestPtr Request
        );
        FGetCompletedQuestListByUserIdTask(
            const FGetCompletedQuestListByUserIdTask& From
        );
        virtual ~FGetCompletedQuestListByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetCompletedQuestListByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetCompletedQuestListByUserIdTask, ESPMode::ThreadSafe> FGetCompletedQuestListByUserIdTaskPtr;
}