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

#include "Identifier/Gs2IdentifierWebSocketClient.h"

namespace Gs2::Identifier
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeUsersTask>> FGs2IdentifierWebSocketClient::DescribeUsers(
        const Request::FDescribeUsersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeUsersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateUserTask>> FGs2IdentifierWebSocketClient::CreateUser(
        const Request::FCreateUserRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateUserTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateUserTask>> FGs2IdentifierWebSocketClient::UpdateUser(
        const Request::FUpdateUserRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateUserTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetUserTask>> FGs2IdentifierWebSocketClient::GetUser(
        const Request::FGetUserRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetUserTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteUserTask>> FGs2IdentifierWebSocketClient::DeleteUser(
        const Request::FDeleteUserRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteUserTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSecurityPoliciesTask>> FGs2IdentifierWebSocketClient::DescribeSecurityPolicies(
        const Request::FDescribeSecurityPoliciesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSecurityPoliciesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCommonSecurityPoliciesTask>> FGs2IdentifierWebSocketClient::DescribeCommonSecurityPolicies(
        const Request::FDescribeCommonSecurityPoliciesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeCommonSecurityPoliciesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateSecurityPolicyTask>> FGs2IdentifierWebSocketClient::CreateSecurityPolicy(
        const Request::FCreateSecurityPolicyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateSecurityPolicyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateSecurityPolicyTask>> FGs2IdentifierWebSocketClient::UpdateSecurityPolicy(
        const Request::FUpdateSecurityPolicyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateSecurityPolicyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSecurityPolicyTask>> FGs2IdentifierWebSocketClient::GetSecurityPolicy(
        const Request::FGetSecurityPolicyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSecurityPolicyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSecurityPolicyTask>> FGs2IdentifierWebSocketClient::DeleteSecurityPolicy(
        const Request::FDeleteSecurityPolicyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteSecurityPolicyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeIdentifiersTask>> FGs2IdentifierWebSocketClient::DescribeIdentifiers(
        const Request::FDescribeIdentifiersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeIdentifiersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateIdentifierTask>> FGs2IdentifierWebSocketClient::CreateIdentifier(
        const Request::FCreateIdentifierRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateIdentifierTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetIdentifierTask>> FGs2IdentifierWebSocketClient::GetIdentifier(
        const Request::FGetIdentifierRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetIdentifierTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteIdentifierTask>> FGs2IdentifierWebSocketClient::DeleteIdentifier(
        const Request::FDeleteIdentifierRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteIdentifierTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribePasswordsTask>> FGs2IdentifierWebSocketClient::DescribePasswords(
        const Request::FDescribePasswordsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribePasswordsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreatePasswordTask>> FGs2IdentifierWebSocketClient::CreatePassword(
        const Request::FCreatePasswordRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreatePasswordTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetPasswordTask>> FGs2IdentifierWebSocketClient::GetPassword(
        const Request::FGetPasswordRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetPasswordTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FEnableMfaTask>> FGs2IdentifierWebSocketClient::EnableMfa(
        const Request::FEnableMfaRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FEnableMfaTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FChallengeMfaTask>> FGs2IdentifierWebSocketClient::ChallengeMfa(
        const Request::FChallengeMfaRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FChallengeMfaTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDisableMfaTask>> FGs2IdentifierWebSocketClient::DisableMfa(
        const Request::FDisableMfaRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDisableMfaTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeletePasswordTask>> FGs2IdentifierWebSocketClient::DeletePassword(
        const Request::FDeletePasswordRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeletePasswordTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetHasSecurityPolicyTask>> FGs2IdentifierWebSocketClient::GetHasSecurityPolicy(
        const Request::FGetHasSecurityPolicyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetHasSecurityPolicyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAttachSecurityPolicyTask>> FGs2IdentifierWebSocketClient::AttachSecurityPolicy(
        const Request::FAttachSecurityPolicyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAttachSecurityPolicyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDetachSecurityPolicyTask>> FGs2IdentifierWebSocketClient::DetachSecurityPolicy(
        const Request::FDetachSecurityPolicyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDetachSecurityPolicyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FLoginTask>> FGs2IdentifierWebSocketClient::Login(
        const Request::FLoginRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FLoginTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FLoginByUserTask>> FGs2IdentifierWebSocketClient::LoginByUser(
        const Request::FLoginByUserRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FLoginByUserTask>>(
            Session,
            Request
        );
    }
}