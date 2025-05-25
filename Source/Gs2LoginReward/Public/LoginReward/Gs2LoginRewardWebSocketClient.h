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
#include "Request/DescribeBonusModelMastersRequest.h"
#include "Task/WebSocket/DescribeBonusModelMastersTask.h"
#include "Request/CreateBonusModelMasterRequest.h"
#include "Task/WebSocket/CreateBonusModelMasterTask.h"
#include "Request/GetBonusModelMasterRequest.h"
#include "Task/WebSocket/GetBonusModelMasterTask.h"
#include "Request/UpdateBonusModelMasterRequest.h"
#include "Task/WebSocket/UpdateBonusModelMasterTask.h"
#include "Request/DeleteBonusModelMasterRequest.h"
#include "Task/WebSocket/DeleteBonusModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentBonusMasterRequest.h"
#include "Task/WebSocket/GetCurrentBonusMasterTask.h"
#include "Request/PreUpdateCurrentBonusMasterRequest.h"
#include "Task/WebSocket/PreUpdateCurrentBonusMasterTask.h"
#include "Request/UpdateCurrentBonusMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentBonusMasterTask.h"
#include "Request/UpdateCurrentBonusMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentBonusMasterFromGitHubTask.h"
#include "Request/DescribeBonusModelsRequest.h"
#include "Task/WebSocket/DescribeBonusModelsTask.h"
#include "Request/GetBonusModelRequest.h"
#include "Task/WebSocket/GetBonusModelTask.h"
#include "Request/ReceiveRequest.h"
#include "Task/WebSocket/ReceiveTask.h"
#include "Request/ReceiveByUserIdRequest.h"
#include "Task/WebSocket/ReceiveByUserIdTask.h"
#include "Request/MissedReceiveRequest.h"
#include "Task/WebSocket/MissedReceiveTask.h"
#include "Request/MissedReceiveByUserIdRequest.h"
#include "Task/WebSocket/MissedReceiveByUserIdTask.h"
#include "Request/DescribeReceiveStatusesRequest.h"
#include "Task/WebSocket/DescribeReceiveStatusesTask.h"
#include "Request/DescribeReceiveStatusesByUserIdRequest.h"
#include "Task/WebSocket/DescribeReceiveStatusesByUserIdTask.h"
#include "Request/GetReceiveStatusRequest.h"
#include "Task/WebSocket/GetReceiveStatusTask.h"
#include "Request/GetReceiveStatusByUserIdRequest.h"
#include "Task/WebSocket/GetReceiveStatusByUserIdTask.h"
#include "Request/DeleteReceiveStatusByUserIdRequest.h"
#include "Task/WebSocket/DeleteReceiveStatusByUserIdTask.h"
#include "Request/DeleteReceiveStatusByStampSheetRequest.h"
#include "Task/WebSocket/DeleteReceiveStatusByStampSheetTask.h"
#include "Request/MarkReceivedRequest.h"
#include "Task/WebSocket/MarkReceivedTask.h"
#include "Request/MarkReceivedByUserIdRequest.h"
#include "Task/WebSocket/MarkReceivedByUserIdTask.h"
#include "Request/UnmarkReceivedByUserIdRequest.h"
#include "Task/WebSocket/UnmarkReceivedByUserIdTask.h"
#include "Request/MarkReceivedByStampTaskRequest.h"
#include "Task/WebSocket/MarkReceivedByStampTaskTask.h"
#include "Request/UnmarkReceivedByStampSheetRequest.h"
#include "Task/WebSocket/UnmarkReceivedByStampSheetTask.h"

namespace Gs2::LoginReward
{
    class GS2LOGINREWARD_API FGs2LoginRewardWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2LoginRewardWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBonusModelMastersTask>> DescribeBonusModelMasters(
            const Request::FDescribeBonusModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateBonusModelMasterTask>> CreateBonusModelMaster(
            const Request::FCreateBonusModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBonusModelMasterTask>> GetBonusModelMaster(
            const Request::FGetBonusModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateBonusModelMasterTask>> UpdateBonusModelMaster(
            const Request::FUpdateBonusModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteBonusModelMasterTask>> DeleteBonusModelMaster(
            const Request::FDeleteBonusModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentBonusMasterTask>> GetCurrentBonusMaster(
            const Request::FGetCurrentBonusMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPreUpdateCurrentBonusMasterTask>> PreUpdateCurrentBonusMaster(
            const Request::FPreUpdateCurrentBonusMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentBonusMasterTask>> UpdateCurrentBonusMaster(
            const Request::FUpdateCurrentBonusMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentBonusMasterFromGitHubTask>> UpdateCurrentBonusMasterFromGitHub(
            const Request::FUpdateCurrentBonusMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBonusModelsTask>> DescribeBonusModels(
            const Request::FDescribeBonusModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBonusModelTask>> GetBonusModel(
            const Request::FGetBonusModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveTask>> Receive(
            const Request::FReceiveRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveByUserIdTask>> ReceiveByUserId(
            const Request::FReceiveByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FMissedReceiveTask>> MissedReceive(
            const Request::FMissedReceiveRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FMissedReceiveByUserIdTask>> MissedReceiveByUserId(
            const Request::FMissedReceiveByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeReceiveStatusesTask>> DescribeReceiveStatuses(
            const Request::FDescribeReceiveStatusesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeReceiveStatusesByUserIdTask>> DescribeReceiveStatusesByUserId(
            const Request::FDescribeReceiveStatusesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetReceiveStatusTask>> GetReceiveStatus(
            const Request::FGetReceiveStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetReceiveStatusByUserIdTask>> GetReceiveStatusByUserId(
            const Request::FGetReceiveStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteReceiveStatusByUserIdTask>> DeleteReceiveStatusByUserId(
            const Request::FDeleteReceiveStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteReceiveStatusByStampSheetTask>> DeleteReceiveStatusByStampSheet(
            const Request::FDeleteReceiveStatusByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FMarkReceivedTask>> MarkReceived(
            const Request::FMarkReceivedRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FMarkReceivedByUserIdTask>> MarkReceivedByUserId(
            const Request::FMarkReceivedByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUnmarkReceivedByUserIdTask>> UnmarkReceivedByUserId(
            const Request::FUnmarkReceivedByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FMarkReceivedByStampTaskTask>> MarkReceivedByStampTask(
            const Request::FMarkReceivedByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUnmarkReceivedByStampSheetTask>> UnmarkReceivedByStampSheet(
            const Request::FUnmarkReceivedByStampSheetRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2LoginRewardWebSocketClient, ESPMode::ThreadSafe> FGs2LoginRewardWebSocketClientPtr;
}