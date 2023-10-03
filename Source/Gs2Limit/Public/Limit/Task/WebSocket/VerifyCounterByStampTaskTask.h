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
#include "Limit/Request/VerifyCounterByStampTaskRequest.h"
#include "Limit/Result/VerifyCounterByStampTaskResult.h"

namespace Gs2::Limit::Task::WebSocket
{
    class GS2LIMIT_API FVerifyCounterByStampTaskTask final : public Gs2::Core::Util::TGs2Future<Result::FVerifyCounterByStampTaskResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FVerifyCounterByStampTaskRequestPtr Request;
    public:
        explicit FVerifyCounterByStampTaskTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FVerifyCounterByStampTaskRequestPtr Request
        );
        FVerifyCounterByStampTaskTask(
            const FVerifyCounterByStampTaskTask& From
        );
        virtual ~FVerifyCounterByStampTaskTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FVerifyCounterByStampTaskResultPtr> Result) override;
    };
    typedef TSharedPtr<FVerifyCounterByStampTaskTask, ESPMode::ThreadSafe> FVerifyCounterByStampTaskTaskPtr;
}