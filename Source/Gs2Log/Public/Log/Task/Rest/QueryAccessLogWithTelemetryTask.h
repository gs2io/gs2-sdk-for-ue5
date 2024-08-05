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
#include "Log/Request/QueryAccessLogWithTelemetryRequest.h"
#include "Log/Result/QueryAccessLogWithTelemetryResult.h"

namespace Gs2::Log::Task::Rest
{
    class GS2LOG_API FQueryAccessLogWithTelemetryTask final : public Gs2::Core::Util::TGs2Future<Result::FQueryAccessLogWithTelemetryResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FQueryAccessLogWithTelemetryRequestPtr Request;
    public:
        explicit FQueryAccessLogWithTelemetryTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FQueryAccessLogWithTelemetryRequestPtr Request
        );
        FQueryAccessLogWithTelemetryTask(
            const FQueryAccessLogWithTelemetryTask& From
        );
        virtual ~FQueryAccessLogWithTelemetryTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FQueryAccessLogWithTelemetryResultPtr> Result) override;
    };
    typedef TSharedPtr<FQueryAccessLogWithTelemetryTask, ESPMode::ThreadSafe> FQueryAccessLogWithTelemetryTaskPtr;
}