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
#include "Lottery/Request/CreatePrizeTableMasterRequest.h"
#include "Lottery/Result/CreatePrizeTableMasterResult.h"

namespace Gs2::Lottery::Task::WebSocket
{
    class GS2LOTTERY_API FCreatePrizeTableMasterTask final : public Gs2::Core::Util::TGs2Future<Result::FCreatePrizeTableMasterResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FCreatePrizeTableMasterRequestPtr Request;
    public:
        explicit FCreatePrizeTableMasterTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FCreatePrizeTableMasterRequestPtr Request
        );
        FCreatePrizeTableMasterTask(
            const FCreatePrizeTableMasterTask& From
        );
        virtual ~FCreatePrizeTableMasterTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FCreatePrizeTableMasterResultPtr> Result) override;
    };
    typedef TSharedPtr<FCreatePrizeTableMasterTask, ESPMode::ThreadSafe> FCreatePrizeTableMasterTaskPtr;
}