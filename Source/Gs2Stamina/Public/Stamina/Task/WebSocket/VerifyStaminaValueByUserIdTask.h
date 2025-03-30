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
#include "Stamina/Request/VerifyStaminaValueByUserIdRequest.h"
#include "Stamina/Result/VerifyStaminaValueByUserIdResult.h"

namespace Gs2::Stamina::Task::WebSocket
{
    class GS2STAMINA_API FVerifyStaminaValueByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FVerifyStaminaValueByUserIdResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FVerifyStaminaValueByUserIdRequestPtr Request;
    public:
        explicit FVerifyStaminaValueByUserIdTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FVerifyStaminaValueByUserIdRequestPtr Request
        );
        FVerifyStaminaValueByUserIdTask(
            const FVerifyStaminaValueByUserIdTask& From
        );
        virtual ~FVerifyStaminaValueByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FVerifyStaminaValueByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FVerifyStaminaValueByUserIdTask, ESPMode::ThreadSafe> FVerifyStaminaValueByUserIdTaskPtr;
}