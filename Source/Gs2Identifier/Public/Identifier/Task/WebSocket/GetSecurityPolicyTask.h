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
#include "Identifier/Request/GetSecurityPolicyRequest.h"
#include "Identifier/Result/GetSecurityPolicyResult.h"

namespace Gs2::Identifier::Task::WebSocket
{
    class GS2IDENTIFIER_API FGetSecurityPolicyTask final : public Gs2::Core::Util::TGs2Future<Result::FGetSecurityPolicyResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FGetSecurityPolicyRequestPtr Request;
    public:
        explicit FGetSecurityPolicyTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FGetSecurityPolicyRequestPtr Request
        );
        FGetSecurityPolicyTask(
            const FGetSecurityPolicyTask& From
        );
        virtual ~FGetSecurityPolicyTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetSecurityPolicyResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetSecurityPolicyTask, ESPMode::ThreadSafe> FGetSecurityPolicyTaskPtr;
}