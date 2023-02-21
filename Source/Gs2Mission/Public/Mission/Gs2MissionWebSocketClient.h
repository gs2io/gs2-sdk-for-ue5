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
#include "Request/DescribeCompletesRequest.h"
#include "Task/WebSocket/DescribeCompletesTask.h"
#include "Request/DescribeCompletesByUserIdRequest.h"
#include "Task/WebSocket/DescribeCompletesByUserIdTask.h"
#include "Request/CompleteRequest.h"
#include "Task/WebSocket/CompleteTask.h"
#include "Request/CompleteByUserIdRequest.h"
#include "Task/WebSocket/CompleteByUserIdTask.h"
#include "Request/ReceiveByUserIdRequest.h"
#include "Task/WebSocket/ReceiveByUserIdTask.h"
#include "Request/GetCompleteRequest.h"
#include "Task/WebSocket/GetCompleteTask.h"
#include "Request/GetCompleteByUserIdRequest.h"
#include "Task/WebSocket/GetCompleteByUserIdTask.h"
#include "Request/DeleteCompleteByUserIdRequest.h"
#include "Task/WebSocket/DeleteCompleteByUserIdTask.h"
#include "Request/ReceiveByStampTaskRequest.h"
#include "Task/WebSocket/ReceiveByStampTaskTask.h"
#include "Request/DescribeCounterModelMastersRequest.h"
#include "Task/WebSocket/DescribeCounterModelMastersTask.h"
#include "Request/CreateCounterModelMasterRequest.h"
#include "Task/WebSocket/CreateCounterModelMasterTask.h"
#include "Request/GetCounterModelMasterRequest.h"
#include "Task/WebSocket/GetCounterModelMasterTask.h"
#include "Request/UpdateCounterModelMasterRequest.h"
#include "Task/WebSocket/UpdateCounterModelMasterTask.h"
#include "Request/DeleteCounterModelMasterRequest.h"
#include "Task/WebSocket/DeleteCounterModelMasterTask.h"
#include "Request/DescribeMissionGroupModelMastersRequest.h"
#include "Task/WebSocket/DescribeMissionGroupModelMastersTask.h"
#include "Request/CreateMissionGroupModelMasterRequest.h"
#include "Task/WebSocket/CreateMissionGroupModelMasterTask.h"
#include "Request/GetMissionGroupModelMasterRequest.h"
#include "Task/WebSocket/GetMissionGroupModelMasterTask.h"
#include "Request/UpdateMissionGroupModelMasterRequest.h"
#include "Task/WebSocket/UpdateMissionGroupModelMasterTask.h"
#include "Request/DeleteMissionGroupModelMasterRequest.h"
#include "Task/WebSocket/DeleteMissionGroupModelMasterTask.h"
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
#include "Request/DescribeCountersRequest.h"
#include "Task/WebSocket/DescribeCountersTask.h"
#include "Request/DescribeCountersByUserIdRequest.h"
#include "Task/WebSocket/DescribeCountersByUserIdTask.h"
#include "Request/IncreaseCounterByUserIdRequest.h"
#include "Task/WebSocket/IncreaseCounterByUserIdTask.h"
#include "Request/GetCounterRequest.h"
#include "Task/WebSocket/GetCounterTask.h"
#include "Request/GetCounterByUserIdRequest.h"
#include "Task/WebSocket/GetCounterByUserIdTask.h"
#include "Request/DeleteCounterByUserIdRequest.h"
#include "Task/WebSocket/DeleteCounterByUserIdTask.h"
#include "Request/IncreaseByStampSheetRequest.h"
#include "Task/WebSocket/IncreaseByStampSheetTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentMissionMasterRequest.h"
#include "Task/WebSocket/GetCurrentMissionMasterTask.h"
#include "Request/UpdateCurrentMissionMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentMissionMasterTask.h"
#include "Request/UpdateCurrentMissionMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentMissionMasterFromGitHubTask.h"
#include "Request/DescribeCounterModelsRequest.h"
#include "Task/WebSocket/DescribeCounterModelsTask.h"
#include "Request/GetCounterModelRequest.h"
#include "Task/WebSocket/GetCounterModelTask.h"
#include "Request/DescribeMissionGroupModelsRequest.h"
#include "Task/WebSocket/DescribeMissionGroupModelsTask.h"
#include "Request/GetMissionGroupModelRequest.h"
#include "Task/WebSocket/GetMissionGroupModelTask.h"
#include "Request/DescribeMissionTaskModelsRequest.h"
#include "Task/WebSocket/DescribeMissionTaskModelsTask.h"
#include "Request/GetMissionTaskModelRequest.h"
#include "Task/WebSocket/GetMissionTaskModelTask.h"
#include "Request/DescribeMissionTaskModelMastersRequest.h"
#include "Task/WebSocket/DescribeMissionTaskModelMastersTask.h"
#include "Request/CreateMissionTaskModelMasterRequest.h"
#include "Task/WebSocket/CreateMissionTaskModelMasterTask.h"
#include "Request/GetMissionTaskModelMasterRequest.h"
#include "Task/WebSocket/GetMissionTaskModelMasterTask.h"
#include "Request/UpdateMissionTaskModelMasterRequest.h"
#include "Task/WebSocket/UpdateMissionTaskModelMasterTask.h"
#include "Request/DeleteMissionTaskModelMasterRequest.h"
#include "Task/WebSocket/DeleteMissionTaskModelMasterTask.h"

