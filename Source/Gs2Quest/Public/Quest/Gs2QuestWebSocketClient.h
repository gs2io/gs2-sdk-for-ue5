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
#include "Request/DescribeQuestGroupModelMastersRequest.h"
#include "Task/WebSocket/DescribeQuestGroupModelMastersTask.h"
#include "Request/CreateQuestGroupModelMasterRequest.h"
#include "Task/WebSocket/CreateQuestGroupModelMasterTask.h"
#include "Request/GetQuestGroupModelMasterRequest.h"
#include "Task/WebSocket/GetQuestGroupModelMasterTask.h"
#include "Request/UpdateQuestGroupModelMasterRequest.h"
#include "Task/WebSocket/UpdateQuestGroupModelMasterTask.h"
#include "Request/DeleteQuestGroupModelMasterRequest.h"
#include "Task/WebSocket/DeleteQuestGroupModelMasterTask.h"
#include "Request/DescribeQuestModelMastersRequest.h"
#include "Task/WebSocket/DescribeQuestModelMastersTask.h"
#include "Request/CreateQuestModelMasterRequest.h"
#include "Task/WebSocket/CreateQuestModelMasterTask.h"
#include "Request/GetQuestModelMasterRequest.h"
#include "Task/WebSocket/GetQuestModelMasterTask.h"
#include "Request/UpdateQuestModelMasterRequest.h"
#include "Task/WebSocket/UpdateQuestModelMasterTask.h"
#include "Request/DeleteQuestModelMasterRequest.h"
#include "Task/WebSocket/DeleteQuestModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentQuestMasterRequest.h"
#include "Task/WebSocket/GetCurrentQuestMasterTask.h"
#include "Request/UpdateCurrentQuestMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentQuestMasterTask.h"
#include "Request/UpdateCurrentQuestMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentQuestMasterFromGitHubTask.h"
#include "Request/DescribeProgressesByUserIdRequest.h"
#include "Task/WebSocket/DescribeProgressesByUserIdTask.h"
#include "Request/CreateProgressByUserIdRequest.h"
#include "Task/WebSocket/CreateProgressByUserIdTask.h"
#include "Request/GetProgressRequest.h"
#include "Task/WebSocket/GetProgressTask.h"
#include "Request/GetProgressByUserIdRequest.h"
#include "Task/WebSocket/GetProgressByUserIdTask.h"
#include "Request/StartRequest.h"
#include "Task/WebSocket/StartTask.h"
#include "Request/StartByUserIdRequest.h"
#include "Task/WebSocket/StartByUserIdTask.h"
#include "Request/EndRequest.h"
#include "Task/WebSocket/EndTask.h"
#include "Request/EndByUserIdRequest.h"
#include "Task/WebSocket/EndByUserIdTask.h"
#include "Request/DeleteProgressRequest.h"
#include "Task/WebSocket/DeleteProgressTask.h"
#include "Request/DeleteProgressByUserIdRequest.h"
#include "Task/WebSocket/DeleteProgressByUserIdTask.h"
#include "Request/CreateProgressByStampSheetRequest.h"
#include "Task/WebSocket/CreateProgressByStampSheetTask.h"
#include "Request/DeleteProgressByStampTaskRequest.h"
#include "Task/WebSocket/DeleteProgressByStampTaskTask.h"
#include "Request/DescribeCompletedQuestListsRequest.h"
#include "Task/WebSocket/DescribeCompletedQuestListsTask.h"
#include "Request/DescribeCompletedQuestListsByUserIdRequest.h"
#include "Task/WebSocket/DescribeCompletedQuestListsByUserIdTask.h"
#include "Request/GetCompletedQuestListRequest.h"
#include "Task/WebSocket/GetCompletedQuestListTask.h"
#include "Request/GetCompletedQuestListByUserIdRequest.h"
#include "Task/WebSocket/GetCompletedQuestListByUserIdTask.h"
#include "Request/DeleteCompletedQuestListByUserIdRequest.h"
#include "Task/WebSocket/DeleteCompletedQuestListByUserIdTask.h"
#include "Request/DescribeQuestGroupModelsRequest.h"
#include "Task/WebSocket/DescribeQuestGroupModelsTask.h"
#include "Request/GetQuestGroupModelRequest.h"
#include "Task/WebSocket/GetQuestGroupModelTask.h"
#include "Request/DescribeQuestModelsRequest.h"
#include "Task/WebSocket/DescribeQuestModelsTask.h"
#include "Request/GetQuestModelRequest.h"
#include "Task/WebSocket/GetQuestModelTask.h"

