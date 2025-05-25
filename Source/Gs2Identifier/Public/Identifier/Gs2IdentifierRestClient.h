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
#include "Core/Net/AbstractGs2Client.h"
#include "Request/DescribeUsersRequest.h"
#include "Task/Rest/DescribeUsersTask.h"
#include "Request/CreateUserRequest.h"
#include "Task/Rest/CreateUserTask.h"
#include "Request/UpdateUserRequest.h"
#include "Task/Rest/UpdateUserTask.h"
#include "Request/GetUserRequest.h"
#include "Task/Rest/GetUserTask.h"
#include "Request/DeleteUserRequest.h"
#include "Task/Rest/DeleteUserTask.h"
#include "Request/DescribeSecurityPoliciesRequest.h"
#include "Task/Rest/DescribeSecurityPoliciesTask.h"
#include "Request/DescribeCommonSecurityPoliciesRequest.h"
#include "Task/Rest/DescribeCommonSecurityPoliciesTask.h"
#include "Request/CreateSecurityPolicyRequest.h"
#include "Task/Rest/CreateSecurityPolicyTask.h"
#include "Request/UpdateSecurityPolicyRequest.h"
#include "Task/Rest/UpdateSecurityPolicyTask.h"
#include "Request/GetSecurityPolicyRequest.h"
#include "Task/Rest/GetSecurityPolicyTask.h"
#include "Request/DeleteSecurityPolicyRequest.h"
#include "Task/Rest/DeleteSecurityPolicyTask.h"
#include "Request/DescribeIdentifiersRequest.h"
#include "Task/Rest/DescribeIdentifiersTask.h"
#include "Request/CreateIdentifierRequest.h"
#include "Task/Rest/CreateIdentifierTask.h"
#include "Request/GetIdentifierRequest.h"
#include "Task/Rest/GetIdentifierTask.h"
#include "Request/DeleteIdentifierRequest.h"
#include "Task/Rest/DeleteIdentifierTask.h"
#include "Request/DescribeAttachedGuardsRequest.h"
#include "Task/Rest/DescribeAttachedGuardsTask.h"
#include "Request/AttachGuardRequest.h"
#include "Task/Rest/AttachGuardTask.h"
#include "Request/DetachGuardRequest.h"
#include "Task/Rest/DetachGuardTask.h"
#include "Request/GetServiceVersionRequest.h"
#include "Task/Rest/GetServiceVersionTask.h"
#include "Request/CreatePasswordRequest.h"
#include "Task/Rest/CreatePasswordTask.h"
#include "Request/GetPasswordRequest.h"
#include "Task/Rest/GetPasswordTask.h"
#include "Request/EnableMfaRequest.h"
#include "Task/Rest/EnableMfaTask.h"
#include "Request/ChallengeMfaRequest.h"
#include "Task/Rest/ChallengeMfaTask.h"
#include "Request/DisableMfaRequest.h"
#include "Task/Rest/DisableMfaTask.h"
#include "Request/DeletePasswordRequest.h"
#include "Task/Rest/DeletePasswordTask.h"
#include "Request/GetHasSecurityPolicyRequest.h"
#include "Task/Rest/GetHasSecurityPolicyTask.h"
#include "Request/AttachSecurityPolicyRequest.h"
#include "Task/Rest/AttachSecurityPolicyTask.h"
#include "Request/DetachSecurityPolicyRequest.h"
#include "Task/Rest/DetachSecurityPolicyTask.h"
#include "Request/LoginRequest.h"
#include "Task/Rest/LoginTask.h"
#include "Request/LoginByUserRequest.h"
#include "Task/Rest/LoginByUserTask.h"

namespace Gs2::Identifier
{
    class GS2IDENTIFIER_API FGs2IdentifierRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2IdentifierRestClient(
            const Core::Net::Rest::FGs2RestSessionPtr Session
        ): FAbstractGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeUsersTask>> DescribeUsers(
            const Request::FDescribeUsersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateUserTask>> CreateUser(
            const Request::FCreateUserRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateUserTask>> UpdateUser(
            const Request::FUpdateUserRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetUserTask>> GetUser(
            const Request::FGetUserRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteUserTask>> DeleteUser(
            const Request::FDeleteUserRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSecurityPoliciesTask>> DescribeSecurityPolicies(
            const Request::FDescribeSecurityPoliciesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCommonSecurityPoliciesTask>> DescribeCommonSecurityPolicies(
            const Request::FDescribeCommonSecurityPoliciesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateSecurityPolicyTask>> CreateSecurityPolicy(
            const Request::FCreateSecurityPolicyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateSecurityPolicyTask>> UpdateSecurityPolicy(
            const Request::FUpdateSecurityPolicyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSecurityPolicyTask>> GetSecurityPolicy(
            const Request::FGetSecurityPolicyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteSecurityPolicyTask>> DeleteSecurityPolicy(
            const Request::FDeleteSecurityPolicyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeIdentifiersTask>> DescribeIdentifiers(
            const Request::FDescribeIdentifiersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateIdentifierTask>> CreateIdentifier(
            const Request::FCreateIdentifierRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetIdentifierTask>> GetIdentifier(
            const Request::FGetIdentifierRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteIdentifierTask>> DeleteIdentifier(
            const Request::FDeleteIdentifierRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeAttachedGuardsTask>> DescribeAttachedGuards(
            const Request::FDescribeAttachedGuardsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAttachGuardTask>> AttachGuard(
            const Request::FAttachGuardRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDetachGuardTask>> DetachGuard(
            const Request::FDetachGuardRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetServiceVersionTask>> GetServiceVersion(
            const Request::FGetServiceVersionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreatePasswordTask>> CreatePassword(
            const Request::FCreatePasswordRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetPasswordTask>> GetPassword(
            const Request::FGetPasswordRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FEnableMfaTask>> EnableMfa(
            const Request::FEnableMfaRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FChallengeMfaTask>> ChallengeMfa(
            const Request::FChallengeMfaRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDisableMfaTask>> DisableMfa(
            const Request::FDisableMfaRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeletePasswordTask>> DeletePassword(
            const Request::FDeletePasswordRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetHasSecurityPolicyTask>> GetHasSecurityPolicy(
            const Request::FGetHasSecurityPolicyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAttachSecurityPolicyTask>> AttachSecurityPolicy(
            const Request::FAttachSecurityPolicyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDetachSecurityPolicyTask>> DetachSecurityPolicy(
            const Request::FDetachSecurityPolicyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FLoginTask>> Login(
            const Request::FLoginRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FLoginByUserTask>> LoginByUser(
            const Request::FLoginByUserRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2IdentifierRestClient, ESPMode::ThreadSafe> FGs2IdentifierRestClientPtr;
}