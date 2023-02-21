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
#include "Lottery/Request/GetPrizeLimitRequest.h"
#include "Lottery/Result/GetPrizeLimitResult.h"

namespace Gs2::Lottery::Task::WebSocket
{
    class GS2LOTTERY_API FGetPrizeLimitTask final : public Gs2::Core::Util::TGs2Future<Result::FGetPrizeLimitResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FGetPrizeLimitRequestPtr Request;
    public:
        explicit FGetPrizeLimitTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FGetPrizeLimitRequestPtr Request
        );
        FGetPrizeLimitTask(
            const FGetPrizeLimitTask& From
        );
        virtual ~FGetPrizeLimitTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetPrizeLimitResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetPrizeLimitTask, ESPMode::ThreadSafe> FGetPrizeLimitTaskPtr;
}