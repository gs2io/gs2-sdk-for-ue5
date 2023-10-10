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
#include "Request/DescribeEntryModelsRequest.h"
#include "Task/WebSocket/DescribeEntryModelsTask.h"
#include "Request/GetEntryModelRequest.h"
#include "Task/WebSocket/GetEntryModelTask.h"
#include "Request/DescribeEntryModelMastersRequest.h"
#include "Task/WebSocket/DescribeEntryModelMastersTask.h"
#include "Request/CreateEntryModelMasterRequest.h"
#include "Task/WebSocket/CreateEntryModelMasterTask.h"
#include "Request/GetEntryModelMasterRequest.h"
#include "Task/WebSocket/GetEntryModelMasterTask.h"
#include "Request/UpdateEntryModelMasterRequest.h"
#include "Task/WebSocket/UpdateEntryModelMasterTask.h"
#include "Request/DeleteEntryModelMasterRequest.h"
#include "Task/WebSocket/DeleteEntryModelMasterTask.h"
#include "Request/DescribeEntriesRequest.h"
#include "Task/WebSocket/DescribeEntriesTask.h"
#include "Request/DescribeEntriesByUserIdRequest.h"
#include "Task/WebSocket/DescribeEntriesByUserIdTask.h"
#include "Request/AddEntriesByUserIdRequest.h"
#include "Task/WebSocket/AddEntriesByUserIdTask.h"
#include "Request/GetEntryRequest.h"
#include "Task/WebSocket/GetEntryTask.h"
#include "Request/GetEntryByUserIdRequest.h"
#include "Task/WebSocket/GetEntryByUserIdTask.h"
#include "Request/GetEntryWithSignatureRequest.h"
#include "Task/WebSocket/GetEntryWithSignatureTask.h"
#include "Request/GetEntryWithSignatureByUserIdRequest.h"
#include "Task/WebSocket/GetEntryWithSignatureByUserIdTask.h"
#include "Request/ResetByUserIdRequest.h"
#include "Task/WebSocket/ResetByUserIdTask.h"
#include "Request/VerifyEntryRequest.h"
#include "Task/WebSocket/VerifyEntryTask.h"
#include "Request/VerifyEntryByUserIdRequest.h"
#include "Task/WebSocket/VerifyEntryByUserIdTask.h"
#include "Request/DeleteEntriesByUserIdRequest.h"
#include "Task/WebSocket/DeleteEntriesByUserIdTask.h"
#include "Request/AddEntriesByStampSheetRequest.h"
#include "Task/WebSocket/AddEntriesByStampSheetTask.h"
#include "Request/DeleteEntriesByStampTaskRequest.h"
#include "Task/WebSocket/DeleteEntriesByStampTaskTask.h"
#include "Request/VerifyEntryByStampTaskRequest.h"
#include "Task/WebSocket/VerifyEntryByStampTaskTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentEntryMasterRequest.h"
#include "Task/WebSocket/GetCurrentEntryMasterTask.h"
#include "Request/UpdateCurrentEntryMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentEntryMasterTask.h"
#include "Request/UpdateCurrentEntryMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentEntryMasterFromGitHubTask.h"

namespace Gs2::Dictionary
{
    class GS2DICTIONARY_API FGs2DictionaryWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2DictionaryWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeEntryModelsTask>> DescribeEntryModels(
            const Request::FDescribeEntryModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetEntryModelTask>> GetEntryModel(
            const Request::FGetEntryModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeEntryModelMastersTask>> DescribeEntryModelMasters(
            const Request::FDescribeEntryModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateEntryModelMasterTask>> CreateEntryModelMaster(
            const Request::FCreateEntryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetEntryModelMasterTask>> GetEntryModelMaster(
            const Request::FGetEntryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateEntryModelMasterTask>> UpdateEntryModelMaster(
            const Request::FUpdateEntryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteEntryModelMasterTask>> DeleteEntryModelMaster(
            const Request::FDeleteEntryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeEntriesTask>> DescribeEntries(
            const Request::FDescribeEntriesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeEntriesByUserIdTask>> DescribeEntriesByUserId(
            const Request::FDescribeEntriesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddEntriesByUserIdTask>> AddEntriesByUserId(
            const Request::FAddEntriesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetEntryTask>> GetEntry(
            const Request::FGetEntryRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetEntryByUserIdTask>> GetEntryByUserId(
            const Request::FGetEntryByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetEntryWithSignatureTask>> GetEntryWithSignature(
            const Request::FGetEntryWithSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetEntryWithSignatureByUserIdTask>> GetEntryWithSignatureByUserId(
            const Request::FGetEntryWithSignatureByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FResetByUserIdTask>> ResetByUserId(
            const Request::FResetByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyEntryTask>> VerifyEntry(
            const Request::FVerifyEntryRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyEntryByUserIdTask>> VerifyEntryByUserId(
            const Request::FVerifyEntryByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteEntriesByUserIdTask>> DeleteEntriesByUserId(
            const Request::FDeleteEntriesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddEntriesByStampSheetTask>> AddEntriesByStampSheet(
            const Request::FAddEntriesByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteEntriesByStampTaskTask>> DeleteEntriesByStampTask(
            const Request::FDeleteEntriesByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyEntryByStampTaskTask>> VerifyEntryByStampTask(
            const Request::FVerifyEntryByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentEntryMasterTask>> GetCurrentEntryMaster(
            const Request::FGetCurrentEntryMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentEntryMasterTask>> UpdateCurrentEntryMaster(
            const Request::FUpdateCurrentEntryMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentEntryMasterFromGitHubTask>> UpdateCurrentEntryMasterFromGitHub(
            const Request::FUpdateCurrentEntryMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2DictionaryWebSocketClient, ESPMode::ThreadSafe> FGs2DictionaryWebSocketClientPtr;
}