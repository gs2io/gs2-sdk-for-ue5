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
#include "Request/DescribeScriptsRequest.h"
#include "Task/WebSocket/DescribeScriptsTask.h"
#include "Request/CreateScriptRequest.h"
#include "Task/WebSocket/CreateScriptTask.h"
#include "Request/CreateScriptFromGitHubRequest.h"
#include "Task/WebSocket/CreateScriptFromGitHubTask.h"
#include "Request/GetScriptRequest.h"
#include "Task/WebSocket/GetScriptTask.h"
#include "Request/UpdateScriptRequest.h"
#include "Task/WebSocket/UpdateScriptTask.h"
#include "Request/UpdateScriptFromGitHubRequest.h"
#include "Task/WebSocket/UpdateScriptFromGitHubTask.h"
#include "Request/DeleteScriptRequest.h"
#include "Task/WebSocket/DeleteScriptTask.h"
#include "Request/InvokeScriptRequest.h"
#include "Task/WebSocket/InvokeScriptTask.h"
#include "Request/DebugInvokeRequest.h"
#include "Task/WebSocket/DebugInvokeTask.h"
#include "Request/InvokeByStampSheetRequest.h"
#include "Task/WebSocket/InvokeByStampSheetTask.h"

namespace Gs2::Script
{
    class GS2SCRIPT_API FGs2ScriptWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2ScriptWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeScriptsTask>> DescribeScripts(
            const Request::FDescribeScriptsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateScriptTask>> CreateScript(
            const Request::FCreateScriptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateScriptFromGitHubTask>> CreateScriptFromGitHub(
            const Request::FCreateScriptFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetScriptTask>> GetScript(
            const Request::FGetScriptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateScriptTask>> UpdateScript(
            const Request::FUpdateScriptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateScriptFromGitHubTask>> UpdateScriptFromGitHub(
            const Request::FUpdateScriptFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteScriptTask>> DeleteScript(
            const Request::FDeleteScriptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FInvokeScriptTask>> InvokeScript(
            const Request::FInvokeScriptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDebugInvokeTask>> DebugInvoke(
            const Request::FDebugInvokeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FInvokeByStampSheetTask>> InvokeByStampSheet(
            const Request::FInvokeByStampSheetRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2ScriptWebSocketClient, ESPMode::ThreadSafe> FGs2ScriptWebSocketClientPtr;
}