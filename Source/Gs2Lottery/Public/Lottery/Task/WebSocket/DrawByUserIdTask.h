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
#include "Lottery/Request/DrawByUserIdRequest.h"
#include "Lottery/Result/DrawByUserIdResult.h"

namespace Gs2::Lottery::Task::WebSocket
{
    class GS2LOTTERY_API FDrawByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FDrawByUserIdResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FDrawByUserIdRequestPtr Request;
    public:
        explicit FDrawByUserIdTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FDrawByUserIdRequestPtr Request
        );
        FDrawByUserIdTask(
            const FDrawByUserIdTask& From
        );
        virtual ~FDrawByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDrawByUserIdResultPtr> Result) override;
    protected:
        virtual void OnError(Core::Model::FGs2ErrorPtr Error) override;
    };
    typedef TSharedPtr<FDrawByUserIdTask, ESPMode::ThreadSafe> FDrawByUserIdTaskPtr;
}