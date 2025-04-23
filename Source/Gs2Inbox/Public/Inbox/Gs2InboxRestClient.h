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
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Task/Rest/DumpUserDataByUserIdTask.h"
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Task/Rest/CheckDumpUserDataByUserIdTask.h"
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Task/Rest/CleanUserDataByUserIdTask.h"
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Task/Rest/CheckCleanUserDataByUserIdTask.h"
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Task/Rest/PrepareImportUserDataByUserIdTask.h"
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Task/Rest/ImportUserDataByUserIdTask.h"
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Task/Rest/CheckImportUserDataByUserIdTask.h"
#include "Request/DescribeMessagesRequest.h"
#include "Task/Rest/DescribeMessagesTask.h"
#include "Request/DescribeMessagesByUserIdRequest.h"
#include "Task/Rest/DescribeMessagesByUserIdTask.h"
#include "Request/SendMessageByUserIdRequest.h"
#include "Task/Rest/SendMessageByUserIdTask.h"
#include "Request/GetMessageRequest.h"
#include "Task/Rest/GetMessageTask.h"
#include "Request/GetMessageByUserIdRequest.h"
#include "Task/Rest/GetMessageByUserIdTask.h"
#include "Request/ReceiveGlobalMessageRequest.h"
#include "Task/Rest/ReceiveGlobalMessageTask.h"
#include "Request/ReceiveGlobalMessageByUserIdRequest.h"
#include "Task/Rest/ReceiveGlobalMessageByUserIdTask.h"
#include "Request/OpenMessageRequest.h"
#include "Task/Rest/OpenMessageTask.h"
#include "Request/OpenMessageByUserIdRequest.h"
#include "Task/Rest/OpenMessageByUserIdTask.h"
#include "Request/CloseMessageByUserIdRequest.h"
#include "Task/Rest/CloseMessageByUserIdTask.h"
#include "Request/ReadMessageRequest.h"
#include "Task/Rest/ReadMessageTask.h"
#include "Request/ReadMessageByUserIdRequest.h"
#include "Task/Rest/ReadMessageByUserIdTask.h"
#include "Request/BatchReadMessagesRequest.h"
#include "Task/Rest/BatchReadMessagesTask.h"
#include "Request/BatchReadMessagesByUserIdRequest.h"
#include "Task/Rest/BatchReadMessagesByUserIdTask.h"
#include "Request/DeleteMessageRequest.h"
#include "Task/Rest/DeleteMessageTask.h"
#include "Request/DeleteMessageByUserIdRequest.h"
#include "Task/Rest/DeleteMessageByUserIdTask.h"
#include "Request/SendByStampSheetRequest.h"
#include "Task/Rest/SendByStampSheetTask.h"
#include "Request/OpenByStampTaskRequest.h"
#include "Task/Rest/OpenByStampTaskTask.h"
#include "Request/DeleteMessageByStampTaskRequest.h"
#include "Task/Rest/DeleteMessageByStampTaskTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentMessageMasterRequest.h"
#include "Task/Rest/GetCurrentMessageMasterTask.h"
#include "Request/UpdateCurrentMessageMasterRequest.h"
#include "Task/Rest/UpdateCurrentMessageMasterTask.h"
#include "Request/UpdateCurrentMessageMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentMessageMasterFromGitHubTask.h"
#include "Request/DescribeGlobalMessageMastersRequest.h"
#include "Task/Rest/DescribeGlobalMessageMastersTask.h"
#include "Request/CreateGlobalMessageMasterRequest.h"
#include "Task/Rest/CreateGlobalMessageMasterTask.h"
#include "Request/GetGlobalMessageMasterRequest.h"
#include "Task/Rest/GetGlobalMessageMasterTask.h"
#include "Request/UpdateGlobalMessageMasterRequest.h"
#include "Task/Rest/UpdateGlobalMessageMasterTask.h"
#include "Request/DeleteGlobalMessageMasterRequest.h"
#include "Task/Rest/DeleteGlobalMessageMasterTask.h"
#include "Request/DescribeGlobalMessagesRequest.h"
#include "Task/Rest/DescribeGlobalMessagesTask.h"
#include "Request/GetGlobalMessageRequest.h"
#include "Task/Rest/GetGlobalMessageTask.h"
#include "Request/GetReceivedByUserIdRequest.h"
#include "Task/Rest/GetReceivedByUserIdTask.h"
#include "Request/UpdateReceivedByUserIdRequest.h"
#include "Task/Rest/UpdateReceivedByUserIdTask.h"
#include "Request/DeleteReceivedByUserIdRequest.h"
#include "Task/Rest/DeleteReceivedByUserIdTask.h"

