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
#include "Log/Request/SendInGameLogRequest.h"
#include "Log/Result/SendInGameLogResult.h"

namespace Gs2::Log::Task::WebSocket
{
    class GS2LOG_API FSendInGameLogTask final : public Gs2::Core::Util::TGs2Future<Result::FSendInGameLogResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FSendInGameLogRequestPtr Request;
    public:
        explicit FSendInGameLogTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FSendInGameLogRequestPtr Request
        );
        FSendInGameLogTask(
            const FSendInGameLogTask& From
        );
        virtual ~FSendInGameLogTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FSendInGameLogResultPtr> Result) override;
    };
    typedef TSharedPtr<FSendInGameLogTask, ESPMode::ThreadSafe> FSendInGameLogTaskPtr;
}