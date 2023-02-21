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
#include "Experience/Request/GetStatusRequest.h"
#include "Experience/Result/GetStatusResult.h"

namespace Gs2::Experience::Task::Rest
{
    class GS2EXPERIENCE_API FGetStatusTask final : public Gs2::Core::Util::TGs2Future<Result::FGetStatusResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FGetStatusRequestPtr Request;
    public:
        explicit FGetStatusTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FGetStatusRequestPtr Request
        );
        FGetStatusTask(
            const FGetStatusTask& From
        );
        virtual ~FGetStatusTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetStatusResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetStatusTask, ESPMode::ThreadSafe> FGetStatusTaskPtr;
}