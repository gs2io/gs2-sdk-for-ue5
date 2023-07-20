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
#include "Enchant/Request/GetBalanceParameterStatusRequest.h"
#include "Enchant/Result/GetBalanceParameterStatusResult.h"

namespace Gs2::Enchant::Task::WebSocket
{
    class GS2ENCHANT_API FGetBalanceParameterStatusTask final : public Gs2::Core::Util::TGs2Future<Result::FGetBalanceParameterStatusResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FGetBalanceParameterStatusRequestPtr Request;
    public:
        explicit FGetBalanceParameterStatusTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FGetBalanceParameterStatusRequestPtr Request
        );
        FGetBalanceParameterStatusTask(
            const FGetBalanceParameterStatusTask& From
        );
        virtual ~FGetBalanceParameterStatusTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetBalanceParameterStatusResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetBalanceParameterStatusTask, ESPMode::ThreadSafe> FGetBalanceParameterStatusTaskPtr;
}