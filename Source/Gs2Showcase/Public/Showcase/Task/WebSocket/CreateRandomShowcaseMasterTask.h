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
#include "Showcase/Request/CreateRandomShowcaseMasterRequest.h"
#include "Showcase/Result/CreateRandomShowcaseMasterResult.h"

namespace Gs2::Showcase::Task::WebSocket
{
    class GS2SHOWCASE_API FCreateRandomShowcaseMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FCreateRandomShowcaseMasterResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FCreateRandomShowcaseMasterRequestPtr Request;
    public:
        explicit FCreateRandomShowcaseMasterTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FCreateRandomShowcaseMasterRequestPtr Request
        );
        FCreateRandomShowcaseMasterTask(
            const FCreateRandomShowcaseMasterTask& From
        );
        virtual ~FCreateRandomShowcaseMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FCreateRandomShowcaseMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FCreateRandomShowcaseMasterTask, ESPMode::ThreadSafe> FCreateRandomShowcaseMasterTaskPtr;
}