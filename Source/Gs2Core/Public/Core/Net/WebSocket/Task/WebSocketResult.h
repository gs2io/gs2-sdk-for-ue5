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
#include "WebSocketSessionRequest.h"
#include "Core/Model/Gs2Error.h"

namespace Gs2::Core::Net::WebSocket::Task
{
    class GS2CORE_API FWebSocketResult
    {
        FGs2SessionTaskId TaskIdValue;
        uint16 StatusCodeValue;
        TSharedPtr<FJsonObject> BodyValue;
        TSharedPtr<Gs2::Core::Model::FGs2Error> ErrorValue;
    public:
        FWebSocketResult(
            FGs2SessionTaskId TaskId,
            uint16 StatusCode,
            TSharedPtr<FJsonObject> Body
        );
        FWebSocketResult(
            FGs2SessionTaskId TaskId,
            uint16 StatusCode,
            TSharedPtr<Gs2::Core::Model::FGs2Error> Error
        );
        ~FWebSocketResult();

        FGs2SessionTaskId TaskId();
        bool IsError() const;
        uint16 StatusCode() const;
        TSharedPtr<FJsonObject> Body();
        TSharedPtr<Gs2::Core::Model::FGs2Error> Error();
    
        static TSharedPtr<FWebSocketResult> FromJson(const TSharedPtr<FJsonObject> Data);
    };
}