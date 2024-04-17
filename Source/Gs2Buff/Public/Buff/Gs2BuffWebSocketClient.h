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
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/DumpUserDataByUserIdTask.h"
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckDumpUserDataByUserIdTask.h"
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CleanUserDataByUserIdTask.h"
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckCleanUserDataByUserIdTask.h"
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/PrepareImportUserDataByUserIdTask.h"
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/ImportUserDataByUserIdTask.h"
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckImportUserDataByUserIdTask.h"
#include "Request/DescribeBuffEntryModelsRequest.h"
#include "Task/WebSocket/DescribeBuffEntryModelsTask.h"
#include "Request/GetBuffEntryModelRequest.h"
#include "Task/WebSocket/GetBuffEntryModelTask.h"
#include "Request/DescribeBuffEntryModelMastersRequest.h"
#include "Task/WebSocket/DescribeBuffEntryModelMastersTask.h"
#include "Request/CreateBuffEntryModelMasterRequest.h"
#include "Task/WebSocket/CreateBuffEntryModelMasterTask.h"
#include "Request/GetBuffEntryModelMasterRequest.h"
#include "Task/WebSocket/GetBuffEntryModelMasterTask.h"
#include "Request/UpdateBuffEntryModelMasterRequest.h"
#include "Task/WebSocket/UpdateBuffEntryModelMasterTask.h"
#include "Request/DeleteBuffEntryModelMasterRequest.h"
#include "Task/WebSocket/DeleteBuffEntryModelMasterTask.h"
#include "Request/ApplyBuffRequest.h"
#include "Task/WebSocket/ApplyBuffTask.h"
#include "Request/ApplyBuffByUserIdRequest.h"
#include "Task/WebSocket/ApplyBuffByUserIdTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentBuffMasterRequest.h"
#include "Task/WebSocket/GetCurrentBuffMasterTask.h"
#include "Request/UpdateCurrentBuffMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentBuffMasterTask.h"
#include "Request/UpdateCurrentBuffMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentBuffMasterFromGitHubTask.h"

namespace Gs2::Buff
{
    class GS2BUFF_API FGs2BuffWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2BuffWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>> DumpUserDataByUserId(
            const Request::FDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>> CheckDumpUserDataByUserId(
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>> CleanUserDataByUserId(
            const Request::FCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>> CheckCleanUserDataByUserId(
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>> PrepareImportUserDataByUserId(
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>> ImportUserDataByUserId(
            const Request::FImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>> CheckImportUserDataByUserId(
            const Request::FCheckImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBuffEntryModelsTask>> DescribeBuffEntryModels(
            const Request::FDescribeBuffEntryModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBuffEntryModelTask>> GetBuffEntryModel(
            const Request::FGetBuffEntryModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBuffEntryModelMastersTask>> DescribeBuffEntryModelMasters(
            const Request::FDescribeBuffEntryModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateBuffEntryModelMasterTask>> CreateBuffEntryModelMaster(
            const Request::FCreateBuffEntryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBuffEntryModelMasterTask>> GetBuffEntryModelMaster(
            const Request::FGetBuffEntryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateBuffEntryModelMasterTask>> UpdateBuffEntryModelMaster(
            const Request::FUpdateBuffEntryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteBuffEntryModelMasterTask>> DeleteBuffEntryModelMaster(
            const Request::FDeleteBuffEntryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FApplyBuffTask>> ApplyBuff(
            const Request::FApplyBuffRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FApplyBuffByUserIdTask>> ApplyBuffByUserId(
            const Request::FApplyBuffByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentBuffMasterTask>> GetCurrentBuffMaster(
            const Request::FGetCurrentBuffMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentBuffMasterTask>> UpdateCurrentBuffMaster(
            const Request::FUpdateCurrentBuffMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentBuffMasterFromGitHubTask>> UpdateCurrentBuffMasterFromGitHub(
            const Request::FUpdateCurrentBuffMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2BuffWebSocketClient, ESPMode::ThreadSafe> FGs2BuffWebSocketClientPtr;
}