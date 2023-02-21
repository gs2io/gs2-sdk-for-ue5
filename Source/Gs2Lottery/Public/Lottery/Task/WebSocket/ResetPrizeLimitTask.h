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
#include "Lottery/Request/ResetPrizeLimitRequest.h"
#include "Lottery/Result/ResetPrizeLimitResult.h"

namespace Gs2::Lottery::Task::WebSocket
{
    class GS2LOTTERY_API FResetPrizeLimitTask final : public Gs2::Core::Util::TGs2Future<Result::FResetPrizeLimitResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FResetPrizeLimitRequestPtr Request;
    public:
        explicit FResetPrizeLimitTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FResetPrizeLimitRequestPtr Request
        );
        FResetPrizeLimitTask(
            const FResetPrizeLimitTask& From
        );
        virtual ~FResetPrizeLimitTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FResetPrizeLimitResultPtr> Result) override;
    };
    typedef TSharedPtr<FResetPrizeLimitTask, ESPMode::ThreadSafe> FResetPrizeLimitTaskPtr;
}