namespace Gs2::Inbox
{
    class GS2INBOX_API FGs2InboxRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2InboxRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDumpUserDataByUserIdTask>> DumpUserDataByUserId(
            const Request::FDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckDumpUserDataByUserIdTask>> CheckDumpUserDataByUserId(
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCleanUserDataByUserIdTask>> CleanUserDataByUserId(
            const Request::FCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckCleanUserDataByUserIdTask>> CheckCleanUserDataByUserId(
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareImportUserDataByUserIdTask>> PrepareImportUserDataByUserId(
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FImportUserDataByUserIdTask>> ImportUserDataByUserId(
            const Request::FImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckImportUserDataByUserIdTask>> CheckImportUserDataByUserId(
            const Request::FCheckImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeMessagesTask>> DescribeMessages(
            const Request::FDescribeMessagesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeMessagesByUserIdTask>> DescribeMessagesByUserId(
            const Request::FDescribeMessagesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSendMessageByUserIdTask>> SendMessageByUserId(
            const Request::FSendMessageByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMessageTask>> GetMessage(
            const Request::FGetMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMessageByUserIdTask>> GetMessageByUserId(
            const Request::FGetMessageByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReceiveGlobalMessageTask>> ReceiveGlobalMessage(
            const Request::FReceiveGlobalMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReceiveGlobalMessageByUserIdTask>> ReceiveGlobalMessageByUserId(
            const Request::FReceiveGlobalMessageByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FOpenMessageTask>> OpenMessage(
            const Request::FOpenMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FOpenMessageByUserIdTask>> OpenMessageByUserId(
            const Request::FOpenMessageByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCloseMessageByUserIdTask>> CloseMessageByUserId(
            const Request::FCloseMessageByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReadMessageTask>> ReadMessage(
            const Request::FReadMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReadMessageByUserIdTask>> ReadMessageByUserId(
            const Request::FReadMessageByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FBatchReadMessagesTask>> BatchReadMessages(
            const Request::FBatchReadMessagesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FBatchReadMessagesByUserIdTask>> BatchReadMessagesByUserId(
            const Request::FBatchReadMessagesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteMessageTask>> DeleteMessage(
            const Request::FDeleteMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteMessageByUserIdTask>> DeleteMessageByUserId(
            const Request::FDeleteMessageByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSendByStampSheetTask>> SendByStampSheet(
            const Request::FSendByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FOpenByStampTaskTask>> OpenByStampTask(
            const Request::FOpenByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteMessageByStampTaskTask>> DeleteMessageByStampTask(
            const Request::FDeleteMessageByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentMessageMasterTask>> GetCurrentMessageMaster(
            const Request::FGetCurrentMessageMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentMessageMasterTask>> UpdateCurrentMessageMaster(
            const Request::FUpdateCurrentMessageMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentMessageMasterFromGitHubTask>> UpdateCurrentMessageMasterFromGitHub(
            const Request::FUpdateCurrentMessageMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalMessageMastersTask>> DescribeGlobalMessageMasters(
            const Request::FDescribeGlobalMessageMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateGlobalMessageMasterTask>> CreateGlobalMessageMaster(
            const Request::FCreateGlobalMessageMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalMessageMasterTask>> GetGlobalMessageMaster(
            const Request::FGetGlobalMessageMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateGlobalMessageMasterTask>> UpdateGlobalMessageMaster(
            const Request::FUpdateGlobalMessageMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteGlobalMessageMasterTask>> DeleteGlobalMessageMaster(
            const Request::FDeleteGlobalMessageMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeGlobalMessagesTask>> DescribeGlobalMessages(
            const Request::FDescribeGlobalMessagesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGlobalMessageTask>> GetGlobalMessage(
            const Request::FGetGlobalMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetReceivedByUserIdTask>> GetReceivedByUserId(
            const Request::FGetReceivedByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateReceivedByUserIdTask>> UpdateReceivedByUserId(
            const Request::FUpdateReceivedByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteReceivedByUserIdTask>> DeleteReceivedByUserId(
            const Request::FDeleteReceivedByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2InboxRestClient, ESPMode::ThreadSafe> FGs2InboxRestClientPtr;
}