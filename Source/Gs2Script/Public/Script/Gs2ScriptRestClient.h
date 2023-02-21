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
#include "Request/DescribeScriptsRequest.h"
#include "Task/Rest/DescribeScriptsTask.h"
#include "Request/CreateScriptRequest.h"
#include "Task/Rest/CreateScriptTask.h"
#include "Request/CreateScriptFromGitHubRequest.h"
#include "Task/Rest/CreateScriptFromGitHubTask.h"
#include "Request/GetScriptRequest.h"
#include "Task/Rest/GetScriptTask.h"
#include "Request/UpdateScriptRequest.h"
#include "Task/Rest/UpdateScriptTask.h"
#include "Request/UpdateScriptFromGitHubRequest.h"
#include "Task/Rest/UpdateScriptFromGitHubTask.h"
#include "Request/DeleteScriptRequest.h"
#include "Task/Rest/DeleteScriptTask.h"
#include "Request/InvokeScriptRequest.h"
#include "Task/Rest/InvokeScriptTask.h"
#include "Request/DebugInvokeRequest.h"
#include "Task/Rest/DebugInvokeTask.h"

namespace Gs2::Script
{
    class GS2SCRIPT_API FGs2ScriptRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2ScriptRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeScriptsTask>> DescribeScripts(
            const Request::FDescribeScriptsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateScriptTask>> CreateScript(
            const Request::FCreateScriptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateScriptFromGitHubTask>> CreateScriptFromGitHub(
            const Request::FCreateScriptFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetScriptTask>> GetScript(
            const Request::FGetScriptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateScriptTask>> UpdateScript(
            const Request::FUpdateScriptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateScriptFromGitHubTask>> UpdateScriptFromGitHub(
            const Request::FUpdateScriptFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteScriptTask>> DeleteScript(
            const Request::FDeleteScriptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FInvokeScriptTask>> InvokeScript(
            const Request::FInvokeScriptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDebugInvokeTask>> DebugInvoke(
            const Request::FDebugInvokeRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2ScriptRestClient, ESPMode::ThreadSafe> FGs2ScriptRestClientPtr;
}