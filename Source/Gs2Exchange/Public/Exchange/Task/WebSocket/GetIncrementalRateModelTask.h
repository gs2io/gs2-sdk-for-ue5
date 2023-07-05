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
#include "Exchange/Request/GetIncrementalRateModelRequest.h"
#include "Exchange/Result/GetIncrementalRateModelResult.h"

namespace Gs2::Exchange::Task::WebSocket
{
    class GS2EXCHANGE_API FGetIncrementalRateModelTask final : public Gs2::Core::Util::TGs2Future<Result::FGetIncrementalRateModelResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FGetIncrementalRateModelRequestPtr Request;
    public:
        explicit FGetIncrementalRateModelTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FGetIncrementalRateModelRequestPtr Request
        );
        FGetIncrementalRateModelTask(
            const FGetIncrementalRateModelTask& From
        );
        virtual ~FGetIncrementalRateModelTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetIncrementalRateModelResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetIncrementalRateModelTask, ESPMode::ThreadSafe> FGetIncrementalRateModelTaskPtr;
}