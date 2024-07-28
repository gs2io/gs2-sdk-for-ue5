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
#include "Request/DescribeNodeModelsRequest.h"
#include "Task/WebSocket/DescribeNodeModelsTask.h"
#include "Request/GetNodeModelRequest.h"
#include "Task/WebSocket/GetNodeModelTask.h"
#include "Request/DescribeNodeModelMastersRequest.h"
#include "Task/WebSocket/DescribeNodeModelMastersTask.h"
#include "Request/CreateNodeModelMasterRequest.h"
#include "Task/WebSocket/CreateNodeModelMasterTask.h"
#include "Request/GetNodeModelMasterRequest.h"
#include "Task/WebSocket/GetNodeModelMasterTask.h"
#include "Request/UpdateNodeModelMasterRequest.h"
#include "Task/WebSocket/UpdateNodeModelMasterTask.h"
#include "Request/DeleteNodeModelMasterRequest.h"
#include "Task/WebSocket/DeleteNodeModelMasterTask.h"
#include "Request/MarkReleaseByUserIdRequest.h"
#include "Task/WebSocket/MarkReleaseByUserIdTask.h"
#include "Request/ReleaseRequest.h"
#include "Task/WebSocket/ReleaseTask.h"
#include "Request/ReleaseByUserIdRequest.h"
#include "Task/WebSocket/ReleaseByUserIdTask.h"
#include "Request/MarkRestrainRequest.h"
#include "Task/WebSocket/MarkRestrainTask.h"
#include "Request/MarkRestrainByUserIdRequest.h"
#include "Task/WebSocket/MarkRestrainByUserIdTask.h"
#include "Request/RestrainRequest.h"
#include "Task/WebSocket/RestrainTask.h"
#include "Request/RestrainByUserIdRequest.h"
#include "Task/WebSocket/RestrainByUserIdTask.h"
#include "Request/DescribeStatusesRequest.h"
#include "Task/WebSocket/DescribeStatusesTask.h"
#include "Request/DescribeStatusesByUserIdRequest.h"
#include "Task/WebSocket/DescribeStatusesByUserIdTask.h"
#include "Request/GetStatusRequest.h"
#include "Task/WebSocket/GetStatusTask.h"
#include "Request/GetStatusByUserIdRequest.h"
#include "Task/WebSocket/GetStatusByUserIdTask.h"
#include "Request/ResetRequest.h"
#include "Task/WebSocket/ResetTask.h"
#include "Request/ResetByUserIdRequest.h"
#include "Task/WebSocket/ResetByUserIdTask.h"
#include "Request/MarkReleaseByStampSheetRequest.h"
#include "Task/WebSocket/MarkReleaseByStampSheetTask.h"
#include "Request/MarkRestrainByStampTaskRequest.h"
#include "Task/WebSocket/MarkRestrainByStampTaskTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentTreeMasterRequest.h"
#include "Task/WebSocket/GetCurrentTreeMasterTask.h"
#include "Request/UpdateCurrentTreeMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentTreeMasterTask.h"
#include "Request/UpdateCurrentTreeMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentTreeMasterFromGitHubTask.h"

namespace Gs2::SkillTree
{
    class GS2SKILLTREE_API FGs2SkillTreeWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2SkillTreeWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNodeModelsTask>> DescribeNodeModels(
            const Request::FDescribeNodeModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetNodeModelTask>> GetNodeModel(
            const Request::FGetNodeModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNodeModelMastersTask>> DescribeNodeModelMasters(
            const Request::FDescribeNodeModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNodeModelMasterTask>> CreateNodeModelMaster(
            const Request::FCreateNodeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetNodeModelMasterTask>> GetNodeModelMaster(
            const Request::FGetNodeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNodeModelMasterTask>> UpdateNodeModelMaster(
            const Request::FUpdateNodeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNodeModelMasterTask>> DeleteNodeModelMaster(
            const Request::FDeleteNodeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FMarkReleaseByUserIdTask>> MarkReleaseByUserId(
            const Request::FMarkReleaseByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReleaseTask>> Release(
            const Request::FReleaseRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReleaseByUserIdTask>> ReleaseByUserId(
            const Request::FReleaseByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FMarkRestrainTask>> MarkRestrain(
            const Request::FMarkRestrainRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FMarkRestrainByUserIdTask>> MarkRestrainByUserId(
            const Request::FMarkRestrainByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRestrainTask>> Restrain(
            const Request::FRestrainRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRestrainByUserIdTask>> RestrainByUserId(
            const Request::FRestrainByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStatusesTask>> DescribeStatuses(
            const Request::FDescribeStatusesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStatusesByUserIdTask>> DescribeStatusesByUserId(
            const Request::FDescribeStatusesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStatusTask>> GetStatus(
            const Request::FGetStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStatusByUserIdTask>> GetStatusByUserId(
            const Request::FGetStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FResetTask>> Reset(
            const Request::FResetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FResetByUserIdTask>> ResetByUserId(
            const Request::FResetByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FMarkReleaseByStampSheetTask>> MarkReleaseByStampSheet(
            const Request::FMarkReleaseByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FMarkRestrainByStampTaskTask>> MarkRestrainByStampTask(
            const Request::FMarkRestrainByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentTreeMasterTask>> GetCurrentTreeMaster(
            const Request::FGetCurrentTreeMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentTreeMasterTask>> UpdateCurrentTreeMaster(
            const Request::FUpdateCurrentTreeMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentTreeMasterFromGitHubTask>> UpdateCurrentTreeMasterFromGitHub(
            const Request::FUpdateCurrentTreeMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2SkillTreeWebSocketClient, ESPMode::ThreadSafe> FGs2SkillTreeWebSocketClientPtr;
}