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
#include "Request/DescribeNamespacesRequest.h"
#include "Task/WebSocket/DescribeNamespacesTask.h"
#include "Request/CreateNamespaceRequest.h"
#include "Task/WebSocket/CreateNamespaceTask.h"
#include "Request/GetNamespaceStatusRequest.h"
#include "Task/WebSocket/GetNamespaceStatusTask.h"
#include "Request/GetNamespaceRequest.h"
#include "Task/WebSocket/GetNamespaceTask.h"
#include "Request/UpdateNamespaceRequest.h"
#include "Task/WebSocket/UpdateNamespaceTask.h"
#include "Request/DeleteNamespaceRequest.h"
#include "Task/WebSocket/DeleteNamespaceTask.h"
#include "Request/GetServiceVersionRequest.h"
#include "Task/WebSocket/GetServiceVersionTask.h"
#include "Request/DescribeKeysRequest.h"
#include "Task/WebSocket/DescribeKeysTask.h"
#include "Request/CreateKeyRequest.h"
#include "Task/WebSocket/CreateKeyTask.h"
#include "Request/UpdateKeyRequest.h"
#include "Task/WebSocket/UpdateKeyTask.h"
#include "Request/GetKeyRequest.h"
#include "Task/WebSocket/GetKeyTask.h"
#include "Request/DeleteKeyRequest.h"
#include "Task/WebSocket/DeleteKeyTask.h"
#include "Request/EncryptRequest.h"
#include "Task/WebSocket/EncryptTask.h"
#include "Request/DecryptRequest.h"
#include "Task/WebSocket/DecryptTask.h"
#include "Request/DescribeGitHubApiKeysRequest.h"
#include "Task/WebSocket/DescribeGitHubApiKeysTask.h"
#include "Request/CreateGitHubApiKeyRequest.h"
#include "Task/WebSocket/CreateGitHubApiKeyTask.h"
#include "Request/UpdateGitHubApiKeyRequest.h"
#include "Task/WebSocket/UpdateGitHubApiKeyTask.h"
#include "Request/GetGitHubApiKeyRequest.h"
#include "Task/WebSocket/GetGitHubApiKeyTask.h"
#include "Request/DeleteGitHubApiKeyRequest.h"
#include "Task/WebSocket/DeleteGitHubApiKeyTask.h"

namespace Gs2::Key
{
    class GS2KEY_API FGs2KeyWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2KeyWebSocketClient(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session
        ): FAbstractWebSocketGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> DescribeNamespaces(
            const Request::FDescribeNamespacesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> CreateNamespace(
            const Request::FCreateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> GetNamespaceStatus(
            const Request::FGetNamespaceStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> GetNamespace(
            const Request::FGetNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> UpdateNamespace(
            const Request::FUpdateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> DeleteNamespace(
            const Request::FDeleteNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetServiceVersionTask>> GetServiceVersion(
            const Request::FGetServiceVersionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeKeysTask>> DescribeKeys(
            const Request::FDescribeKeysRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateKeyTask>> CreateKey(
            const Request::FCreateKeyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateKeyTask>> UpdateKey(
            const Request::FUpdateKeyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetKeyTask>> GetKey(
            const Request::FGetKeyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteKeyTask>> DeleteKey(
            const Request::FDeleteKeyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FEncryptTask>> Encrypt(
            const Request::FEncryptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDecryptTask>> Decrypt(
            const Request::FDecryptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGitHubApiKeysTask>> DescribeGitHubApiKeys(
            const Request::FDescribeGitHubApiKeysRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGitHubApiKeyTask>> CreateGitHubApiKey(
            const Request::FCreateGitHubApiKeyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateGitHubApiKeyTask>> UpdateGitHubApiKey(
            const Request::FUpdateGitHubApiKeyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGitHubApiKeyTask>> GetGitHubApiKey(
            const Request::FGetGitHubApiKeyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteGitHubApiKeyTask>> DeleteGitHubApiKey(
            const Request::FDeleteGitHubApiKeyRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2KeyWebSocketClient, ESPMode::ThreadSafe> FGs2KeyWebSocketClientPtr;
}