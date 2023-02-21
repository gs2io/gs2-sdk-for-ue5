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

#include "Auth/Gs2AuthWebSocketClient.h"

namespace Gs2::Auth
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FLoginTask>> FGs2AuthWebSocketClient::Login(
        const Request::FLoginRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FLoginTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FLoginBySignatureTask>> FGs2AuthWebSocketClient::LoginBySignature(
        const Request::FLoginBySignatureRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FLoginBySignatureTask>>(
            Session,
            Request
        );
    }
}