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

#include "Identifier/Gs2IdentifierRestClient.h"

namespace Gs2::Identifier
{

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeUsersTask>> FGs2IdentifierRestClient::DescribeUsers(
        const Request::FDescribeUsersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeUsersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateUserTask>> FGs2IdentifierRestClient::CreateUser(
        const Request::FCreateUserRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateUserTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateUserTask>> FGs2IdentifierRestClient::UpdateUser(
        const Request::FUpdateUserRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateUserTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetUserTask>> FGs2IdentifierRestClient::GetUser(
        const Request::FGetUserRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetUserTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteUserTask>> FGs2IdentifierRestClient::DeleteUser(
        const Request::FDeleteUserRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteUserTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSecurityPoliciesTask>> FGs2IdentifierRestClient::DescribeSecurityPolicies(
        const Request::FDescribeSecurityPoliciesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSecurityPoliciesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeCommonSecurityPoliciesTask>> FGs2IdentifierRestClient::DescribeCommonSecurityPolicies(
        const Request::FDescribeCommonSecurityPoliciesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeCommonSecurityPoliciesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateSecurityPolicyTask>> FGs2IdentifierRestClient::CreateSecurityPolicy(
        const Request::FCreateSecurityPolicyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateSecurityPolicyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateSecurityPolicyTask>> FGs2IdentifierRestClient::UpdateSecurityPolicy(
        const Request::FUpdateSecurityPolicyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateSecurityPolicyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSecurityPolicyTask>> FGs2IdentifierRestClient::GetSecurityPolicy(
        const Request::FGetSecurityPolicyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSecurityPolicyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteSecurityPolicyTask>> FGs2IdentifierRestClient::DeleteSecurityPolicy(
        const Request::FDeleteSecurityPolicyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteSecurityPolicyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeIdentifiersTask>> FGs2IdentifierRestClient::DescribeIdentifiers(
        const Request::FDescribeIdentifiersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeIdentifiersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateIdentifierTask>> FGs2IdentifierRestClient::CreateIdentifier(
        const Request::FCreateIdentifierRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateIdentifierTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetIdentifierTask>> FGs2IdentifierRestClient::GetIdentifier(
        const Request::FGetIdentifierRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetIdentifierTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteIdentifierTask>> FGs2IdentifierRestClient::DeleteIdentifier(
        const Request::FDeleteIdentifierRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteIdentifierTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribePasswordsTask>> FGs2IdentifierRestClient::DescribePasswords(
        const Request::FDescribePasswordsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribePasswordsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreatePasswordTask>> FGs2IdentifierRestClient::CreatePassword(
        const Request::FCreatePasswordRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreatePasswordTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetPasswordTask>> FGs2IdentifierRestClient::GetPassword(
        const Request::FGetPasswordRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetPasswordTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeletePasswordTask>> FGs2IdentifierRestClient::DeletePassword(
        const Request::FDeletePasswordRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeletePasswordTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetHasSecurityPolicyTask>> FGs2IdentifierRestClient::GetHasSecurityPolicy(
        const Request::FGetHasSecurityPolicyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetHasSecurityPolicyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAttachSecurityPolicyTask>> FGs2IdentifierRestClient::AttachSecurityPolicy(
        const Request::FAttachSecurityPolicyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAttachSecurityPolicyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDetachSecurityPolicyTask>> FGs2IdentifierRestClient::DetachSecurityPolicy(
        const Request::FDetachSecurityPolicyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDetachSecurityPolicyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FLoginTask>> FGs2IdentifierRestClient::Login(
        const Request::FLoginRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FLoginTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FLoginByUserTask>> FGs2IdentifierRestClient::LoginByUser(
        const Request::FLoginByUserRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FLoginByUserTask>>(
            Session,
            Request
        );
    }
}