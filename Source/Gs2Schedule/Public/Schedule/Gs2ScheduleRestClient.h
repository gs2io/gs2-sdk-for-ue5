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
#include "Request/DescribeEventMastersRequest.h"
#include "Task/Rest/DescribeEventMastersTask.h"
#include "Request/CreateEventMasterRequest.h"
#include "Task/Rest/CreateEventMasterTask.h"
#include "Request/GetEventMasterRequest.h"
#include "Task/Rest/GetEventMasterTask.h"
#include "Request/UpdateEventMasterRequest.h"
#include "Task/Rest/UpdateEventMasterTask.h"
#include "Request/DeleteEventMasterRequest.h"
#include "Task/Rest/DeleteEventMasterTask.h"
#include "Request/DescribeTriggersRequest.h"
#include "Task/Rest/DescribeTriggersTask.h"
#include "Request/DescribeTriggersByUserIdRequest.h"
#include "Task/Rest/DescribeTriggersByUserIdTask.h"
#include "Request/GetTriggerRequest.h"
#include "Task/Rest/GetTriggerTask.h"
#include "Request/GetTriggerByUserIdRequest.h"
#include "Task/Rest/GetTriggerByUserIdTask.h"
#include "Request/TriggerByUserIdRequest.h"
#include "Task/Rest/TriggerByUserIdTask.h"
#include "Request/TriggerByStampSheetRequest.h"
#include "Task/Rest/TriggerByStampSheetTask.h"
#include "Request/DeleteTriggerRequest.h"
#include "Task/Rest/DeleteTriggerTask.h"
#include "Request/DeleteTriggerByUserIdRequest.h"
#include "Task/Rest/DeleteTriggerByUserIdTask.h"
#include "Request/DeleteTriggerByStampTaskRequest.h"
#include "Task/Rest/DeleteTriggerByStampTaskTask.h"
#include "Request/DescribeEventsRequest.h"
#include "Task/Rest/DescribeEventsTask.h"
#include "Request/DescribeEventsByUserIdRequest.h"
#include "Task/Rest/DescribeEventsByUserIdTask.h"
#include "Request/DescribeRawEventsRequest.h"
#include "Task/Rest/DescribeRawEventsTask.h"
#include "Request/GetEventRequest.h"
#include "Task/Rest/GetEventTask.h"
#include "Request/GetEventByUserIdRequest.h"
#include "Task/Rest/GetEventByUserIdTask.h"
#include "Request/GetRawEventRequest.h"
#include "Task/Rest/GetRawEventTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentEventMasterRequest.h"
#include "Task/Rest/GetCurrentEventMasterTask.h"
#include "Request/UpdateCurrentEventMasterRequest.h"
#include "Task/Rest/UpdateCurrentEventMasterTask.h"
#include "Request/UpdateCurrentEventMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentEventMasterFromGitHubTask.h"

namespace Gs2::Schedule
{
    class GS2SCHEDULE_API FGs2ScheduleRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2ScheduleRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeEventMastersTask>> DescribeEventMasters(
            const Request::FDescribeEventMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateEventMasterTask>> CreateEventMaster(
            const Request::FCreateEventMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetEventMasterTask>> GetEventMaster(
            const Request::FGetEventMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateEventMasterTask>> UpdateEventMaster(
            const Request::FUpdateEventMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteEventMasterTask>> DeleteEventMaster(
            const Request::FDeleteEventMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeTriggersTask>> DescribeTriggers(
            const Request::FDescribeTriggersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeTriggersByUserIdTask>> DescribeTriggersByUserId(
            const Request::FDescribeTriggersByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetTriggerTask>> GetTrigger(
            const Request::FGetTriggerRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetTriggerByUserIdTask>> GetTriggerByUserId(
            const Request::FGetTriggerByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FTriggerByUserIdTask>> TriggerByUserId(
            const Request::FTriggerByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FTriggerByStampSheetTask>> TriggerByStampSheet(
            const Request::FTriggerByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteTriggerTask>> DeleteTrigger(
            const Request::FDeleteTriggerRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteTriggerByUserIdTask>> DeleteTriggerByUserId(
            const Request::FDeleteTriggerByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteTriggerByStampTaskTask>> DeleteTriggerByStampTask(
            const Request::FDeleteTriggerByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeEventsTask>> DescribeEvents(
            const Request::FDescribeEventsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeEventsByUserIdTask>> DescribeEventsByUserId(
            const Request::FDescribeEventsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRawEventsTask>> DescribeRawEvents(
            const Request::FDescribeRawEventsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetEventTask>> GetEvent(
            const Request::FGetEventRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetEventByUserIdTask>> GetEventByUserId(
            const Request::FGetEventByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRawEventTask>> GetRawEvent(
            const Request::FGetRawEventRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentEventMasterTask>> GetCurrentEventMaster(
            const Request::FGetCurrentEventMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentEventMasterTask>> UpdateCurrentEventMaster(
            const Request::FUpdateCurrentEventMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentEventMasterFromGitHubTask>> UpdateCurrentEventMasterFromGitHub(
            const Request::FUpdateCurrentEventMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2ScheduleRestClient, ESPMode::ThreadSafe> FGs2ScheduleRestClientPtr;
}