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
#include "SeasonRating/Request/CreateMatchSessionRequest.h"
#include "SeasonRating/Result/CreateMatchSessionResult.h"

namespace Gs2::SeasonRating::Task::WebSocket
{
    class GS2SEASONRATING_API FCreateMatchSessionTask final : public Gs2::Core::Util::TGs2Future<Result::FCreateMatchSessionResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FCreateMatchSessionRequestPtr Request;
    public:
        explicit FCreateMatchSessionTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FCreateMatchSessionRequestPtr Request
        );
        FCreateMatchSessionTask(
            const FCreateMatchSessionTask& From
        );
        virtual ~FCreateMatchSessionTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FCreateMatchSessionResultPtr> Result) override;
    };
    typedef TSharedPtr<FCreateMatchSessionTask, ESPMode::ThreadSafe> FCreateMatchSessionTaskPtr;
}