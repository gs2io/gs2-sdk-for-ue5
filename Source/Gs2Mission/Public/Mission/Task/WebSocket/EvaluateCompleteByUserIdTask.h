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
#include "Mission/Request/EvaluateCompleteByUserIdRequest.h"
#include "Mission/Result/EvaluateCompleteByUserIdResult.h"

namespace Gs2::Mission::Task::WebSocket
{
    class GS2MISSION_API FEvaluateCompleteByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FEvaluateCompleteByUserIdResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FEvaluateCompleteByUserIdRequestPtr Request;
    public:
        explicit FEvaluateCompleteByUserIdTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FEvaluateCompleteByUserIdRequestPtr Request
        );
        FEvaluateCompleteByUserIdTask(
            const FEvaluateCompleteByUserIdTask& From
        );
        virtual ~FEvaluateCompleteByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FEvaluateCompleteByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FEvaluateCompleteByUserIdTask, ESPMode::ThreadSafe> FEvaluateCompleteByUserIdTaskPtr;
}