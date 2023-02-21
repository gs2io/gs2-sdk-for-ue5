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
#include "MegaField/Request/DeleteAreaModelMasterRequest.h"
#include "MegaField/Result/DeleteAreaModelMasterResult.h"

namespace Gs2::MegaField::Task::WebSocket
{
    class GS2MEGAFIELD_API FDeleteAreaModelMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FDeleteAreaModelMasterResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FDeleteAreaModelMasterRequestPtr Request;
    public:
        explicit FDeleteAreaModelMasterTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FDeleteAreaModelMasterRequestPtr Request
        );
        FDeleteAreaModelMasterTask(
            const FDeleteAreaModelMasterTask& From
        );
        virtual ~FDeleteAreaModelMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDeleteAreaModelMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FDeleteAreaModelMasterTask, ESPMode::ThreadSafe> FDeleteAreaModelMasterTaskPtr;
}