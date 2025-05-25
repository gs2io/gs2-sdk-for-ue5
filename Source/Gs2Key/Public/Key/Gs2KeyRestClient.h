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
#include "Request/DescribeNamespacesRequest.h"
#include "Task/Rest/DescribeNamespacesTask.h"
#include "Request/CreateNamespaceRequest.h"
#include "Task/Rest/CreateNamespaceTask.h"
#include "Request/GetNamespaceStatusRequest.h"
#include "Task/Rest/GetNamespaceStatusTask.h"
#include "Request/GetNamespaceRequest.h"
#include "Task/Rest/GetNamespaceTask.h"
#include "Request/UpdateNamespaceRequest.h"
#include "Task/Rest/UpdateNamespaceTask.h"
#include "Request/DeleteNamespaceRequest.h"
#include "Task/Rest/DeleteNamespaceTask.h"
#include "Request/GetServiceVersionRequest.h"
#include "Task/Rest/GetServiceVersionTask.h"
#include "Request/DescribeKeysRequest.h"
#include "Task/Rest/DescribeKeysTask.h"
#include "Request/CreateKeyRequest.h"
#include "Task/Rest/CreateKeyTask.h"
#include "Request/UpdateKeyRequest.h"
#include "Task/Rest/UpdateKeyTask.h"
#include "Request/GetKeyRequest.h"
#include "Task/Rest/GetKeyTask.h"
#include "Request/DeleteKeyRequest.h"
#include "Task/Rest/DeleteKeyTask.h"
#include "Request/EncryptRequest.h"
#include "Task/Rest/EncryptTask.h"
#include "Request/DecryptRequest.h"
#include "Task/Rest/DecryptTask.h"
#include "Request/DescribeGitHubApiKeysRequest.h"
#include "Task/Rest/DescribeGitHubApiKeysTask.h"
#include "Request/CreateGitHubApiKeyRequest.h"
#include "Task/Rest/CreateGitHubApiKeyTask.h"
#include "Request/UpdateGitHubApiKeyRequest.h"
#include "Task/Rest/UpdateGitHubApiKeyTask.h"
#include "Request/GetGitHubApiKeyRequest.h"
#include "Task/Rest/GetGitHubApiKeyTask.h"
#include "Request/DeleteGitHubApiKeyRequest.h"
#include "Task/Rest/DeleteGitHubApiKeyTask.h"

namespace Gs2::Key
{
    class GS2KEY_API FGs2KeyRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2KeyRestClient(
            const Core::Net::Rest::FGs2RestSessionPtr Session
        ): FAbstractGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> DescribeNamespaces(
            const Request::FDescribeNamespacesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> CreateNamespace(
            const Request::FCreateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> GetNamespaceStatus(
            const Request::FGetNamespaceStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> GetNamespace(
            const Request::FGetNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> UpdateNamespace(
            const Request::FUpdateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> DeleteNamespace(
            const Request::FDeleteNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetServiceVersionTask>> GetServiceVersion(
            const Request::FGetServiceVersionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeKeysTask>> DescribeKeys(
            const Request::FDescribeKeysRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateKeyTask>> CreateKey(
            const Request::FCreateKeyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateKeyTask>> UpdateKey(
            const Request::FUpdateKeyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetKeyTask>> GetKey(
            const Request::FGetKeyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteKeyTask>> DeleteKey(
            const Request::FDeleteKeyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FEncryptTask>> Encrypt(
            const Request::FEncryptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDecryptTask>> Decrypt(
            const Request::FDecryptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeGitHubApiKeysTask>> DescribeGitHubApiKeys(
            const Request::FDescribeGitHubApiKeysRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateGitHubApiKeyTask>> CreateGitHubApiKey(
            const Request::FCreateGitHubApiKeyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateGitHubApiKeyTask>> UpdateGitHubApiKey(
            const Request::FUpdateGitHubApiKeyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGitHubApiKeyTask>> GetGitHubApiKey(
            const Request::FGetGitHubApiKeyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteGitHubApiKeyTask>> DeleteGitHubApiKey(
            const Request::FDeleteGitHubApiKeyRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2KeyRestClient, ESPMode::ThreadSafe> FGs2KeyRestClientPtr;
}