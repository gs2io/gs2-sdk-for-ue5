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
#include "Log/Request/CountExecuteStampSheetLogRequest.h"
#include "Log/Result/CountExecuteStampSheetLogResult.h"

namespace Gs2::Log::Task::WebSocket
{
    class GS2LOG_API FCountExecuteStampSheetLogTask final : public Gs2::Core::Util::TGs2Future<Result::FCountExecuteStampSheetLogResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FCountExecuteStampSheetLogRequestPtr Request;
    public:
        explicit FCountExecuteStampSheetLogTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FCountExecuteStampSheetLogRequestPtr Request
        );
        FCountExecuteStampSheetLogTask(
            const FCountExecuteStampSheetLogTask& From
        );
        virtual ~FCountExecuteStampSheetLogTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FCountExecuteStampSheetLogResultPtr> Result) override;
    };
    typedef TSharedPtr<FCountExecuteStampSheetLogTask, ESPMode::ThreadSafe> FCountExecuteStampSheetLogTaskPtr;
}