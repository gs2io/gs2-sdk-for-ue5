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
#include "Limit/Request/CountUpByStampTaskRequest.h"
#include "Limit/Result/CountUpByStampTaskResult.h"

namespace Gs2::Limit::Task::WebSocket
{
    class GS2LIMIT_API FCountUpByStampTaskTask final : public Gs2::Core::Util::TGs2Future<Result::FCountUpByStampTaskResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FCountUpByStampTaskRequestPtr Request;
    public:
        explicit FCountUpByStampTaskTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FCountUpByStampTaskRequestPtr Request
        );
        FCountUpByStampTaskTask(
            const FCountUpByStampTaskTask& From
        );
        virtual ~FCountUpByStampTaskTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FCountUpByStampTaskResultPtr> Result) override;
    };
    typedef TSharedPtr<FCountUpByStampTaskTask, ESPMode::ThreadSafe> FCountUpByStampTaskTaskPtr;
}