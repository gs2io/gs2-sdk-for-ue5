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

// Model
#include "Model/Namespace.h"
#include "Model/EventMaster.h"
#include "Model/Trigger.h"
#include "Model/Event.h"
#include "Model/RepeatSetting.h"
#include "Model/RepeatSchedule.h"
#include "Model/CurrentEventMaster.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/LogSetting.h"

// DescribeNamespaces
#include "Request/DescribeNamespacesRequest.h"
#include "Result/DescribeNamespacesResult.h"
#include "Task/Rest/DescribeNamespacesTask.h"
#include "Task/WebSocket/DescribeNamespacesTask.h"

// CreateNamespace
#include "Request/CreateNamespaceRequest.h"
#include "Result/CreateNamespaceResult.h"
#include "Task/Rest/CreateNamespaceTask.h"
#include "Task/WebSocket/CreateNamespaceTask.h"

// GetNamespaceStatus
#include "Request/GetNamespaceStatusRequest.h"
#include "Result/GetNamespaceStatusResult.h"
#include "Task/Rest/GetNamespaceStatusTask.h"
#include "Task/WebSocket/GetNamespaceStatusTask.h"

// GetNamespace
#include "Request/GetNamespaceRequest.h"
#include "Result/GetNamespaceResult.h"
#include "Task/Rest/GetNamespaceTask.h"
#include "Task/WebSocket/GetNamespaceTask.h"

// UpdateNamespace
#include "Request/UpdateNamespaceRequest.h"
#include "Result/UpdateNamespaceResult.h"
#include "Task/Rest/UpdateNamespaceTask.h"
#include "Task/WebSocket/UpdateNamespaceTask.h"

// DeleteNamespace
#include "Request/DeleteNamespaceRequest.h"
#include "Result/DeleteNamespaceResult.h"
#include "Task/Rest/DeleteNamespaceTask.h"
#include "Task/WebSocket/DeleteNamespaceTask.h"

// DumpUserDataByUserId
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Result/DumpUserDataByUserIdResult.h"
#include "Task/Rest/DumpUserDataByUserIdTask.h"
#include "Task/WebSocket/DumpUserDataByUserIdTask.h"

// CheckDumpUserDataByUserId
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Result/CheckDumpUserDataByUserIdResult.h"
#include "Task/Rest/CheckDumpUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckDumpUserDataByUserIdTask.h"

// CleanUserDataByUserId
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Result/CleanUserDataByUserIdResult.h"
#include "Task/Rest/CleanUserDataByUserIdTask.h"
#include "Task/WebSocket/CleanUserDataByUserIdTask.h"

// CheckCleanUserDataByUserId
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Result/CheckCleanUserDataByUserIdResult.h"
#include "Task/Rest/CheckCleanUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckCleanUserDataByUserIdTask.h"

// PrepareImportUserDataByUserId
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Result/PrepareImportUserDataByUserIdResult.h"
#include "Task/Rest/PrepareImportUserDataByUserIdTask.h"
#include "Task/WebSocket/PrepareImportUserDataByUserIdTask.h"

// ImportUserDataByUserId
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Result/ImportUserDataByUserIdResult.h"
#include "Task/Rest/ImportUserDataByUserIdTask.h"
#include "Task/WebSocket/ImportUserDataByUserIdTask.h"

// CheckImportUserDataByUserId
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Result/CheckImportUserDataByUserIdResult.h"
#include "Task/Rest/CheckImportUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckImportUserDataByUserIdTask.h"

// DescribeEventMasters
#include "Request/DescribeEventMastersRequest.h"
#include "Result/DescribeEventMastersResult.h"
#include "Task/Rest/DescribeEventMastersTask.h"
#include "Task/WebSocket/DescribeEventMastersTask.h"

// CreateEventMaster
#include "Request/CreateEventMasterRequest.h"
#include "Result/CreateEventMasterResult.h"
#include "Task/Rest/CreateEventMasterTask.h"
#include "Task/WebSocket/CreateEventMasterTask.h"

// GetEventMaster
#include "Request/GetEventMasterRequest.h"
#include "Result/GetEventMasterResult.h"
#include "Task/Rest/GetEventMasterTask.h"
#include "Task/WebSocket/GetEventMasterTask.h"

// UpdateEventMaster
#include "Request/UpdateEventMasterRequest.h"
#include "Result/UpdateEventMasterResult.h"
#include "Task/Rest/UpdateEventMasterTask.h"
#include "Task/WebSocket/UpdateEventMasterTask.h"

// DeleteEventMaster
#include "Request/DeleteEventMasterRequest.h"
#include "Result/DeleteEventMasterResult.h"
#include "Task/Rest/DeleteEventMasterTask.h"
#include "Task/WebSocket/DeleteEventMasterTask.h"

// DescribeTriggers
#include "Request/DescribeTriggersRequest.h"
#include "Result/DescribeTriggersResult.h"
#include "Task/Rest/DescribeTriggersTask.h"
#include "Task/WebSocket/DescribeTriggersTask.h"

// DescribeTriggersByUserId
#include "Request/DescribeTriggersByUserIdRequest.h"
#include "Result/DescribeTriggersByUserIdResult.h"
#include "Task/Rest/DescribeTriggersByUserIdTask.h"
#include "Task/WebSocket/DescribeTriggersByUserIdTask.h"