namespace Gs2::Mission
{
    class GS2MISSION_API FGs2MissionWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2MissionWebSocketClient(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session
        ): FAbstractWebSocketGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCompletesTask>> DescribeCompletes(
            const Request::FDescribeCompletesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCompletesByUserIdTask>> DescribeCompletesByUserId(
            const Request::FDescribeCompletesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCompleteTask>> Complete(
            const Request::FCompleteRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCompleteByUserIdTask>> CompleteByUserId(
            const Request::FCompleteByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveByUserIdTask>> ReceiveByUserId(
            const Request::FReceiveByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCompleteTask>> GetComplete(
            const Request::FGetCompleteRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCompleteByUserIdTask>> GetCompleteByUserId(
            const Request::FGetCompleteByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteCompleteByUserIdTask>> DeleteCompleteByUserId(
            const Request::FDeleteCompleteByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveByStampTaskTask>> ReceiveByStampTask(
            const Request::FReceiveByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCounterModelMastersTask>> DescribeCounterModelMasters(
            const Request::FDescribeCounterModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateCounterModelMasterTask>> CreateCounterModelMaster(
            const Request::FCreateCounterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCounterModelMasterTask>> GetCounterModelMaster(
            const Request::FGetCounterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCounterModelMasterTask>> UpdateCounterModelMaster(
            const Request::FUpdateCounterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteCounterModelMasterTask>> DeleteCounterModelMaster(
            const Request::FDeleteCounterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMissionGroupModelMastersTask>> DescribeMissionGroupModelMasters(
            const Request::FDescribeMissionGroupModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateMissionGroupModelMasterTask>> CreateMissionGroupModelMaster(
            const Request::FCreateMissionGroupModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetMissionGroupModelMasterTask>> GetMissionGroupModelMaster(
            const Request::FGetMissionGroupModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateMissionGroupModelMasterTask>> UpdateMissionGroupModelMaster(
            const Request::FUpdateMissionGroupModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMissionGroupModelMasterTask>> DeleteMissionGroupModelMaster(
            const Request::FDeleteMissionGroupModelMasterRequestPtr Request
        ) const;

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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCountersTask>> DescribeCounters(
            const Request::FDescribeCountersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCountersByUserIdTask>> DescribeCountersByUserId(
            const Request::FDescribeCountersByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FIncreaseCounterByUserIdTask>> IncreaseCounterByUserId(
            const Request::FIncreaseCounterByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCounterTask>> GetCounter(
            const Request::FGetCounterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCounterByUserIdTask>> GetCounterByUserId(
            const Request::FGetCounterByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteCounterByUserIdTask>> DeleteCounterByUserId(
            const Request::FDeleteCounterByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FIncreaseByStampSheetTask>> IncreaseByStampSheet(
            const Request::FIncreaseByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentMissionMasterTask>> GetCurrentMissionMaster(
            const Request::FGetCurrentMissionMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentMissionMasterTask>> UpdateCurrentMissionMaster(
            const Request::FUpdateCurrentMissionMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentMissionMasterFromGitHubTask>> UpdateCurrentMissionMasterFromGitHub(
            const Request::FUpdateCurrentMissionMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCounterModelsTask>> DescribeCounterModels(
            const Request::FDescribeCounterModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCounterModelTask>> GetCounterModel(
            const Request::FGetCounterModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMissionGroupModelsTask>> DescribeMissionGroupModels(
            const Request::FDescribeMissionGroupModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetMissionGroupModelTask>> GetMissionGroupModel(
            const Request::FGetMissionGroupModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMissionTaskModelsTask>> DescribeMissionTaskModels(
            const Request::FDescribeMissionTaskModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetMissionTaskModelTask>> GetMissionTaskModel(
            const Request::FGetMissionTaskModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMissionTaskModelMastersTask>> DescribeMissionTaskModelMasters(
            const Request::FDescribeMissionTaskModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateMissionTaskModelMasterTask>> CreateMissionTaskModelMaster(
            const Request::FCreateMissionTaskModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetMissionTaskModelMasterTask>> GetMissionTaskModelMaster(
            const Request::FGetMissionTaskModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateMissionTaskModelMasterTask>> UpdateMissionTaskModelMaster(
            const Request::FUpdateMissionTaskModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMissionTaskModelMasterTask>> DeleteMissionTaskModelMaster(
            const Request::FDeleteMissionTaskModelMasterRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2MissionWebSocketClient, ESPMode::ThreadSafe> FGs2MissionWebSocketClientPtr;
}