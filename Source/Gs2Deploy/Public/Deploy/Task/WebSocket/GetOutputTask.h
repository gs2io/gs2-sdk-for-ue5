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
#include "Deploy/Request/GetOutputRequest.h"
#include "Deploy/Result/GetOutputResult.h"

namespace Gs2::Deploy::Task::WebSocket
{
    class GS2DEPLOY_API FGetOutputTask final : public Gs2::Core::Util::TGs2Future<Result::FGetOutputResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FGetOutputRequestPtr Request;
    public:
        explicit FGetOutputTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FGetOutputRequestPtr Request
        );
        FGetOutputTask(
            const FGetOutputTask& From
        );
        virtual ~FGetOutputTask() override = default;

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetOutputResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetOutputTask, ESPMode::ThreadSafe> FGetOutputTaskPtr;
}