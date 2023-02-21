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
#include "Chat/Request/UpdateRoomRequest.h"
#include "Chat/Result/UpdateRoomResult.h"

namespace Gs2::Chat::Task::WebSocket
{
    class GS2CHAT_API FUpdateRoomTask final : public Gs2::Core::Util::TGs2Future<Result::FUpdateRoomResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FUpdateRoomRequestPtr Request;
    public:
        explicit FUpdateRoomTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FUpdateRoomRequestPtr Request
        );
        FUpdateRoomTask(
            const FUpdateRoomTask& From
        );
        virtual ~FUpdateRoomTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FUpdateRoomResultPtr> Result) override;
    };
    typedef TSharedPtr<FUpdateRoomTask, ESPMode::ThreadSafe> FUpdateRoomTaskPtr;
}