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
#include "Deploy/Request/ForceDeleteStackRequest.h"
#include "Deploy/Result/ForceDeleteStackResult.h"

namespace Gs2::Deploy::Task::WebSocket
{
    class GS2DEPLOY_API FForceDeleteStackTask final : public Gs2::Core::Util::TGs2Future<Result::FForceDeleteStackResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FForceDeleteStackRequestPtr Request;
    public:
        explicit FForceDeleteStackTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FForceDeleteStackRequestPtr Request
        );
        FForceDeleteStackTask(
            const FForceDeleteStackTask& From
        );
        virtual ~FForceDeleteStackTask() override = default;

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FForceDeleteStackResultPtr> Result) override;
    };
    typedef TSharedPtr<FForceDeleteStackTask, ESPMode::ThreadSafe> FForceDeleteStackTaskPtr;
}