// GetTrigger
#include "Request/GetTriggerRequest.h"
#include "Result/GetTriggerResult.h"
#include "Task/Rest/GetTriggerTask.h"
#include "Task/WebSocket/GetTriggerTask.h"

// GetTriggerByUserId
#include "Request/GetTriggerByUserIdRequest.h"
#include "Result/GetTriggerByUserIdResult.h"
#include "Task/Rest/GetTriggerByUserIdTask.h"
#include "Task/WebSocket/GetTriggerByUserIdTask.h"

// TriggerByUserId
#include "Request/TriggerByUserIdRequest.h"
#include "Result/TriggerByUserIdResult.h"
#include "Task/Rest/TriggerByUserIdTask.h"
#include "Task/WebSocket/TriggerByUserIdTask.h"

// TriggerByStampSheet
#include "Request/TriggerByStampSheetRequest.h"
#include "Result/TriggerByStampSheetResult.h"
#include "Task/Rest/TriggerByStampSheetTask.h"
#include "Task/WebSocket/TriggerByStampSheetTask.h"

// DeleteTrigger
#include "Request/DeleteTriggerRequest.h"
#include "Result/DeleteTriggerResult.h"
#include "Task/Rest/DeleteTriggerTask.h"
#include "Task/WebSocket/DeleteTriggerTask.h"

// DeleteTriggerByUserId
#include "Request/DeleteTriggerByUserIdRequest.h"
#include "Result/DeleteTriggerByUserIdResult.h"
#include "Task/Rest/DeleteTriggerByUserIdTask.h"
#include "Task/WebSocket/DeleteTriggerByUserIdTask.h"

// DeleteTriggerByStampTask
#include "Request/DeleteTriggerByStampTaskRequest.h"
#include "Result/DeleteTriggerByStampTaskResult.h"
#include "Task/Rest/DeleteTriggerByStampTaskTask.h"
#include "Task/WebSocket/DeleteTriggerByStampTaskTask.h"

// DescribeEvents
#include "Request/DescribeEventsRequest.h"
#include "Result/DescribeEventsResult.h"
#include "Task/Rest/DescribeEventsTask.h"
#include "Task/WebSocket/DescribeEventsTask.h"

// DescribeEventsByUserId
#include "Request/DescribeEventsByUserIdRequest.h"
#include "Result/DescribeEventsByUserIdResult.h"
#include "Task/Rest/DescribeEventsByUserIdTask.h"
#include "Task/WebSocket/DescribeEventsByUserIdTask.h"

// DescribeRawEvents
#include "Request/DescribeRawEventsRequest.h"
#include "Result/DescribeRawEventsResult.h"
#include "Task/Rest/DescribeRawEventsTask.h"
#include "Task/WebSocket/DescribeRawEventsTask.h"

// GetEvent
#include "Request/GetEventRequest.h"
#include "Result/GetEventResult.h"
#include "Task/Rest/GetEventTask.h"
#include "Task/WebSocket/GetEventTask.h"

// GetEventByUserId
#include "Request/GetEventByUserIdRequest.h"
#include "Result/GetEventByUserIdResult.h"
#include "Task/Rest/GetEventByUserIdTask.h"
#include "Task/WebSocket/GetEventByUserIdTask.h"

// GetRawEvent
#include "Request/GetRawEventRequest.h"
#include "Result/GetRawEventResult.h"
#include "Task/Rest/GetRawEventTask.h"
#include "Task/WebSocket/GetRawEventTask.h"

// VerifyEvent
#include "Request/VerifyEventRequest.h"
#include "Result/VerifyEventResult.h"
#include "Task/Rest/VerifyEventTask.h"
#include "Task/WebSocket/VerifyEventTask.h"

// VerifyEventByUserId
#include "Request/VerifyEventByUserIdRequest.h"
#include "Result/VerifyEventByUserIdResult.h"
#include "Task/Rest/VerifyEventByUserIdTask.h"
#include "Task/WebSocket/VerifyEventByUserIdTask.h"

// VerifyEventByStampTask
#include "Request/VerifyEventByStampTaskRequest.h"
#include "Result/VerifyEventByStampTaskResult.h"
#include "Task/Rest/VerifyEventByStampTaskTask.h"
#include "Task/WebSocket/VerifyEventByStampTaskTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentEventMaster
#include "Request/GetCurrentEventMasterRequest.h"
#include "Result/GetCurrentEventMasterResult.h"
#include "Task/Rest/GetCurrentEventMasterTask.h"
#include "Task/WebSocket/GetCurrentEventMasterTask.h"

// UpdateCurrentEventMaster
#include "Request/UpdateCurrentEventMasterRequest.h"
#include "Result/UpdateCurrentEventMasterResult.h"
#include "Task/Rest/UpdateCurrentEventMasterTask.h"
#include "Task/WebSocket/UpdateCurrentEventMasterTask.h"

// UpdateCurrentEventMasterFromGitHub
#include "Request/UpdateCurrentEventMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentEventMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentEventMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentEventMasterFromGitHubTask.h"

// Client
#include "Gs2ScheduleRestClient.h"
#include "Gs2ScheduleWebSocketClient.h"