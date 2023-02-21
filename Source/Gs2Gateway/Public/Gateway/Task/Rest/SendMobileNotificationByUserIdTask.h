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
#include "Gateway/Request/SendMobileNotificationByUserIdRequest.h"
#include "Gateway/Result/SendMobileNotificationByUserIdResult.h"

namespace Gs2::Gateway::Task::Rest
{
    class GS2GATEWAY_API FSendMobileNotificationByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FSendMobileNotificationByUserIdResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FSendMobileNotificationByUserIdRequestPtr Request;
    public:
        explicit FSendMobileNotificationByUserIdTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FSendMobileNotificationByUserIdRequestPtr Request
        );
        FSendMobileNotificationByUserIdTask(
            const FSendMobileNotificationByUserIdTask& From
        );
        virtual ~FSendMobileNotificationByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FSendMobileNotificationByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FSendMobileNotificationByUserIdTask, ESPMode::ThreadSafe> FSendMobileNotificationByUserIdTaskPtr;
}