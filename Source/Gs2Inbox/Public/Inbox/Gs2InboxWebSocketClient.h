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
#include "Request/DescribeMessagesRequest.h"
#include "Task/WebSocket/DescribeMessagesTask.h"
#include "Request/DescribeMessagesByUserIdRequest.h"
#include "Task/WebSocket/DescribeMessagesByUserIdTask.h"
#include "Request/SendMessageByUserIdRequest.h"
#include "Task/WebSocket/SendMessageByUserIdTask.h"
#include "Request/GetMessageRequest.h"
#include "Task/WebSocket/GetMessageTask.h"
#include "Request/GetMessageByUserIdRequest.h"
#include "Task/WebSocket/GetMessageByUserIdTask.h"
#include "Request/ReceiveGlobalMessageRequest.h"
#include "Task/WebSocket/ReceiveGlobalMessageTask.h"
#include "Request/ReceiveGlobalMessageByUserIdRequest.h"
#include "Task/WebSocket/ReceiveGlobalMessageByUserIdTask.h"
#include "Request/OpenMessageRequest.h"
#include "Task/WebSocket/OpenMessageTask.h"
#include "Request/OpenMessageByUserIdRequest.h"
#include "Task/WebSocket/OpenMessageByUserIdTask.h"
#include "Request/CloseMessageByUserIdRequest.h"
#include "Task/WebSocket/CloseMessageByUserIdTask.h"
#include "Request/ReadMessageRequest.h"
#include "Task/WebSocket/ReadMessageTask.h"
#include "Request/ReadMessageByUserIdRequest.h"
#include "Task/WebSocket/ReadMessageByUserIdTask.h"
#include "Request/BatchReadMessagesRequest.h"
#include "Task/WebSocket/BatchReadMessagesTask.h"
#include "Request/BatchReadMessagesByUserIdRequest.h"
#include "Task/WebSocket/BatchReadMessagesByUserIdTask.h"
#include "Request/DeleteMessageRequest.h"
#include "Task/WebSocket/DeleteMessageTask.h"
#include "Request/DeleteMessageByUserIdRequest.h"
#include "Task/WebSocket/DeleteMessageByUserIdTask.h"
#include "Request/SendByStampSheetRequest.h"
#include "Task/WebSocket/SendByStampSheetTask.h"
#include "Request/OpenByStampTaskRequest.h"
#include "Task/WebSocket/OpenByStampTaskTask.h"
#include "Request/DeleteMessageByStampTaskRequest.h"
#include "Task/WebSocket/DeleteMessageByStampTaskTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentMessageMasterRequest.h"
#include "Task/WebSocket/GetCurrentMessageMasterTask.h"
#include "Request/UpdateCurrentMessageMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentMessageMasterTask.h"
#include "Request/UpdateCurrentMessageMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentMessageMasterFromGitHubTask.h"
#include "Request/DescribeGlobalMessageMastersRequest.h"
#include "Task/WebSocket/DescribeGlobalMessageMastersTask.h"
#include "Request/CreateGlobalMessageMasterRequest.h"
#include "Task/WebSocket/CreateGlobalMessageMasterTask.h"
#include "Request/GetGlobalMessageMasterRequest.h"
#include "Task/WebSocket/GetGlobalMessageMasterTask.h"
#include "Request/UpdateGlobalMessageMasterRequest.h"
#include "Task/WebSocket/UpdateGlobalMessageMasterTask.h"
#include "Request/DeleteGlobalMessageMasterRequest.h"
#include "Task/WebSocket/DeleteGlobalMessageMasterTask.h"
#include "Request/DescribeGlobalMessagesRequest.h"
#include "Task/WebSocket/DescribeGlobalMessagesTask.h"
#include "Request/GetGlobalMessageRequest.h"
#include "Task/WebSocket/GetGlobalMessageTask.h"
#include "Request/GetReceivedByUserIdRequest.h"
#include "Task/WebSocket/GetReceivedByUserIdTask.h"
#include "Request/UpdateReceivedByUserIdRequest.h"
#include "Task/WebSocket/UpdateReceivedByUserIdTask.h"
#include "Request/DeleteReceivedByUserIdRequest.h"
#include "Task/WebSocket/DeleteReceivedByUserIdTask.h"

