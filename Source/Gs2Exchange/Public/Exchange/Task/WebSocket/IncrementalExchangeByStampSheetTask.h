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
#include "Exchange/Request/IncrementalExchangeByStampSheetRequest.h"
#include "Exchange/Result/IncrementalExchangeByStampSheetResult.h"

namespace Gs2::Exchange::Task::WebSocket
{
    class GS2EXCHANGE_API FIncrementalExchangeByStampSheetTask final : public Gs2::Core::Util::TGs2Future<Result::FIncrementalExchangeByStampSheetResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FIncrementalExchangeByStampSheetRequestPtr Request;
    public:
        explicit FIncrementalExchangeByStampSheetTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FIncrementalExchangeByStampSheetRequestPtr Request
        );
        FIncrementalExchangeByStampSheetTask(
            const FIncrementalExchangeByStampSheetTask& From
        );
        virtual ~FIncrementalExchangeByStampSheetTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FIncrementalExchangeByStampSheetResultPtr> Result) override;
    };
    typedef TSharedPtr<FIncrementalExchangeByStampSheetTask, ESPMode::ThreadSafe> FIncrementalExchangeByStampSheetTaskPtr;
}