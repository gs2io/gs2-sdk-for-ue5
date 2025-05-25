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
#include "Model/Key.h"
#include "Model/GitHubApiKey.h"
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

// GetServiceVersion
#include "Request/GetServiceVersionRequest.h"
#include "Result/GetServiceVersionResult.h"
#include "Task/Rest/GetServiceVersionTask.h"
#include "Task/WebSocket/GetServiceVersionTask.h"

// DescribeKeys
#include "Request/DescribeKeysRequest.h"
#include "Result/DescribeKeysResult.h"
#include "Task/Rest/DescribeKeysTask.h"
#include "Task/WebSocket/DescribeKeysTask.h"

// CreateKey
#include "Request/CreateKeyRequest.h"
#include "Result/CreateKeyResult.h"
#include "Task/Rest/CreateKeyTask.h"
#include "Task/WebSocket/CreateKeyTask.h"

// UpdateKey
#include "Request/UpdateKeyRequest.h"
#include "Result/UpdateKeyResult.h"
#include "Task/Rest/UpdateKeyTask.h"
#include "Task/WebSocket/UpdateKeyTask.h"

// GetKey
#include "Request/GetKeyRequest.h"
#include "Result/GetKeyResult.h"
#include "Task/Rest/GetKeyTask.h"
#include "Task/WebSocket/GetKeyTask.h"

// DeleteKey
#include "Request/DeleteKeyRequest.h"
#include "Result/DeleteKeyResult.h"
#include "Task/Rest/DeleteKeyTask.h"
#include "Task/WebSocket/DeleteKeyTask.h"

// Encrypt
#include "Request/EncryptRequest.h"
#include "Result/EncryptResult.h"
#include "Task/Rest/EncryptTask.h"
#include "Task/WebSocket/EncryptTask.h"

// Decrypt
#include "Request/DecryptRequest.h"
#include "Result/DecryptResult.h"
#include "Task/Rest/DecryptTask.h"
#include "Task/WebSocket/DecryptTask.h"

// DescribeGitHubApiKeys
#include "Request/DescribeGitHubApiKeysRequest.h"
#include "Result/DescribeGitHubApiKeysResult.h"
#include "Task/Rest/DescribeGitHubApiKeysTask.h"
#include "Task/WebSocket/DescribeGitHubApiKeysTask.h"

// CreateGitHubApiKey
#include "Request/CreateGitHubApiKeyRequest.h"
#include "Result/CreateGitHubApiKeyResult.h"
#include "Task/Rest/CreateGitHubApiKeyTask.h"
#include "Task/WebSocket/CreateGitHubApiKeyTask.h"

// UpdateGitHubApiKey
#include "Request/UpdateGitHubApiKeyRequest.h"
#include "Result/UpdateGitHubApiKeyResult.h"
#include "Task/Rest/UpdateGitHubApiKeyTask.h"
#include "Task/WebSocket/UpdateGitHubApiKeyTask.h"

// GetGitHubApiKey
#include "Request/GetGitHubApiKeyRequest.h"
#include "Result/GetGitHubApiKeyResult.h"
#include "Task/Rest/GetGitHubApiKeyTask.h"
#include "Task/WebSocket/GetGitHubApiKeyTask.h"

// DeleteGitHubApiKey
#include "Request/DeleteGitHubApiKeyRequest.h"
#include "Result/DeleteGitHubApiKeyResult.h"
#include "Task/Rest/DeleteGitHubApiKeyTask.h"
#include "Task/WebSocket/DeleteGitHubApiKeyTask.h"

// Client
#include "Gs2KeyRestClient.h"
#include "Gs2KeyWebSocketClient.h"