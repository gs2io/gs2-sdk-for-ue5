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
#include "LoginReward/Request/GetReceiveStatusRequest.h"
#include "LoginReward/Result/GetReceiveStatusResult.h"

namespace Gs2::LoginReward::Task::Rest
{
    class GS2LOGINREWARD_API FGetReceiveStatusTask final : public Gs2::Core::Util::TGs2Future<Result::FGetReceiveStatusResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FGetReceiveStatusRequestPtr Request;
    public:
        explicit FGetReceiveStatusTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FGetReceiveStatusRequestPtr Request
        );
        FGetReceiveStatusTask(
            const FGetReceiveStatusTask& From
        );
        virtual ~FGetReceiveStatusTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetReceiveStatusResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetReceiveStatusTask, ESPMode::ThreadSafe> FGetReceiveStatusTaskPtr;
}