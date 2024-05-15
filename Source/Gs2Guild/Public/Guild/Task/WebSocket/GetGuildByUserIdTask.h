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
#include "Guild/Request/GetGuildByUserIdRequest.h"
#include "Guild/Result/GetGuildByUserIdResult.h"

namespace Gs2::Guild::Task::WebSocket
{
    class GS2GUILD_API FGetGuildByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FGetGuildByUserIdResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FGetGuildByUserIdRequestPtr Request;
    public:
        explicit FGetGuildByUserIdTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FGetGuildByUserIdRequestPtr Request
        );
        FGetGuildByUserIdTask(
            const FGetGuildByUserIdTask& From
        );
        virtual ~FGetGuildByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetGuildByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetGuildByUserIdTask, ESPMode::ThreadSafe> FGetGuildByUserIdTaskPtr;
}