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
#include "Account/Request/CreateTakeOverOpenIdConnectAndByUserIdRequest.h"
#include "Account/Result/CreateTakeOverOpenIdConnectAndByUserIdResult.h"

namespace Gs2::Account::Task::WebSocket
{
    class GS2ACCOUNT_API FCreateTakeOverOpenIdConnectAndByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FCreateTakeOverOpenIdConnectAndByUserIdResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FCreateTakeOverOpenIdConnectAndByUserIdRequestPtr Request;
    public:
        explicit FCreateTakeOverOpenIdConnectAndByUserIdTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FCreateTakeOverOpenIdConnectAndByUserIdRequestPtr Request
        );
        FCreateTakeOverOpenIdConnectAndByUserIdTask(
            const FCreateTakeOverOpenIdConnectAndByUserIdTask& From
        );
        virtual ~FCreateTakeOverOpenIdConnectAndByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FCreateTakeOverOpenIdConnectAndByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FCreateTakeOverOpenIdConnectAndByUserIdTask, ESPMode::ThreadSafe> FCreateTakeOverOpenIdConnectAndByUserIdTaskPtr;
}