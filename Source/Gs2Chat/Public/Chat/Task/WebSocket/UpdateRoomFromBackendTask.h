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
#include "Chat/Request/UpdateRoomFromBackendRequest.h"
#include "Chat/Result/UpdateRoomFromBackendResult.h"

namespace Gs2::Chat::Task::WebSocket
{
    class GS2CHAT_API FUpdateRoomFromBackendTask final : public Gs2::Core::Util::TGs2Future<Result::FUpdateRoomFromBackendResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FUpdateRoomFromBackendRequestPtr Request;
    public:
        explicit FUpdateRoomFromBackendTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FUpdateRoomFromBackendRequestPtr Request
        );
        FUpdateRoomFromBackendTask(
            const FUpdateRoomFromBackendTask& From
        );
        virtual ~FUpdateRoomFromBackendTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FUpdateRoomFromBackendResultPtr> Result) override;
    };
    typedef TSharedPtr<FUpdateRoomFromBackendTask, ESPMode::ThreadSafe> FUpdateRoomFromBackendTaskPtr;
}