namespace Gs2::Inbox
{
    class GS2INBOX_API FGs2InboxWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2InboxWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMessagesTask>> DescribeMessages(
            const Request::FDescribeMessagesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMessagesByUserIdTask>> DescribeMessagesByUserId(
            const Request::FDescribeMessagesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSendMessageByUserIdTask>> SendMessageByUserId(
            const Request::FSendMessageByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetMessageTask>> GetMessage(
            const Request::FGetMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetMessageByUserIdTask>> GetMessageByUserId(
            const Request::FGetMessageByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveGlobalMessageTask>> ReceiveGlobalMessage(
            const Request::FReceiveGlobalMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveGlobalMessageByUserIdTask>> ReceiveGlobalMessageByUserId(
            const Request::FReceiveGlobalMessageByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FOpenMessageTask>> OpenMessage(
            const Request::FOpenMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FOpenMessageByUserIdTask>> OpenMessageByUserId(
            const Request::FOpenMessageByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCloseMessageByUserIdTask>> CloseMessageByUserId(
            const Request::FCloseMessageByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReadMessageTask>> ReadMessage(
            const Request::FReadMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReadMessageByUserIdTask>> ReadMessageByUserId(
            const Request::FReadMessageByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FBatchReadMessagesTask>> BatchReadMessages(
            const Request::FBatchReadMessagesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FBatchReadMessagesByUserIdTask>> BatchReadMessagesByUserId(
            const Request::FBatchReadMessagesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMessageTask>> DeleteMessage(
            const Request::FDeleteMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMessageByUserIdTask>> DeleteMessageByUserId(
            const Request::FDeleteMessageByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSendByStampSheetTask>> SendByStampSheet(
            const Request::FSendByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FOpenByStampTaskTask>> OpenByStampTask(
            const Request::FOpenByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMessageByStampTaskTask>> DeleteMessageByStampTask(
            const Request::FDeleteMessageByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentMessageMasterTask>> GetCurrentMessageMaster(
            const Request::FGetCurrentMessageMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentMessageMasterTask>> UpdateCurrentMessageMaster(
            const Request::FUpdateCurrentMessageMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentMessageMasterFromGitHubTask>> UpdateCurrentMessageMasterFromGitHub(
            const Request::FUpdateCurrentMessageMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalMessageMastersTask>> DescribeGlobalMessageMasters(
            const Request::FDescribeGlobalMessageMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGlobalMessageMasterTask>> CreateGlobalMessageMaster(
            const Request::FCreateGlobalMessageMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalMessageMasterTask>> GetGlobalMessageMaster(
            const Request::FGetGlobalMessageMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateGlobalMessageMasterTask>> UpdateGlobalMessageMaster(
            const Request::FUpdateGlobalMessageMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteGlobalMessageMasterTask>> DeleteGlobalMessageMaster(
            const Request::FDeleteGlobalMessageMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGlobalMessagesTask>> DescribeGlobalMessages(
            const Request::FDescribeGlobalMessagesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGlobalMessageTask>> GetGlobalMessage(
            const Request::FGetGlobalMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetReceivedByUserIdTask>> GetReceivedByUserId(
            const Request::FGetReceivedByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateReceivedByUserIdTask>> UpdateReceivedByUserId(
            const Request::FUpdateReceivedByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteReceivedByUserIdTask>> DeleteReceivedByUserId(
            const Request::FDeleteReceivedByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2InboxWebSocketClient, ESPMode::ThreadSafe> FGs2InboxWebSocketClientPtr;
}