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
#include "Exchange/Request/GetAwaitByUserIdRequest.h"
#include "Exchange/Result/GetAwaitByUserIdResult.h"

namespace Gs2::Exchange::Task::WebSocket
{
    class GS2EXCHANGE_API FGetAwaitByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FGetAwaitByUserIdResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FGetAwaitByUserIdRequestPtr Request;
    public:
        explicit FGetAwaitByUserIdTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FGetAwaitByUserIdRequestPtr Request
        );
        FGetAwaitByUserIdTask(
            const FGetAwaitByUserIdTask& From
        );
        virtual ~FGetAwaitByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetAwaitByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetAwaitByUserIdTask, ESPMode::ThreadSafe> FGetAwaitByUserIdTaskPtr;
}