namespace Gs2::Quest
{
    class GS2QUEST_API FGs2QuestWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2QuestWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeQuestGroupModelMastersTask>> DescribeQuestGroupModelMasters(
            const Request::FDescribeQuestGroupModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateQuestGroupModelMasterTask>> CreateQuestGroupModelMaster(
            const Request::FCreateQuestGroupModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetQuestGroupModelMasterTask>> GetQuestGroupModelMaster(
            const Request::FGetQuestGroupModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateQuestGroupModelMasterTask>> UpdateQuestGroupModelMaster(
            const Request::FUpdateQuestGroupModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteQuestGroupModelMasterTask>> DeleteQuestGroupModelMaster(
            const Request::FDeleteQuestGroupModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeQuestModelMastersTask>> DescribeQuestModelMasters(
            const Request::FDescribeQuestModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateQuestModelMasterTask>> CreateQuestModelMaster(
            const Request::FCreateQuestModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetQuestModelMasterTask>> GetQuestModelMaster(
            const Request::FGetQuestModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateQuestModelMasterTask>> UpdateQuestModelMaster(
            const Request::FUpdateQuestModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteQuestModelMasterTask>> DeleteQuestModelMaster(
            const Request::FDeleteQuestModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentQuestMasterTask>> GetCurrentQuestMaster(
            const Request::FGetCurrentQuestMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentQuestMasterTask>> UpdateCurrentQuestMaster(
            const Request::FUpdateCurrentQuestMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentQuestMasterFromGitHubTask>> UpdateCurrentQuestMasterFromGitHub(
            const Request::FUpdateCurrentQuestMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeProgressesByUserIdTask>> DescribeProgressesByUserId(
            const Request::FDescribeProgressesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateProgressByUserIdTask>> CreateProgressByUserId(
            const Request::FCreateProgressByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetProgressTask>> GetProgress(
            const Request::FGetProgressRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetProgressByUserIdTask>> GetProgressByUserId(
            const Request::FGetProgressByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FStartTask>> Start(
            const Request::FStartRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FStartByUserIdTask>> StartByUserId(
            const Request::FStartByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FEndTask>> End(
            const Request::FEndRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FEndByUserIdTask>> EndByUserId(
            const Request::FEndByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteProgressTask>> DeleteProgress(
            const Request::FDeleteProgressRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteProgressByUserIdTask>> DeleteProgressByUserId(
            const Request::FDeleteProgressByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateProgressByStampSheetTask>> CreateProgressByStampSheet(
            const Request::FCreateProgressByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteProgressByStampTaskTask>> DeleteProgressByStampTask(
            const Request::FDeleteProgressByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCompletedQuestListsTask>> DescribeCompletedQuestLists(
            const Request::FDescribeCompletedQuestListsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCompletedQuestListsByUserIdTask>> DescribeCompletedQuestListsByUserId(
            const Request::FDescribeCompletedQuestListsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCompletedQuestListTask>> GetCompletedQuestList(
            const Request::FGetCompletedQuestListRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCompletedQuestListByUserIdTask>> GetCompletedQuestListByUserId(
            const Request::FGetCompletedQuestListByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteCompletedQuestListByUserIdTask>> DeleteCompletedQuestListByUserId(
            const Request::FDeleteCompletedQuestListByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeQuestGroupModelsTask>> DescribeQuestGroupModels(
            const Request::FDescribeQuestGroupModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetQuestGroupModelTask>> GetQuestGroupModel(
            const Request::FGetQuestGroupModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeQuestModelsTask>> DescribeQuestModels(
            const Request::FDescribeQuestModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetQuestModelTask>> GetQuestModel(
            const Request::FGetQuestModelRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2QuestWebSocketClient, ESPMode::ThreadSafe> FGs2QuestWebSocketClientPtr;
}