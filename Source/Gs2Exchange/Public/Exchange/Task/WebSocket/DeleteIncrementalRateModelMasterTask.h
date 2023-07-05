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
#include "Exchange/Request/DeleteIncrementalRateModelMasterRequest.h"
#include "Exchange/Result/DeleteIncrementalRateModelMasterResult.h"

namespace Gs2::Exchange::Task::WebSocket
{
    class GS2EXCHANGE_API FDeleteIncrementalRateModelMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FDeleteIncrementalRateModelMasterResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FDeleteIncrementalRateModelMasterRequestPtr Request;
    public:
        explicit FDeleteIncrementalRateModelMasterTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FDeleteIncrementalRateModelMasterRequestPtr Request
        );
        FDeleteIncrementalRateModelMasterTask(
            const FDeleteIncrementalRateModelMasterTask& From
        );
        virtual ~FDeleteIncrementalRateModelMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDeleteIncrementalRateModelMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FDeleteIncrementalRateModelMasterTask, ESPMode::ThreadSafe> FDeleteIncrementalRateModelMasterTaskPtr;
}