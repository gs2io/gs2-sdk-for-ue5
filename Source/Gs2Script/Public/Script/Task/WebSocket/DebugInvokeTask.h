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
#include "Script/Request/DebugInvokeRequest.h"
#include "Script/Result/DebugInvokeResult.h"

namespace Gs2::Script::Task::WebSocket
{
    class GS2SCRIPT_API FDebugInvokeTask final : public Gs2::Core::Util::TGs2Future<Result::FDebugInvokeResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FDebugInvokeRequestPtr Request;
    public:
        explicit FDebugInvokeTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FDebugInvokeRequestPtr Request
        );
        FDebugInvokeTask(
            const FDebugInvokeTask& From
        );
        virtual ~FDebugInvokeTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDebugInvokeResultPtr> Result) override;
    };
    typedef TSharedPtr<FDebugInvokeTask, ESPMode::ThreadSafe> FDebugInvokeTaskPtr;
}