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
#include "Core/Net/AbstractWebSocketGs2Client.h"
#include "Request/LoginRequest.h"
#include "Task/WebSocket/LoginTask.h"
#include "Request/LoginBySignatureRequest.h"
#include "Task/WebSocket/LoginBySignatureTask.h"
#include "Request/FederationRequest.h"
#include "Task/WebSocket/FederationTask.h"
#include "Request/IssueTimeOffsetTokenByUserIdRequest.h"
#include "Task/WebSocket/IssueTimeOffsetTokenByUserIdTask.h"
#include "Request/GetServiceVersionRequest.h"
#include "Task/WebSocket/GetServiceVersionTask.h"

namespace Gs2::Auth
{
    class GS2AUTH_API FGs2AuthWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2AuthWebSocketClient(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session
        ): FAbstractWebSocketGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::WebSocket::FLoginTask>> Login(
            const Request::FLoginRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FLoginBySignatureTask>> LoginBySignature(
            const Request::FLoginBySignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FFederationTask>> Federation(
            const Request::FFederationRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FIssueTimeOffsetTokenByUserIdTask>> IssueTimeOffsetTokenByUserId(
            const Request::FIssueTimeOffsetTokenByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetServiceVersionTask>> GetServiceVersion(
            const Request::FGetServiceVersionRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2AuthWebSocketClient, ESPMode::ThreadSafe> FGs2AuthWebSocketClientPtr;
}