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
#include "Request/DescribeUsersRequest.h"
#include "Task/WebSocket/DescribeUsersTask.h"
#include "Request/CreateUserRequest.h"
#include "Task/WebSocket/CreateUserTask.h"
#include "Request/UpdateUserRequest.h"
#include "Task/WebSocket/UpdateUserTask.h"
#include "Request/GetUserRequest.h"
#include "Task/WebSocket/GetUserTask.h"
#include "Request/DeleteUserRequest.h"
#include "Task/WebSocket/DeleteUserTask.h"
#include "Request/DescribeSecurityPoliciesRequest.h"
#include "Task/WebSocket/DescribeSecurityPoliciesTask.h"
#include "Request/DescribeCommonSecurityPoliciesRequest.h"
#include "Task/WebSocket/DescribeCommonSecurityPoliciesTask.h"
#include "Request/CreateSecurityPolicyRequest.h"
#include "Task/WebSocket/CreateSecurityPolicyTask.h"
#include "Request/UpdateSecurityPolicyRequest.h"
#include "Task/WebSocket/UpdateSecurityPolicyTask.h"
#include "Request/GetSecurityPolicyRequest.h"
#include "Task/WebSocket/GetSecurityPolicyTask.h"
#include "Request/DeleteSecurityPolicyRequest.h"
#include "Task/WebSocket/DeleteSecurityPolicyTask.h"
#include "Request/DescribeIdentifiersRequest.h"
#include "Task/WebSocket/DescribeIdentifiersTask.h"
#include "Request/CreateIdentifierRequest.h"
#include "Task/WebSocket/CreateIdentifierTask.h"
#include "Request/GetIdentifierRequest.h"
#include "Task/WebSocket/GetIdentifierTask.h"
#include "Request/DeleteIdentifierRequest.h"
#include "Task/WebSocket/DeleteIdentifierTask.h"
#include "Request/DescribeAttachedGuardsRequest.h"
#include "Task/WebSocket/DescribeAttachedGuardsTask.h"
#include "Request/AttachGuardRequest.h"
#include "Task/WebSocket/AttachGuardTask.h"
#include "Request/DetachGuardRequest.h"
#include "Task/WebSocket/DetachGuardTask.h"
#include "Request/DescribePasswordsRequest.h"
#include "Task/WebSocket/DescribePasswordsTask.h"
#include "Request/CreatePasswordRequest.h"
#include "Task/WebSocket/CreatePasswordTask.h"
#include "Request/GetPasswordRequest.h"
#include "Task/WebSocket/GetPasswordTask.h"
#include "Request/EnableMfaRequest.h"
#include "Task/WebSocket/EnableMfaTask.h"
#include "Request/ChallengeMfaRequest.h"
#include "Task/WebSocket/ChallengeMfaTask.h"
#include "Request/DisableMfaRequest.h"
#include "Task/WebSocket/DisableMfaTask.h"
#include "Request/DeletePasswordRequest.h"
#include "Task/WebSocket/DeletePasswordTask.h"
#include "Request/GetHasSecurityPolicyRequest.h"
#include "Task/WebSocket/GetHasSecurityPolicyTask.h"
#include "Request/AttachSecurityPolicyRequest.h"
#include "Task/WebSocket/AttachSecurityPolicyTask.h"
#include "Request/DetachSecurityPolicyRequest.h"
#include "Task/WebSocket/DetachSecurityPolicyTask.h"
#include "Request/LoginRequest.h"
#include "Task/WebSocket/LoginTask.h"
#include "Request/LoginByUserRequest.h"
#include "Task/WebSocket/LoginByUserTask.h"

namespace Gs2::Identifier
{
    class GS2IDENTIFIER_API FGs2IdentifierWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2IdentifierWebSocketClient(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session
        ): FAbstractWebSocketGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeUsersTask>> DescribeUsers(
            const Request::FDescribeUsersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateUserTask>> CreateUser(
            const Request::FCreateUserRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateUserTask>> UpdateUser(
            const Request::FUpdateUserRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetUserTask>> GetUser(
            const Request::FGetUserRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteUserTask>> DeleteUser(
            const Request::FDeleteUserRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSecurityPoliciesTask>> DescribeSecurityPolicies(
            const Request::FDescribeSecurityPoliciesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCommonSecurityPoliciesTask>> DescribeCommonSecurityPolicies(
            const Request::FDescribeCommonSecurityPoliciesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateSecurityPolicyTask>> CreateSecurityPolicy(
            const Request::FCreateSecurityPolicyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateSecurityPolicyTask>> UpdateSecurityPolicy(
            const Request::FUpdateSecurityPolicyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSecurityPolicyTask>> GetSecurityPolicy(
            const Request::FGetSecurityPolicyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSecurityPolicyTask>> DeleteSecurityPolicy(
            const Request::FDeleteSecurityPolicyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeIdentifiersTask>> DescribeIdentifiers(
            const Request::FDescribeIdentifiersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateIdentifierTask>> CreateIdentifier(
            const Request::FCreateIdentifierRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetIdentifierTask>> GetIdentifier(
            const Request::FGetIdentifierRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteIdentifierTask>> DeleteIdentifier(
            const Request::FDeleteIdentifierRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeAttachedGuardsTask>> DescribeAttachedGuards(
            const Request::FDescribeAttachedGuardsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAttachGuardTask>> AttachGuard(
            const Request::FAttachGuardRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDetachGuardTask>> DetachGuard(
            const Request::FDetachGuardRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribePasswordsTask>> DescribePasswords(
            const Request::FDescribePasswordsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreatePasswordTask>> CreatePassword(
            const Request::FCreatePasswordRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetPasswordTask>> GetPassword(
            const Request::FGetPasswordRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FEnableMfaTask>> EnableMfa(
            const Request::FEnableMfaRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FChallengeMfaTask>> ChallengeMfa(
            const Request::FChallengeMfaRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDisableMfaTask>> DisableMfa(
            const Request::FDisableMfaRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeletePasswordTask>> DeletePassword(
            const Request::FDeletePasswordRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetHasSecurityPolicyTask>> GetHasSecurityPolicy(
            const Request::FGetHasSecurityPolicyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAttachSecurityPolicyTask>> AttachSecurityPolicy(
            const Request::FAttachSecurityPolicyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDetachSecurityPolicyTask>> DetachSecurityPolicy(
            const Request::FDetachSecurityPolicyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FLoginTask>> Login(
            const Request::FLoginRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FLoginByUserTask>> LoginByUser(
            const Request::FLoginByUserRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2IdentifierWebSocketClient, ESPMode::ThreadSafe> FGs2IdentifierWebSocketClientPtr;
}