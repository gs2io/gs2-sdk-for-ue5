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
#include "Request/DescribeEventMastersRequest.h"
#include "Task/WebSocket/DescribeEventMastersTask.h"
#include "Request/CreateEventMasterRequest.h"
#include "Task/WebSocket/CreateEventMasterTask.h"
#include "Request/GetEventMasterRequest.h"
#include "Task/WebSocket/GetEventMasterTask.h"
#include "Request/UpdateEventMasterRequest.h"
#include "Task/WebSocket/UpdateEventMasterTask.h"
#include "Request/DeleteEventMasterRequest.h"
#include "Task/WebSocket/DeleteEventMasterTask.h"
#include "Request/DescribeTriggersRequest.h"
#include "Task/WebSocket/DescribeTriggersTask.h"
#include "Request/DescribeTriggersByUserIdRequest.h"
#include "Task/WebSocket/DescribeTriggersByUserIdTask.h"
#include "Request/GetTriggerRequest.h"
#include "Task/WebSocket/GetTriggerTask.h"
#include "Request/GetTriggerByUserIdRequest.h"
#include "Task/WebSocket/GetTriggerByUserIdTask.h"
#include "Request/TriggerByUserIdRequest.h"
#include "Task/WebSocket/TriggerByUserIdTask.h"
#include "Request/TriggerByStampSheetRequest.h"
#include "Task/WebSocket/TriggerByStampSheetTask.h"
#include "Request/DeleteTriggerRequest.h"
#include "Task/WebSocket/DeleteTriggerTask.h"
#include "Request/DeleteTriggerByUserIdRequest.h"
#include "Task/WebSocket/DeleteTriggerByUserIdTask.h"
#include "Request/DeleteTriggerByStampTaskRequest.h"
#include "Task/WebSocket/DeleteTriggerByStampTaskTask.h"
#include "Request/DescribeEventsRequest.h"
#include "Task/WebSocket/DescribeEventsTask.h"
#include "Request/DescribeEventsByUserIdRequest.h"
#include "Task/WebSocket/DescribeEventsByUserIdTask.h"
#include "Request/DescribeRawEventsRequest.h"
#include "Task/WebSocket/DescribeRawEventsTask.h"
#include "Request/GetEventRequest.h"
#include "Task/WebSocket/GetEventTask.h"
#include "Request/GetEventByUserIdRequest.h"
#include "Task/WebSocket/GetEventByUserIdTask.h"
#include "Request/GetRawEventRequest.h"
#include "Task/WebSocket/GetRawEventTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentEventMasterRequest.h"
#include "Task/WebSocket/GetCurrentEventMasterTask.h"
#include "Request/UpdateCurrentEventMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentEventMasterTask.h"
#include "Request/UpdateCurrentEventMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentEventMasterFromGitHubTask.h"

namespace Gs2::Schedule
{
    class GS2SCHEDULE_API FGs2ScheduleWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2ScheduleWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeEventMastersTask>> DescribeEventMasters(
            const Request::FDescribeEventMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateEventMasterTask>> CreateEventMaster(
            const Request::FCreateEventMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetEventMasterTask>> GetEventMaster(
            const Request::FGetEventMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateEventMasterTask>> UpdateEventMaster(
            const Request::FUpdateEventMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteEventMasterTask>> DeleteEventMaster(
            const Request::FDeleteEventMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeTriggersTask>> DescribeTriggers(
            const Request::FDescribeTriggersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeTriggersByUserIdTask>> DescribeTriggersByUserId(
            const Request::FDescribeTriggersByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetTriggerTask>> GetTrigger(
            const Request::FGetTriggerRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetTriggerByUserIdTask>> GetTriggerByUserId(
            const Request::FGetTriggerByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FTriggerByUserIdTask>> TriggerByUserId(
            const Request::FTriggerByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FTriggerByStampSheetTask>> TriggerByStampSheet(
            const Request::FTriggerByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteTriggerTask>> DeleteTrigger(
            const Request::FDeleteTriggerRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteTriggerByUserIdTask>> DeleteTriggerByUserId(
            const Request::FDeleteTriggerByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteTriggerByStampTaskTask>> DeleteTriggerByStampTask(
            const Request::FDeleteTriggerByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeEventsTask>> DescribeEvents(
            const Request::FDescribeEventsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeEventsByUserIdTask>> DescribeEventsByUserId(
            const Request::FDescribeEventsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRawEventsTask>> DescribeRawEvents(
            const Request::FDescribeRawEventsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetEventTask>> GetEvent(
            const Request::FGetEventRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetEventByUserIdTask>> GetEventByUserId(
            const Request::FGetEventByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRawEventTask>> GetRawEvent(
            const Request::FGetRawEventRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentEventMasterTask>> GetCurrentEventMaster(
            const Request::FGetCurrentEventMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentEventMasterTask>> UpdateCurrentEventMaster(
            const Request::FUpdateCurrentEventMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentEventMasterFromGitHubTask>> UpdateCurrentEventMasterFromGitHub(
            const Request::FUpdateCurrentEventMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2ScheduleWebSocketClient, ESPMode::ThreadSafe> FGs2ScheduleWebSocketClientPtr;
}