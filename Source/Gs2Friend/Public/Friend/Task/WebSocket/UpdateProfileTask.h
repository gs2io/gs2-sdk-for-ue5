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
#include "Friend/Request/UpdateProfileRequest.h"
#include "Friend/Result/UpdateProfileResult.h"

namespace Gs2::Friend::Task::WebSocket
{
    class GS2FRIEND_API FUpdateProfileTask final : public Gs2::Core::Util::TGs2Future<Result::FUpdateProfileResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FUpdateProfileRequestPtr Request;
    public:
        explicit FUpdateProfileTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FUpdateProfileRequestPtr Request
        );
        FUpdateProfileTask(
            const FUpdateProfileTask& From
        );
        virtual ~FUpdateProfileTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FUpdateProfileResultPtr> Result) override;
    };
    typedef TSharedPtr<FUpdateProfileTask, ESPMode::ThreadSafe> FUpdateProfileTaskPtr;
}