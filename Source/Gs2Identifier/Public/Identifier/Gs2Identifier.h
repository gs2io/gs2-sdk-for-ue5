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

// Model
#include "Model/User.h"
#include "Model/SecurityPolicy.h"
#include "Model/Identifier.h"
#include "Model/Password.h"
#include "Model/AttachSecurityPolicy.h"
#include "Model/ProjectToken.h"

// DescribeUsers
#include "Request/DescribeUsersRequest.h"
#include "Result/DescribeUsersResult.h"
#include "Task/Rest/DescribeUsersTask.h"
#include "Task/WebSocket/DescribeUsersTask.h"

// CreateUser
#include "Request/CreateUserRequest.h"
#include "Result/CreateUserResult.h"
#include "Task/Rest/CreateUserTask.h"
#include "Task/WebSocket/CreateUserTask.h"

// UpdateUser
#include "Request/UpdateUserRequest.h"
#include "Result/UpdateUserResult.h"
#include "Task/Rest/UpdateUserTask.h"
#include "Task/WebSocket/UpdateUserTask.h"

// GetUser
#include "Request/GetUserRequest.h"
#include "Result/GetUserResult.h"
#include "Task/Rest/GetUserTask.h"
#include "Task/WebSocket/GetUserTask.h"

// DeleteUser
#include "Request/DeleteUserRequest.h"
#include "Result/DeleteUserResult.h"
#include "Task/Rest/DeleteUserTask.h"
#include "Task/WebSocket/DeleteUserTask.h"

// DescribeSecurityPolicies
#include "Request/DescribeSecurityPoliciesRequest.h"
#include "Result/DescribeSecurityPoliciesResult.h"
#include "Task/Rest/DescribeSecurityPoliciesTask.h"
#include "Task/WebSocket/DescribeSecurityPoliciesTask.h"

// DescribeCommonSecurityPolicies
#include "Request/DescribeCommonSecurityPoliciesRequest.h"
#include "Result/DescribeCommonSecurityPoliciesResult.h"
#include "Task/Rest/DescribeCommonSecurityPoliciesTask.h"
#include "Task/WebSocket/DescribeCommonSecurityPoliciesTask.h"

// CreateSecurityPolicy
#include "Request/CreateSecurityPolicyRequest.h"
#include "Result/CreateSecurityPolicyResult.h"
#include "Task/Rest/CreateSecurityPolicyTask.h"
#include "Task/WebSocket/CreateSecurityPolicyTask.h"

// UpdateSecurityPolicy
#include "Request/UpdateSecurityPolicyRequest.h"
#include "Result/UpdateSecurityPolicyResult.h"
#include "Task/Rest/UpdateSecurityPolicyTask.h"
#include "Task/WebSocket/UpdateSecurityPolicyTask.h"

// GetSecurityPolicy
#include "Request/GetSecurityPolicyRequest.h"
#include "Result/GetSecurityPolicyResult.h"
#include "Task/Rest/GetSecurityPolicyTask.h"
#include "Task/WebSocket/GetSecurityPolicyTask.h"

// DeleteSecurityPolicy
#include "Request/DeleteSecurityPolicyRequest.h"
#include "Result/DeleteSecurityPolicyResult.h"
#include "Task/Rest/DeleteSecurityPolicyTask.h"
#include "Task/WebSocket/DeleteSecurityPolicyTask.h"

// DescribeIdentifiers
#include "Request/DescribeIdentifiersRequest.h"
#include "Result/DescribeIdentifiersResult.h"
#include "Task/Rest/DescribeIdentifiersTask.h"
#include "Task/WebSocket/DescribeIdentifiersTask.h"

// CreateIdentifier
#include "Request/CreateIdentifierRequest.h"
#include "Result/CreateIdentifierResult.h"
#include "Task/Rest/CreateIdentifierTask.h"
#include "Task/WebSocket/CreateIdentifierTask.h"

// GetIdentifier
#include "Request/GetIdentifierRequest.h"
#include "Result/GetIdentifierResult.h"
#include "Task/Rest/GetIdentifierTask.h"
#include "Task/WebSocket/GetIdentifierTask.h"

// DeleteIdentifier
#include "Request/DeleteIdentifierRequest.h"
#include "Result/DeleteIdentifierResult.h"
#include "Task/Rest/DeleteIdentifierTask.h"
#include "Task/WebSocket/DeleteIdentifierTask.h"

// DescribePasswords
#include "Request/DescribePasswordsRequest.h"
#include "Result/DescribePasswordsResult.h"
#include "Task/Rest/DescribePasswordsTask.h"
#include "Task/WebSocket/DescribePasswordsTask.h"

// CreatePassword
#include "Request/CreatePasswordRequest.h"
#include "Result/CreatePasswordResult.h"
#include "Task/Rest/CreatePasswordTask.h"
#include "Task/WebSocket/CreatePasswordTask.h"

// GetPassword
#include "Request/GetPasswordRequest.h"
#include "Result/GetPasswordResult.h"
#include "Task/Rest/GetPasswordTask.h"
#include "Task/WebSocket/GetPasswordTask.h"

// DeletePassword
#include "Request/DeletePasswordRequest.h"
#include "Result/DeletePasswordResult.h"
#include "Task/Rest/DeletePasswordTask.h"
#include "Task/WebSocket/DeletePasswordTask.h"

// GetHasSecurityPolicy
#include "Request/GetHasSecurityPolicyRequest.h"
#include "Result/GetHasSecurityPolicyResult.h"
#include "Task/Rest/GetHasSecurityPolicyTask.h"
#include "Task/WebSocket/GetHasSecurityPolicyTask.h"

// AttachSecurityPolicy
#include "Request/AttachSecurityPolicyRequest.h"
#include "Result/AttachSecurityPolicyResult.h"
#include "Task/Rest/AttachSecurityPolicyTask.h"
#include "Task/WebSocket/AttachSecurityPolicyTask.h"

// DetachSecurityPolicy
#include "Request/DetachSecurityPolicyRequest.h"
#include "Result/DetachSecurityPolicyResult.h"
#include "Task/Rest/DetachSecurityPolicyTask.h"
#include "Task/WebSocket/DetachSecurityPolicyTask.h"

// Login
#include "Request/LoginRequest.h"
#include "Result/LoginResult.h"
#include "Task/Rest/LoginTask.h"
#include "Task/WebSocket/LoginTask.h"

// LoginByUser
#include "Request/LoginByUserRequest.h"
#include "Result/LoginByUserResult.h"
#include "Task/Rest/LoginByUserTask.h"
#include "Task/WebSocket/LoginByUserTask.h"

// Client
#include "Gs2IdentifierRestClient.h"
#include "Gs2IdentifierWebSocketClient.h"