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
#include "Model/Namespace.h"
#include "Model/Account.h"
#include "Model/TakeOver.h"
#include "Model/DataOwner.h"
#include "Model/ScriptSetting.h"
#include "Model/LogSetting.h"

// DescribeNamespaces
#include "Request/DescribeNamespacesRequest.h"
#include "Result/DescribeNamespacesResult.h"
#include "Task/Rest/DescribeNamespacesTask.h"
#include "Task/WebSocket/DescribeNamespacesTask.h"

// CreateNamespace
#include "Request/CreateNamespaceRequest.h"
#include "Result/CreateNamespaceResult.h"
#include "Task/Rest/CreateNamespaceTask.h"
#include "Task/WebSocket/CreateNamespaceTask.h"

// GetNamespaceStatus
#include "Request/GetNamespaceStatusRequest.h"
#include "Result/GetNamespaceStatusResult.h"
#include "Task/Rest/GetNamespaceStatusTask.h"
#include "Task/WebSocket/GetNamespaceStatusTask.h"

// GetNamespace
#include "Request/GetNamespaceRequest.h"
#include "Result/GetNamespaceResult.h"
#include "Task/Rest/GetNamespaceTask.h"
#include "Task/WebSocket/GetNamespaceTask.h"

// UpdateNamespace
#include "Request/UpdateNamespaceRequest.h"
#include "Result/UpdateNamespaceResult.h"
#include "Task/Rest/UpdateNamespaceTask.h"
#include "Task/WebSocket/UpdateNamespaceTask.h"

// DeleteNamespace
#include "Request/DeleteNamespaceRequest.h"
#include "Result/DeleteNamespaceResult.h"
#include "Task/Rest/DeleteNamespaceTask.h"
#include "Task/WebSocket/DeleteNamespaceTask.h"

// DescribeAccounts
#include "Request/DescribeAccountsRequest.h"
#include "Result/DescribeAccountsResult.h"
#include "Task/Rest/DescribeAccountsTask.h"
#include "Task/WebSocket/DescribeAccountsTask.h"

// CreateAccount
#include "Request/CreateAccountRequest.h"
#include "Result/CreateAccountResult.h"
#include "Task/Rest/CreateAccountTask.h"
#include "Task/WebSocket/CreateAccountTask.h"

// UpdateTimeOffset
#include "Request/UpdateTimeOffsetRequest.h"
#include "Result/UpdateTimeOffsetResult.h"
#include "Task/Rest/UpdateTimeOffsetTask.h"
#include "Task/WebSocket/UpdateTimeOffsetTask.h"

// UpdateBanned
#include "Request/UpdateBannedRequest.h"
#include "Result/UpdateBannedResult.h"
#include "Task/Rest/UpdateBannedTask.h"
#include "Task/WebSocket/UpdateBannedTask.h"

// GetAccount
#include "Request/GetAccountRequest.h"
#include "Result/GetAccountResult.h"
#include "Task/Rest/GetAccountTask.h"
#include "Task/WebSocket/GetAccountTask.h"

// DeleteAccount
#include "Request/DeleteAccountRequest.h"
#include "Result/DeleteAccountResult.h"
#include "Task/Rest/DeleteAccountTask.h"
#include "Task/WebSocket/DeleteAccountTask.h"

// Authentication
#include "Request/AuthenticationRequest.h"
#include "Result/AuthenticationResult.h"
#include "Task/Rest/AuthenticationTask.h"
#include "Task/WebSocket/AuthenticationTask.h"

// DescribeTakeOvers
#include "Request/DescribeTakeOversRequest.h"
#include "Result/DescribeTakeOversResult.h"
#include "Task/Rest/DescribeTakeOversTask.h"
#include "Task/WebSocket/DescribeTakeOversTask.h"

// DescribeTakeOversByUserId
#include "Request/DescribeTakeOversByUserIdRequest.h"
#include "Result/DescribeTakeOversByUserIdResult.h"
#include "Task/Rest/DescribeTakeOversByUserIdTask.h"
#include "Task/WebSocket/DescribeTakeOversByUserIdTask.h"

// CreateTakeOver
#include "Request/CreateTakeOverRequest.h"
#include "Result/CreateTakeOverResult.h"
#include "Task/Rest/CreateTakeOverTask.h"
#include "Task/WebSocket/CreateTakeOverTask.h"

// CreateTakeOverByUserId
#include "Request/CreateTakeOverByUserIdRequest.h"
#include "Result/CreateTakeOverByUserIdResult.h"
#include "Task/Rest/CreateTakeOverByUserIdTask.h"
#include "Task/WebSocket/CreateTakeOverByUserIdTask.h"

// GetTakeOver
#include "Request/GetTakeOverRequest.h"
#include "Result/GetTakeOverResult.h"
#include "Task/Rest/GetTakeOverTask.h"
#include "Task/WebSocket/GetTakeOverTask.h"

// GetTakeOverByUserId
#include "Request/GetTakeOverByUserIdRequest.h"
#include "Result/GetTakeOverByUserIdResult.h"
#include "Task/Rest/GetTakeOverByUserIdTask.h"
#include "Task/WebSocket/GetTakeOverByUserIdTask.h"

// UpdateTakeOver
#include "Request/UpdateTakeOverRequest.h"
#include "Result/UpdateTakeOverResult.h"
#include "Task/Rest/UpdateTakeOverTask.h"
#include "Task/WebSocket/UpdateTakeOverTask.h"

// UpdateTakeOverByUserId
#include "Request/UpdateTakeOverByUserIdRequest.h"
#include "Result/UpdateTakeOverByUserIdResult.h"
#include "Task/Rest/UpdateTakeOverByUserIdTask.h"
#include "Task/WebSocket/UpdateTakeOverByUserIdTask.h"

// DeleteTakeOver
#include "Request/DeleteTakeOverRequest.h"
#include "Result/DeleteTakeOverResult.h"
#include "Task/Rest/DeleteTakeOverTask.h"
#include "Task/WebSocket/DeleteTakeOverTask.h"

// DeleteTakeOverByUserIdentifier
#include "Request/DeleteTakeOverByUserIdentifierRequest.h"
#include "Result/DeleteTakeOverByUserIdentifierResult.h"
#include "Task/Rest/DeleteTakeOverByUserIdentifierTask.h"
#include "Task/WebSocket/DeleteTakeOverByUserIdentifierTask.h"

// DoTakeOver
#include "Request/DoTakeOverRequest.h"
#include "Result/DoTakeOverResult.h"
#include "Task/Rest/DoTakeOverTask.h"
#include "Task/WebSocket/DoTakeOverTask.h"

// GetDataOwnerByUserId
#include "Request/GetDataOwnerByUserIdRequest.h"
#include "Result/GetDataOwnerByUserIdResult.h"
#include "Task/Rest/GetDataOwnerByUserIdTask.h"
#include "Task/WebSocket/GetDataOwnerByUserIdTask.h"

// DeleteDataOwnerByUserId
#include "Request/DeleteDataOwnerByUserIdRequest.h"
#include "Result/DeleteDataOwnerByUserIdResult.h"
#include "Task/Rest/DeleteDataOwnerByUserIdTask.h"
#include "Task/WebSocket/DeleteDataOwnerByUserIdTask.h"

// Client
#include "Gs2AccountRestClient.h"
#include "Gs2AccountWebSocketClient.h"