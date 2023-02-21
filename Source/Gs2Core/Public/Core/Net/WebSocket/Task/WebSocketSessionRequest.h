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

typedef FString FGs2ClientId;
typedef FString FGs2ProjectToken;
typedef FString FGs2SessionTaskId;
typedef FString FGs2Service;
typedef FString FGs2Component;
typedef FString FGs2Function;

namespace Gs2::Core::Net::WebSocket::Task
{
    class GS2CORE_API FWebSocketSessionRequest
    {
        FGs2SessionTaskId TaskIdValue;
        TSharedPtr<FJsonObject> BodyValue;
    public:
        FWebSocketSessionRequest(
            TSharedPtr<FJsonObject> Body
        );
        ~FWebSocketSessionRequest();
    
        FGs2SessionTaskId TaskId() const;

        void AddHeader(
            const FGs2ClientId ClientId,
            const FGs2ProjectToken ProjectToken,
            const FGs2Service Service,
            const FGs2Component Component,
            const FGs2Function Function
        ) const;
        FString Payload() const;
    };
}